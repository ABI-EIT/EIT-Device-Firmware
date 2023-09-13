#!/bin/bash

echo 
echo ##########################################################################
echo # Make (DEBUG)                                                           #
echo ##########################################################################
make -v
echo 

read -p "This will DELETE your existing output files if you have not saved them. [Y|N]" -n 1 -r
echo 
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo 
else
    exit
fi

read -p "Do you wish to perform a clean first. [Y|N]" -n 1 -r
echo 
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo 1. Clean
    pushd _build/debug
    make clean
    popd
else
    echo 1. Skipping clean ...
fi


echo 
echo 2. Compile
pushd _build/debug
make firmware
popd
