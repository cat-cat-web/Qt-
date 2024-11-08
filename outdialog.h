#ifndef OUTDIALOG_H
#define OUTDIALOG_H

#include <QDialog>
#include "queue.h"
#include "car.h"
#include "lot.h"
#include "billing.h"
namespace Ui {
class outDialog;
}

class outDialog : public QDialog
{
    Q_OBJECT

public:
    explicit outDialog(QWidget *parent = nullptr,lot *parkingLot=nullptr,queue<car> *waitingQueue=nullptr,Billing *billing=nullptr);
    ~outDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::outDialog *ui;
    lot *parkingLot;
    queue<car> *waitingQueue;
    Billing *billing;
};

#endif // OUTDIALOG_H
