#include "SVPCameraApp.h"
#include "device/input/SVPInputType.h"
#include "SVPPersist.h"

SVPCameraApp g_CameraApp(SVPAppIndex::APP_PLATFORM_CONST_CAMERA);
SVPBool g_bWakeup = SVP_FALSE;

SVPCameraApp::SVPCameraApp(SVPInt32 iAppIndex)
:m_pDlg(SVP_NULL)
,ISVPAppBase(iAppIndex)
{

}

SVPCameraApp::~SVPCameraApp()
{

}

SVPBool SVPCameraApp::OnCheckAppActive(SVPAppActiveCase eCase)
{
	if(1 == SVPPersist::GetRamShareByte(SVPPersist::RS_RVC_STATUS))
		return SVP_TRUE;
	else
		return SVP_FALSE;
}
SVPBool SVPCameraApp::InitGUI()
{
	SVP_INFO_BUILD_TIME();

	BRMInstance::CreateInstance("../../resource/SVPCameraPicture.dat");
	BRMInstance::GetInstance()->CreateGroup(1, true);

	m_pDlg = new SVPCameraDlg();
	if(!m_pDlg)
	{
		SVP_INFO("InitGUI() new dlg fail!");
		return SVP_FALSE;
	}

	ISVPAppBase::InitGUI();
	return SVP_TRUE;
}

SVPBool SVPCameraApp::InitAppBase()
{
#ifdef USE_SERVICE
	SVP_GetCameraService()->StartService();
	SVP_GetPowerService()->StartService();
#endif
	return ISVPAppBase::InitAppBase();
}

SVPBool SVPCameraApp::UnInitAppBase()
{
#ifdef USE_SERVICE
	if(g_bWakeup)
		SVPPersist::SetRamShareByte(SVPPersist::RS_WAKEUP, 0);

	SVP_GetCameraService()->CloseCamera();
	SVP_GetPowerService()->StopService();//avoid to wakeup when standby
	SVP_GetCameraService()->StopService();
	SVP_ReleaseCameraService();
	SVP_ReleasePowerService();
#endif
}

SVPBool SVPCameraApp::OnSwitchToFg()
{
	ISVPAppBase::OnSwitchToFg();
#ifdef USE_SERVICE
	if(m_pDlg)
	{
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_VR);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_MAP);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_NAVI);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_FAVORITE);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_NOW_PLAYING);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_HOME);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_RADIO);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_TONE);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_DISC);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_SETUP);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_EJECT);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_BACK);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_TASK);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_MEDIA);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_PREV);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_NEXT);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_MUTE);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_POWER);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_DOWN);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_UP);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_LEFT);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_RIGHT);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_OK);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_PHONE);
		m_pDlg->RegisterVKeyEvent(SVPInput::VKEY_PHONE_HANG_UP);//need to check wheather need!
	}
	else
		SVP_ERROR("m_pDlg is NULL!!");
#endif
	return SVP_TRUE;
}
SVPBool SVPCameraApp::OnSwitchToBg(SVPBool bOverlap)
{
	ISVPAppBase::OnSwitchToBg(bOverlap);
#ifdef USE_SERVICE
	if(m_pDlg)
	{
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_VR);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_MAP);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_NAVI);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_FAVORITE);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_NOW_PLAYING);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_HOME);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_RADIO);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_TONE);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_DISC);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_SETUP);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_EJECT);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_BACK);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_TASK);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_MEDIA);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_PREV);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_NEXT);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_MUTE);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_POWER);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_DOWN);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_UP);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_LEFT);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_RIGHT);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_OK);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_PHONE);
		m_pDlg->UnRegisterVKeyEvent(SVPInput::VKEY_PHONE_HANG_UP);//need to check wheather need!
	}
#endif
	return SVP_TRUE;
}
