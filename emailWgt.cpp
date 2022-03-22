#include "emialWgt.h"


emailWgt::emailWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emailWgt)
{
    ui->setupUi(this);
}

emailWgt::emailWgt(Email e,QWidget *parent ):
    QWidget(parent),
    ui(new Ui::emailWgt)
{
    ui->setupUi(this);
    string s = "from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject  ;
    ui->label->setText(QString::fromUtf8(&s[0]));

}
emailWgt::~emailWgt()
{
    delete ui;
}
