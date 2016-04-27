#include "talkingclock.h"
#include <QApplication>
#include <QTime>
#include "gpio/GPIO.h"

/**
 * SE3910 Spring 2016 - Lab 6
 * Author: sorianog, wattsz
 *
 * @brief main - show the main UI and configure the push button for the system
 * @param argc
 * @param argv
 * @return
 *
 */
using namespace exploringBB;
int hardBtnClicked(int var);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TalkingClock tc;
    tc.show();
    GPIO* button1 = new GPIO(66); //button 1 png
    button1->setDirection(GPIO::INPUT);
    button1->setEdgeType(GPIO::RISING);
    button1->waitForEdge(hardBtnClicked);
    return a.exec();
}

/**
 * @brief hardBtnClicked
 * Vocalize the current time when the physical push button is pressed
 * @param var
 * @return
 */
int hardBtnClicked(int var)
{
    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh:mm:ss");
    QString createAudio = "espeak -w time.wav 'The current time is " + timeText + ". Beep'";
    system(qPrintable(createAudio));
    QString playTime = "mplayer -ao alsa:device=hw=1 time.wav";
    system(qPrintable(playTime));
    return 0;
}

