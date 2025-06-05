#!/bin/bash
##
## EPITECH PROJECT, 2025
## B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
## File description:
## run-cmakes
##

ARGC=$#
MAX_ARGS=1

if [ "$ARGC" -ne "$MAX_ARGS" ]; then
    echo "Error: Invalid number of arguments."
    echo "Usage: $0 [build|clean]"
    exit 1
fi

if [ "$1" = "build" ]; then
    if [ ! -d "./build/" ]; then
        mkdir ./build/
    fi
    cd ./build/
    cmake ..
    make
    cd ..
elif [ "$1" = "clean" ]; then
    rm -rf ./build/
    rm -f zappy_server
else
    echo "Error: Only 'build' and 'clean' are allowed."
    exit 1
fi