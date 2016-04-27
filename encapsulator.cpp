#include "encapsulator.h"
#include "talkingclock.h"
#include "ui_talkingclock.h"
#include <QtGui>
#include "imageviewer.h"

/**
 * SE3910 Spring 2016 - Lab 6
 * Author: sorianog, wattsz
 *
 * @brief Encapsulator::Encapsulator - the container for the image viewer, clock, and speak time button
 * @param parent
 * @param tc
 */
Encapsulator::Encapsulator(QWidget *parent, TalkingClock *tc) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    lcd = new QLCDNumber();
    lcd->setSegmentStyle(QLCDNumber::Filled);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();

    QPushButton *speakBtn = new QPushButton("Speak the Time!");
    connect(speakBtn, SIGNAL(clicked()), this, SLOT(speakTime()));

    viewer = new ImageViewer(0, tc);
    layout->addWidget(viewer);
    layout->addWidget(lcd);
    layout->addWidget(speakBtn);
    setLayout(layout);
}

/**
 * @brief Encapsulator::getImageViewer
 * @return
 */
ImageViewer* Encapsulator::getImageViewer(){
    return viewer;
}

/**
 * @brief Encapsulator::showTime
 * Update the clock's time
 */
void Encapsulator::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    lcd->display(text);
}

/**
 * @brief Encapsulator::speakTime
 * Vocalize the current time
 */
void Encapsulator::speakTime()
{
    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh:mm:ss");
    QString createAudio = "espeak -w time.wav 'The current time is now" + timeText + ". Beep'";
    system(qPrintable(createAudio));
    QString playTime = "mplayer -ao alsa:device=hw=1 time.wav";
    system(qPrintable(playTime));
}
