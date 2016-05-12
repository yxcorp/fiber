#include <QtWidgets>
#include "configarea.h"
#include <QDebug>
#include <QLibrary>

ConfigArea::ConfigArea(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    QComboBox *harnessTypeBox = new QComboBox;
    //QLabel *label = new QLabel(tr("<b>%1</b>").arg("text"));
    //harnessTypeBox->setAlignment(Qt::AlignTop);
    gridLayout->addWidget(new QLabel(tr("harness")),0,0);
    gridLayout->addWidget(harnessTypeBox,0,1);

    QPushButton *testButton = new QPushButton(tr("test1"));
    connect(testButton, &QPushButton::clicked, this, &ConfigArea::AlertText);
    gridLayout->addWidget(testButton,1,0,1,2);

    QPushButton *testButton2 = new QPushButton(tr("test2"));
    connect(testButton2, &QPushButton::clicked, this, &ConfigArea::AlertText2);
    gridLayout->addWidget(testButton2,2,0,1,2);

    gridLayout->setAlignment(Qt::AlignTop);
}

void ConfigArea::AlertText()
{
    //Yximage *yximage = new Yximage();
    //QMessageBox::information(this, tr("Hmmm..."), yximage->GetStr());
}

void ConfigArea::AlertText2()
{
    //typedef QString (*myfun)(QString str);
    typedef int (*SumFunction)(int,int);
    //    qDebug() << QApplication::applicationDirPath();
    //    QStringList stings = QApplication::libraryPaths();
    //    foreach (QString str, stings) {
    //        qDebug() << str;
    //    }
    if(QLibrary::isLibrary("dlltest3.dll"))
    {
        qDebug() << "QLibrary isLibrary!";
    }
    QLibrary library("dlltest3.dll");
    if(library.load())
    {
        //myfun fun1 = (myfun)hdll.resolve("GetStr");

        SumFunction sum=(SumFunction)library.resolve("sum");
        if ( sum )
        {
            qDebug()<<"sum="<<sum(1,9);
        }
    }
    else{
        qDebug() << "QLibrary load error!";
        qDebug()<<library.errorString()<<endl;
    }
}

