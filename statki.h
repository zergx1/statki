#ifndef STATKI_H
#define STATKI_H

#include <QMainWindow>
#include <QTableWidgetItem>


namespace Ui {
    class statki;
}

class statki : public QMainWindow {
    Q_OBJECT
public:
    statki(QWidget *parent = 0);
    ~statki();
    bool czyustawic(QTableWidgetItem *item,int pol); // sprawdza pola czy moze ustawic kolejny statek
    bool czyustawic2(QTableWidgetItem *item,int pol,int pion);
    bool sprawdz(int row,int col,int tryb);     //tryb=0 na tym polu, tryb=1 rowniez na sasiednich
    int zatopiony(int row,int col);            //sprawdza czy statek zosta³ zatopiony
    int szukaj(int row,int col);    //szuka numeru itemu o wspolrzednych row, col w liscie
    void przeszukuj();              //oznacza zatopiony statek komputera na czarno
    void rozstaw();   //rozstawia statki komputera
    void cpustrzel();
    void cpurozstaw();
    void init();

public slots:
    void start();
    void nowa();
    void akcja(QTableWidgetItem *item);
    void akcja2(QTableWidgetItem *item);
    void losowy_strzal();
    void autorzy();



protected:
    void changeEvent(QEvent *e);

private:
    Ui::statki *ui;
    int m4,m3,m2,m1;
    QList<QTableWidgetItem *> itemLists1; // to dziala tak samo jak wektor
    QList<QTableWidgetItem *> itemLists2;
    QList<QTableWidgetItem *> itemLists3;   //dla inteligentnych strza³ow komputera
    QList<QTableWidgetItem *> bufor;     //taka ma³a pomoc dla pewnego wyj¹tku
    int tablica[4][10];         //potrzebne aby wiedziec kiedy statek jest zatopiony
    int zycie1,zycie2;
    int los1;          //potrzebne do inteligencji cpu
    int r,c,r2,c2;    //ostatni strzal komputera r-row (wiersz) c-column (kolumna) oraz przedostatni strza³
    bool traf,zat,pomoc;  //true-ostatni strza³ komputera trafiony false-ostatni strza³ komputera nietrafiony
                    //zat -zatopiony
};

#endif // STATKI_H
