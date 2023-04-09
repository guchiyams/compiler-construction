# Project 2 - Predictive Parser

## Description

The main goal of this project is to construct a parser that can recognize the syntax of a given programming language based on the rules defined by the context-free grammar. This parser should be able to efficiently and accurately parse the input source code and produce an error-free parse tree. The project will require a thorough understanding of parsing algorithms, lexical analysis, syntax analysis, and compiler construction concepts. The successful completion of this project will demonstrate the ability to develop a reliable and efficient parser for a programming language, which is a crucial component of any compiler or interpreter.

## Getting Started

### Dependencies & Environment

* OS: Mac OS || Linux
* Compiler: LLVM Clang

### Installing

* Download repository [here](https://github.com/guchiyams/compiler-construction)

### Executing program

* Open the command line of your OS
* Change into downloaded repository directory
* Execute the folliwng command:
```
./run_parser.sh <input_file>
```
* NOTE: the input_file can be one of the following:
    * input_01
    * input_02
    * input_03
* NOTE: the output of the program will be printed into the corresponding input file suffix number output file (e.g. input_01 -> 01_output.txt)

## Help

Your OS may reject your attempt to run the downloaded executable file. To fix this, try running the executable file as a super user:
```
sudo ./run_parser.sh <input_file>
```

## Author

Yamato Eguchi