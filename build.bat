@echo off
echo =================================================================
echo   NeuroCOBOL V3.0 - Native C99 Build Tool
echo   UPL+ Systems Standard - Zero Python Dependencies
echo =================================================================

if not exist bin mkdir bin

echo [1/2] Compiling neurocobol.exe...
gcc -std=c99 -O2 -Wall -Wextra src/nc_core.c -o neurocobol.exe
gcc -std=c99 -O2 -Wall -Wextra src/nc_core.c -o bin/neurocobol.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile neurocobol.exe
    exit /b 1
)

echo [2/2] Compiling nc_legacy_bridge.exe...
gcc -std=c99 -O2 -Wall -Wextra HERRAMIENTAS/nc_legacy_bridge.c -o nc_legacy_bridge.exe
gcc -std=c99 -O2 -Wall -Wextra HERRAMIENTAS/nc_legacy_bridge.c -o bin/nc_legacy_bridge.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile nc_legacy_bridge.exe
    exit /b 1
)

echo.
echo [SUCCESS] Build completed successfully. Binaries generated in root and bin/
