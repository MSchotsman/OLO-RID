@echo off

set "C_COMP_ROOT=D:\msys64\mingw64\bin"
@set "PATH=%PATH%;%C_COMP_ROOT%"

@REM call "%C_COMP_ROOT%\mingw32-make.exe" -f correlatedRelease_rtw.mk clean
if "%1"=="" ("%C_COMP_ROOT%\mingw32-make.exe" -f correlatedRelease_rtw.mk all)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1