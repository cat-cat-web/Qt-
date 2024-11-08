#include "outdialog.h"
#include "ui_outdialog.h"
#include "utils.h"
#include <QMessageBox>
#include "billing.h"
#include "widget.h"
outDialog::outDialog(QWidget *parent,lot *parkingLot,queue<car> *waitingQueue,Billing *billing)
    : QDialog(parent)
    , ui(new Ui::outDialog)
    ,parkingLot(parkingLot)
    ,waitingQueue(waitingQueue)
    ,billing(billing)
{
    ui->setupUi(this);
}

outDialog::~outDialog()
{
    delete ui;
}

//出车
void outDialog::on_okButton_clicked()
{
    bool flagRemove=false; //用于记录车是否被成功移出
    bool flagFound=false;

    //获取车牌号
    std::string AimPlate=(ui->lineEdit_2->text()).toStdString();

    //遍历车库内中的车辆信息,比对
    if(parkingLot->getCurrentCars()==0){
        QMessageBox::warning(this,"出车失败","车库中无车！");
        accept();//此时继续输入信息无意义,直接关闭窗口
        return;

    }

    for(int i=0;i<CAPACITY;i++){

        if(parkingLot->spaces[i]!=nullptr&&parkingLot->spaces[i]->plate==AimPlate){
            flagFound=true;
            parkingLot->spaces[i]->setOutTime();

            //同时计算费用
            //设置10r/h

            double durationInHours=billing->getDurationInHours(parkingLot->spaces[i]->getInTime(),parkingLot->spaces[i]->getOutTime());
            double charge=billing->calculateFee(durationInHours);
            billing->addSum(charge);
            std::cout<<"the sum:"<<billing->getSum()<<std::endl;
            parkingLot->history.append(getCurrentTime()+":"+
                                       "车辆"+QString::fromStdString(parkingLot->spaces[i]->plate)+
                                       "请求出车"+","+
                                       "停车费用为"+QString::number(charge));

            QString message = QString("车 %1 的停车时长为：%2 小时\n 费用为：%3 元")
                                  .arg(QString::fromStdString(AimPlate))
                                  .arg(durationInHours)
                                  .arg(charge);

            QMessageBox::information(this, "结算信息", message);

            //移出该车
            parkingLot->removeCar(i);
            flagRemove=true;
            QMessageBox::information(this, "出车成功", "已成功出车！");
        }
    }


    if(!flagFound){
        QMessageBox::warning(this, "出车失败", "车库中无该车！");
    }

    //排队入车
    if(flagRemove&&(!waitingQueue->isEmpty())){ //成功出车且队列中有车
        car nextCar=waitingQueue->getFront();
        waitingQueue->deQueue();

        parkingLot->parkCar(nextCar);
    }

    //更新标签
    Widget *parentWidget = qobject_cast<Widget*>(parent());
    if (parentWidget) {
        parentWidget->updatePushButton();
    }

    ui->lineEdit_2->setText("");
    this->accept();

}


void outDialog::on_cancelButton_clicked()
{
    this->reject();


}

