#!/bin/bash

BOARD=pico2_w
TARGET=$1

if [[ -z "${TARGET}" ]]; then
    echo "No target app was given. Please try again specifying one"
    return || exit 1
fi
BUILD_DIR=build_$BOARD
INIT_PATH=`pwd`
SCRIPT_PATH=`dirname $(realpath $BASH_SOURCE)`
echo $SCRIPT_PATH
cd $SCRIPT_PATH
# echo 
# cd $INIT_PATH
# return
# cd $HOME/repos/sandbox/exercises/pico/pico-examples

cmake -S . -B $BUILD_DIR -GNinja -DPICO_BOARD=$BOARD -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
echo "Building $TARGET for $BOARD"
cmake --build $BUILD_DIR --target $TARGET

cd $INIT_PATH
