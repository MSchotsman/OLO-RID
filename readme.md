
# Obfuscated Location Disclosure for Remote ID-enabled UAVs (OLD-RID)
This is a proof-of-concept for Obfuscated Location Disclosure for Remote ID-enabled UAVs, using a modified Planar Isotropic Mechanism (PIM) from Xiao et al. [\[1\]](https://doi.org/10.1145/2810103.2813640). This code was tested on a Raspberry PI 3 Model B+ (Raspbian OS) and a Personal Computer (VM with a Linux OS). From a flight path, in csv format with headers (latitude, longitude, altitude), it will obfuscate each location and encrypt the UAV's actual location. All of the components needed for a Remote ID message are stored in the `message` variable in `main.c`.  

<figure>
  <img
  src="obfuscated.png"
  alt="obfuscated">
  <figcaption>Flight path with an average (obfuscation) distance of 100 meters and maximum transmit range of 1000 meters.</figcaption>
</figure>

## Installation steps
Download MiraclCore from [https://github.com/miracl/core/tree/master/c](https://github.com/miracl/core/tree/master/c) and place it in `./include/MiraclCore/`.
Go to .`/include/MiraclCore/`, depending on a 32-bit or 64-bit system run `python3 config32.py` or `python3 config64.py`, respectively. To use the same curves as in the report, select curves 3, 8, 10, 28, and 38. Once the curves have been selected press 0 to complete the process.  
Go to `./include/PIM/`  
Depending on the operating system, follow the corresponding steps:

### Windows OS

In `correlatedRelease_rtw.bat`  
* Line 3: Change the C compiler path
* Line 7: Change the Make path

In `correlatedRelease_rtw.mk`
* Line 23: Change the START_DIR
* Line 78: Change the Make path

Run `correlatedRelease_rtw.bat`
Go back to the root of this directory
In `run.bat`
* Line 3: Change the path

Run `run.bat`
Run `main.exe`

### Linux-based OS

In `correlatedRelease_rtw.bat`
* Line 3: Change the C compiler path

In `correlatedRelease_rtw.mk`
* Line 23: Change the START_DIR

If Linux is run on a non-standard CPU architecture, such as on a Raspberry PI
* Line 97 and 101: Remove -m64

Run correlatedRelease_rtw.sh
Go back to the root of this directory
Run `run.sh`
Run `main.exe`

### Future Work

This proof-of-concept was created to obfuscate locations in a location trace. Tested on a Raspberry PI 3 Model B+ and a Personal Computer. To implement it on a UAV changes in the `main.c` are required, of which a few are named here: connection to a GNSS (for the UAV location and velocity, and Control Station location), emergency status indicator, and connection to the Wi-Fi transmitter to send a package.

### Disclaimer:

On top of the GPL-3.0 license, the code in ./include/PIM/ and ./main.* was (mostly) automatically generated by MATLAB, via the MATLAB Coder toolbox. These generated files are all under Academic License:  
Academic License - for use in teaching, academic research, and meeting course requirements at degree granting institutions only. Not for government, commercial, or other organizational use.
