#!/bin/bash

BOARD=pico2_w
TARGET=$1

if [[ -z "${TARGET}" ]]; then
    echo "No target app was given. Please try again specifying one"
    return
fi
BUILD_DIR=build_$BOARD
INIT_PATH=`pwd`
SCRIPT_PATH=`realpath "$0"`
cd $SCRIPT_PATH
# cd $HOME/repos/sandbox/exercises/pico/pico-examples

cmake -S . -B $BUILD_DIR -GNinja -DPICO_BOARD=$BOARD -DCMAKE_BUILD_TYPE=Debug
echo "Building $TARGET for $BOARD"
cmake --build $BUILD_DIR --target $TARGET

cd $INIT_PATH