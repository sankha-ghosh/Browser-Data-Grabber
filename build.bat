@echo off
setlocal EnableExtensions DisableDelayedExpansion

echo ===================================
echo Stealer Builder - Build Script
echo ===================================
echo.

REM [1/5] Check CMake
echo [1/5] Checking dependencies...
where cmake >nul 2>nul || (
  echo ERROR: CMake not found.
  echo Install from: https://cmake.org/download/
  exit /b 1
)
echo - CMake found

REM [2/5] Check/Install MSVC
echo.
echo [2/5] Checking for MSVC compiler...
where cl.exe >nul 2>nul && goto msvc_found

echo - MSVC not found. Attempting auto-install...

REM Try winget first
where winget >nul 2>nul && (
  echo - Installing Visual Studio 2022 Build Tools via winget (this takes 10-15 minutes)...
  winget install -e --id Microsoft.VisualStudio.2022.BuildTools --silent --accept-package-agreements --accept-source-agreements --override "--quiet --wait --norestart --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended" >nul 2>nul
  timeout /t 5 /nobreak >nul
  where cl.exe >nul 2>nul && goto msvc_found
)

REM Try direct download
echo - Downloading VS Build Tools installer...
set "VSBT_INSTALLER=%TEMP%\vs_BuildTools.exe"
powershell -NoProfile -ExecutionPolicy Bypass -Command "[Net.ServicePointManager]::SecurityProtocol='Tls12'; try { Invoke-WebRequest -Uri 'https://aka.ms/vs/17/release/vs_BuildTools.exe' -OutFile '%VSBT_INSTALLER%' -UseBasicParsing; exit 0 } catch { exit 1 }" >nul 2>nul
if exist "%VSBT_INSTALLER%" (
  echo - Installing VS Build Tools silently (this takes 10-15 minutes)...
  start /wait "" "%VSBT_INSTALLER%" --quiet --wait --norestart --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended
  timeout /t 3 /nobreak >nul
  REM Try to find cl.exe
  where cl.exe >nul 2>nul && goto msvc_found
)

echo.
echo WARNING: MSVC auto-install failed. Manual install required:
echo   1. Download: https://aka.ms/vs/17/release/vs_BuildTools.exe
echo   2. Run installer and select "Desktop development with C++"
echo   3. After install, open "x64 Native Tools Command Prompt for VS 2022"
echo   4. Run: build
echo.
echo Alternatively, if VS Build Tools IS installed but cl.exe not detected:
echo   - Make sure you run this script in "x64 Native Tools Command Prompt for VS 2022"
echo.
exit /b 1

:msvc_found
echo - MSVC found

REM Initialize Visual Studio environment
echo - Setting up Visual Studio environment...
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
  call "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
  call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
  call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
  call "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" (
  call "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" >nul 2>nul
) else (
  echo WARNING: Could not find Visual Studio environment setup script
  echo Make sure you're running this from "x64 Native Tools Command Prompt for VS 2022"
)

REM Verify compiler is accessible after environment setup
where cl.exe >nul 2>nul || (
  echo ERROR: cl.exe not accessible after environment setup
  echo Please run this script from "x64 Native Tools Command Prompt for VS 2022"
  echo Or install Visual Studio Build Tools with C++ workload
  exit /b 1
)

REM [3/5] Check/Install Python
echo.
echo [3/5] Checking for Python...
set "PY_CMD="
where py >nul 2>nul && set "PY_CMD=py" && goto py_found
where python >nul 2>nul && set "PY_CMD=python" && goto py_found
if exist "%ProgramFiles%\Python312\python.exe" set "PY_CMD=%ProgramFiles%\Python312\python.exe" && goto py_found
if exist "%LocalAppData%\Programs\Python\Python312\python.exe" set "PY_CMD=%LocalAppData%\Programs\Python\Python312\python.exe" && goto py_found

echo - Python not found. Attempting auto-install...

REM Try winget first
where winget >nul 2>nul && (
  echo - Installing Python via winget...
  winget install -e --id Python.Python.3.12 --silent --accept-package-agreements --accept-source-agreements >nul 2>nul
  timeout /t 3 /nobreak >nul
  where py >nul 2>nul && set "PY_CMD=py" && goto py_found
)

