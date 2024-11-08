#include "lot.h"
#include "billing.cpp"
#include "utils.cpp"
#include<QDateTime>
lot::lot(){
    currentCars=0;

    //为每个空位初始化
    for(int i=0;i<CAPACITY;++i){
        spaces[i]=nullptr;
    }
}

lot::~lot(){
    for(int i=0;i<CAPACITY;++i){
        if(spaces[i]!=nullptr){
            delete spaces[i];
        }
    }
}

//进车
bool lot::parkCar(const car &newCar){
    if(currentCars>=CAPACITY){
        return false;
    }

    for(int i=0;i<CAPACITY;++i){
        if(spaces[i]==nullptr){
            spaces[i]=new car(newCar);//找到第一个空位加入
            spaces[i]->setInTime(); //为副本设置进车时间
            currentCars++;
            history.append(getCurrentTime()+":"+
                           "车辆"+QString::fromStdString(newCar.plate)+
                           "已成功停入车位"+QString::number(i));
            return true;
        }
    }
    return false;
}

bool lot::isFull(){
    return currentCars==CAPACITY;
}


//出车
bool lot::removeCar(int index){

    history.append(getCurrentTime()+":"+
                   "车辆"+QString::fromStdString(spaces[index]->plate)+
                   "已成功离开车位"+QString::number(index));
    delete spaces[index];
    spaces[index]=nullptr;
    currentCars--;
    return true;
}

int lot::getCurrentCars(){
    return currentCars;
}




