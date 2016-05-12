#include "createanalyzewizard.h"
#include <QtWidgets>
#include <QPrinter>
#include <QPrintDialog>
#include <QLibrary>
CreateAnalyzeWizard::CreateAnalyzeWizard(QWidget *parent) :
    QWizard(parent)
{
//! [0]
    setPage(Page_Setting, new SettingPage);
    setPage(Page_CaptureA, new CapturePage(Capture_A, this));
    setPage(Page_CaptureB, new CapturePage(Capture_B, this));
    setPage(Page_CaptureC, new CapturePage(Capture_C, this));
    setPage(Page_Conclusion, new AnalyzeProgressPage);
//! [1]

    setStartId(Page_Setting);
    setOptions(WizardOption::NoBackButtonOnLastPage);
//! [2]

//! [3]
#ifndef Q_OS_MAC
//! [3] //! [4]
    setWizardStyle(ModernStyle);
#endif

    //setOption(HaveHelpButton, true);

    setPixmap(QWizard::LogoPixmap, QPixmap(":/icons/logo.ico"));


    //connect(this, &QWizard::helpRequested, this, &CreateAnalyzeWizard::showHelp);


    setWindowTitle(tr("Test Wizard"));
}

void CreateAnalyzeWizard::accept()
{
    QDialog::accept();
}

void CreateAnalyzeWizard::showHelp()
//! [9] //! [11]
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Setting:
        message = tr("The decision you make here will affect which page you "
                     "get to see next.");
        break;
//! [10] //! [11]
    case Page_CaptureA:
        message = tr("Make sure to provide a valid email address, such as "
                     "toni.buddenbrook@example.de.");
        break;
    case Page_CaptureB:
        message = tr("If you don't provide an upgrade key, you will be "
                     "asked to fill in your details.");
        break;
    case Page_CaptureC:
        message = tr("Make sure to provide a valid email address, such as "
                     "thomas.gradgrind@example.co.uk.");
        break;
    case Page_Conclusion:
        message = tr("You must accept the terms and conditions of the "
                     "license to proceed.");
        break;
//! [12] //! [13]
    default:
        message = tr("This help is likely not to be of any help.");
    }
//! [12]

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

//! [14]
    QMessageBox::information(this, tr("Create Analyze Wizard Help"), message);
//! [14]

    lastHelpMessage = message;
//! [15]
}

SettingPage::SettingPage(QWidget *parent)
    : QWizardPage(parent)
{
    QSpinBox *dummyTestType = new QSpinBox(this);
    dummyTestType->setVisible(false);
    registerField("testTypeId", dummyTestType);
    QSpinBox *dummyConnectorType = new QSpinBox(this);
    dummyConnectorType->setVisible(false);
    registerField("testConnectorId", dummyConnectorType);

    setTitle(tr("Set your config:"));
    setSubTitle(tr("This wizard will help you start test."));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/resultphoto.png"));

    QGroupBox *grpHarnessType = new QGroupBox(tr("&Choose Harness Type:"));
    QVBoxLayout *layoutHarnessType = new QVBoxLayout(grpHarnessType);
    harnessTypeBox = new QComboBox;
    layoutHarnessType->addWidget(harnessTypeBox);


    QGroupBox *grpTestType = new QGroupBox(tr("&Choose Test Type:"));
    QVBoxLayout *layoutTestType = new QVBoxLayout(grpTestType);

    btnGroupTestType = new QButtonGroup;
    analyzeRadioButton1 = new QRadioButton(tr("&Only Defect"));
    analyzeRadioButton2 = new QRadioButton(tr("&Only Intensity"));
    analyzeRadioButton3 = new QRadioButton(tr("&Both"));
    btnGroupTestType->addButton(analyzeRadioButton1, Analyze_Defect);
    btnGroupTestType->addButton(analyzeRadioButton2, Analyze_Intensity);
    btnGroupTestType->addButton(analyzeRadioButton3, Analyze_Both);
    analyzeRadioButton3->setChecked(true);
    layoutTestType->addWidget(analyzeRadioButton1);
    layoutTestType->addWidget(analyzeRadioButton2);
    layoutTestType->addWidget(analyzeRadioButton3);

    QGroupBox *grpConnectorType = new QGroupBox(tr("&Choose Test Connectors:"));
    QVBoxLayout *layoutConnectorType = new QVBoxLayout(grpConnectorType);
    btnGroupTestConnector = new QButtonGroup;
    connectorRadioButton1 = new QRadioButton(tr("&Only Male"));
    connectorRadioButton2 = new QRadioButton(tr("&Only Female"));
    connectorRadioButton3 = new QRadioButton(tr("&Both"));
    btnGroupTestConnector->addButton(connectorRadioButton1, Connetor_Male);
    btnGroupTestConnector->addButton(connectorRadioButton2, Connetor_Female);
    btnGroupTestConnector->addButton(connectorRadioButton3, Connetor_Both);
    connectorRadioButton3->setChecked(true);
    layoutConnectorType->addWidget(connectorRadioButton1);
    layoutConnectorType->addWidget(connectorRadioButton2);
    layoutConnectorType->addWidget(connectorRadioButton3);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(grpHarnessType);
    layout->addWidget(grpTestType);
    layout->addWidget(grpConnectorType);
    setLayout(layout);
}
//! [16] //! [17]

