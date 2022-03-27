#include "emialWgt.h"


emailWgt::emailWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emailWgt)
{
    ui->setupUi(this);
}

emailWgt::emailWgt( int ids,Email e,QWidget *parent ):
    QWidget(parent),
    ui(new Ui::emailWgt)
{
    this->id =ids;
    ui->setupUi(this);
    string s1 = "from:" + e.from  ;
    string s2 = "    date:" + e.date ;
    string s3 = "    sub: " + e.subject  ;
    ///TODO： 这里研究下格式化的问题
    ui->label->setText(QString::fromUtf8(&s2[0]));
    ui->label_4->setText(QString::fromUtf8(&s3[0]));
    ui->label_5->setText(QString::fromUtf8(&s1[0]));
    if(e.star){
        ui->pushButton_star->setText("★");
    }else {
         ui->pushButton_star->setText("☆");
    }

}
emailWgt::~emailWgt()
{
    delete ui;
}

bool emailWgt::isCheck(){
    return ui->checkBox->isChecked();
}


void emailWgt::on_pushButton_star_clicked(){

    if(ui->pushButton_star->text()=="★"){
        ui->pushButton_star->setText("☆");
    }else{
       ui->pushButton_star->setText("★");
    }

    emit this->chagestar(this->id);
}
