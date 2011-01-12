#include "statki.h"
#include <exception>
#include "ui_statki.h"
#include <ctime>
#include <QMessageBox>
#include <QThread>

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);
    // CONNECTY
    connect(ui->pb_start,SIGNAL(clicked()),this,SLOT(start())); // DLA Guzika start
    connect(ui->pb_nowa,SIGNAL(clicked()),this,SLOT(nowa())); // DLA Guzika nowy
    connect(ui->losowy,SIGNAL(clicked()),this,SLOT(losowy_strzal()));//dla guzika losowy strzal
    connect(ui->plansza_1,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja(QTableWidgetItem *)));
    connect(ui->plansza_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja2(QTableWidgetItem *)));
    connect(ui->actionAutorzy,SIGNAL(triggered()),this,SLOT(autorzy()));
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
    ui->plansza_2->resizeRowsToContents(); // Ustawienie rozmiarow
    ui->plansza_2->resizeColumnsToContents();

    ui->plansza_1->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->plansza_1->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->plansza_2->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->plansza_2->horizontalHeader()->setResizeMode(QHeaderView::Fixed);

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
        ui->pb_start->setEnabled(false);
        ui->plansza_2->setEnabled(false);
        cpurozstaw();
    }
    else if(ui->pb_start->text() == "Rozpocznij gre")
    {
        ui->gb_stat->setEnabled(false);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Zatrzymaj"));
        ui->losowy->setEnabled(true);
    }
    else if(ui->pb_start->text() == "Zatrzymaj")
    {

        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(false);
        ui->plansza_2->setEnabled(false);
        ui->pb_start->setText(tr("Konntynuj"));
        ui->losowy->setEnabled(false);
    }
    else if(ui->pb_start->text() == "Konntynuj")
    {

        ui->gb_stat->setEnabled(false);
        ui->plansza_1->setEnabled(true);
        ui->plansza_2->setEnabled(true);
        ui->pb_start->setText(tr("Zatrzymaj"));
        ui->losowy->setEnabled(true);
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
    if(item->backgroundColor()!=Qt::red && item->backgroundColor()!=Qt::darkBlue){            //zeby nie marnowac strzalu w to samo miejsce
        if(item->text() == " "){
            ui->progressBar->setValue(ui->progressBar->value()+5);
            item->setBackgroundColor(Qt::red);
            zycie2--;
        }
        else
            item->setBackground(Qt::darkBlue);

        //item->setText(tr("X"));
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

void statki::losowy_strzal()
{
    int los;
    bool warunek=true;
    do
    {
    los=rand()%itemLists2.length();
    if(itemLists2.at(los)->backgroundColor()!=Qt::red && itemLists2.at(los)->backgroundColor()!=Qt::darkBlue && itemLists2.at(los)->backgroundColor()!=Qt::darkRed)
    {            //zeby nie marnowac strzalu w to samo miejsce
        if(itemLists2.at(los)->text() == " ")
        {
            ui->progressBar->setValue(ui->progressBar->value()+5);
            itemLists2.at(los)->setBackgroundColor(Qt::red);
            zycie2--;
        }
        else
            itemLists2.at(los)->setBackground(Qt::darkBlue);


        cpustrzel();
        warunek=false;

    }
    itemLists2.removeAt(los);
    }
    while(warunek);


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
przeszukuj();   //dotyczy uzytkownika dodane tu z lenistwa

    if(zat==true)
    {
        bool bufor,bufor2;
        do
        {
            los1=rand()% itemLists1.length();
            r=itemLists1.at(los1)->row();
            c=itemLists1.at(los1)->column();
            bufor=traf;
            traf=false;

            if(sprawdz(r,c,2)==false)
            {
                itemLists1.removeAt(los1);
                bufor2=true;
            }
            else
                bufor2=false;

            traf=bufor;
        }
        while(bufor2);


        if(itemLists1.at(los1)->backgroundColor() == Qt::gray)
        {
            zycie1--;
            traf=true;
            itemLists1.at(los1)->setBackgroundColor(Qt::red);
            ui->progressBar_2->setValue(ui->progressBar_2->value()+5);
                if(zatopiony(r,c)==1)
                    zat=true;
                else
                {
                    if(zatopiony(r,c)==2)
                    {
                        pomoc=true;
                        r2=itemLists1.at(los1)->row();
                        c2=itemLists1.at(los1)->column();
                    }
                        zat=false;
                }

        }
        else
        {
            itemLists1.at(los1)->setBackgroundColor(Qt::darkBlue);
        }

        itemLists3.clear();
        itemLists1.removeAt(los1);
    }
    else        //w poprzednim strzale statek nie zosta³ zatopiony
    {
        if(traf==true)
        {
            itemLists3.clear();
            if(sprawdz(r-1,c,2)){itemLists3.push_front(ui->plansza_1->item(r-1,c));}
            if(sprawdz(r+1,c,2)){itemLists3.push_front(ui->plansza_1->item(r+1,c));}
            if(sprawdz(r,c-1,2)){itemLists3.push_front(ui->plansza_1->item(r,c-1));}
            if(sprawdz(r,c+1,2)){itemLists3.push_front(ui->plansza_1->item(r,c+1));}
        }
        if(pomoc==true)
        {
            bufor.clear();
            if(sprawdz(r2-1,c2,2)){bufor.push_front(ui->plansza_1->item(r2-1,c2));}
            if(sprawdz(r2+1,c2,2)){bufor.push_front(ui->plansza_1->item(r2+1,c2));}
            if(sprawdz(r2,c2-1,2)){bufor.push_front(ui->plansza_1->item(r2,c2-1));}
            if(sprawdz(r2,c2+1,2)){bufor.push_front(ui->plansza_1->item(r2,c2+1));}

        }

        los1=rand()%itemLists3.length();
        r=itemLists3.at(los1)->row();
        c=itemLists3.at(los1)->column();


        if(itemLists3.at(los1)->backgroundColor() == Qt::gray)
        {
            zycie1--;
            traf=true;
            itemLists3.at(los1)->setBackgroundColor(Qt::red);
            ui->progressBar_2->setValue(ui->progressBar_2->value()+5);
        }
        else
        {
            itemLists3.at(los1)->setBackgroundColor(Qt::darkBlue);
            traf=false;
        }
        itemLists3.removeAt(los1);
        los1=szukaj(r,c);
        itemLists1.removeAt(los1);

        if(zatopiony(r,c)==1 && traf==true && pomoc==false)
            zat=true;
        else
        {
            if(pomoc==true && zatopiony(r,c)==1)
            {
                itemLists3.clear();
                itemLists3=bufor;
                pomoc=false;
                traf=false;
                r=r2;
                c=c2;
            }
            else
            {
                if(zatopiony(r,c)==1 && pomoc==false && traf==true){zat=true;}
            }
        }
    }




}

void statki::przeszukuj()
{

    int r,c,ilosc;
    for(int i=0;i<=9;i++)
    {
         //ui->plansza_2->item(2,2)->setBackgroundColor(Qt::black);
        r=0;
        c=0;
        if(tablica[2][i]>0)
        {
            r=tablica[2][i];
            ilosc=r;
        }
        else
        {
            if(tablica[3][i]>0)
            {
                c=tablica[3][i];
                ilosc=c;
            }
        }

        while(r+c>0)
        {
            if(r>0){r--;}
            if(c>0){c--;}
            if(ui->plansza_2->item(tablica[0][i]+r,tablica[1][i]+c)->backgroundColor()==Qt::red ){ilosc--;}

        }
        if(ilosc==0)
        {

            r=tablica[2][i];
            c=tablica[3][i];
            while(r+c>0)
            {
                if(r>0){r--;}
                if(c>0){c--;}
                ui->plansza_2->item(tablica[0][i]+r,tablica[1][i]+c)->setBackgroundColor(Qt::darkRed);

            }
        }
    }
}

bool statki::sprawdz(int row, int col, int tryb)
{
    if(row<0 || row>9 || col<0 || col>9){return false;}
    if(ui->plansza_1->item(row,col)->backgroundColor()==Qt::red)
    {

        return false;
    }

    if(tryb==2 && ui->plansza_1->item(row,col)->backgroundColor()==Qt::darkBlue){return false;}

        int ilosc;

        if(traf==true || zat==false)
            ilosc=1;
        else
            ilosc=0;

    for(int r=-1;r<=1;r++)
    {
        for(int c=-1;c<=1;c++)
        {
            if(row==0 && r==-1){r=0;}
            if(col==0 && c==-1){c=0;}

            if(ui->plansza_1->item(row+r,col+c)->backgroundColor()==Qt::red){ilosc--;}

            if(col==9 && c==0){c=2;}
        }
        if(row==9 && r==0){r=2;}
    }

    if(ilosc>=0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int statki::zatopiony(int row, int col)
{
    int ilosc=0;
    for(int r=-1;r<=1;r++)
    {
        for(int c=-1;c<=1;c++)
        {
            if(row==0 && r==-1){r=0;}
            if(col==0 && c==-1){c=0;}

            if(ui->plansza_1->item(row+r,col+c)->backgroundColor()==Qt::gray)
                ilosc++;

            if(col==9 && c==0){c=2;}
        }
        if(row==9 && r==0){r=2;}
    }
    if(ilosc>=2)
        return 2;
    else
    {
    if(ilosc==1)
        return false;       //0
    else
        return true;        //1
    }
}

int statki::szukaj(int row, int col)
{
for(int i=0;i<=100;i++)
    {
    if(i<itemLists1.length())
    {
            if(itemLists1.at(i)->row()==row && itemLists1.at(i)->column()==col)
             {
                return (i);
            }
     }

    }
return -1;  //blad
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
    int pion,pion1;
    bool ustaw;

    QTableWidgetItem *temp,*item;

    while((tm4+tm3+tm2+tm1) != 0)
    {
        los = rand()%templist.length();
        pion = rand()%2;
        item = templist.at(los);
        if(pion==0){pion1=1;}
        else
        pion1=0;
        //czteromasztowce
        if (tm4>0)
        {
            ustaw = czyustawic2(item,4,pion);
            if(ustaw)
            {
                tablica[0][0]=item->row();
                tablica[1][0]=item->column();
                tablica[2][0]=pion1*4;
                tablica[3][0]=pion*4;

                for(int i=0;i<4;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);


                    temp->setText(tr(" "));
                   // temp->setBackgroundColor(Qt::gray);
                }

                tm4--;
            }

        }

        //trzymasztowce
        if (tm3>0)
        {
            ustaw = czyustawic2(item,3,pion);
            if(ustaw)
            {
                tablica[0][tm3]=item->row();
                tablica[1][tm3]=item->column();
                tablica[2][tm3]=pion1*3;
                tablica[3][tm3]=pion*3;
                for(int i=0;i<3;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);
                    temp->setText(tr(" "));
                    //temp->setBackgroundColor(Qt::gray);
                }
                tm3--;

            }
        }

        //dwumasztowce
        if (tm2>0)
        {
            ustaw = czyustawic2(item,2,pion);
            if(ustaw)
            {
                tablica[0][6-tm2]=item->row();
                tablica[1][6-tm2]=item->column();
                tablica[2][6-tm2]=pion1*2;
                tablica[3][6-tm2]=pion*2;
                for(int i=0;i<2;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);

                    temp->setText(tr(" "));
                    //temp->setBackgroundColor(Qt::gray);
                }
                tm2--;

            }
        }

        //jednomasztowce
        if (tm1>0)
        {
            ustaw = czyustawic2(item,1,pion);
            if(ustaw)
            {
                tablica[0][10-tm1]=item->row();
                tablica[1][10-tm1]=item->column();
                tablica[2][10-tm1]=pion1*1;
                tablica[3][10-tm1]=pion*1;
                for(int i=0;i<1;i++)
                {
                    if(pion==0)
                        temp = ui->plansza_2->item(item->row()+i,item->column());
                    else if(pion==1)
                        temp = ui->plansza_2->item(item->row(),item->column()+i);

                    temp->setText(tr(" "));
                    //temp->setBackgroundColor(Qt::gray);
                }
                tm1--;

            }
        }

    }

}

bool statki::czyustawic2(QTableWidgetItem *item,int pol,int pion)
{

    int pocz = 0;
    if(pion==0) //pion==0 czyli pionowo
        pocz = item->row() + pol;
    else        //pion==1 czyli poziomo
        pocz = item->column()+pol;

    if(pocz > 10 or pocz<0)
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

     traf=false;
     zat=true;
     pomoc=false;
     ui->losowy->setEnabled(false);
     ui->progressBar->reset();
     ui->progressBar_2->reset();
     ui->progressBar->setValue(0);
     ui->progressBar_2->setValue(0);



     ui->rb_4->setChecked(true);
     ui->rb_4->setEnabled(true);
     ui->rb_3->setEnabled(true);
     ui->rb_2->setEnabled(true);
     ui->rb_1->setEnabled(true);
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

void statki::autorzy()
{
    QMessageBox::about(this, tr("Autorzy"),
                                tr("<center><h2>GRA STATKI</h2></center>"
                                "<p><b>Autorzy:</b><p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Artur Duszyñski<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Adam Kunikowski&nbsp;&nbsp;&nbsp;&nbsp;"
                                "<p><b>Wersja:</b><p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.002b"
                                "<p><b>Data:</b><p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.01.2010&nbsp;&nbsp;&nbsp;&nbsp;"
                                "                     "
                                ));
}

