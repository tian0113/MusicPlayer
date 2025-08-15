#include "widget.h"
#include <QApplication>

/*
日期：2025-8-05
开发者：田阳
项目：实现基于Qt的音乐播放器
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    //消息循环，防止闪退
    return a.exec();
}
