#include "entrydialog.h"
#include "ui_entrydialog.h"
#include "utils.h"
#include <QMessageBox>
#include <widget.h>
entryDialog::entryDialog(QWidget *parent,lot *parkingLot,queue<car> *waitingQueue)
    : QDialog(parent)
    , ui(new Ui::entryDialog)
    ,parkingLot(parkingLot)
    ,waitingQueue(waitingQueue)
{
    ui->setupUi(this);
}

entryDialog::~entryDialog()
{
    delete ui;
}

//点击OK按钮：新建一个Car实例，检查停车场是否有空位，有则入，并为该Car类设置入场时间，无则入队等候；
void entryDialog::on_okButton_clicked(){
    QString plateNumber=ui->lineEdit->text();


    if(plateNumber.isEmpty()){
        return;
    }

    //队列中重复
    if(!waitingQueue->isEmpty()){
       Node<car>* currentNode = waitingQueue->front;
        while (currentNode != nullptr) {
            car currentCar = currentNode->data;
            if(currentCar.plate==plateNumber.toStdString()){
                QMessageBox::warning(this,"入车失败","等待队列中已有该车！");
                return;
            }
            currentNode=currentNode->next;
        }
    }

    for(int i=0;i<CAPACITY;i++){
        //车库中有车且车牌重复
        if(parkingLot->spaces[i]!=nullptr&&plateNumber.toStdString()==parkingLot->spaces[i]->plate){
            QMessageBox::warning(this,"入车失败","车库中已有该车！");
            ui->lineEdit->setText("");
            return;
        }
    }

    car newCar(plateNumber.toStdString());


    if(!parkingLot->isFull()){
        parkingLot->parkCar(newCar);

         QMessageBox::information(this, "入车成功", "车辆已成功停入车位！");
    }else {
        waitingQueue->enQueue(newCar);

        parkingLot->history.append(getCurrentTime()+":"+
                                   "车辆"+QString::fromStdString(newCar.plate)+
                                   "已成功进入等待队列");

        QString message=QString("进入队列等待，当前排在第 %1 位").arg(waitingQueue->getSize());
        QMessageBox::information(this, "入车失败", message);
    }

    //更新标签
    Widget *parentWidget = qobject_cast<Widget*>(parent());
    if (parentWidget) {
        parentWidget->updatePushButton();
    }

     ui->lineEdit->setText("");
    //关闭对话框
    accept();

}



void entryDialog::on_cancelButton_clicked()
{
    this->reject();
}

