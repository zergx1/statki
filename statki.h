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
    bool czyustawic1(int x,int y,int p,int m);  //sprawdza czy zaczynajac od pola (x,y) w pionie lub poziomie p mozna ustawic m maszatowiec
    void rozstaw();   //rozstawia statki komputera
public slots:
    void start();
    void akcja(QTableWidgetItem *item);



protected:
    void changeEvent(QEvent *e);

private:
    Ui::statki *ui;
    int m4,m3,m2,m1;
};

#endif // STATKI_H