REM Try direct download
echo - Downloading Python installer...
set "PY_INSTALLER=%TEMP%\python-3.12.6-amd64.exe"
powershell -NoProfile -ExecutionPolicy Bypass -Command "[Net.ServicePointManager]::SecurityProtocol='Tls12'; try { Invoke-WebRequest -Uri 'https://www.python.org/ftp/python/3.12.6/python-3.12.6-amd64.exe' -OutFile '%PY_INSTALLER%' -UseBasicParsing; exit 0 } catch { exit 1 }" >nul 2>nul
if exist "%PY_INSTALLER%" (
  echo - Installing Python silently...
  start /wait "" "%PY_INSTALLER%" /quiet InstallAllUsers=1 PrependPath=1 Include_pip=1
  timeout /t 2 /nobreak >nul
  REM Refresh PATH
  where py >nul 2>nul && set "PY_CMD=py" && goto py_found
  where python >nul 2>nul && set "PY_CMD=python" && goto py_found
  if exist "%ProgramFiles%\Python312\python.exe" set "PY_CMD=%ProgramFiles%\Python312\python.exe" && goto py_found
)

echo.
echo WARNING: Auto-install failed. Please install Python manually:
echo   1. Download: https://www.python.org/ftp/python/3.12.6/python-3.12.6-amd64.exe
echo   2. Run installer and check "Add Python to PATH"
echo   3. Open a NEW VS command prompt
echo   4. Run: build
echo.
exit /b 1

:py_found
echo - Python found: %PY_CMD%

REM Add Python Scripts to PATH (for aqt.exe)
if exist "%ProgramFiles%\Python312\Scripts" set "PATH=%ProgramFiles%\Python312\Scripts;%PATH%"
if exist "%LocalAppData%\Programs\Python\Python312\Scripts" set "PATH=%LocalAppData%\Programs\Python\Python312\Scripts;%PATH%"

REM [4/5] Check/Install Qt
echo.
echo [4/5] Checking for Qt...
set "QT_VERSION=6.7.2"
set "QT_ROOT=C:\Qt"
set "QT_DIR=%QT_ROOT%\%QT_VERSION%\msvc2019_64"
set "QT_ARCH=win64_msvc2019_64"

if exist "%QT_DIR%\bin\Qt6Core.dll" goto qt_found

echo - Qt not found. Attempting auto-install...
echo - Installing aqtinstall (Qt installer)...
"%PY_CMD%" -m pip install --quiet --upgrade aqtinstall
if errorlevel 1 (
  echo WARNING: Failed to install aqtinstall. Check Python/pip.
  goto qt_manual
)

echo - Downloading Qt %QT_VERSION% MSVC 2019 x64 (this takes 5-10 minutes)...
"%PY_CMD%" -m aqt install-qt --outputdir %QT_ROOT% windows desktop %QT_VERSION% %QT_ARCH%
if errorlevel 1 (
  echo WARNING: Qt download failed.
  goto qt_manual
)

if not exist "%QT_DIR%\bin\Qt6Core.dll" goto qt_manual
goto qt_found

:qt_manual
echo.
echo Qt auto-install failed. Manual install options:
echo.
echo Option 1 - Using aqtinstall (recommended):
echo   1. Ensure Python is working: py --version
echo   2. Install aqtinstall: py -m pip install aqtinstall
echo   3. Download Qt: py -m aqt install-qt --outputdir C:\Qt windows desktop 6.7.2 win64_msvc2019_64
echo   4. Set these environment variables in this prompt:
echo      set Qt6_DIR=C:\Qt\6.7.2\msvc2019_64\lib\cmake\Qt6
echo      set CMAKE_PREFIX_PATH=C:\Qt\6.7.2\msvc2019_64
echo   5. Run: build
echo.
echo Option 2 - Using official installer:
echo   1. Download Qt: https://www.qt.io/download-qt-installer
echo   2. Install Qt 6.7.2 with MSVC 2019 64-bit component
echo   3. Set these environment variables in this prompt:
echo      set Qt6_DIR=C:\Qt\6.7.2\msvc2019_64\lib\cmake\Qt6
echo      set CMAKE_PREFIX_PATH=C:\Qt\6.7.2\msvc2019_64
echo   4. Run: build
echo.
exit /b 1

