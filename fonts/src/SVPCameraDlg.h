/*
 * SVPCameraDlg.h
 *
 *  Created on: Apr 25, 2013
 *      Author: ubuntu
 */

#ifndef SVPCAMERADLG_H_
#define SVPCAMERADLG_H_

#include "SVPPower.h"
#include "SVPApp.h"
#include "app/SVPAppIndexDefine.h"
#include "app/SVPAppMsgIDDefine.h"
#include <QObject>
#include "GeneralCtrlPtr.h"
#include "GeneralCtrlPkgInter.h"
#include "CtrlPkgInter.h"
#include <QTimer>
#include "app/ISVPAppBase.h"
#include "app/ISVPViewBase.h"
#include "SVPCamera.h"
#include "SVPLog.h"

#ifdef SVP_LOG_TAG
	 #undef SVP_LOG_TAG
#endif
#define SVP_LOG_TAG  "app|camera"


#define SET_ALPHA_0_WHEN_BEGIN_RVC

class SVPCameraDlg : public QObject
					, public ISVPViewBase
					, public ISVPCameraListener
					//, public ISVPScrollBarEvent
					, public ISVPProgressCtrlEvent
					, public ISVPButtonEvent
					, public ISVPStaticIconCtrlEvent
					, public ISVPPowerListener
{
Q_OBJECT
Q_SIGNALS:
	void SignalRvcChanged(bool bActive);
	void SignalCameraEffectValue(SVPCamera::CameraSelect cameraSelect, SVPUint32 value);
public slots:
	void SlotRvcChanged(bool bActive);
	void SlotCameraEffectValue(SVPCamera::CameraSelect cameraSelect, SVPUint32 value);
	//void SlotTimeout();
public:
	SVPCameraDlg();
	virtual ~SVPCameraDlg();

	SVPBool IsRvcActive(){return m_bRvcActive;};

	virtual void On_SVPStaticIconCtrl_Clicked(ISVPStaticIconCtrl *pCtrl);
	virtual void On_SVPButtonEvent_Clicked(ISVPButton *pCtrl);

	virtual void On_SVPProgressCtrl_SlideFinish(ISVPProgressCtrl *pCtrl, SVPReal fNewPos);	// 滑块滑行完成
	virtual void On_SVPProgressCtrl_SliderRelease(ISVPProgressCtrl *pCtrl, SVPReal fPos);	// 滑块被释放

	virtual SVPVoid OnPowerStateChanged(SVPPower::PowerState state, SVPUint8 params);
	virtual SVPVoid OnBkLightLevelChanged(SVPPower::BkLight::BkLightMode mode,
										SVPPower::BkLight::BkLightType type,
										SVPUint8 level){};

	virtual SVPVoid OnRvcSignalChange(SVPBool bActive);
	virtual SVPVoid OnCameraEffectValue(SVPCamera::CameraSelect cameraSelect, SVPUint32 value) ;

protected:
	SVPVoid CreateProgress(SVPProgressCtrlPtr& progress, SVPInt32 id, SVPPoint point, int value, int minValue, int maxValue);
	SVPUint32 GetMergeCfgValue();
	SVPVoid ShowCtrls(SVPBool bShow);

	SVPVoid SetAlpha(SVPUint8 alpha);
	SVPVoid SetCurSet(SVPUint8 curSet);
private:
	SVPStaticIconPtr m_bgIcon;
	SVPStaticIconPtr m_barIcon;
	SVPProgressCtrlPtr m_progress;

	SVPBool m_bShowStatus;
	SVPUint8 m_curSet;

	enum{
		SET_BRIGHTNESS = 0,
		SET_CONTRAST,
		SET_HUE,
		SET_SATURATION,
		SET_MAX,
	};

	SVPUint8 m_setValueMax[SET_MAX];
	SVPUint8 m_setValue[SET_MAX];
	SVPButtonPtr m_setBtn[SET_MAX];
	SVPUint8 m_curAlpha;

	SVPBool m_bRvcActive;
	SVPPower::PowerState m_powerState;

	//QTimer m_timerSetAlpha;
};

#endif /* SVPCAMERADLG_H_ */
