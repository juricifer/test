#include <QtCore>
#include <QApplication>

#include "SVPView.h"
#include "SVPBaseCtrl.h"
#include "GeneralCtrlPtr.h"
#include "SVPPluginHome.h"

class TestDlg  : public SVPBaseCtrl, public ISVPPluginMsgNotify
{
//	Q_OBJECT

public:
	TestDlg(const SVPRect &rect, ISVPView *pView);
	virtual ~TestDlg();
	virtual SVPLong MsgNotify(SVPUint32 uMessage, SVPInt32 iIndex);

//private:
//	signals:
//	void signalSetPos();
//private slots:
//	void slotSetPos();

private:
	SVPBitmap m_bmpBkgnd;
	ISVPPluginBase* m_pPlugin;
	SVPInt32 m_nIndex;
};

TestDlg::TestDlg(const SVPRect &rect, ISVPView *pView)
: SVPBaseCtrl(0, SVP_NULL, rect, pView->GetHandle())
{
    pView->SetFramelessStyle();
    pView->Show(true);
    pView->SetGeometryRect(0, 0, 800, 50);
    pView->SetStayFlag(SVPViewStayOnTop);//设置置顶
    m_bmpBkgnd.Load("/app/statusbar/resource/TopBar.png");
    pView->SetBkgndBitmap(&m_bmpBkgnd);

//    connect(this, SIGNAL(signalSetPos()), this, SLOT(slotSetPos()));

    m_nIndex = SVP_GetPluginType();
    printf("Plugin Type = %d\n", m_nIndex);
    m_pPlugin = SVP_CreatePlugin(m_nIndex, "statusbar", "libstatusbarhome.so.1.0.0", (ISVPBaseCtrl *)this);//不能直接传this指针，否则SVPVoid型转换为ISVPBaseCtrl型时会直接把派生类TestDlg的入口地址转换为基类ISVPBaseCtrl的地址
}

TestDlg::~TestDlg()
{
    SVP_DestroyPlugin();
}

SVPLong TestDlg::MsgNotify(SVPUint32 uMessage, SVPInt32 iIndex)
{
	printf("TestDlg::MsgNotify(%u, %d) called\n", uMessage, iIndex);
	if (uMessage == MSG_ID_SIZE_UPDATE && iIndex == m_nIndex)
	{
//		emit signalSetPos();
		return SVP_TRUE;
	}
	return SVP_FALSE;
}

//SVPVoid TestDlg::slotSetPos()
//{
//	m_pPlugin->SetPos(0, 0);
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestDlg *pDlg = new TestDlg(SVPRect(0, 0, 800, 50), new SVPView());

    return a.exec();
}
