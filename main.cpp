#include <QtGui/QApplication>
#include "statki.h"

int main(int argc, char *argv[])
{
    int kurwa;
    QApplication a(argc, argv);
    statki w;
    w.show();
    return a.exec();
}
