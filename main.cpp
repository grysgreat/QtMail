
#include <QApplication>
#include "Qmailbegin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QMailbegin b;
    b.show();

    return a.exec();
}
