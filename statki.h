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
