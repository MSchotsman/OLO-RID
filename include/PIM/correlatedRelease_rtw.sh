#!/bin/bash

export C_COMP_ROOT="/usr/bin"

make -f correlatedRelease_rtw_linux.mk clean
make -f correlatedRelease_rtw_linux.mk all
