#include "statki.h"
#include <exception>
#include "ui_statki.h"
#include <ctime>
#include <QMessageBox>

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);
    // CONNECTY
    connect(ui->pb_start,SIGNAL(clicked()),this,SLOT(start())); // DLA Guzika start
    connect(ui->pb_nowa,SIGNAL(clicked()),this,SLOT(nowa())); // DLA Guzika nowy
    connect(ui->plansza_1,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja(QTableWidgetItem *)));
    connect(ui->plansza_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja2(QTableWidgetItem *)));
    srand(time(NULL));


    //USTAWIANIE PLANSZ
    ui->plansza_1->setRowCount(10); // ustawia 10 pinowych pol (1-10)
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


    init();



}

void statki::start()
{
    if(ui->pb_start->text() == "Faza rozstawiania")
    {

        ui->gb_stat->setEnabled(true);
        ui->plansza_1->setEnabled(true);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Rozpocznij gre"));
        cpurozstaw();
        ui->pb_start->setEnabled(false);
        ui->plansza_2->setEnabled(false);
    }
    else if(ui->pb_start->text() == "Rozpocznij gre")
    {

        ui->gb_stat->setEnabled(false);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Zatrzymaj"));
    }
    else if(ui->pb_start->text() == "Zatrzymaj")
    {

        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(false);
        ui->plansza_2->setEnabled(false);
        ui->pb_start->setText(tr("Konntynuj"));
    }
    else if(ui->pb_start->text() == "Konntynuj")
    {

        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(true);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Zatrzymaj"));
    }

}

void statki::nowa()
{
    init();
}

void statki::akcja(QTableWidgetItem *item)
{


    QTableWidgetItem *temp;
    int pol = 0;
    bool ustaw = true;
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


        ustaw = czyustawic(item,pol);

        if(ustaw){

            if (ui->rb_4->isChecked())
            {
                m4--;
                if(m4==0){
                    ui->rb_4->setChecked(false);
                    ui->rb_4->setEnabled(false);
                }
            }
            else if (ui->rb_3->isChecked())
            {
                m3 -= 1;
                if(m3==0){
                    ui->rb_3->setChecked(false);
                    ui->rb_3->setEnabled(false);
                }
            }
            else if (ui->rb_2->isChecked())
            {
                m2--;
                if(m2==0){
                    ui->rb_2->setChecked(false);
                    ui->rb_2->setEnabled(false);
                }
            }
            else if (ui->rb_1->isChecked())
            {
                m1--;
                if(m1==0){
                    ui->rb_1->setChecked(false);
                    ui->rb_1->setEnabled(false);
                }
            }

        for(int i=0;i<pol;i++)
        {
            if(ui->rb_pion->isChecked())
                temp = ui->plansza_1->item(item->row()+i,item->column());
            else if(ui->rb_poziom->isChecked())
                temp = ui->plansza_1->item(item->row(),item->column()+i);
            //temp->setText(tr("X"));
            temp->setBackgroundColor(Qt::gray);

        }}
        if(ui->rb_2->isEnabled() == false and ui->rb_1->isEnabled() == false and ui->rb_3->isEnabled() == false and ui->rb_4->isEnabled() == false )
            ui->pb_start->setEnabled(true);
    }




}

bool statki::czyustawic(QTableWidgetItem *item,int pol)
{

    int pocz = 0;
    if(ui->rb_pion->isChecked())
        pocz = item->row() + pol;
    else if(ui->rb_poziom->isChecked())
        pocz = item->column()+pol;

    if(pocz > 10 or pocz<-1)
        return false;

    for(int i=-1;i<pol+1;i++)
    {
        if(ui->rb_pion->isChecked()){
            if( item->row()+i > 9 or item->row()+i < 0)
                continue;
            if(ui->plansza_1->item(item->row()+i,item->column())->backgroundColor() == Qt::gray)
                return false;
            if(item->column()+1 < 10 ) // sprawdz czy miesic sie w kolumnach
                if(ui->plansza_1->item(item->row()+i,item->column()+1)->backgroundColor() == Qt::gray) //jesli tak to sprawdz dopiero item
                    return false;
            if(item->column()-1 > -1 )
                if(ui->plansza_1->item(item->row()+i,item->column()-1)->backgroundColor() == Qt::gray)
                    return false;
            if(item->row()-1 > -1)
                if(ui->plansza_1->item(item->row()-1,item->column())->backgroundColor() == Qt::gray)
                    return false;
            if(item->row()+pol < 10)
                if(ui->plansza_1->item(item->row()+pol,item->column())->backgroundColor() == Qt::gray)
                    return false;


        }
                    else if(ui->rb_poziom->isChecked()){
            if( item->column()+i > 9 or item->column()+i < 0)
                continue;
            if(ui->plansza_1->item(item->row(),item->column()+i)->backgroundColor() == Qt::gray)
                return false;
            if(item->row()+1 < 10 ) // sprawdz czy miesic sie w kolumnach
                if(ui->plansza_1->item(item->row()+1,item->column()+i)->backgroundColor() == Qt::gray) //jesli tak to sprawdz dopiero item
                    return false;
            if(item->row()-1 > -1 )
                if(ui->plansza_1->item(item->row()-1,item->column()+i)->backgroundColor() == Qt::gray)
                    return false;
            if(item->column()-1 > -1)
                if(ui->plansza_1->item(item->row(),item->column()-1)->backgroundColor() == Qt::gray)
                    return false;
            if(item->column()+pol < 10)
                if(ui->plansza_1->item(item->row(),item->column()+pol)->backgroundColor() == Qt::gray)
                    return false;
        }
    }
    return true;

}

