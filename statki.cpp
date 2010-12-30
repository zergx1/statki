#include "statki.h"
#include "ui_statki.h"

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);
    // CONNECTY
    connect(ui->pb_start,SIGNAL(clicked()),this,SLOT(start())); // DLA Guzika start
    connect(ui->plansza_1,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja(QTableWidgetItem *)));

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


    // USTAWIENIE KOMOREK I WLEPIENIE ICH DO PLANSZ
    QList<QTableWidgetItem *> itemLists1; // to dziala tak samo jak wektor
    QList<QTableWidgetItem *> itemLists2;

    for(int i=0;i<100;i++)
    {
        QTableWidgetItem *test = new QTableWidgetItem();
        test->setBackgroundColor(Qt::blue);
        itemLists1.push_front(test);

        QTableWidgetItem *test2 = new QTableWidgetItem();
        test2->setBackgroundColor(Qt::blue);
        itemLists2.push_front(test2);
    }
    int k=-1;

    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            k+=1;
            ui->plansza_1->setItem(i,j,itemLists1[k]);
            ui->plansza_2->setItem(i,j,itemLists2[k]);
        }
    // KONIEC WLEPIANIA KOMOREK DO PLANSZ

   // ui->plansza_1->setCurrentCell(0,0,QItemSelectionModel::Select);
   // ui->plansza_1->setCurrentCell(0,1,QItemSelectionModel::Select);




    //ui->plansza_1->setItem(0, 0, test);
   // ui->plansza_1->setItem(1, 1, test1);


    // KONIEC USTAWIANIA PLANSZY


    // ustawienia poczatkowe
    ui->gb_wspol->setEnabled(false);
    ui->gb_stat->setEnabled(false);
    ui->plansza_1->setEnabled(false);
    ui->plansza_2->setEnabled(false);
    


}

void statki::start()
{
    if(ui->pb_start->text() == "Faza rozstawiania")
    {
        ui->gb_wspol->setEnabled(false);
        ui->gb_stat->setEnabled(true);
        ui->plansza_1->setEnabled(true);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Rozpocznij gre"));
    }
    else if(ui->pb_start->text() == "Rozpocznij gre")
    {
        ui->gb_wspol->setEnabled(true);
        ui->gb_stat->setEnabled(false);
        ui->pb_start->setText(tr("Zatrzymaj"));
    }
    else if(ui->pb_start->text() == "Zatrzymaj")
    {
        ui->gb_wspol->setEnabled(false);
        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(false);
        ui->plansza_2->setEnabled(false);
        ui->pb_start->setText(tr("Konntynuj"));
    }
    else if(ui->pb_start->text() == "Konntynuj")
    {
        ui->gb_wspol->setEnabled(true);
        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(true);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Zatrzymaj"));
    }

}

void statki::akcja(QTableWidgetItem *item)
{
    QTableWidgetItem *temp;
    int pol = 0;
    if (ui->pb_start->text() == "Rozpocznij gre")
    {
        if (ui->rb_4->isChecked())
            pol = 4;
        else if (ui->rb_3->isChecked())
            pol = 3;
        else if (ui->rb_2->isChecked())
            pol = 2;
        else if (ui->rb_1->isChecked())
            pol = 1;

        item->setText(tr("#"));
        item->setBackgroundColor(Qt::green);

        for(int i=0;i<pol;i++)
        {
            temp = ui->plansza_1->item(item->row()+i,item->column());
            temp->setText(tr("X"));
            temp->setBackgroundColor(Qt::green);


        }
    }




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
