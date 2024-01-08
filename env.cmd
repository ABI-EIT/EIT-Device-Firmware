:: Update this env file with the paths specific to your system.
::    If everthing is already on the path, just comment out the required lines or delete this file.
echo.
echo Using paths specified in set_env.cmd
echo.
call :setShortPath ARMGCC_DIR "C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\11.2 2022.02"
call :setShortPath MinGW_DIR "C:\\MinGW"
call :setShortPath CMAKE_DIR "C:\\Program Files\\CMake"

goto :EOF

:setShortPath
set "%1=%~s2"
EXIT /b

:EOF