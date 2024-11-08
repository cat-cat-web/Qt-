#include "billing.h"
#include<cmath>
Billing::Billing(double ratePerHour):ratePerHour(ratePerHour),sum(0) {}

    double Billing::calculateFee(double durationInHours){

    return ceil(durationInHours) * ratePerHour; //向上取整
}

    double Billing::getDurationInHours(time_t inTime,time_t outTime){
        double durationInSeconds =difftime(outTime,inTime);
        std::cout<<"duration time(seconds):"<<durationInSeconds<<std::endl;
        double durationInHours = durationInSeconds / 3600.0;
        return ceil(durationInHours);
    }

    bool Billing::addSum(double charge){
        sum+=charge;
        return true;
    }

    double Billing::getSum(){
        return sum;
    }
