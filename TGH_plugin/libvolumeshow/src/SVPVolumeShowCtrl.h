/******************************************* 
 * Copyright (c) 2012，德赛西威汽车电子有限公司
 * All rights reserved
 * 文件名: SVPVolumeShowCtrl.h
 * 编写者: Yao Fen
 * 编写日期: Mar 11, 2013
 * 简要描述:
 * 修改记录:
 *******************************************/

#ifndef SVPVOLUMESHOWCTRL_H_
#define SVPVOLUMESHOWCTRL_H_

#include <SVPBaseCtrl.h>
#include <GeneralCtrlPkgInter.h>
#include <GeneralCtrlPtr.h>
#include <QGraphicsItem>
#include <QObject>
#include "SVPType.h"
#include "CtrlPkgInter.h"
#include "SVPUIService.h"
#include "SVPType.h"
#include "SVPPluginBase.h"
#include "SVPPluginBaseDefine.h"
#include "SVPVolumeShowPic.h"
#include "SVPAudio.h"
#include "audio/SVPAudioType.h"
#include "audio/ISVPAudioListener.h"
#include "QTimer"

class SVPVolumeShowCtrl: public QObject , public ISVPAudioListener, public SVPStatusbarPluginBase
{
	Q_OBJECT
	Q_SIGNALS:
	void SignalIconChange(int m_vol);
	void SignalIconMuteState(int state);
	void SignalTelVolUpdate(int type,int value);
protected slots:
	void SlotNewIcon(int m_vol);
	void SlotMuteState(int m_state);
	void SlotTelVolUpdate(int type,int value);
	void SlotShowUpdate();

public:
	SVPVolumeShowCtrl(SVPInt32 iIndex, const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl* pParent);
	virtual ~SVPVolumeShowCtrl();
	SVPVoid InitDlg();
	virtual SVPBool SetPos(SVPInt32 x,SVPInt32 y);

private slots:
	void SlotSizeUpdate();

private:
	SVPStaticIconPtr m_volBk;
	SVPStaticIconPtr  m_pVolumeSignalCtrl;
	SVPProgressCtrlPtr m_provolume;
	SVPStaticTextPtr m_volInfo;
	SVPBitmapResMgr *m_pResMgr;
	QTimer m_timerSetSize;
	QTimer m_timerShow;
	SVPPluginSize m_size;
	SVPBool m_bSingleShow;

	//Listener监听
	virtual SVPVoid OnAudioVolumeChanged(SVPUint8 vol_step);
	virtual SVPVoid OnAudioParamsUpdated(SVPAudio::AudioParamType param_type, SVPAudio::AudioParams params);
	virtual SVPVoid OnAudioMuteStateChanged(SVPAudio::MuteState state, SVPAudio::MuteType type);

	virtual SVPBool SetVisible(SVPBool bVisible);

};

extern "C"
{
	SVPPluginType SVP_GetPluginType();
	ISVPPluginBase* SVP_CreatePlugin(SVPInt32 iPluginIndex,const SVPChar* strPkgName,const SVPChar* strPluginName,SVPVoid* pParent);
	SVPVoid SVP_DestroyPlugin();
}

#endif /* SVPVOLUMESHOWCTRL_H_ */
