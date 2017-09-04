#include "SVPCameraDlg.h"
#include <qcolor.h>
#include "SVPCameraPictureID.h"
#include "SVPCameraApp.h"
#include "SVPSource.h"
#include "SVPPersist.h"
#include "qmetatype.h"

#ifdef USE_SERVICE
#include "SVPOverlay.h"
struct SVPOverlay    g_overlay;
#endif

#define TEXT_COLOR qRgb(0x1c, 0x1d, 0x1e)

extern SVPCameraApp g_CameraApp;
extern SVPBool g_bWakeup;


SVPCameraDlg::SVPCameraDlg()
:ISVPViewBase()
,m_bShowStatus(SVP_FALSE)
,m_bRvcActive(SVP_FALSE)
,m_curSet(SET_BRIGHTNESS)
,m_curAlpha(0)
{
	SVP_INFO("SVPCameraDlg() in.");

	m_setValueMax[SET_BRIGHTNESS] = 72;//127 根据效果自行调整,不超过127就行.
	m_setValueMax[SET_CONTRAST] = 63;
	m_setValueMax[SET_HUE] = 255;
	m_setValueMax[SET_SATURATION] = 63;

	m_setValue[SET_BRIGHTNESS] = 64;
	m_setValue[SET_CONTRAST] = 63;
	m_setValue[SET_HUE] = 0;
	m_setValue[SET_SATURATION] = 63;

	SetStatusbarVisible(SBM_HIDE);

#ifdef USE_SERVICE
    if(!SVP_Overlay_IsValid(g_overlay))
    	SVP_Overlay_Init(g_overlay, "/dev/fb0");
#endif

	m_bgIcon.CreateInstance(0, SVP_NULL, SVPRect(0, 0, 800, 480), this);
	m_bgIcon->SetBkgndColor(qRgb(0,0,0));
	m_bgIcon->SetEventInterface(this);

	CreateProgress(m_progress, 0, SVPPoint(157, 314), m_setValue[SET_BRIGHTNESS], 0, m_setValueMax[SET_BRIGHTNESS]);

	m_barIcon.CreateInstance(0, SVP_NULL, SVPRect(0, 400, 800, 80), this);
	m_barIcon->SetBkgndBitmap(PBMP(SVPBR_BASSBAR));

	m_setBtn[SET_BRIGHTNESS].CreateInstance(0, m_barIcon.GetInterface(), SVPPoint(87, 0), PBMP(SVPBR_BTN_BRIGHTNESS_NORMAL), this);
	m_setBtn[SET_BRIGHTNESS]->SetBkgndPressPixmap(PBMP(SVPBR_BTN_BRIGHTNESS_PRESSED));
	m_setBtn[SET_BRIGHTNESS]->SetBkgndDisablePixmap(PBMP(SVPBR_BTN_BRIGHTNESS_DISABLED));
	m_setBtn[SET_BRIGHTNESS]->SetBkgndCheckPixmap(PBMP(SVPBR_BTN_BRIGHTNESS_PRESSED));
	m_setBtn[SET_BRIGHTNESS]->SetEventInterface(this);

	m_setBtn[SET_CONTRAST].CreateInstance(0, m_barIcon.GetInterface(), SVPPoint(267, 0), PBMP(SVPBR_BTN_CONTRAST_NORMAL), this);
	m_setBtn[SET_CONTRAST]->SetBkgndPressPixmap(PBMP(SVPBR_BTN_CONTRAST_PRESSED));
	m_setBtn[SET_CONTRAST]->SetBkgndDisablePixmap(PBMP(SVPBR_BTN_CONTRAST_DISABLED));
	m_setBtn[SET_CONTRAST]->SetBkgndCheckPixmap(PBMP(SVPBR_BTN_CONTRAST_PRESSED));
	m_setBtn[SET_CONTRAST]->SetEventInterface(this);

	m_setBtn[SET_HUE].CreateInstance(0, m_barIcon.GetInterface(), SVPPoint(447, 0), PBMP(SVPBR_BTN_CHROMA_NORMAL), this);
	m_setBtn[SET_HUE]->SetBkgndPressPixmap(PBMP(SVPBR_BTN_CHROMA_PRESSED));
	m_setBtn[SET_HUE]->SetBkgndDisablePixmap(PBMP(SVPBR_BTN_CONTRAST_DISABLED));
	m_setBtn[SET_HUE]->SetBkgndCheckPixmap(PBMP(SVPBR_BTN_CHROMA_PRESSED));
	m_setBtn[SET_HUE]->SetEventInterface(this);

	m_setBtn[SET_SATURATION].CreateInstance(0, m_barIcon.GetInterface(), SVPPoint(627, 0), PBMP(SVPBR_BTN_SATURATION_NORMAL), this);
	m_setBtn[SET_SATURATION]->SetBkgndPressPixmap(PBMP(SVPBR_BTN_SATURATION_PRESSED));
	m_setBtn[SET_SATURATION]->SetBkgndDisablePixmap(PBMP(SVPBR_BTN_SATURATION_DISABLED));
	m_setBtn[SET_SATURATION]->SetBkgndCheckPixmap(PBMP(SVPBR_BTN_SATURATION_PRESSED));
	m_setBtn[SET_SATURATION]->SetEventInterface(this);

	qRegisterMetaType<SVPCamera::CameraSelect>("SVPCamera::CameraSelect");
	qRegisterMetaType<SVPUint32>("SVPUint32");

#ifdef USE_SERVICE
	connect(this,SIGNAL(SignalRvcChanged(bool)),this,SLOT(SlotRvcChanged(bool)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalCameraEffectValue(SVPCamera::CameraSelect, SVPUint32)),this,SLOT(SlotCameraEffectValue(SVPCamera::CameraSelect, SVPUint32)),Qt::QueuedConnection);

	SVP_GetPowerService()->AddListener(this);

	m_powerState = SVP_GetPowerService()->GetPowerState();

    SVP_GetCameraService()->AddListener(this);

	m_bRvcActive = SVP_GetCameraService()->GetRvcSignal();
    if(m_bRvcActive)
    {
		if(SVPPower::PS_USER_OFF == m_powerState)
		{
			SVP_GetPowerService()->SetPowerState(SVPPower::PS_USER_ON, SVPPower::PP_TEMP_USER_ON);
		}
    	SVP_GetCameraService()->OpenCamera(SVPCamera::CS_BACK, SVP_TRUE);//底层已打开倒车，这里只是切一下source
    	SVP_StartApp(SVPAppIndex::APP_PLATFORM_CONST_CAMERA, "normal",ADP_ABOVE_NORMAL);
    }

    SVP_GetCameraService()->CameraAppStarted();//can't call before addlistener.

	SVPUint32 value = SVPPersist::GetUInt32(SVPPersist::U32_CAMERA_EFFECT);
	if(PERSIST_INVALID_U32 != value)
	{
		SVP_GetCameraService()->SetCameraEffect(SVPCamera::CS_BACK, value);
	}
	else
	{
		value = GetMergeCfgValue();
		SVPPersist::SetUInt32(SVPPersist::U32_CAMERA_EFFECT, value);
		SVP_GetCameraService()->SetCameraEffect(SVPCamera::CS_BACK, value);
	}

	SVP_GetCameraService()->QueryCameraEffect(SVPCamera::CS_BACK);
#else
    SVP_StartApp(SVPAppIndex::APP_PLATFORM_CONST_CAMERA, "normal");
#endif

    SetCurSet(m_curSet);
    ShowCtrls(SVP_FALSE);
    SVP_INFO("SVPCameraDlg() out.");
}

