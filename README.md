# Pipex: The Unix Pipeline Reinvented 🚀

Welcome to `pipex`, a project that is a deep dive into UNIX interprocess communication and the workings of the shell pipeline. I've crafted this C project to emulate the UNIX pipeline behavior.

This repository holds the essence of my journey through system-level programming, presenting a custom implementation of the UNIX command `|`. `pipex` takes the standard output from one command and uses it as the standard input for another, much like combining commands in a shell with a pipe.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

`pipex` is your conduit between commands, a bespoke utility that mirrors the behavior of:

< infile cmd1 | cmd2 > outfile

It takes an input file, applies a command (cmd1), and directs the output to another command (cmd2), with the final output redirected to an outfile.

## Installation

```bash
1. Clone the repository
- "git clone https://github.com/Safwaan-GitHub/PipexSolution.git"

2. Change directory
- cd pipex

3. Compile the program
- make
```

## Features

Streamlined Execution: Effortlessly recreate shell pipeline workflows.
Error Handling: Built-in robust error handling for graceful failure responses.
Customizability: Easy to modify and extend for various applications.
Resource Management: Impeccable memory and process management for efficient performance.

## Usage

To use pipex, compile the source files and then execute it as follows:
```
./pipex infile "cmd1" "cmd2" outfile
```
This will apply cmd1 to infile and then cmd2 to the output of cmd1, with the final output written to outfile.
