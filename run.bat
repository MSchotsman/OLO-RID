echo off
echo "Compiling Correlated Release Library"
cd "C:\Users\s153326\Documents\School\2022-2023\Preparation Phase\OLDRIDUAV"
@REM del /s *.obj
cd ".\include\PIM"
call correlatedRelease_rtw.bat
cd "..\.."
echo "Compiling main script"
gcc -o main.exe main.c .\include\PIM\correlatedRelease.lib .\include\MiraclCore\core.a
echo " Script Completed, feel free to run: main.exe"