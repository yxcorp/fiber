#ifndef PHOTOPREVIEWAREA_H
#define PHOTOPREVIEWAREA_H

#include <QLabel>

class PhotoPreviewArea : public QLabel
{
    Q_OBJECT

public:
    explicit PhotoPreviewArea(QString path, const QSize &s, QWidget *parent = 0);



};

#endif // PHOTOPREVIEWAREA_H
