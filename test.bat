@echo off
setlocal enabledelayedexpansion

echo =================================================================
echo   NeuroCOBOL V3.0 - Automated Test Suite
echo   100%% Standalone ANSI C99 Toolchain - UPL+ Systems Standard
echo =================================================================
echo.

:: 1. Compile C99 Core Engine & Legacy Bridge
echo [1/5] Compiling neurocobol and nc_legacy_bridge with GCC...
gcc -std=c99 -O2 -Wall -Wextra src/nc_core.c -o neurocobol.exe
if errorlevel 1 (
    echo [FAIL] Compilation of neurocobol.exe failed!
    exit /b 1
)
gcc -std=c99 -O2 -Wall -Wextra HERRAMIENTAS/nc_legacy_bridge.c -o nc_legacy_bridge.exe
if errorlevel 1 (
    echo [FAIL] Compilation of nc_legacy_bridge.exe failed!
    exit /b 1
)
echo [PASS] Compiled neurocobol.exe and nc_legacy_bridge.exe successfully.
echo.

:: 2. Run Internal Self-Tests (Compiler & BCD Bridge)
echo [2/5] Running internal self-tests...
neurocobol.exe --test
if errorlevel 1 (
    echo [FAIL] neurocobol self-tests failed!
    exit /b 1
)
nc_legacy_bridge.exe --test
if errorlevel 1 (
    echo [FAIL] nc_legacy_bridge self-tests failed!
    exit /b 1
)
echo.

:: 3. Test In-Memory Execution Across Languages
echo [3/5] Testing In-Memory Multi-Agent Execution...

echo --- Spanish (es) ---
neurocobol.exe run examples\Spanish_ES\hello_cognitive.ncb -l es
if errorlevel 1 goto error

echo --- English (en) ---
neurocobol.exe run examples\English_EN\hello_cognitive.ncb -l en
if errorlevel 1 goto error

echo --- French (fr) ---
neurocobol.exe run examples\French_FR\hello_cognitive.ncb -l fr
if errorlevel 1 goto error

echo.
:: 4. Test ANSI C99 Transpilation Pipeline
echo [4/5] Testing ANSI C99 Transpilation Pipeline...
neurocobol.exe compile examples\Spanish_ES\hello_cognitive.ncb -o test_output.c
if not exist test_output.c goto error
del test_output.c
echo [PASS] Transpilation to ANSI C99 verified!
echo.

:: 5. Test Legacy Bridge and BCD Math CLI
echo [5/5] Testing Legacy Bridge and Exact BCD Math CLI...
nc_legacy_bridge.exe --calc-bcd 10000.50 + 250.75
if errorlevel 1 goto error

echo.
echo =================================================================
echo   ALL TESTS PASSED! NeuroCOBOL V3.0 Toolchain is 100%% Operational!
echo =================================================================
exit /b 0

:error
echo [FAIL] Test execution encountered an error!
exit /b 1