SVPCameraDlg::~SVPCameraDlg()
{

}

SVPVoid SVPCameraDlg::CreateProgress(SVPProgressCtrlPtr& progress, SVPInt32 id, SVPPoint point, int value, int minValue, int maxValue)
{
	progress.CreateInstance(id, NULL, point, PBMP(SVPBR_SLIDER_BG), this);
	//progress->SetSlider(PBMP(SVPBR_BTN_PROGRESS_NORMAL), SVPPoint(20, 20), SVPPoint(313-20, 20));
	progress->SetSlider(PBMP(SVPBR_BTN_PROGRESS_NORMAL), SVPPoint(33, 32), SVPPoint(485-33, 32));//对应滑块中心点
	progress->SetSliderPressBitmap(PBMP(SVPBR_BTN_PROGRESS_PRESSED));
	//progress->SetProgressBarPixmap(PBMP(SVPBR_PROGRESS_420PX), SVPPoint(11, 20));
	progress->SetProgressBarPixmap(PBMP(SVPBR_PROGRESS_420PX), SVPPoint(33, 28));
	progress->SetRange(minValue, maxValue);
	progress->SetProgressPos(value);
	//progress->ShowProgressPosText(SVPPoint(0, 0), SVPAlignCenter);
	progress->SetMinUnit(1);
	//progress->SetTextColor(qRgb(255, 255, 255));
	progress->SetEventInterface(this);
}

