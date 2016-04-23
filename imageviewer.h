#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QtGui>
#include <QAction>
#include "talkingclock.h"
class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0, TalkingClock *tc = 0);
private:
    TalkingClock *tcwindow;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QLCDNumber *lcd;
    double scaleFactor;
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

signals:

public slots:
    void open();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
};

#endif // IMAGEVIEWER_H
