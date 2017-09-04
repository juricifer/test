/*
 * SVPPluginAppName.h
 *
 *  Created on: Apr 22, 2013
 *      Author: ubuntu
 */

#ifndef SVPPLUGINAPPNAME_H_
#define SVPPLUGINAPPNAME_H_

#include "SVPType.h"
#include "SVPPluginBase.h"
#include <GeneralCtrlPtr.h>
#include <QObject>
#include <QTimer>

class SVPPluginAppName :  public QObject, public SVPStatusbarPluginBase
{
	Q_OBJECT
public:
	SVPPluginAppName(SVPInt32 iIndex,const SVPChar* strPkgName, const SVPChar* strPluginName, ISVPBaseCtrl *pParent);
	virtual ~SVPPluginAppName();
	virtual SVPBool SetPos(SVPInt32 x,SVPInt32 y);
	virtual SVPBool SetVisible(SVPBool bVisible);
	virtual SVPLong PluginMsgProc(SVP_HANDLE hMsg, SVPUint32 message, SVPUint32 wParam, SVPLong lParam);
	SVPVoid UpdateAppName();

protected:
	virtual SVPVoid OnUpdateLanguage(SVPUint32 uiLGId);//language msg
	virtual SVPBool OnUpdateSystemTitle();//system title update msg

private:
signals:
	void SignalUpdateAppName();

private slots:
	void SlotSizeUpdate();
	void SlotUpdateAppName();

private:
	SVPStaticTextPtr m_pStaticTextCtrl;
	QTimer m_timerSetSize;
};

#endif /* SVPPLUGINAPPNAME_H_ */
