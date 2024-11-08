#ifndef CAR_H
#define CAR_H
#include<iostream>
#include<QString>
class car
{

public:
    std::string plate;
    time_t inTime;
    time_t outTime;

    car(const std::string plateNumber);

    void setInTime();

    void setOutTime();

    time_t getInTime();

    QString getInTimeString();

    time_t getOutTime();

    QString getOutTimeString();
};

#endif // CAR_H
