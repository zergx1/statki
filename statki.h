#ifndef STATKI_H
#define STATKI_H

#include <QMainWindow>

namespace Ui {
    class statki;
}

class statki : public QMainWindow {
    Q_OBJECT
public:
    statki(QWidget *parent = 0);
    ~statki();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::statki *ui;
};

#endif // STATKI_H
