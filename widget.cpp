#include "widget.h"
#include "ui_widget.h"
#include <qmessagebox.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,entryWindow(nullptr)
    ,outWindow(nullptr)
    ,parkingLot(new lot)
    ,waitingLine(new queue<car>)
    ,billing(new Billing(10.0)) //初始10r/h

{
    ui->setupUi(this);
    setWindowTitle("停车场管理系统");

    //初始化文本
    ui->numberOfAll_PushButton->setText(QString("车位总数：%1").arg(CAPACITY));
    ui->spareSpace_PushButton->setText(QString("空余车位：%1").arg(CAPACITY));
    ui->currentCars_PushButton->setText(QString("当前车辆：%1").arg(0)); // 初始为0
    ui->waitingCars_PushButton->setText(QString("等候车辆：%1").arg(0)); // 初始为0

    //初始化样式
    ui->numberOfAll_PushButton->setStyleSheet("font-size: 14px;font-weight: bold;border: none; background-color: transparent;");
    ui->spareSpace_PushButton->setStyleSheet("font-size: 14px;border: none; background-color: transparent;");
    ui->currentCars_PushButton->setStyleSheet("font-size: 14px;border: none; background-color: transparent;");
    ui->waitingCars_PushButton->setStyleSheet("font-size: 14px;border: none; background-color: transparent;");

    ui->infoButton->setStyleSheet("background-color:lightblue");
}


Widget::~Widget()
{
    delete ui;
    if(entryWindow!=nullptr){
        delete entryWindow;
    }
}

void Widget::on_entryButton_clicked()
{

    if(entryWindow==nullptr){
        entryWindow = new entryDialog(this,parkingLot,waitingLine); //新建窗口
    }
    entryWindow->setWindowTitle("进车");
    entryWindow->show();

}


void Widget::on_outButton_clicked()
{
    if(outWindow==nullptr){
        outWindow=new outDialog(this,parkingLot,waitingLine,billing);
    }
    outWindow->setWindowTitle("出车");
    outWindow->show();

}


void Widget::on_infoButton_clicked()
{
    QMessageBox historyDialog(this);
    historyDialog.setWindowTitle("历史信息");
    historyDialog.setText(parkingLot->getHistory());
    historyDialog.exec(); //
}

void Widget::updatePushButton() {
    ui->numberOfAll_PushButton->setText(QString("车位总数：%1").arg(CAPACITY));
    ui->spareSpace_PushButton->setText(QString("空余车位：%1").arg(CAPACITY-parkingLot->getCurrentCars()));
    ui->currentCars_PushButton->setText(QString("当前车辆：%1").arg(parkingLot->getCurrentCars()));
    ui->waitingCars_PushButton->setText(QString("等候车辆：%1").arg(waitingLine->getSize()));
}

//空闲车位:显示当前空闲的车位
void Widget::on_spareSpace_PushButton_clicked()
{
    ui->info_textBrowser->setText(""); //初始化界面

    //显示当前空余的位置--车位号
    QString combinedInfo="空闲车位：\n";
    for(int i=0;i<CAPACITY;++i)
    if(parkingLot->spaces[i]==nullptr){
        QString info_spareSpace=QString("车位 %1 ； ").arg(i);
        combinedInfo += info_spareSpace;
    }
    ui->info_textBrowser->setText(combinedInfo);
}

//当前车辆:显示每辆车对应的信息
void Widget::on_currentCars_PushButton_clicked()
{
    ui->info_textBrowser->setText(""); //初始化界面

    QString combinedInfo="当前车库中车辆信息：\n";
    for(int i=0;i<CAPACITY;++i)
        if(parkingLot->spaces[i]!=nullptr){
            QString info_carsInLot=QString("车位 %1 :\n 车牌号 %2 ；\n 入场时间：%3\n")
                                         .arg(i)
                                         .arg(QString::fromStdString(parkingLot->spaces[i]->plate))
                                         .arg(parkingLot->spaces[i]->getInTimeString());

            combinedInfo += info_carsInLot;
    }
    ui->info_textBrowser->setText(combinedInfo);
}

//等待车辆:显示在队列中的车辆信息
void Widget::on_waitingCars_PushButton_clicked()
{
    ui->info_textBrowser->setText(""); // 初始化界面
    QString combinedInfo = "当前等待队列中车辆信息：\n";
    //直接使用原队列
    if(!waitingLine->isEmpty()){
        Node<car>* currentNode = waitingLine->front;
        int index = 1;
        while (currentNode != nullptr) {

            car currentCar = currentNode->data;

            QString info_carInLine = QString("序号 %1 : 车牌号 %2\n")
                                         .arg(index++)
                                         .arg(QString::fromStdString(currentCar.plate));
            combinedInfo += info_carInLine;

            currentNode = currentNode->next;
        }
    } else {
        combinedInfo = "当前等待队列为空。\n";
    }

    ui->info_textBrowser->setText(combinedInfo);
}

void Widget::on_income_pushButton_clicked()
{
    QString combinedInfo=QString("当前总收入：\n %1").arg(billing->getSum());
    ui->info_textBrowser->setText(combinedInfo);
}

