#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString qString("hello world.");
    qDebug() << qString;

    QString qStr("简体中文");
    qDebug() << qStr;

    return app.exec();
}
