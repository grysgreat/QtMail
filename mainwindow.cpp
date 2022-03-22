#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>

#include "QMessageBox"
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_wqeww_clicked()
{
    int argc = 4;
    char* argv[10];
    argv[0]="myemail ";
    argv[1]="bind";
    string s=ui->textEdit->toPlainText().toStdString();
    argv[2]=&s[0];
    string s2=ui->textEdit_2->toPlainText().toStdString();
    argv[3]=&s2[0];
    //int flag = fx(argc,argv);
    if(1){
        QMessageBox::information(this, tr("success"),  tr("生成个人信息成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    } else {
        QMessageBox::critical(this, tr("error"),  tr("生成个人信息失败"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    }



}
