/*
 * SVPPluginTime.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: ubuntu
 */

#include "SVPPluginTime.h"
#include "SVPPluginTimeBmp.h"
#include "SVPString.h"
#include "app/SVPAppMsgIDDefine.h"

#include "SVPLog.h"

#ifdef SVP_LOG_TAG
	#undef SVP_LOG_TAG
#endif
#define SVP_LOG_TAG		"statusbar|libstatusbartime"

SVPPluginTime::SVPPluginTime(SVPInt32 iIndex,const SVPChar* strPkgName,const SVPChar* strPluginName, ISVPBaseCtrl *pParent)
: SVPStatusbarPluginBase(iIndex, strPkgName, strPluginName, "const", 0)
{
	SVPString szResourcePath = GetAppResourcePath();
	szResourcePath = szResourcePath + "/" + "SVPPluginTimeBmp.dat";
	m_pResMgr = new SVPBitmapResMgr(szResourcePath.data());
	m_pResMgr->CreateGroup(1, true);

//	SVP_INFO("SVPPluginTime::SVPPluginTime(%d, %s, %p) called", iIndex, strPkgName, pParent);
	const SVPBitmap *pbmp = m_pResMgr->PrepBmp(SVPBR_TIME_0);
	m_pDateTimeCtrl.CreateInstance(iIndex, pParent, SVPRect(0, 0, 120, pbmp->GetHeight()), NULL);
	m_pDateTimeCtrl->SetFormatString("%H:%M");
	m_pDateTimeCtrl->SetNumberPixmap(0, pbmp, 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(1, m_pResMgr->PrepBmp(SVPBR_TIME_1), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(2, m_pResMgr->PrepBmp(SVPBR_TIME_2), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(3, m_pResMgr->PrepBmp(SVPBR_TIME_3), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(4, m_pResMgr->PrepBmp(SVPBR_TIME_4), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(5, m_pResMgr->PrepBmp(SVPBR_TIME_5), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(6, m_pResMgr->PrepBmp(SVPBR_TIME_6), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(7, m_pResMgr->PrepBmp(SVPBR_TIME_7), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(8, m_pResMgr->PrepBmp(SVPBR_TIME_8), 1, 1);
	m_pDateTimeCtrl->SetNumberPixmap(9, m_pResMgr->PrepBmp(SVPBR_TIME_9), 1, 1);
	m_pDateTimeCtrl->SetCharPixmap(':', m_pResMgr->PrepBmp(SVPBR_TIME_POINT), 2, 2);
	//m_pDateTimeCtrl->SetMainRectMargins(0, 0, 0, 0);

	connect(this, SIGNAL(SignalUpdateDateTime()), this, SLOT(SlotUpdateDateTime()));

	m_timerSetSize.setSingleShot(true);
	connect(&m_timerSetSize, SIGNAL(timeout()), this, SLOT(SlotSizeUpdate()));
	m_timerSetSize.start(20);
}

SVPPluginTime::~SVPPluginTime()
{
	m_pResMgr->DestoyGroup(1);
	delete m_pResMgr;
}

SVPLong SVPPluginTime::PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam)
{
	switch (message)
	{
	case SVPAppMsgID::MSG_ID_SYSTEM_TIME_UPDATE://更新时间显示
		UpdateDateTime();
		break;
	default:
		break;
	}
	return hMsg+message+wParam+lParam;//为了避免编译警告
}

SVPBool SVPPluginTime::OnUpdateSystemTime()
{
	SVPStatusbarPluginBase::OnUpdateSystemTime();
	SlotUpdateDateTime();
	return SVP_TRUE;
}

SVPVoid SVPPluginTime::UpdateDateTime()
{
	emit SignalUpdateDateTime();
}

SVPVoid SVPPluginTime::SlotUpdateDateTime()
{
	m_pDateTimeCtrl->UpdateShow();
}

SVPVoid SVPPluginTime::SlotSizeUpdate()
{
	SVPSize size = m_pDateTimeCtrl->GetSize();
	SVPPluginSize pluginSize;
	pluginSize.w = size.width;
	pluginSize.h = size.height;
	SetSize(pluginSize);
}

SVPBool SVPPluginTime::SetPos(SVPInt32 x,SVPInt32 y)
{
	m_pDateTimeCtrl->SetPos(x, y);
	return SVP_TRUE;
}

SVPBool SVPPluginTime::SetVisible(SVPBool bVisible)
{
	m_pDateTimeCtrl->Show(bVisible);
	return SVP_TRUE;
}

SVPPluginTime *g_pPluginTime = SVP_NULL;
SVPPluginType SVP_GetPluginType()
{
	return PT_STATUSBAR;
}

ISVPPluginBase* SVP_CreatePlugin(SVPInt32 iPluginIndex,const SVPChar* strPkgName,const SVPChar* strPluginName,SVPVoid* pParent)
{
	if (g_pPluginTime == SVP_NULL)
	{
		g_pPluginTime = new SVPPluginTime(iPluginIndex, strPkgName, strPluginName, (ISVPBaseCtrl*)pParent);//把SVPVoid型转换为ISVPBaseCtrl型时会直接把派生类pParent的入口地址转换为基类ISVPBaseCtrl的地址
	}
	return g_pPluginTime;
}

SVPVoid SVP_DestroyPlugin()
{
	if (g_pPluginTime != SVP_NULL)
	{
		delete g_pPluginTime;
		g_pPluginTime = SVP_NULL;
	}
}
