#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QAxObject>
#include <QAxWidget>
#include <QTextCodec>
#include <QtDebug>

int main(int argc, char *argv[])
{

        QApplication a(argc, argv);


//        QTextCodec *codec = QTextCodec::codecForName("UTF8");    //鑾峰彇绯荤粺缂栫爜
//        QTextCodec::setCodecForLocale(codec);
//        QTextCodec::setCodecForCStrings(codec);
//        QTextCodec::setCodecForTr(codec);
//        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));
//        QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
//        QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
        MainWindow w;
        w.show();
        return a.exec();


//    QApplication a(argc, argv);
//    //设置字体
//    QFont font("ZYSong18030",12);
//    a.setFont(font);
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
//    //主splitter，以下填充text和子splitter
//    QSplitter *splitterMain=new QSplitter(Qt::Horizontal,0);
//    QTextEdit *textLeft=new QTextEdit(QObject::tr("Left Widget"),splitterMain);
//    textLeft->setAlignment(Qt::AlignCenter);
//    QSplitter *splitterRight=new QSplitter(Qt::Vertical,splitterMain);
//    splitterRight->setOpaqueResize(false);
//    //开始填充右边的splitter，放上两个text
//    QTextEdit *textTop=new QTextEdit(QObject::tr("Right Top Widget"),splitterRight);
//    textTop->setAlignment(Qt::AlignCenter);
//    QTextEdit *textBottom=new QTextEdit(QObject::tr("Right Bottom Widget"),splitterRight);
//    textBottom->setAlignment(Qt::AlignCenter);
//    //设置主splitter
//    splitterMain->setStretchFactor(1,1);
//    splitterMain->setWindowTitle(QObject::tr("Splitter"));
//    splitterMain->show();
//    return a.exec();


}
