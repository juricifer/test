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

class SVPPluginTime :  public QObject, public SVPStatusbarPluginBase, public ISVPButtonEvent
{
	Q_OBJECT
public:
	SVPPluginTime(SVPInt32 iIndex,const SVPChar* strPkgName,const SVPChar* strPluginName, ISVPBaseCtrl *pParent);
	virtual ~SVPPluginTime();
	virtual SVPBool SetPos(SVPInt32 x,SVPInt32 y);
	virtual SVPBool SetVisible(SVPBool bVisible);
	virtual SVPLong PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam);
	SVPVoid UpdateDateTime();

signals:
	void SignalUpdateDateTime();

protected:
	virtual SVPBool OnUpdateSystemTime();

private slots:
	void SlotSizeUpdate();
	void SlotUpdateDateTime();

private:
	SVPBitmapDateTimeCtrlPtr m_pDateTimeCtrl;
	SVPBitmapResMgr *m_pResMgr;
	QTimer m_timerSetSize;
};

#endif /* SVPPLUGINHOME_H_ */
