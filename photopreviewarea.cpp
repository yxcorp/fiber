#include "photopreviewarea.h"
#include <QtWidgets>

PhotoPreviewArea::PhotoPreviewArea(QString path, const QSize &s, QWidget *parent) :
    QLabel(parent)
{
    QImage image;
    image.load( path);

    QPixmap pixmapToShow = QPixmap::fromImage( image.scaled(s, Qt::KeepAspectRatio) );

    setPixmap(pixmapToShow);
    setFixedSize(120, 120);
    setScaledContents(true);
}


