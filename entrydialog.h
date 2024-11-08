#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include "queue.h"
#include "car.h"
#include "lot.h"

namespace Ui {
class entryDialog;
}

class entryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit entryDialog(QWidget *parent = nullptr,lot *parkingLot=nullptr,queue<car> *waitingQueue=nullptr);
    ~entryDialog();

private slots:
     void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::entryDialog *ui;
    lot *parkingLot;
    queue<car> *waitingQueue;
};

#endif // ENTRYDIALOG_H
