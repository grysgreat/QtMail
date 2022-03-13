#ifndef SENDMAIL_H
#define SENDMAIL_H

#include <QDialog>
#include <User.h>


namespace Ui {
class SendMail;
}

class SendMail : public QDialog
{
    Q_OBJECT

public:
    explicit SendMail(QWidget *parent = nullptr);
    ~SendMail();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SendMail *ui;
};

#endif // SENDMAIL_H
