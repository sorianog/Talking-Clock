#include "talkingclock.h"
#include <QApplication>
/**
 * SE3910 Spring 2016 - Lab 6
 * Author: sorianog, wattsz
 *
 * @brief main
 * @param argc
 * @param argv
 * @return
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TalkingClock w;
    w.show();

    return a.exec();
}
