#ifndef SVPCAMERAAPP_H
#define SVPCAMERAAPP_H

#include <app/ISVPAppBase.h>
#include "SVPCameraDlg.h"


class SVPCameraApp : public ISVPAppBase
{
public:
	SVPCameraApp(SVPInt32 iAppIndex);
	virtual ~SVPCameraApp();

	virtual SVPBool InitGUI();
	virtual SVPBool InitAppBase();
	virtual SVPBool UnInitAppBase();
	virtual SVPBool OnSwitchToFg();
	virtual SVPBool OnSwitchToBg(SVPBool bOverlap);
	virtual SVPBool OnCheckAppActive(SVPAppActiveCase eCase);
private:
	SVPCameraDlg* m_pDlg;
};

#endif // SVPCAMERAAPP_H
