#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

clang++ -std=c++17 main.cpp -o compile
sudo chmod u+x compile

$SCRIPT_DIR/parse $1