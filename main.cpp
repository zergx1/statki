#include <QtGui/QApplication>
#include "statki.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    statki w;
    w.show();
    return a.exec();
}
