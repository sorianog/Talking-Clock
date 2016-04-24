#ifndef TALKINGCLOCK_H
#define TALKINGCLOCK_H

#include <QMainWindow>
#include <QPrinter>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QLCDNumber;
class Encapsulator;

class TalkingClock : public QMainWindow
{
    Q_OBJECT

public:
    TalkingClock();
    QAction *printAct;
    QAction *fitToWindowAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    Encapsulator *capsule;
    void updateActions();

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

private slots:
    void about();

private:
    void createActions();
    void createMenus();

    QAction *openAct;
    QAction *exitAct;
    QAction *normalSizeAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};

#endif
