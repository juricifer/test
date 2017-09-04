/*
 * SVPPluginBack.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: ubuntu
 */

#include "SVPPluginBack.h"
#include "SVPPluginBackBmp.h"
#include "SVPDevice.h"
#include "SVPString.h"
#include "app/SVPAppMsgIDDefine.h"
#include "SVPApp.h"
#include "app/SVPAppIndexDefine.h"

#include "SVPLog.h"

#ifdef SVP_LOG_TAG
	#undef SVP_LOG_TAG
#endif
#define SVP_LOG_TAG		"statusbar|libstatusbarback"

SVPPluginBack::SVPPluginBack(SVPInt32 iIndex,const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl *pParent)
: SVPStatusbarPluginBase(iIndex, strPkgName, strPluginName, "const", 0)
{
	SVPString szResourcePath = GetAppResourcePath();
	szResourcePath = szResourcePath + "/" + "SVPPluginBackBmp.dat";
	m_pResMgr = new SVPBitmapResMgr(szResourcePath.data());
	m_pResMgr->CreateGroup(1, true);

//	SVP_INFO("SVPPluginBack::SVPPluginBack(%d, %s, %p) called", iIndex, strPkgName, pParent);
	m_pIconButton.CreateInstance(iIndex, pParent, SVPPoint(0, 0), m_pResMgr->PrepBmp(SVPBR_BTN_BACK_NORMAL));
	m_pIconButton->SetBkgndPressPixmap(m_pResMgr->PrepBmp(SVPBR_BTN_BACK_PRESSED));
	m_pIconButton->SetBkgndDisablePixmap(m_pResMgr->PrepBmp(SVPBR_BTN_BACK_DISABLED));
	m_pIconButton->SetEventInterface(this);
	m_pIconButton->SetEnable(false);//默认在launcher界面下，要处于Disable状态

	connect(this, SIGNAL(SignalEnableButton(bool)), this, SLOT(SlotEnableButton(bool)));

	m_timerSetSize.setSingleShot(true);
	connect(&m_timerSetSize, SIGNAL(timeout()), this, SLOT(SlotSizeUpdate()));
	m_timerSetSize.start(20);
//
//	m_timerTest.setInterval(1000);
//	connect(&m_timerTest, SIGNAL(timeout()), this, SLOT(SlotTest()));
//	m_timerTest.start();
}

//SVPVoid SVPPluginBack::SlotTest()
//{
//	static bool bFlag = true;
//	if (bFlag)
//	{
//		bFlag = false;
//		PluginMsgProc(0, SVPAppMsgID::MSG_ID_APP_FG_LAUNCHER, 0, 0);
//	}
//	else
//	{
//		bFlag = true;
//		PluginMsgProc(0, SVPAppMsgID::MSG_ID_APP_FG_NO_LAUNCHER, 0, 0);
//	}
//}

SVPPluginBack::~SVPPluginBack()
{
	m_pResMgr->DestoyGroup(1);
	delete m_pResMgr;
}

SVPVoid SVPPluginBack::SlotSizeUpdate()
{
	SVPSize size = m_pIconButton->GetSize();
	SVPPluginSize pluginSize;
	pluginSize.w = size.width;
	pluginSize.h = size.height;
	SetSize(pluginSize);
}

SVPBool SVPPluginBack::SetPos(SVPInt32 x,SVPInt32 y)
{
	m_pIconButton->SetPos(x, y);
	return SVP_TRUE;
}

SVPBool SVPPluginBack::SetVisible(SVPBool bVisible)
{
	m_pIconButton->Show(bVisible);
	return SVP_TRUE;
}

SVPVoid SVPPluginBack::On_SVPButtonEvent_Clicked(ISVPButton *pCtrl)
{
	if (m_pIconButton.GetInterface() == pCtrl)
	{
		SVP_INFO("SVPPluginBack::On_SVPButtonEvent_Clicked called");
#ifdef SVP_SIMULATOR
		 SVP_ResumeLastApp();//PC版本，显示上一个APP
#else
		SVP_GetInputService()->SendKeyEvent(SVPInput:: VKEY_BACK,SVPInput::VKEY_PRESSED);
		SVP_GetInputService()->SendKeyEvent(SVPInput:: VKEY_BACK,SVPInput::VKEY_RELEASE);
#endif
	}
}

SVPLong SVPPluginBack::PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam)
{
//	SVP_INFO("SVPPluginBack::PluginMsgProc(%d, %d, %d, %ld) called", hMsg, message, wParam, lParam);
	switch (message)
	{
	case SVPAppMsgID::MSG_ID_APP_FG_LAUNCHER://处于launcher界面下disable返回按钮
		EnableButton(false);
		break;
	case SVPAppMsgID::MSG_ID_APP_FG_NO_LAUNCHER://处于其他界面下enable返回按钮
		EnableButton(true);
		break;
	default:
		break;
	}
	return hMsg+message+wParam+lParam;//为了避免编译警告
}

SVPBool SVPPluginBack::OnSwitchLauncher(SVPBool bFg)
{
	SVPStatusbarPluginBase::OnSwitchLauncher(bFg);
	m_pIconButton->SetEnable(!bFg);
	return SVP_TRUE;
}

SVPVoid SVPPluginBack::EnableButton(bool bEnable)
{
	emit SignalEnableButton(bEnable);
}

SVPVoid SVPPluginBack::SlotEnableButton(bool bEnable)
{
	m_pIconButton->SetEnable(bEnable);
}

SVPPluginBack *g_pPluginBack = SVP_NULL;
SVPPluginType SVP_GetPluginType()
{
	return PT_STATUSBAR;
}

ISVPPluginBase* SVP_CreatePlugin(SVPInt32 iPluginIndex,const SVPChar* strPkgName,const SVPChar* strPluginName,SVPVoid* pParent)
{
	if (g_pPluginBack == SVP_NULL)
	{
		g_pPluginBack = new SVPPluginBack(iPluginIndex, strPkgName, strPluginName, (ISVPBaseCtrl*)pParent);//把SVPVoid型转换为ISVPBaseCtrl型时会直接把派生类pParent的入口地址转换为基类ISVPBaseCtrl的地址
	}
	return g_pPluginBack;
}

SVPVoid SVP_DestroyPlugin()
{
	if (g_pPluginBack != SVP_NULL)
	{
		delete g_pPluginBack;
		g_pPluginBack = SVP_NULL;
	}
}
