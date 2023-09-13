#!/bin/bash

echo 
echo ##########################################################################
echo # Regenerate makefiles with cmake                                        #
echo ##########################################################################
cmake --version
echo 

read -p "This will DELETE your existing build files if you have not saved them. [Y|N]" -n 1 -r
echo 
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo 
    echo 1. Delete old build files
    rm -r _build
    mkdir -p _build
else
    exit
fi


echo 
echo 2. Generate the Debug Makefile
mkdir -p _build/debug
pushd _build/debug
cmake -D CMAKE_TOOLCHAIN_FILE=../../cmake/arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Debug ../..
popd


echo 
echo 2. Generate the Release Makefile

mkdir -p _build/release
pushd _build/release
cmake -D CMAKE_TOOLCHAIN_FILE=../../cmake/arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Release ../..
popd