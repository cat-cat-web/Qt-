#ifndef BILLING_H
#define BILLING_H

#include "car.h"

class Billing
{
private:
    double ratePerHour;
    double sum;
public:
    Billing(double ratePerHour);

    double calculateFee(double durationInHours);

    double getDurationInHours(time_t inTime,time_t outTime);

    bool addSum(double charge);

    double getSum();
};

#endif // BILLING_H
