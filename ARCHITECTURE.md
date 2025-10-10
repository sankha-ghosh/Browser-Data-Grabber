# Architecture Documentation

## Project Structure

```
stealer-gui/
├── CMakeLists.txt              # CMake build configuration
├── build.sh                    # Linux build script
├── build.bat                   # Windows build script
├── .gitignore                  # Git ignore rules
│
├── Documentation
│   ├── README.md               # Main documentation (installation, usage, features)
│   ├── QUICKSTART.md           # 5-minute getting started guide
│   ├── CONTRIBUTING.md         # Contribution guidelines
│   ├── LICENSE                 # MIT License with restrictions
│   ├── PROJECT_STATUS.md       # Complete implementation status
│   └── ARCHITECTURE.md         # This file - architecture overview
│
├── example_config.json         # Sample configuration file
│
└── src/                        # Source code directory
    ├── main.cpp                # Application entry point
    │
    ├── ui/                     # User Interface
    │   ├── mainwindow.h        # Main window interface
    │   └── mainwindow.cpp      # Qt GUI implementation
    │
    ├── config/                 # Configuration Management
    │   ├── config.h            # Configuration data structure
    │   └── config.cpp          # JSON serialization/deserialization
    │
    ├── generator/              # Code Generation
    │   ├── stubgenerator.h     # Stub generator interface
    │   └── stubgenerator.cpp   # Generate Windows C++ code from config
    │
    └── build/                  # Build System & Compiler Management
        ├── builder.h           # Build process interface
        ├── builder.cpp         # Invoke compiler, handle output
        ├── compilermanager.h   # Compiler detection interface
        └── compilermanager.cpp # Auto-detect MSVC/MinGW/MinGW-w64
```

## Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     User Interface Layer                     │
│                       (Qt6 Widgets)                          │
├─────────────────────────────────────────────────────────────┤
│  MainWindow                                                  │
│  ├── Downloader Tab      (URL, save path, parameters)       │
│  ├── Grabber Tab         (browsers, apps, wallets)          │
│  ├── Exfiltration Tab    (webhook, HTTP, Telegram)          │
│  ├── Screenshots Tab     (desktop, webcam)                  │
│  ├── System Info Tab     (HWID, IP, OS, AV)                 │
│  ├── Stealth Tab         (hide, mutex, self-destruct)       │
│  ├── Anti-Analysis Tab   (VM, sandbox, debug)               │
│  └── Build Options Tab   (output, arch, compiler)           │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                    Configuration Layer                       │
├─────────────────────────────────────────────────────────────┤
│  Config                                                      │
│  ├── toJson()            Convert to JSON                    │
│  ├── fromJson()          Parse from JSON                    │
│  ├── saveToFile()        Save configuration                 │
│  └── loadFromFile()      Load configuration                 │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                   Code Generation Layer                      │
├─────────────────────────────────────────────────────────────┤
│  StubGenerator                                               │
│  ├── generateStub()           Generate complete C++ code    │
│  ├── generateIncludes()       Windows headers               │
│  ├── generateAntiAnalysis()   VM/sandbox/debug detection    │
│  ├── generateDownloader()     URLDownloadToFile             │
│  ├── generateBrowserGrabber() SQLite + DPAPI                │
│  ├── generateExfiltration()   WinHTTP POST                  │
│  └── generateMainFunction()   Entry point with logic        │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                    Compiler Layer                            │
├─────────────────────────────────────────────────────────────┤
│  CompilerManager                                             │
│  ├── detectCompilers()        Find available compilers      │
│  ├── detectMSVC()            Visual Studio (Windows)        │
│  ├── detectMinGW()           MinGW-w64 (Windows)            │
│  └── detectMinGWW64()        Cross-compiler (Linux)         │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                      Build Layer                             │
├─────────────────────────────────────────────────────────────┤
│  Builder                                                     │
│  ├── build()                 Main build function            │
│  ├── buildWithMSVC()         MSVC compilation               │
│  ├── buildWithMinGW()        MinGW compilation              │
│  ├── buildWithMinGWW64()     Cross-compilation              │
│  └── packWithUPX()           Optional UPX packing           │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                   Output: Windows PE Executable              │
└─────────────────────────────────────────────────────────────┘
```

## Data Flow

### Building an Executable

```
User Input (GUI)
    ↓
Configuration Object (StealerConfig)
    ↓
StubGenerator.generateStub(config)
    ↓
Windows C++ Source Code (stub.cpp)
    ↓
Builder.build(stub.cpp, output.exe)
    ↓
CompilerManager.getCompilerPath()
    ↓
Execute Compiler (g++ / cl.exe)
    ↓
Windows PE Executable (output.exe)
    ↓
Optional: UPX Packing
    ↓
Final Executable
```

### Generated Executable Workflow

```
Stub Execution (on Windows target)
    ↓
