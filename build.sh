#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_FLAGS="-march=native" -D EIGEN_INCLUDE_DIR=~/eigen-eigen-5a0156e40feb ../
cmake --build .
