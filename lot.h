#ifndef LOT_H
#define LOT_H

#include "car.h"
#include <QString>
#include <QStringList>

#define CAPACITY 3
class lot
{
private:

    int currentCars;

public:
    car* spaces[CAPACITY]; //设置停车场有CAPACITY个车位
    lot();
    ~lot();

    bool parkCar(const car &newCar);
    bool removeCar(int index);
    bool isFull();


    int getCurrentCars() ;

    //历史信息存储
    QStringList history;
    QString getHistory() const{
        return history.join("\n");
    }


};

#endif // LOT_H
