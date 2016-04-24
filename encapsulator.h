#ifndef ENCAPSULATOR_H
#define ENCAPSULATOR_H

#include <QWidget>
#include "imageviewer.h"
#include "talkingclock.h"
class Encapsulator : public QWidget
{
    Q_OBJECT
public:
    explicit Encapsulator(QWidget *parent = 0, TalkingClock *tc = 0);
    ImageViewer* getImageViewer();
private:
    ImageViewer *viewer;
    QLCDNumber *lcd;
signals:

public slots:
    void speakTime();

private slots:
    void showTime();
};

#endif // ENCAPSULATOR_H
