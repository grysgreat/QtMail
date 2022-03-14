#ifndef TOAST_H
#define TOAST_H


#include <QObject>
#include <QRect>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>

class ToastDlg;

class Toast: QObject
{

public:

    static Toast& instance();
    void show(int i, const QString& text);
private:
    Toast();
    void timerEvent(QTimerEvent *event) override;
    ToastDlg* mDlg;
    int mTimerId{0};
    QRect mGeometry;
};

//————————————————
//版权声明：本文为CSDN博主「wwwlyj123321」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/wwwlyj123321/article/details/112391884
#endif // TOAST_H
