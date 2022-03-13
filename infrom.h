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

public slots:
    void iscloseed();


private slots:
    void on_wqeww_clicked();
    void on_infrom_destroyed();


private:
    Ui::infrom *ui;
};

#endif // INFROM_H
