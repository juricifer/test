#include <QtGui>
#include <stdio.h>
#include <QTextCodec>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QString qString("hello world.");
    qDebug() << qString;

    QString qStr("��������");
    qDebug() << qStr;

    QString str = QString::fromUtf8("��������");
    qDebug() << str;

    return app.exec();
}
