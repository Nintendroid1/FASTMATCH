#!/bin/bash

FILE=/test/test-main.o
if [ ! -f "$FILE" ]; then
    g++ tests-main.cpp -c -o test/test-main.o
fi

g++ src/*.cpp test/*.cpp test/test-main.o -o build/test_fastmatch -I/include -I/test/catch.hpp