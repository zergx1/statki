#include "statki.h"
#include "ui_statki.h"

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);
}

statki::~statki()
{
    delete ui;
}

void statki::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
