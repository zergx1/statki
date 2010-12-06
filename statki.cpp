#include "statki.h"
#include "ui_statki.h"

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);

    //USTAWIANIE PLANSZ
    ui->plansza_1->setRowCount(10); //  ustawia 10 pinowych pol (1-10)
    ui->plansza_2->setRowCount(10);

    ui->plansza_1->setColumnCount(10); // To samo co wyzej tylko ze poziomych (A-J)
    ui->plansza_2->setColumnCount(10);

    QStringList alfabet;
    alfabet << "A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J";

    ui->plansza_1->setHorizontalHeaderLabels(alfabet); // Ustawienie literek zamiast liczb na poziome pola
    ui->plansza_2->setHorizontalHeaderLabels(alfabet);

    ui->plansza_1->resizeRowsToContents(); // Ustawienie rozmiarow
    ui->plansza_1->resizeColumnsToContents();

    ui->plansza_2->resizeRowsToContents();
    ui->plansza_2->resizeColumnsToContents();
    // KONIEC USTAWIANIA PLANSZY
    
    ui->gb_wspol->hide();
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
