@echo off

call :setESC

echo.
echo %ESC%[1m##########################################################################%ESC%[1m%ESC%[0m%ESC%[0m
echo %ESC%[1m# Regenerate makefiles with cmake                                        #%ESC%[1m%ESC%[0m%ESC%[0m
echo %ESC%[1m##########################################################################%ESC%[1m%ESC%[0m%ESC%[0m

if exist set_env.cmd (
    call set_env.cmd
    if ERRORLEVEL ==1 goto :END 
)


CHOICE /C YN /T 20 /D N /M "This will DELETE your existing build files if you have not saved them."
if ERRORLEVEL ==255 goto :END 
if ERRORLEVEL ==2 goto :END 

echo.
echo %ESC%[1m1. Delete old build files%ESC%[1m%ESC%[0m%ESC%[0m
rmdir /s /q _build
mkdir _build


echo.
echo %ESC%[1m2. Generate the Debug Makefile%ESC%[1m%ESC%[0m%ESC%[0m

mkdir _build\debug
pushd _build\debug
cmake -G "MinGW Makefiles" -D CMAKE_TOOLCHAIN_FILE=..\..\cmake\arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Debug ..\..
if ERRORLEVEL == 1 (
    echo.
    echo %ESC%[91m[FAILED]%ESC%[91m%ESC%[0m%ESC%[0m The generation of the debug makefiles did not complete properly...
    popd
    goto :END 
)
echo.
echo %ESC%[92m[Succcess]%ESC%[92m%ESC%[0m%ESC%[0m Debug makefiles built successfully
popd


echo.
echo %ESC%[1m3. Generate the Release Makefile%ESC%[1m%ESC%[0m%ESC%[0m
mkdir _build\release
pushd _build\release
cmake -G "MinGW Makefiles" -D CMAKE_TOOLCHAIN_FILE=..\..\cmake\arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Release ..\..
if ERRORLEVEL == 1 (
    echo.
    echo %ESC%[91m[FAILED]%ESC%[91m%ESC%[0m%ESC%[0m The generation of the debug makefiles did not complete properly...
    popd
    goto :END 
)
echo.
echo %ESC%[92m[Succcess]%ESC%[92m%ESC%[0m%ESC%[0m Release makefiles built successfully
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