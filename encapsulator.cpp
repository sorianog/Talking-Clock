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
    QPushButton *speak = new QPushButton("Speak the Time!");
    viewer = new ImageViewer(0, tc);

    layout->addWidget(viewer);
    layout->addWidget(lcd);
    layout->addWidget(speak);
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
void Encapsulator::showTime(){
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    lcd->display(text);
}
