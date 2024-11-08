#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "entryDialog.h"
#include "outdialog.h"
#include "billing.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updatePushButton();

private slots:

    void on_entryButton_clicked();

    void on_outButton_clicked();

    void on_infoButton_clicked();



    void on_spareSpace_PushButton_clicked();

    void on_currentCars_PushButton_clicked();

    void on_waitingCars_PushButton_clicked();

    void on_income_pushButton_clicked();

private:
    Ui::Widget *ui;
    entryDialog *entryWindow;
    outDialog *outWindow;
    lot *parkingLot;

    queue<car> *waitingLine;

    Billing *billing; //计费器


};
#endif // WIDGET_H
