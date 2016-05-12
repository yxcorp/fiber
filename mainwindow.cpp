#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "photopreviewarea.h"
#include "createanalyzewizard.h"
#include "configarea.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle(tr("MainWindow"));
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    createActions();

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    recordList = new QListWidget;
    for ( int i=67; i<88; i++) {
        recordList->addItem(new QListWidgetItem(QIcon(":/icons/success"), QObject::tr("2016.5.1 First Test")));
        recordList->addItem(new QListWidgetItem(QIcon(":/icons/success"), QObject::tr("2016.5.1 Second Test")));
        recordList->addItem(new QListWidgetItem(QIcon(":/icons/fail"), QObject::tr("2016.5.1 Third Test")));
    }
    detailTabWidget = new QTabWidget;

    QIcon icon1(":/icons/logo");
    detailTabWidget->addTab((new QPushButton("Click Me1")), icon1, tr("&Test Result"));
    detailTabWidget->addTab((new QPushButton("Click Me2")), icon1, tr("&PhotoMale"));
    detailTabWidget->addTab((new QPushButton("Click Me3")), icon1, tr("&PhotoFemale"));
    detailTabWidget->addTab((new QPushButton("Click Me4")), icon1, tr("&PhotoIntensity"));

    mainLayout->addWidget(recordList);
    mainLayout->addWidget(detailTabWidget);
    mainLayout->setStretch(0,1);
    mainLayout->setStretch(1,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget *MainWindow::createCameraGroupBox()
{
    QGroupBox *cameraGroupBox = new QGroupBox(tr("Preview"));
    camera=new QCamera(this);
    viewfinder=new QCameraViewfinder(this);
    imageCapture=new QCameraImageCapture(camera);
    QVBoxLayout *layout = new QVBoxLayout(cameraGroupBox);
    layout->addWidget(viewfinder);

    camera->setViewfinder(viewfinder);
    camera->start();
    connect(imageCapture, &QCameraImageCapture::imageCaptured, this, &MainWindow::displayImage);
    //connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));
    return cameraGroupBox;
}

QWidget *MainWindow::createConfigGroupBox()
{
    QGroupBox *configGroupBox = new QGroupBox(tr("Configs"));

    configArea = new ConfigArea(configGroupBox);

    QVBoxLayout *layout = new QVBoxLayout(configGroupBox);
    layout->addWidget(configArea);
    return configGroupBox;
}

QWidget *MainWindow::createResultGroupBox()
{
    QGroupBox *imagesGroupBox = new QGroupBox(tr("Results"));
    QPalette pal;
    resultlabel = new QLabel(tr("Success!"));
    pal.setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));

    //resultlabel->setGeometry(x,y,w,h );

    pal.setColor(QPalette::WindowText, Qt::darkGreen);
    resultlabel->setPalette(pal);

    resultlabel->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(18);
    ft.setBold(true);
    resultlabel->setFont(ft);
    QVBoxLayout *layout = new QVBoxLayout(imagesGroupBox);
    layout->addWidget(resultlabel);
    return imagesGroupBox;
}

QWidget *MainWindow::createAnalyzePicGroupBox()
{
    QGroupBox *previewGroupBox = new QGroupBox(tr("Channel Status")); //image show
    resultArea = new PhotoPreviewArea(":/pics/resultphoto.png" ,QSize(120, 120), previewGroupBox);
    QVBoxLayout *previewLayout = new QVBoxLayout(previewGroupBox);
    previewLayout->addWidget(resultArea);

    resultArea->setAlignment(Qt::AlignCenter);
    return previewGroupBox;
}

void MainWindow::openTpllst()
{

}

void MainWindow::openUserlst()
{

}
void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

void MainWindow::captureImage()
{
    ui->statusBar->showMessage(tr("capturing..."), 1000);
    imageCapture->capture();
}

void MainWindow::displayImage(int, QImage image)
{
    resultArea->setPixmap(QPixmap::fromImage(image));
    ui->statusBar->showMessage(tr("captured success"), 5000);
}

void MainWindow::saveImage()
{
//    QString fileName=QFileDialog::getSaveFileName(this, tr("save to file"), QDir::homePath(), tr("jpeg格式文件(*.jpg)"));
//    if(fileName.isEmpty()) {
//        ui->statusBar->showMessage(tr("save canceld"), 5000);
//        return;
//    }
//    const QPixmap* pixmap=ui->label_Display->pixmap();
//    if(pixmap) {
//        pixmap->save(fileName);
//        ui->statusBar->showMessage(tr("save success"), 5000);
//    }
}
void MainWindow::createWizard()
{
    CreateAnalyzeWizard* wizard = new CreateAnalyzeWizard;
    wizard->resize(450, 600);
    wizard->show();
}
void MainWindow::createActions()
{
    createWizardAction = new QAction(QIcon(":/icons/capture"), tr("&Create..."), this);
    createWizardAction->setShortcuts(QKeySequence::New);
    createWizardAction->setStatusTip(tr("Create Wizard..."));
    connect(createWizardAction, &QAction::triggered, this, &MainWindow::createWizard);

    openTpllstAction = new QAction(QIcon(":/icons/tpls"), tr("&Tpllist..."), this);
    //openTpllstAction->setShortcuts(QKeySequence::Open);
    openTpllstAction->setStatusTip(tr("Open template manage list"));
    connect(openTpllstAction, &QAction::triggered, this, &MainWindow::openTpllst);

    openUserlstAction = new QAction(QIcon(":/icons/users"), tr("&Userlist..."), this);
    //openUserlstAction->setShortcuts(QKeySequence::Open);
    openUserlstAction->setStatusTip(tr("Open user manage list"));
    connect(openUserlstAction, &QAction::triggered, this, &MainWindow::openUserlst);

    openFileAction = new QAction(QIcon(":/icons/file-open"), tr("&Open..."), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open File..."));
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    saveFileAction = new QAction(QIcon(":/icons/file-save"), tr("&Save..."), this);
    saveFileAction->setShortcuts(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Open File..."));
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);


    quitAction = new QAction(QIcon(":/icons/quit"),tr("&Quit..."), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit Application"));
    QObject::connect(quitAction, &QAction::triggered, &QApplication::quit);

    captureAction = new QAction(QIcon(":/icons/capture"), tr("&Capture..."), this);
    //captureAction->setShortcuts(QKeySequence::Save);
    captureAction->setStatusTip(tr("Capture..."));
    connect(captureAction, &QAction::triggered, this, &MainWindow::captureImage);

    saveImageAction = new QAction(QIcon(":/icons/saveimage"), tr("&Save Image..."), this);
    //saveFileAction->setShortcuts(QKeySequence::Save);
    saveImageAction->setStatusTip(tr("Save Image..."));
    connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);

    QMenu *file = menuBar()->addMenu(tr("&File"));    
    file->addAction(createWizardAction);
    file->addAction(openTpllstAction);
    file->addAction(openUserlstAction);
    file->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    ui->mainToolBar->addAction(createWizardAction);
    ui->mainToolBar->addAction(openFileAction);
    ui->mainToolBar->addAction(saveFileAction);
    ui->mainToolBar->addAction(captureAction);
    ui->mainToolBar->addAction(quitAction);


}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Icons"),
            tr("The <b>Icons</b> example illustrates how Qt renders an icon in "
               "different modes (active, normal, disabled, and selected) and "
               "states (on and off) based on a set of images."));
}
