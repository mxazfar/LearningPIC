#!/bin/bash

echo "Building production firmware"

make -f nbproject/Makefile-default.mk SUBPROJECTS= .build-conf
make  -f nbproject/Makefile-default.mk dist/default/production/Learning_PIC.X.production.hex