/******************************************* 
 * Copyright (c) 2012，德赛西威汽车电子有限公司
 * All rights reserved
 * 文件名: SVPVolumeShowCtrl.cpp
 * 编写者: Yao Fen
 * 编写日期: Mar 11, 2013
 * 简要描述:
 * 修改记录:
 *******************************************/

#include "SVPVolumeShowCtrl.h"

#ifndef SVP_LINUX_ARM
#include "SVPSource.h"
#endif

#include "SVPLog.h"

#ifdef SVP_LOG_TAG
	#undef SVP_LOG_TAG
#endif
#define SVP_LOG_TAG		"statusbar|libvolumeshow"

SVPVolumeShowCtrl::SVPVolumeShowCtrl(SVPInt32 iIndex, const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl* pParent)
:SVPStatusbarPluginBase (iIndex, strPkgName, strPluginName, "notify", 1)
,m_bSingleShow(SVP_FALSE)
{
	SVP_INFO("SVPVolumeShowCtrl()::SVPVolumeShowCtrl start .");
	SVPString szResourcePath = GetAppResourcePath();
	szResourcePath = szResourcePath + "/" + "SVPVolumeShowBR.dat";
	m_pResMgr = new SVPBitmapResMgr(szResourcePath.data());
	m_pResMgr->CreateGroup(1, true);

	m_volBk.CreateInstance(0, pParent, SVPRect(0, 0, 0, 0), SVP_NULL);

	m_pVolumeSignalCtrl.CreateInstance(0, m_volBk.GetInterface(),SVPPoint(17,2),m_pResMgr->PrepBmp(SVPBR_VOL_ICON),SVP_NULL);

	m_provolume.CreateInstance(0, m_volBk.GetInterface(), SVPRect(93, 18, 396, 32), SVP_NULL);
	m_provolume->SetProgressBarPixmap(m_pResMgr->PrepBmp(SVPBR_VOL_PROGRESS), SVPPoint(0, 0));
	m_provolume->SetBkgndAlignment(SVPAlignLeft | SVPAlignVCenter);
	m_provolume->SetOrientation(SVPOrientHorizontal);
	m_provolume->SetRange(0, 30);
	m_provolume->SetProgressPos(15);
	m_provolume->ShowProgressPosTextPositiveSign(false);
	m_provolume->SetMinUnit(1);
	m_provolume->SetEnable(false);

	m_volInfo.CreateInstance(0, m_volBk.GetInterface(), SVPRect(510,10,50,32), NULL);
	m_volInfo->SetAlign(Qt::AlignLeft);
	m_volInfo->SetTextColor(0x383838);

	m_timerSetSize.setSingleShot(true);
	m_timerShow.setSingleShot(true);
	connect(this,SIGNAL(SignalIconChange(int)),this,SLOT(SlotNewIcon(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalIconMuteState(int)),this,SLOT(SlotMuteState(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalTelVolUpdate(int, int)),this,SLOT(SlotTelVolUpdate(int, int)),Qt::QueuedConnection);
	connect(&m_timerSetSize, SIGNAL(timeout()), this, SLOT(SlotSizeUpdate()));
	connect(&m_timerShow, SIGNAL(timeout()), this, SLOT(SlotShowUpdate()));

	InitDlg();
}

void SVPVolumeShowCtrl::InitDlg()
{
	SVP_INFO("InitDlg start .");
	m_size.w = m_size.h = 0;
	const SVPBitmap *pBitmap1 = m_pResMgr->PrepBmp(SVPBR_VOL_BG);
	m_volBk->SetBkgndBitmap(pBitmap1);
	m_size.w = pBitmap1->GetWidth();
	m_size.h = pBitmap1->GetHeight();
	m_volBk->SetRect(6, 5, m_size.w, m_size.h);

	char cTxt[256] = {"0"};
	#ifndef SVP_LINUX_ARM
	SVP_GetAudioService()->AddListener(this);
	SVP_GetAudioService()->StartService();
	int m_firstvol = SVP_GetAudioService()->GetVolume();
	sprintf(cTxt,"%d",m_firstvol);
	#endif
	m_volInfo->SetText(cTxt);

	m_volBk->Show(false);

	m_timerSetSize.start(20);
	SVP_INFO("InitDlg end .");
}

SVPVoid SVPVolumeShowCtrl::SlotSizeUpdate()
{
	SetSize(m_size);
	m_bSingleShow = SVP_TRUE;
}

SVPVolumeShowCtrl::~SVPVolumeShowCtrl()
{
	 m_pResMgr->DestoyGroup(1);
	 delete m_pResMgr;
#ifndef SVP_LINUX_ARM
	 SVP_GetAudioService()->StopService();
	 SVP_GetAudioService()->RemoveListener(this);
	 SVP_ReleaseAudioService();
#else
#endif
}

SVPBool SVPVolumeShowCtrl::SetPos(SVPInt32 x,SVPInt32 y)
{
	m_volBk->SetPos(x, y);
	return SVP_TRUE;
}

SVPBool SVPVolumeShowCtrl::SetVisible(SVPBool bVisible)
{
	SVP_INFO("SetVisible start, bVisible = %d .",bVisible);
	if(bVisible && m_bSingleShow)
	{
		m_volBk->Show(true);
	}
	else
	{
		m_volBk->Show(false);
	}
}

SVPVoid SVPVolumeShowCtrl::OnAudioVolumeChanged(SVPUint8 vol_step)
{
	SVP_INFO("OnAudioVolumeChanged start .");
	ActiveNotifyMode();
	SetSize(m_size);
	m_bSingleShow = SVP_TRUE;
	emit SignalIconChange((int)vol_step);
	SVP_INFO("OnAudioVolumeChanged end .");
}

SVPVoid SVPVolumeShowCtrl::OnAudioMuteStateChanged(SVPAudio::MuteState state, SVPAudio::MuteType type)
{
	ActiveNotifyMode();
	SetSize(m_size);
	m_bSingleShow = SVP_TRUE;
	emit SignalIconMuteState(state);
}

SVPVoid SVPVolumeShowCtrl::OnAudioParamsUpdated(SVPAudio::AudioParamType param_type, SVPAudio::AudioParams params)
{
	if(param_type == SVPAudio::APT_VOL)
	{
		ActiveNotifyMode();
		SetSize(m_size);
		m_bSingleShow = SVP_TRUE;
		emit SignalTelVolUpdate(SVPAudio::APT_VOL, params.Volume_Params.tel_volume);
	}
}

void SVPVolumeShowCtrl::SlotTelVolUpdate(int type,int value)
{
#ifndef SVP_LINUX_ARM
	SVP_INFO("SlotTelVolUpdate start .");
	 if(SVPSource::IsValid(SVPSource::SID_PHONE))
	 {
		 const SVPBitmap *pBitmap1 = m_pResMgr->PrepBmp(SVPBR_PHONEVOL_ICON);
		m_pVolumeSignalCtrl->SetBkgndBitmap(pBitmap1);

		m_provolume->SetRange(0, 10);
		if (value <= 0)
			value = 0;

		if(value > 10)
			value = 10;
		m_provolume->SetProgressPos(value);

		char cTxt[256] = {0};
		sprintf(cTxt,"%d",value);
		m_volInfo->SetText(cTxt);
	 }
	 m_timerShow.stop();
	 m_timerShow.start(3000);
#endif
}

void SVPVolumeShowCtrl::SlotMuteState(int m_state)
{
#ifndef SVP_LINUX_ARM
	SVP_INFO("SlotMuteState start .");
	if (m_state == 0)
	{
		const SVPBitmap *pBitmap1 = m_pResMgr->PrepBmp(SVPBR_VOL_ICON);
		m_pVolumeSignalCtrl->SetBkgndBitmap(pBitmap1);
	}
	else if (m_state == 1)
	{
		const SVPBitmap *pBitmap1 = m_pResMgr->PrepBmp(SVPBR_MUTE_ICON);
		m_pVolumeSignalCtrl->SetBkgndBitmap(pBitmap1);
	}
	m_timerShow.stop();
	m_timerShow.start(3000);
#endif
}

void SVPVolumeShowCtrl::SlotNewIcon(int m_vol)
{
#ifndef SVP_LINUX_ARM
	SVP_INFO("SlotNewIcon start .");
	const SVPBitmap *pBitmap1 = m_pResMgr->PrepBmp(SVPBR_VOL_ICON);
	m_pVolumeSignalCtrl->SetBkgndBitmap(pBitmap1);
	m_provolume->SetRange(0, 30);
	if (m_vol < 0)
		m_vol = 0;
	if(m_vol > 30)
		m_vol = 30;
	m_provolume->SetProgressPos(m_vol);
	char cTxt[256] = {0};
	sprintf(cTxt,"%d",m_vol);
	m_volInfo->SetText(cTxt);
	m_timerShow.stop();
	m_timerShow.start(3000);
#endif
}


void SVPVolumeShowCtrl::SlotShowUpdate()
{
	SVP_INFO("SlotShowUpdate start .");
	SetSize(SVPPluginSize());
	m_bSingleShow = SVP_FALSE;
	ResumeNormalMode();
}

SVPVolumeShowCtrl *g_pVolumeSignalPlugin = SVP_NULL;

SVPPluginType SVP_GetPluginType()
{
	return PT_STATUSBAR;
}
ISVPPluginBase* SVP_CreatePlugin(SVPInt32 iPluginIndex,const SVPChar* strPkgName,const SVPChar* strPluginName,SVPVoid* pParent)
{
	SVP_INFO("start to Create volumePlugin start .");
	if (g_pVolumeSignalPlugin == SVP_NULL)
	{
		g_pVolumeSignalPlugin = new SVPVolumeShowCtrl(iPluginIndex, strPkgName, strPluginName, (ISVPBaseCtrl*)pParent);
	}
	return g_pVolumeSignalPlugin;
}
SVPVoid SVP_DestroyPlugin()
{
	SVP_INFO("start to Destroy volumePlugin start .");
	if (g_pVolumeSignalPlugin != SVP_NULL)
	{
		delete g_pVolumeSignalPlugin;
		g_pVolumeSignalPlugin = SVP_NULL;
	}
}





