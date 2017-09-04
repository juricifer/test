/*
 * SVPPluginHome.h
 *
 *  Created on: Mar 25, 2013
 *      Author: ubuntu
 */

#ifndef SVPPLUGINHOME_H_
#define SVPPLUGINHOME_H_

#include "SVPType.h"
#include "SVPPluginBase.h"
#include <GeneralCtrlPtr.h>
#include <QObject>
#include <QTimer>

class SVPPluginHome : public QObject, public SVPStatusbarPluginBase, public ISVPButtonEvent
{
	Q_OBJECT
public:
	SVPPluginHome(SVPInt32 iIndex,const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl *pParent);
	virtual ~SVPPluginHome();
	virtual SVPBool SetPos(SVPInt32 x,SVPInt32 y);
	virtual SVPBool SetVisible(SVPBool bVisible);
	virtual SVPVoid On_SVPButtonEvent_Clicked(ISVPButton *pCtrl);
	virtual SVPLong PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam);
	SVPVoid EnableButton(bool bEnable);

protected:
	virtual SVPBool OnSwitchLauncher(SVPBool bFg);

private:
signals:
	void SignalEnableButton(bool bEnable);

private slots:
	void SlotSizeUpdate();
	void SlotEnableButton(bool bEnable);
//	void SlotTest();

private:
	SVPButtonPtr m_pIconButton;
	SVPBitmapResMgr *m_pResMgr;
	QTimer m_timerSetSize;
//	QTimer m_timerTest;
};

#endif /* SVPPLUGINHOME_H_ */
