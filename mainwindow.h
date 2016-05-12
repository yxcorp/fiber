#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class PhotoPreviewArea;
class ConfigArea;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;    
    QWidget *createCameraGroupBox();
    QWidget *createConfigGroupBox();
    QWidget *createResultGroupBox();
    QWidget *createAnalyzePicGroupBox();
    void createActions();
    void about();
    void openTpllst();
    void openUserlst();
    void openFile();
    void saveFile();
    void createWizard();

    void captureImage();
    void displayImage(int,QImage);
    void saveImage();
    PhotoPreviewArea *previewArea;
    PhotoPreviewArea *resultArea;
    QAction *openTpllstAction;
    QAction *openUserlstAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *quitAction;
    QAction *captureAction;
    QAction *saveImageAction;    
    QAction *createWizardAction;

    QListWidget *recordList;
    QTabWidget *detailTabWidget;
    QTextEdit *textEdit;
    ConfigArea *configArea;
    QLabel *resultlabel;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
};

#endif // MAINWINDOW_H
