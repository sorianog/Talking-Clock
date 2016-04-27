#include "talkingclock.h"
#include "ui_talkingclock.h"
#include <QtGui>
#include "imageviewer.h"
#include "encapsulator.h"

/**
 * SE3910 Spring 2016 - Lab 6
 * Author: sorianog, wattsz
 *
 * @brief TalkingClock::TalkingClock - The main window containg all widgets
 */
TalkingClock::TalkingClock()
{
    capsule = new Encapsulator(0 , this);
    setCentralWidget(capsule);
    createActions();
    createMenus();

    setWindowTitle(tr("Talking Clock By Gerald Soriano & Zach Watts"));
    resize(500, 400);
}

/**
 * @brief TalkingClock::about
 */
void TalkingClock::about()
{
    QMessageBox::about(this, tr("About Talking Clock"),
            tr("<p>The <b>Talking Clock</b> is an application "
               "created for MSOE's SE3910 - Real Time Systems class. "
               "The main features of the app are viewing images,"
               "displaying the current time, and speaking the time."
               "</p><p>This app uses QT's Image Viewer and Digital Clock examples.</p>"));
}

/**
 * @brief TalkingClock::createActions
 * Connect all the necessary actions to their respective slots
 */
void TalkingClock::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), capsule->getImageViewer(), SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

/**
 * @brief TalkingClock::createMenus
 * Construct the menu itmes for the main menu bar
 */
void TalkingClock::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}

/**
 * @brief TalkingClock::updateActions
 * Enable/disable the necessary actions
 */
void TalkingClock::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}



