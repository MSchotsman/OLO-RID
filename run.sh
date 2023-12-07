#!/bin/bash

echo "Make sure to first compile both PIM and MiraclCore before running this!!!"
echo "Compiling main script"
gcc -o main main.c ./include/PIM/correlatedRelease.a ./include/MiraclCore/core.a -lm
echo " Script Completed, feel free to run: main"