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
    string s = "from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject  ;
    ///TODO： 这里研究下格式化的问题
    ui->label->setText(QString::fromUtf8(&s[0]));
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
