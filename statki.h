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
    void rozstaw();   //rozstawia statki komputera
    void cpustrzel();
    void cpurozstaw();
public slots:
    void start();
    void akcja(QTableWidgetItem *item);
    void akcja2(QTableWidgetItem *item);



protected:
    void changeEvent(QEvent *e);

private:
    Ui::statki *ui;
    int m4,m3,m2,m1;
    QList<QTableWidgetItem *> itemLists1; // to dziala tak samo jak wektor
    QList<QTableWidgetItem *> itemLists2;
    int zycie1,zycie2;

};

#endif // STATKI_H
