#include "statki.h"
#include <exception>
#include "ui_statki.h"
#include <ctime>

statki::statki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statki)
{
    ui->setupUi(this);
    // CONNECTY
    connect(ui->pb_start,SIGNAL(clicked()),this,SLOT(start())); // DLA Guzika start
    connect(ui->plansza_1,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja(QTableWidgetItem *)));
    //connect(ui->plansza_2,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(akcja(QTableWidgetItem *)));

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
    ui->rb_4->setChecked(true);
    ui->rb_pion->setChecked(true);
    ui->gb_stat->setEnabled(false);
    ui->plansza_1->setEnabled(false);
    ui->plansza_2->setEnabled(false);

    m4=1;
    m3=2;
    m2=3;
    m1=4;
    


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
        rozstaw();
    }
    else if(ui->pb_start->text() == "Rozpocznij gre")
    {

        ui->gb_stat->setEnabled(false);

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
    QTableWidgetItem *temp,*temp2;
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
bool statki::czyustawic1(int x,int y,int p,int m)
{
    QTableWidgetItem *temp;
                if(p==0)
                {       //w pionie
                    if(y+m<=10) //czy sie zmiesci w pionie
                    {
                            for(int i=-1;i<=m;i++)
                            {
                                if(y==0)
                                {
                                    i=0;
                                }              //¿eby nie sprawdzaæ nad
                                for(int j=-1;j<=1;j++)
                                {
                                    if(x==0){j=0;}          //¿eby nei sprawdzaæ z lewej

                                    temp=ui->plansza_2->item(y+i,x+j);
                                    if(temp->backgroundColor()==Qt::red)
                                        return false;
                                    else
                                        temp->setBackgroundColor(Qt::green);
                                    if(y+m==10 && i==m-1){i=5;}         //¿eby nie sprawdzaæ pod
                                    if(x==9 && j==0){j=2;}  //¿eby nie sprawdzaæ z prawej
                                }
                            }
                    }
                    else
                        return false;
                }
                else
                {       //w poziomie
                    if(x+m<=10) //czy sie zmiesci w poziomie
                    {
                            for(int i=-1;i<=m;i++)
                            {
                                if(x==0){i=0;}              //¿eby nie sprawdzaæ z lewej
                                for(int j=-1;j<=1;j++)
                                {
                                    if(y==0){j=0;}          //¿eby nei sprawdzaæ z góry
                                    temp=ui->plansza_2->item(y+i,x+j);
                                    if(temp->backgroundColor()==Qt::red)
                                        return false;
                                    else
                                        temp->setBackgroundColor(Qt::green);
                                    if(y==9 && j==0){j=2;}         //¿eby nie sprawdzaæ pod
                                    if(x==9){i=5;}                 //¿eby nie sprawdzaæ z prawej
                                }
                            }
                    }
                    else
                        return false;
                }
        return true;
}


void statki::rozstaw()
{
    srand(time(NULL));
    bool koniec =true;
    int koniec1,x,y,p;
    koniec1=10;
    QTableWidgetItem *temp;
    while(koniec)
    {
    p=rand()%2;         //losujemy czy w pionie=0 czy poziomie=1
    x=rand()%10;
    y=rand()%10;

    if(koniec1==10)
            koniec=false;
        else
            koniec1--;


        if(czyustawic1(3,0,0,1)==true)  // na ta chwile na sztywno probujemy sprawddzic pole kolumna=3 rzad=0 dla jednomasztowca ustawionego pionowo
        {
        temp=ui->plansza_2->item(1,1);
        temp->setBackgroundColor(Qt::red);
        //temp->setText(" ");
        temp->setText(QString::number(koniec1));
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