void statki::akcja2(QTableWidgetItem *item)
{
    if(item->text() != "X"){
        if(item->text() == " "){
            item->setBackgroundColor(Qt::gray);
            zycie2--;


        }
        item->setText(tr("X"));
        cpustrzel();

    }
    if(zycie2 == 0)
    {
        QMessageBox::warning(this, tr("Statki"),tr("You win! Good Job"),QMessageBox::Ok);
        init();
    }
    else if(zycie1 == 0)
    {
        QMessageBox::warning(this, tr("Statki"),tr("You lose, Sorry"),QMessageBox::Ok);
        init();
    }

}

void statki::cpustrzel()
{
    int los = rand()% itemLists1.length();
    if(los != 0){
    itemLists1.at(los)->setText(tr("X"));
    itemLists1.removeAt(los);
    if(itemLists1.at(los)->backgroundColor() == Qt::gray)
        zycie1--;
}

}

void statki::cpurozstaw()
{

    QList<QTableWidgetItem *> templist;
    templist = itemLists2;

    int tm4,tm3,tm2,tm1;
    tm4 = m4;
    tm3 = m3;
    tm2 = m2;
    tm1 = m1;

    int los;
    int pion;
    bool ustaw;
    QTableWidgetItem *temp,*item;



    while((tm4+tm3+tm2+tm1) != 0)
    {
        los = rand()%templist.length();
        pion = rand()%2;
        item = templist.at(los);

        if (tm4>0)
        {
            ustaw = czyustawic2(item,4,pion);
            if(ustaw)
            {
                for(int i=0;i<4;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);
                    //temp->setText(tr("X"));

                    temp->setText(tr(" "));
                    temp->setBackgroundColor(Qt::red);



                }
                tm4--;

            }
           

        }
        if (tm3>0)
        {
            ustaw = czyustawic2(item,3,pion);
            if(ustaw)
            {
                for(int i=0;i<3;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);
                    //temp->setText(tr("X"));

                    temp->setText(tr(" "));
                    temp->setBackgroundColor(Qt::red);


                }
                tm3--;

            }


        }
        if (tm2>0)
        {
            ustaw = czyustawic2(item,2,pion);
            if(ustaw)
            {
                for(int i=0;i<2;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);
                    //temp->setText(tr("X"));

                    temp->setText(tr(" "));
                    temp->setBackgroundColor(Qt::red);


                }
                tm2--;

            }


        }
        if (tm1>0)
        {
            ustaw = czyustawic2(item,1,pion);
            if(ustaw)
            {
                for(int i=0;i<1;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);
                    //temp->setText(tr("X"));

                    temp->setText(tr(" "));
                    temp->setBackgroundColor(Qt::red);


                }
                tm1--;

            }


        }

    }

}

bool statki::czyustawic2(QTableWidgetItem *item,int pol,int pion)
{

    int pocz = 0;
    if(ui->rb_pion->isChecked())
        pocz = item->row() + pol;
    else if(ui->rb_poziom->isChecked())
        pocz = item->column()+pol;

    if(pocz > 10 or pocz<-1)
        return false;

    for(int i=-1;i<pol+1;i++)
    {
        if(pion == 0){
            if( item->row()+i > 9 or item->row()+i < 0)
                continue;
            if(ui->plansza_2->item(item->row()+i,item->column())->text() == " ")
                return false;
            if(item->column()+1 < 10 ) // sprawdz czy miesic sie w kolumnach
                if(ui->plansza_2->item(item->row()+i,item->column()+1)->text() == " ") //jesli tak to sprawdz dopiero item
                    return false;
            if(item->column()-1 > -1 )
                if(ui->plansza_2->item(item->row()+i,item->column()-1)->text() == " ")
                    return false;
            if(item->row()-1 > -1)
                if(ui->plansza_2->item(item->row()-1,item->column())->text() == " ")
                    return false;
            if(item->row()+pol < 10)
                if(ui->plansza_2->item(item->row()+pol,item->column())->text() == " ")
                    return false;


        }
                    else if(pion == 1){
            if( item->column()+i > 9 or item->column()+i < 0)
                continue;
            if(ui->plansza_2->item(item->row(),item->column()+i)->text() == " ")
                return false;
            if(item->row()+1 < 10 ) // sprawdz czy miesic sie w kolumnach
                if(ui->plansza_2->item(item->row()+1,item->column()+i)->text() == " ") //jesli tak to sprawdz dopiero item
                    return false;
            if(item->row()-1 > -1 )
                if(ui->plansza_2->item(item->row()-1,item->column()+i)->text() == " ")
                    return false;
            if(item->column()-1 > -1)
                if(ui->plansza_2->item(item->row(),item->column()-1)->text() == " ")
                    return false;
            if(item->column()+pol < 10)
                if(ui->plansza_2->item(item->row(),item->column()+pol)->text() == " ")
                    return false;
        }
    }
    return true;

}

void statki::init()
{

    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {

            ui->plansza_1->removeCellWidget(i,j);
            ui->plansza_2->removeCellWidget(i,j);

        }


     itemLists1.clear(); // to dziala tak samo jak wektor
     itemLists2.clear();


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

     m4=1;
     m3=2;
     m2=3;
     m1=4;

     zycie1 =  4*m4+3*m3+2*m2+1*m1;
     zycie2 =4*m4+3*m3+2*m2+1*m1;


     ui->rb_4->setChecked(true);
     ui->rb_pion->setChecked(true);
     ui->gb_stat->setEnabled(false);
     ui->plansza_1->setEnabled(false);
     ui->plansza_2->setEnabled(false);

     ui->pb_start->setText(tr("Faza rozstawiania"));
     ui->pb_start->setEnabled(true);

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