SVPVoid SVPCameraDlg::OnCameraEffectValue(SVPCamera::CameraSelect cameraSelect, SVPUint32 value)
{
	SVP_INFO_FUNC();
	emit SignalCameraEffectValue(cameraSelect,  value);
}
SVPVoid SVPCameraDlg::OnRvcSignalChange(SVPBool bActive)
{
	SVP_INFO("OnRvcSignalChange(%d).", bActive);
	emit SignalRvcChanged(bActive);
}

void SVPCameraDlg::SlotRvcChanged(bool bActive)
{
	SVP_INFO("SlotRvcChanged(%d) in.", bActive);
	m_bRvcActive = bActive;
#ifdef USE_SERVICE
	if(bActive)
	{
		if(SVPPower::PS_USER_OFF == m_powerState)
		{
			g_bWakeup = SVP_TRUE;
			SVPPersist::SetRamShareByte(SVPPersist::RS_WAKEUP, 1);
			SVP_GetPowerService()->SetPowerState(SVPPower::PS_USER_ON,  SVPPower::PP_TEMP_USER_ON);
		}
		SVP_GetCameraService()->OpenCamera(SVPCamera::CS_BACK, SVP_TRUE);
		SetAlpha(0);
		SVP_StartApp(SVPAppIndex::APP_PLATFORM_CONST_CAMERA, "normal", ADP_ABOVE_NORMAL);
	}
	else
	{
		SVPBool bGotoStandby = SVP_FALSE;
		if(g_bWakeup)
		{
			g_bWakeup = SVP_FALSE;
			SVPPersist::SetRamShareByte(SVPPersist::RS_WAKEUP, 0);
			if(!SVPSource::IsActived(SVPSource::SID_PHONE) && !SVPSource::IsActived(SVPSource::SID_RINGTONE))
			{
				bGotoStandby = SVP_TRUE;
				SVPPersist::SetRamShareByte(SVPPersist::RS_GOTO_STANDBY, 1);
			}
		}
		SetAlpha(255);
		SVP_GetCameraService()->CloseCamera();//radio don't deal with source msg at standby
		if(bGotoStandby)
			SVP_GetPowerService()->SetPowerState(SVPPower::PS_USER_OFF);

		SVP_ResumeLastApp();

		ShowCtrls(SVP_FALSE);
	}
#endif
	SVP_INFO("SlotRvcChanged(%d) out.", bActive);
}

void SVPCameraDlg::SlotCameraEffectValue(SVPCamera::CameraSelect cameraSelect, SVPUint32 value)
{
	SVP_INFO_FUNC();
	m_setValue[SET_HUE] = (SVPUint8)value;
	m_setValue[SET_CONTRAST] = (SVPUint8)(value>>8);
	m_setValue[SET_BRIGHTNESS] = (SVPUint8)(value>>16);
	m_setValue[SET_SATURATION] = (SVPUint8)(value>>24);

	m_progress->SetProgressPos(m_setValue[m_curSet]);
}

SVPUint32 SVPCameraDlg::GetMergeCfgValue()
{
	SVPUint32 mergeValue = m_setValue[SET_HUE] + (((SVPUint32)m_setValue[SET_CONTRAST])<<8) + (((SVPUint32)m_setValue[SET_BRIGHTNESS])<<16)\
			+ (((SVPUint32)m_setValue[SET_SATURATION])<<24);
	SVP_INFO("mergeValue = 0X%x.", mergeValue);
	return mergeValue;
}

