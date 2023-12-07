# Obfuscated Location Disclosure for Remote ID-enabled UAVs

## Installation steps

Download MiraclCore from [https://github.com/miracl/core/tree/master/c](https://github.com/miracl/core/tree/master/c) and place it in ./include/MiraclCore

Go to ./include/MiraclCore, depending on a 32-bit or 64-bit system run `python3 config32.py` or `python3 config64.py` respectively
To use the same curves as in the report, select curves 3, 8, 10, 28, and 38.
Once the curves have been selected press 0 to complete the process

Go to ./include/PIM
Depending on the operating system, follow the corresponding steps:

### Windows OS
In `correlatedRelease_rtw.bat` 
    Line 3: Change the C compiler path
    Line 7: Change the Make path
In `correlatedRelease_rtw.mk`
    Line 23: Change the START_DIR
    Line 78: Change the Make path

Run correlatedRelease_rtw.bat

Go back to the root of this directory

In `run.bat`
    Line 3: Change the path

Run `run.bat`
Run `main.exe`

### Linux-based OS
In `correlatedRelease_rtw.bat` 
    Line 3: Change the C compiler path
In `correlatedRelease_rtw.mk`
    Line 23: Change the START_DIR
    If Linux is run on a non-standard CPU architecture, such as on a Raspberry PI
        Line 97 and 101: Remove -m64
Run correlatedRelease_rtw.sh

Go back to the root of this directory

Run run.sh
Run main

### Planar Isotropic Mechanism Disclaimer:
This code was automatically generated by MATLAB.