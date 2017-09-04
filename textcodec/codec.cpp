#include <stdio.h>
#include <QApplication>
#include <QString>
#include <QByteArray>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QString qStr = "简体中文";
    QByteArray qBa1 = qStr.toAscii();
    QByteArray qBa2 = qStr.toLatin1();
    QByteArray qBa3 = qStr.toLocal8Bit();
    
    qDebug(qStr);
    printf("%s\n", qBa1.data());
    printf("%s\n", qBa2.data());
    printf("%s\n", qBa3.data());
    return app.exec();
}