void SVPCameraDlg::On_SVPProgressCtrl_SlideFinish(ISVPProgressCtrl *pCtrl, SVPReal fNewPos)
{
	m_setValue[m_curSet] = fNewPos;
	SVPUint32 mergeValue = GetMergeCfgValue();
#ifdef USE_SERVICE
	SVPPersist::SetUInt32(SVPPersist::U32_CAMERA_EFFECT, mergeValue);
	SVP_GetCameraService()->SetCameraEffect(SVPCamera::CS_BVS, mergeValue);
#endif
}

void SVPCameraDlg::On_SVPProgressCtrl_SliderRelease(ISVPProgressCtrl *pCtrl, SVPReal fPos)
{
	//SVP_INFO_FUNC();
	On_SVPProgressCtrl_SlideFinish(pCtrl, fPos);
}

SVPVoid SVPCameraDlg::ShowCtrls(SVPBool bShow)
{
	SVP_INFO("ShowCtrls(%d).", bShow);

	if(bShow)
	{
#ifdef USE_SERVICE
		if(m_bRvcActive)
#endif
		{
			m_bShowStatus = bShow;
			m_progress->Show(bShow);
			m_barIcon->Show(bShow);
			SetAlpha(255);
		}
	}
	else
	{
		m_bShowStatus = bShow;
		m_progress->Show(bShow);
		m_barIcon->Show(bShow);
	}

}

void SVPCameraDlg::On_SVPStaticIconCtrl_Clicked(ISVPStaticIconCtrl *pCtrl)
{
	if(pCtrl == m_bgIcon.GetInterface())
		ShowCtrls(!m_bShowStatus);
}

void SVPCameraDlg::On_SVPButtonEvent_Clicked(ISVPButton *pCtrl)
{
	if(pCtrl == m_setBtn[SET_BRIGHTNESS].GetInterface())
	{
		SetCurSet(SET_BRIGHTNESS);
	}
	if(pCtrl == m_setBtn[SET_CONTRAST].GetInterface())
	{
		SetCurSet(SET_CONTRAST);
	}
	if(pCtrl == m_setBtn[SET_HUE].GetInterface())
	{
		SetCurSet(SET_HUE);
	}
	if(pCtrl == m_setBtn[SET_SATURATION].GetInterface())
	{
		SetCurSet(SET_SATURATION);
	}
}

SVPVoid SVPCameraDlg::SetCurSet(SVPUint8 curSet)
{
	if(curSet >= SET_MAX)
	{
		SVP_ERROR("SetCurSet(%d) invalid parameter!!",curSet);
		return;
	}
	SVP_INFO("SetCurSet(%d).", curSet);
	m_setBtn[m_curSet]->SetCheck(false);
	m_setBtn[curSet]->SetCheck(true);

	m_progress->SetRange(0, m_setValueMax[curSet]);
	m_progress->SetProgressPos(m_setValue[curSet]);

	m_curSet = curSet;
}

SVPVoid SVPCameraDlg::OnPowerStateChanged(SVPPower::PowerState state, SVPUint8 params)
{
	m_powerState = state;
#ifdef USE_SERVICE
	if(SVPPower::PS_USER_OFF == state && m_bRvcActive && SVPPower::PP_VLOW_USER_OFF != params)
	{
		g_bWakeup = SVP_TRUE;
		SVPPersist::SetRamShareByte(SVPPersist::RS_WAKEUP, 1);
		SVP_GetPowerService()->SetPowerState(SVPPower::PS_USER_ON, SVPPower::PP_TEMP_USER_ON);
	}
#endif
}

SVPVoid SVPCameraDlg::SetAlpha(SVPUint8 alpha)
{
#ifdef USE_SERVICE
	if(SVP_Overlay_IsValid(g_overlay))
	{
		if(alpha == m_curAlpha)
			return;

		if(SVP_Overlay_SetAlpha(g_overlay, alpha))
		{
			m_curAlpha = alpha;
		}
	}
#endif
}
