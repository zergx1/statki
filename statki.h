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
public slots:
    void start();
    void akcja(QTableWidgetItem *item);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::statki *ui;
};

#endif // STATKI_H
