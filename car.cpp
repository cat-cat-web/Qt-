#include "car.h"

car::car(const std::string plateNumber){
    if (plateNumber.empty()) {
        throw std::logic_error("无效的车牌号");
    }
    plate=plateNumber;
    inTime=0;
    outTime=0;
}



void car::setInTime(){
    inTime=time(nullptr);
}

void car::setOutTime(){
    outTime=time(nullptr);
}


time_t car::getInTime(){
    return inTime;
}

time_t car::getOutTime(){
    return outTime;
}

//把time_t转化成标准时间形式
QString car::getInTimeString() {

    struct tm *timeinfo=localtime(&inTime);
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return QString::fromUtf8(buffer); // 转换为 QString
}


QString car::getOutTimeString(){
    struct tm *timeinfo = localtime(&outTime); // 将 time_t 转换为本地时间
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo); // 格式化时间

    return QString::fromUtf8(buffer); // 转换为 QString
}
