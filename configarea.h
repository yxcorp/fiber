#ifndef CONFIGAREA_H
#define CONFIGAREA_H

#include <QWidget>
#include <QComboBox>

class ConfigArea : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigArea(QWidget *parent = 0);
private:
    void AlertText();
    void AlertText2();
};

#endif // CONFIGAREA_H
