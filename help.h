#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class HELP;
}

class HELP : public QDialog
{
    Q_OBJECT

public:
    explicit HELP(QWidget *parent = nullptr);
    ~HELP();

private:
    Ui::HELP *ui;
};

#endif // HELP_H
