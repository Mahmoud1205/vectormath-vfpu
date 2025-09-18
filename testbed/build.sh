#!/bin/bash

mkdir -p build
mkdir -p bin

cd ..
./build.sh

cd testbed
make "$@"