//! [18]
int SettingPage::nextId() const
//! [17] //! [19]
{
    if (testConnectorId == Connetor_Female) {
        return CreateAnalyzeWizard::Page_CaptureB;
    } else {
        return CreateAnalyzeWizard::Page_CaptureA;
    }
}

bool SettingPage::validatePage()
{
    testTypeId = btnGroupTestType->checkedId();
    testConnectorId = btnGroupTestConnector->checkedId();
    setField("testTypeId",testTypeId);
    setField("testConnectorId",testConnectorId);
    return true;
}
//! [18] //! [19]

//! [20]
CapturePage::CapturePage(Capture_Option id, QWidget *parent)
    : QWizardPage(parent)
{
    switch(id)
    {
    case Capture_A:
        setTitle(tr("capture <i>Male Defect</i>&trade;"));
        break;
    case Capture_B:
        setTitle(tr("capture <i>Female Defect</i>&trade;"));
         break;
    case Capture_C:
        setTitle(tr("capture <i>Male or Female Intensity</i>&trade;"));
         break;
    default:
        setTitle(tr("capture <i>nothingssss</i>&trade;"));
         break;
    }
    m_captured = false;
    setSubTitle(tr("Please connect harness male connector."));
    photoLabel = new QLabel(tr("Please click the capture button to get photo."));
    photoLabel->setScaledContents(true);
    photoLabel->setFixedSize(400, 400);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(photoLabel);
    setLayout(layout);
    //! [22]
}

bool CapturePage::isComplete() const
{
    return m_captured;
}
//! [22]

//! [23]
int CapturePage::nextId() const
{
    int testTypeId = field("testTypeId").toInt();
    int testConnectorId = field("testConnectorId").toInt();
    int cId = this->wizard()->currentId();
    switch(cId)
    {
    case CreateAnalyzeWizard::Page_CaptureA:
        if (testConnectorId == Connetor_Male) {
            if (testTypeId == Analyze_Defect) {
                return CreateAnalyzeWizard::Page_Conclusion;
            } else {
                return CreateAnalyzeWizard::Page_CaptureC;
            }
        } else {
            return CreateAnalyzeWizard::Page_CaptureB;
        }
    case CreateAnalyzeWizard::Page_CaptureB:
        if (testTypeId == Analyze_Defect) {
            return CreateAnalyzeWizard::Page_Conclusion;
        } else {
            return CreateAnalyzeWizard::Page_CaptureC;
        }
    case CreateAnalyzeWizard::Page_CaptureC:
        return CreateAnalyzeWizard::Page_Conclusion;
    default:
        return -1;
    }

}
//! [23]

//! [28]
void CapturePage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);

    if (visible) {

        wizard()->setButtonText(QWizard::CustomButton1, tr("&Capture"));
        wizard()->setOption(QWizard::HaveCustomButton1, true);
        connect(wizard(), &QWizard::customButtonClicked,
                this, &CapturePage::captureButtonClicked);

    } else {
        wizard()->setOption(QWizard::HaveCustomButton1, false);
        disconnect(wizard(), &QWizard::customButtonClicked,
                   this, &CapturePage::captureButtonClicked);
    }
}

