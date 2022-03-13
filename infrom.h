#ifndef INFROM_H
#define INFROM_H

#include <QDialog>

namespace Ui {
class infrom;
}

class infrom : public QDialog
{
    Q_OBJECT

public:
    explicit infrom(QWidget *parent = nullptr);
    ~infrom();

private slots:
    void on_wqeww_clicked();

private:
    Ui::infrom *ui;
};

#endif // INFROM_H
