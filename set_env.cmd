call :setESC

if exist env.cmd (
    call env.cmd
)

SET "TLPATH="
if defined ARMGCC_DIR (
    echo Overriding ARM Toolchain : "%ARMGCC_DIR%"
    SET "TLPATH=%TLPATH%;%ARMGCC_DIR%\bin"
)
if defined MinGW_DIR (
    echo Overriding Make : "%MinGW_DIR%"
    SET "TLPATH=%TLPATH%;%MinGW_DIR%\bin"
)
if defined CMAKE_DIR ( 
    echo Overriding CMake : "%CMAKE_DIR%"
    SET "TLPATH=%TLPATH%;%CMAKE_DIR%\bin"
)
SET "PATH=%TLPATH%;%PATH%"

echo.
echo %ESC%[1mChecking environment ...%ESC%[1m %ESC%[0m %ESC%[0m 
echo.

call :TestProgram arm-none-eabi-gcc "ARM Toolchain"
if %ERRORLEVEL% == 9009 goto :FAILED

call :TestProgram mingw32-make "mingw32-make"
if %ERRORLEVEL% == 9009 goto :FAILED

call :TestProgram cmake "CMake"
if %ERRORLEVEL% == 9009 goto :FAILED

echo.
echo %ESC%[92mEnvironment seems correct%ESC%[92m %ESC%[0m %ESC%[0m 
echo.

goto :EOF


:TestProgram
echo.
where /q %1 %2
if ERRORLEVEL 1 (
    echo %ESC%[91m[ERROR] %ESC%[91m %ESC%[0m %2 ^(%1^) not found! %ESC%[0m
    ::echo ERROR : %2 ^(%1^) not found!
    exit /B 9009
) 
echo %ESC%[92m[SUCCESS] %ESC%[96m %ESC%[0m %2 ^(%1^) found! %ESC%[0m
::echo %2 found :
%1 --version
exit /B 0

:setESC
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set ESC=%%b
  exit /B 0
)
exit /B 0


:FAILED
echo.
echo %ESC%[91mCheck that you have correctly installed the toolchain and configured env.cmd%ESC%[91m
echo %ESC%[0m %ESC%[0m
exit /B 9009