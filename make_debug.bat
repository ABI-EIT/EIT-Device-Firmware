@echo off

call :setESC

echo.
echo %ESC%[1m##########################################################################%ESC%[1m%ESC%[0m%ESC%[0m
echo %ESC%[1m# Make (DEBUG)                                                           #%ESC%[1m%ESC%[0m%ESC%[0m
echo %ESC%[1m##########################################################################%ESC%[1m%ESC%[0m%ESC%[0m

if exist set_env.cmd (
    call set_env.cmd
    if ERRORLEVEL ==1 goto :END 
)


CHOICE /C YN /T 20 /D N /M "This will DELETE your existing output files if you have not saved them."
if ERRORLEVEL ==255 goto :END 
if ERRORLEVEL ==2 goto :END 

echo.
CHOICE /C YN /T 20 /D N /M "Do you wish to perform a clean first?"
if ERRORLEVEL ==255 goto :NOCLEAN 
if ERRORLEVEL ==2 goto :NOCLEAN 

:CLEAN
echo.
echo %ESC%[1m1. Clean%ESC%[1m%ESC%[0m%ESC%[0m
pushd _build\debug
mingw32-make clean
popd
goto :COMPILE

:NOCLEAN
echo.
echo %ESC%[1m1. Skipping clean..%ESC%[1m%ESC%[0m%ESC%[0m

:COMPILE
echo.
echo %ESC%[1m2. Compile%ESC%[1m%ESC%[0m%ESC%[0m
pushd _build\debug
mingw32-make firmware
if ERRORLEVEL == 1 (
    echo.
    echo %ESC%[91m[FAILED]%ESC%[91m%ESC%[0m%ESC%[0m 
    popd
    goto :END 
)
echo.
echo %ESC%[92m[Succcess]%ESC%[92m%ESC%[0m%ESC%[0m Debug built successfully!
popd


:END

echo.
echo.
echo %cmdcmdline% | findstr /i /c:"%~nx0" && set standalone=1
if defined standalone pause

goto :EOF

:setESC
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set ESC=%%b
  exit /B 0
)
exit /B 0
