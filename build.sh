#!/bin/bash

mkdir -p build
mkdir -p bin

psp-gcc -c vfpu/vfpu.s -o build/vfpu.o
psp-ar rcs bin/libVectorMathVFPU.a build/vfpu.o