void CapturePage::initializePage()
{
    if(nextId() == CreateAnalyzeWizard::Page_Conclusion)
    {
        setButtonText(QWizard::NextButton, tr("&Analyze"));
    }
    else
    {
         setButtonText(QWizard::NextButton, tr("&Next"));
    }
}
//! [28]
//!
void CapturePage::captureButtonClicked()
{
    QImage image;
    image.load(":/pics/try1");

    QPixmap pixmapToShow = QPixmap::fromImage( image.scaled(photoLabel->size(), Qt::KeepAspectRatio) );

    photoLabel->setPixmap(pixmapToShow);

    m_captured = true;
    emit completeChanged();
}

AnalyzeProgressPage::AnalyzeProgressPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Analyze Progress..."));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AnalyzeProgressPage::processinc);
    analyzeProgressBar = new QProgressBar;
    analyzeProgressBar->setRange(0,100);
    bottomLabel = new QLabel;
    bottomLabel->setWordWrap(true);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(analyzeProgressBar);
    layout->addWidget(bottomLabel);
    analyzeProgressBar->setAlignment(Qt::AlignVCenter);
    setLayout(layout);
}

bool AnalyzeProgressPage::isComplete() const
{
    return m_processBarValue >= 100;
}

//! [26]
int AnalyzeProgressPage::nextId() const
{
    return -1;
}

void AnalyzeProgressPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);

//    if (visible) {

//        wizard()->setButtonText(QWizard::CustomButton2, tr("&Analyze"));
//        wizard()->setOption(QWizard::HaveCustomButton2, true);
//        connect(wizard(), &QWizard::customButtonClicked,
//                this, &AnalyzeProgressPage::execAnalyze);

//    } else {
//        wizard()->setOption(QWizard::HaveCustomButton2, false);
//        disconnect(wizard(), &QWizard::customButtonClicked,
//                   this, &AnalyzeProgressPage::execAnalyze);
//    }
}

bool AnalyzeProgressPage::execAnalyze()
{

    bool flag = false;
    QCoreApplication::addLibraryPath("./");
    typedef bool (*SumFunction)(char *,char *,char *,int);
    qDebug() << QApplication::applicationDirPath();


    if(!QFile::exists("./debug/tmpApi.dll"))
    {
        QFile dllFile(":/libs/gongtou_Detect_DefectOrlight.dll");
        dllFile.copy("./debug/tmpApi.dll");
    }
    if(QLibrary::isLibrary("./debug/tmpApi.dll"))
    {
        qDebug() << "QLibrary isLibrary!";
    }
    QLibrary library("tmpApi");
    if(library.load())
    {
        //?mutou_Detect_Defect@@YA_NPEAD0@Z
        SumFunction detect=(SumFunction)library.resolve("?gongtou_Detect_DefectOrlight@@YA_NPEAD00H@Z");
        if ( detect )
        {
            qDebug() << "QLibrary resolve!";
            try
            {
                flag = detect("C:\\qtconfig\\gongtou01.png", "C:\\qtconfig\\gongtou01.png", "C:\\qtconfig\\gpldata01.txt", 2);

            }
            catch(QString exception)
            {
                 qDebug()<<exception;
            }
        }
        else
        {
            qDebug()<<library.errorString()<<endl;
        }
    }
    else {
        qDebug() << "QLibrary load error!";
        qDebug()<<library.errorString()<<endl;
    }
    m_finished = true;
    return flag;
}

void AnalyzeProgressPage::processinc()
{
    if (m_processBarValue < 100) {

        if(m_processBarValue < 40)
        {
            m_processBarValue += 0.5;
        }
        else if(m_processBarValue < 70 && m_processBarValue >= 40)
        {
             m_processBarValue += 1;
        }
        else{
            if(!m_finished)
            {
                m_processBarValue += 0.05;
            }
            else
            {
                m_processBarValue += 2;
            }
        }
        analyzeProgressBar->setValue(m_processBarValue);
    } else if (m_processBarValue >= 100) {
        analyzeProgressBar->setValue(100);
        timer->stop();
        emit completeChanged();
    }
}
//! [26]

//! [27]
void AnalyzeProgressPage::initializePage()
{
    QString licenseText;
    licenseText = tr("<u>Upgrade License Agreement:</u> "
                     "This software is licensed under the terms of your "
                     "current license.");
    bottomLabel->setText(licenseText);
    m_processBarValue = 0;
    m_finished = false;
    analyzeProgressBar->setValue(0.0);
    timer->setInterval(20);
    timer->start();
    execAnalyze();
}
//! [27]

