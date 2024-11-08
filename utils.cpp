#include "utils.h"
#include <QDateTime>

QString getCurrentTime() {
    QDateTime current = QDateTime::currentDateTime();
    return current.toString("yyyy-MM-dd HH:mm:ss");
}
