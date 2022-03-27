#include "help.h"
#include "ui_help.h"
#include <QFile>
#include <QMessageBox>
#include<QTextStream>
HELP::HELP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HELP)
{
    ui->setupUi(this);
    QFile file(":/pics/help.html");

        if(!file.open(QFile::ReadOnly | QFile::Text))

            QMessageBox::information(NULL, QStringLiteral("提示"),

                                     QStringLiteral("打不开用户协议文件"));

        QTextStream textStream(&file);

        ui->textBrowser->setHtml(textStream.readAll());
}

HELP::~HELP()
{
    delete ui;
}