Anti-Analysis Checks
    ├→ VM Detection → Exit if detected
    ├→ Sandbox Detection → Exit if detected
    └→ Debug Detection → Exit if detected
    ↓
Create Mutex (single instance)
    ↓
Data Collection
    ├→ System Information (HWID, IP, OS)
    ├→ Browser Data (passwords, cookies)
    ├→ Discord Tokens
    ├→ Cryptocurrency Wallets
    └→ Screenshots
    ↓
Data Exfiltration
    ├→ Discord Webhook (JSON POST)
    ├→ HTTP Endpoint (multipart)
    └→ Telegram Bot (API)
    ↓
Payload Download & Execute
    ├→ URLDownloadToFile(url, path)
    └→ ShellExecuteEx(path, params)
    ↓
Self-Destruct (optional)
    └→ DeleteFile(self)
```

## Key Design Decisions

### 1. Cross-Platform GUI, Windows-Only Output
**Rationale:** Most red team operations target Windows endpoints, while operators use various OSes. Qt6 provides excellent cross-platform support for the GUI.

### 2. Template-Based Code Generation
**Rationale:** Generates clean, readable C++ code that can be inspected and modified. No binary packing or crypters - transparency for security testing.

### 3. WinAPI-Only Dependencies
**Rationale:** Minimizes detection surface, reduces file size, ensures compatibility across Windows versions without DLL dependencies.

### 4. Modular Feature System
**Rationale:** Users can enable only needed features, reducing detection surface and binary size.

### 5. JSON Configuration Format
**Rationale:** Human-readable, easy to version control, supports team collaboration on red team engagements.

### 6. Static Linking
**Rationale:** Generated executables are portable and don't require runtime dependencies on target systems.

## Security Considerations

### GUI Application
- No sensitive data stored
- Configurations may contain webhooks/tokens (use .gitignore)
- Build output is temporary (cleaned automatically)

## Performance Characteristics

### GUI Application
- **Startup Time:** < 1 second
- **Memory Usage:** ~50-100 MB (Qt overhead)
- **Build Time:** 5-30 seconds (depends on compiler, features)

### Generated Executables
- **Size:** 100 KB - 2 MB (depends on features, packing)
- **Execution Time:** < 5 seconds (normal operation)
- **Memory Usage:** 5-20 MB
- **Network:** Minimal (only for exfiltration)

## Extension Points

### Adding New Features

1. **New Data Source:**
   - Update `config.h` with new boolean flag
   - Add UI checkbox in `mainwindow.cpp`
   - Implement grabber function in `stubgenerator.cpp`
   - Add to JSON serialization in `config.cpp`

2. **New Exfiltration Method:**
   - Add endpoint config in `config.h`
   - Add UI field in Exfiltration tab
   - Implement HTTP client code in `stubgenerator.cpp`

3. **New Anti-Analysis Technique:**
   - Add boolean flag in `config.h`
   - Add checkbox in Anti-Analysis tab
   - Implement detection logic in `generateAntiAnalysis()`

4. **New Compiler Support:**
   - Add enum value to `CompilerType`
   - Implement detection in `CompilerManager`
   - Add build function in `Builder`

## Technology Stack

### Languages
- **C++17:** Core application and generated stubs
- **Qt Meta-Object Language:** Qt signals/slots

### Frameworks & Libraries
- **Qt6:** GUI framework (Widgets, Network, Core)
- **CMake:** Build system configuration
- **WinAPI:** Windows system programming
- **Standard C++ Library:** String manipulation, containers

### Tools
- **CMake 3.16+:** Build configuration
- **MinGW-w64:** Cross-compilation toolchain
- **MSVC 2019+:** Native Windows compilation
- **UPX (optional):** Executable packing

## Build Process

### CMake Configuration Phase
```
cmake ..
  ↓
Find Qt6 package
  ↓
Configure source files
  ↓
Generate Makefiles/VS projects
```

### Compilation Phase
```
make / msbuild
  ↓
MOC: Generate Qt meta-object code
  ↓
Compile C++ sources
  ↓
Link Qt libraries
  ↓
Create executable
```

### Stub Compilation Phase (Runtime)
```
User clicks "Build"
  ↓
Generate stub source code
  ↓
Write to temporary file
  ↓
Invoke compiler with flags
  ↓
Capture compiler output
  ↓
Display in GUI
  ↓
Optional UPX packing
  ↓
Output final .exe
```

## Future Architecture Considerations

### Scalability
- Plugin system for additional features
- Distributed compilation support
- Batch building of multiple configurations

### Maintainability
- Unit tests for each component
- Integration tests for build pipeline
- Automated UI testing

### Security
- Code signing integration
- Encrypted configuration storage
- Secure credential handling

---

**Note:** This architecture emphasizes clarity, modularity, and ethical use for authorized security testing.





