#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

//队列用于满员时排队（先进先出）
//停车场--车可以从各个方向出:自定义数组
// car类：in;out;
// lot类：isFull;
// queue类：out
//存储车辆信息：number;time when in;

//计费功能：
