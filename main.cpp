#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(resource);

    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/pics/loading"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::white);

    splash->showMessage(QObject::tr("Loading modules..."),
                        topRight, Qt::white);
    //loadModules();
    splash->showMessage(QObject::tr("Establishing connections..."),
                        topRight, Qt::white);
    //establishConnections();

    QTranslator qtranslator;
    if (qtranslator.load("fiber", ":/translations")) {
        a.installTranslator(&qtranslator);
        qDebug() << "translate install sucess!";
    }
    MainWindow w;
    w.resize(800, 600);
    w.show();
    splash->finish(&w);
    delete splash;//释放空间，节省内存
    return a.exec();
}
