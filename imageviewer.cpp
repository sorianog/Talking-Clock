#include "imageviewer.h"
#include <QtGui>
/**
 * SE3910 Spring 2016 - Lab 6
 * Author: sorianog, wattsz
 *
 * @brief imageviewer::imageviewer - the widget that allows for the viewing of images
 * @param parent
 * @param tc
 */
ImageViewer::ImageViewer(QWidget *parent, TalkingClock *tc) :
    QWidget(parent)
{
    tcwindow = tc;
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    setLayout(layout);
}

/**
 * @brief ImageViewer::open
 * Allow for a an image to be opened and displayed in the window
 */
void ImageViewer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        tcwindow->printAct->setEnabled(true);
        tcwindow->fitToWindowAct->setEnabled(true);
        tcwindow->updateActions();

        if (!tcwindow->fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    }
}

/**
 * @brief ImageViewer::print
 * Allow for an image to be sent to a printer
 */
void ImageViewer::print()
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&tcwindow->printer, this);
    if (dialog.exec()) {
        QPainter painter(&tcwindow->printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

/**
 * @brief ImageViewer::zoomIn
 */
void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

/**
 * @brief ImageViewer::zoomOut
 */
void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

/**
 * @brief ImageViewer::normalSize
 */
void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

/**
 * @brief ImageViewer::fitToWindow
 */
void ImageViewer::fitToWindow()
{
    bool fitToWindow = tcwindow->fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    tcwindow->updateActions();
}

/**
 * @brief ImageViewer::scaleImage
 * Scale an image based on the scale factor
 * @param factor
 */
void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    tcwindow->zoomInAct->setEnabled(scaleFactor < 3.0);
    tcwindow->zoomOutAct->setEnabled(scaleFactor > 0.333);
}

/**
 * @brief ImageViewer::adjustScrollBar
 * @param scrollBar
 * @param factor
 */
void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
