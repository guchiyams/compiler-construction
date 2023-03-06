# Project Title

CPSC 323 - Project 1 - Lexical Analyzer

## Description

In this project we created a lexical analyzer that reads the source code of a program to break it down into a sequence of tokens or lexemes: identifiers, keywords, operators, literals, etc. It identifies the patterns of characters that represent specific language constructs.

To identify these patters, the lexical analyzer uses a fininte state machine (FSM). The FSM's state transition function is represented as a two-dimensional array, where each column represents an input symbol, and each row as different states. It lists the current state of the machine, the input symbol being read, and the next state to which the machine transitions, given that input symbol.

## Getting Started

### Dependencies

* OS: Mac OS || Linux

### Installing

* Download repository [here](https://drive.google.com/drive/folders/1-hHyjDu8-U9jEtvkZXcql5gZyLFBQCNO?usp=share_link)
* Change ```LexicalAnalyzer``` executable file permission
```
chmod +x LexicalAnalyzer
```

### Executing program

* How to run the program
* Open the command line of your OS
* Change into downloaded repository directory
* Execute the folliwng command:
```
./LexicalAnalyzer <input_file>
```
* NOTE: the input_file can be one of the following:
    * input_01
    * input_02
    * input_03
* NOTE: the output of the program will be printed into the corresponding input file suffix number output file (e.g. input_01 -> 01_output.txt)

## Help

Your OS may reject your attempt to run the downloaded executable file. To fix this, try running the executable file as a super user:
```
sudo ./LexicalAnalyzer <input_file>
```

## Authors

Yamato Eguchi