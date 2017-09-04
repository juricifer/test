/*
 * SVPPluginAppName.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: ubuntu
 */

#include "SVPPluginAppName.h"
#include "SVPString.h"
#include "SVPApp.h"
#include "app/SVPAppMsgIDDefine.h"

#include "SVPLog.h"

#ifdef SVP_LOG_TAG
	#undef SVP_LOG_TAG
#endif
#define SVP_LOG_TAG		"statusbar|libstatusbarappname"

SVPPluginAppName::SVPPluginAppName(SVPInt32 iIndex,const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl *pParent)
: SVPStatusbarPluginBase(iIndex, strPkgName, strPluginName, "normal", 0)//需要独显时属性为notify，需要定义优先级，const和normal不需要定义优先级
{
//	SVP_INFO("SVPPluginAppName::SVPPluginAppName(%d, %s, %p) called", iIndex, strPkgName, pParent);
	m_pStaticTextCtrl.CreateInstance(iIndex, pParent, SVPRect(0, 0, 302, 50), SVP_NULL);
	m_pStaticTextCtrl->SetFont(PFONT(FontID_Big_3));
	m_pStaticTextCtrl->SetTextColor(/*SVPRgba(255, 255, 255, 0)*/0xB8C8D9);
	m_pStaticTextCtrl->SetAlign(SVPAlignLeft);
	m_pStaticTextCtrl->SetText("launcher");
	m_pStaticTextCtrl->SetMainRectMargins(30, 0, 0, 0);

	connect(this, SIGNAL(SignalUpdateAppName()), this, SLOT(SlotUpdateAppName()));

	m_timerSetSize.setSingleShot(true);
	connect(&m_timerSetSize, SIGNAL(timeout()), this, SLOT(SlotSizeUpdate()));
	m_timerSetSize.start(20);
}

SVPPluginAppName::~SVPPluginAppName()
{}

SVPLong SVPPluginAppName::PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam)
{
	SVP_INFO("SVPPluginAppName::PluginMsgProc(%d, %d, %d, %ld) called", hMsg, message, wParam, lParam);
	switch (message)
	{
	case SVPAppMsgID::MSG_ID_SYSTEM_TITLE_UPDATE://更新APP名称显示
		UpdateAppName();
		break;
	default:
		break;
	}
	return hMsg+message+wParam+lParam;//为了避免编译警告
}

SVPVoid SVPPluginAppName::OnUpdateLanguage(SVPUint32 uiLGId)
{
	SVPStatusbarPluginBase::OnUpdateLanguage(uiLGId);
	SlotUpdateAppName();
}

SVPBool SVPPluginAppName::OnUpdateSystemTitle()
{
	SVPStatusbarPluginBase::OnUpdateSystemTitle();
	SlotUpdateAppName();
}

SVPVoid SVPPluginAppName::UpdateAppName()
{
	emit SignalUpdateAppName();
}

SVPVoid SVPPluginAppName::SlotUpdateAppName()
{
	SVPString szFGAppTitle;
	SVP_GetTitle(szFGAppTitle);
	m_pStaticTextCtrl->SetText(szFGAppTitle);
}

SVPVoid SVPPluginAppName::SlotSizeUpdate()
{
	SVPSize size = m_pStaticTextCtrl->GetSize();
	SVPPluginSize pluginSize;
	pluginSize.w = size.width;
	pluginSize.h = size.height;
	SetSize(pluginSize);
}

SVPBool SVPPluginAppName::SetPos(SVPInt32 x,SVPInt32 y)
{
	m_pStaticTextCtrl->SetPos(x, y);
//	SetTipMsg("Find New Wifi Net...");//测试代码
	return SVP_TRUE;
}

SVPBool SVPPluginAppName::SetVisible(SVPBool bVisible)
{
	m_pStaticTextCtrl->Show(bVisible);
	return SVP_TRUE;
}

SVPPluginAppName *g_pPluginAppName = SVP_NULL;
SVPPluginType SVP_GetPluginType()
{
	return PT_STATUSBAR;
}

ISVPPluginBase* SVP_CreatePlugin(SVPInt32 iPluginIndex,const SVPChar* strPkgName,const SVPChar* strPluginName,SVPVoid* pParent)
{
	if (g_pPluginAppName == SVP_NULL)
	{
		g_pPluginAppName = new SVPPluginAppName(iPluginIndex, strPkgName, strPluginName, (ISVPBaseCtrl*)pParent);//把SVPVoid型转换为ISVPBaseCtrl型时会直接把派生类pParent的入口地址转换为基类ISVPBaseCtrl的地址
	}
	return g_pPluginAppName;
}

SVPVoid SVP_DestroyPlugin()
{
	if (g_pPluginAppName != SVP_NULL)
	{
		delete g_pPluginAppName;
		g_pPluginAppName = SVP_NULL;
	}
}

