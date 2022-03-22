
#include <QApplication>
#include "qmailbegin.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置中文字体
     a.setFont(QFont("Microsoft Yahei", 9));

 //设置中文编码
 #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
 #if _MSC_VER
     QTextCodec *codec = QTextCodec::codecForName("gbk");
 #else
     QTextCodec *codec = QTextCodec::codecForName("utf-8");
 #endif
     QTextCodec::setCodecForLocale(codec);
     QTextCodec::setCodecForCStrings(codec);
     QTextCodec::setCodecForTr(codec);
 #else
     QTextCodec *codec = QTextCodec::codecForName("utf-8");
     //QTextCodec *codec = QTextCodec::codecForName("GBK");
     QTextCodec::setCodecForLocale(codec);
 #endif

    QMailbegin b;
    b.show();

    return a.exec();
}
