#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

clang++ -std=c++17 main.cpp -o parse
sudo chmod u+x parse

$SCRIPT_DIR/parse $1