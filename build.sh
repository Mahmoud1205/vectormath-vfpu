#!/bin/bash

mkdir -p build
mkdir -p bin

psp-gcc -g -c vfpu/vfpu.s -o build/vfpu.o
psp-ar rcs bin/libVectorMathVFPU.a build/vfpu.o