:qt_found
set "Qt6_DIR=%QT_DIR%\lib\cmake\Qt6"
set "CMAKE_PREFIX_PATH=%QT_DIR%"
echo - Qt found at: %QT_DIR%

REM [5/5] Build
echo.
echo [5/5] Building...

REM Force clean build to avoid generator mismatch
if exist build (
  echo - Removing stale build directory...
  rd /S /Q build 2>nul
  timeout /t 1 /nobreak >nul
)
md build || (
  echo ERROR: Failed to create build directory
  exit /b 1
)

echo - Configuring with CMake...
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
  echo - VS 2022 not available, trying VS 2019...
  rd /S /Q build 2>nul
  timeout /t 1 /nobreak >nul
  md build
  cmake -S . -B build -G "Visual Studio 16 2019" -A x64
  if errorlevel 1 (
    echo ERROR: CMake configuration failed.
    echo.
    echo This usually means:
    echo 1. Visual Studio environment not properly set up
    echo 2. Qt installation incomplete
    echo.
    echo Try running this script from "x64 Native Tools Command Prompt for VS 2022"
    echo Or install Visual Studio Build Tools with C++ workload
    echo.
    exit /b 1
  )
)

echo - Building Release configuration...
cmake --build build --config Release
if errorlevel 1 (
  echo ERROR: Build failed. Check build errors above.
  exit /b 1
)

REM Copy final binary and Qt DLLs to project root
if exist build\bin\Release\StealerBuilder.exe (
  echo - Copying executable and Qt DLLs to project root...
  copy /Y build\bin\Release\StealerBuilder.exe . >nul 2>nul
  REM Copy Qt6 DLLs from Qt installation
  if exist "%QT_DIR%\bin\Qt6Core.dll" copy /Y "%QT_DIR%\bin\Qt6Core.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Gui.dll" copy /Y "%QT_DIR%\bin\Qt6Gui.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Widgets.dll" copy /Y "%QT_DIR%\bin\Qt6Widgets.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Network.dll" copy /Y "%QT_DIR%\bin\Qt6Network.dll" . >nul 2>nul
  REM Copy platform plugin
  if exist "%QT_DIR%\plugins\platforms\qwindows.dll" (
    if not exist platforms mkdir platforms
    copy /Y "%QT_DIR%\plugins\platforms\qwindows.dll" platforms\ >nul 2>nul
  )
  REM Copy styles plugin
  if exist "%QT_DIR%\plugins\styles\qwindowsvistastyle.dll" (
    if not exist styles mkdir styles
    copy /Y "%QT_DIR%\plugins\styles\qwindowsvistastyle.dll" styles\ >nul 2>nul
  )
) else if exist build\bin\StealerBuilder.exe (
  echo - Copying executable and Qt DLLs to project root...
  copy /Y build\bin\StealerBuilder.exe . >nul 2>nul
  REM Copy Qt6 DLLs from Qt installation
  if exist "%QT_DIR%\bin\Qt6Core.dll" copy /Y "%QT_DIR%\bin\Qt6Core.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Gui.dll" copy /Y "%QT_DIR%\bin\Qt6Gui.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Widgets.dll" copy /Y "%QT_DIR%\bin\Qt6Widgets.dll" . >nul 2>nul
  if exist "%QT_DIR%\bin\Qt6Network.dll" copy /Y "%QT_DIR%\bin\Qt6Network.dll" . >nul 2>nul
  REM Copy platform plugin
  if exist "%QT_DIR%\plugins\platforms\qwindows.dll" (
    if not exist platforms mkdir platforms
    copy /Y "%QT_DIR%\plugins\platforms\qwindows.dll" platforms\ >nul 2>nul
  )
  REM Copy styles plugin
  if exist "%QT_DIR%\plugins\styles\qwindowsvistastyle.dll" (
    if not exist styles mkdir styles
    copy /Y "%QT_DIR%\plugins\styles\qwindowsvistastyle.dll" styles\ >nul 2>nul
  )
)

echo.
echo ===================================
echo Build successful!
echo ===================================
echo.
echo Run the application:
echo   .\StealerBuilder.exe (copied to project root)
echo.
exit /b 0


// Commit 24 - 2024-03-18


