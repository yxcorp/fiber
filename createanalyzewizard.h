#ifndef CREATEANALYZEWIZARD_H
#define CREATEANALYZEWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <enumsettings.h>

class CreateAnalyzeWizard : public QWizard
{
    Q_OBJECT

public:
    explicit CreateAnalyzeWizard(QWidget *parent = 0);
    enum { Page_Setting, Page_CaptureA, Page_CaptureB, Page_CaptureC,
           Page_Conclusion };
    void accept() Q_DECL_OVERRIDE;
private:
    void showHelp();
};

class SettingPage : public QWizardPage
{
    Q_OBJECT

public:
    SettingPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;
    bool validatePage() Q_DECL_OVERRIDE;
    int testTypeId;
    int testConnectorId;

private:
    QButtonGroup *btnGroupTestType;
    QButtonGroup *btnGroupTestConnector;
    QComboBox *harnessTypeBox;
    QRadioButton *analyzeRadioButton1;
    QRadioButton *analyzeRadioButton2;
    QRadioButton *analyzeRadioButton3;
    QRadioButton *connectorRadioButton1;
    QRadioButton *connectorRadioButton2;
    QRadioButton *connectorRadioButton3;
};

class CapturePage : public QWizardPage
{
    Q_OBJECT

public:
    CapturePage(Capture_Option id, QWidget *parent = 0);

    bool isComplete() const Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void initializePage() Q_DECL_OVERRIDE;

private:
    bool m_captured;
    QLabel *photoLabel;
    void captureButtonClicked();
};

class AnalyzeProgressPage : public QWizardPage
{
    Q_OBJECT

public:
    AnalyzeProgressPage(QWidget *parent = 0);
    bool isComplete() const Q_DECL_OVERRIDE;
    void initializePage() Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;


private:
    QTimer *timer;
    double m_processBarValue;
    bool m_finished;
    QLabel *bottomLabel;
    QProgressBar *analyzeProgressBar;
    bool execAnalyze();
    void processinc();
};
#endif // CREATEANALYZEWIZARD_H
