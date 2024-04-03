# Pipex: The Unix Pipeline Reinvented 🚀

Welcome to `pipex`, a project that is a deep dive into UNIX interprocess communication and the workings of the shell pipeline. As a `42 London` student with a background in full-stack development, I've crafted this C project to emulate the UNIX pipeline behavior.

This repository holds the essence of my journey through system-level programming, presenting a custom implementation of the UNIX command `|`. `pipex` takes the standard output from one command and uses it as the standard input for another, much like combining commands in a shell with a pipe.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Future Scope](#future-scope)

## Introduction

`pipex` is your conduit between commands, a bespoke utility that mirrors the behavior of:

```sh
< infile cmd1 | cmd2 > outfile

It takes an input file, applies a command (cmd1), and directs the output to another command (cmd2), with the final output redirected to an outfile.
Features

    Streamlined Execution: Effortlessly recreate shell pipeline workflows.
    Error Handling: Built-in robust error handling for graceful failure responses.
    Customizability: Easy to modify and extend for various applications.
    Resource Management: Impeccable memory and process management for efficient performance.

Installation

bash

# Clone the repository
git clone git@github.com:Safwaan-GitHub/pipex.git

# Change directory
cd pipex

# Compile the program
make

Usage

To use pipex, compile the source files and then execute it as follows:

sh
```
./pipex infile "cmd1" "cmd2" outfile

This will apply cmd1 to infile and then cmd2 to the output of cmd1, with the final output written to outfile.
Future Scope

I am passionately driving this project towards being a comprehensive toolkit for UNIX systems, potentially including features like support for multiple pipes, increased command parsing sophistication, and broader compatibility. I'm on a path towards cyber security and advanced application development, and pipex is just the beginning.

A great Resouce; https://github.com/madebypixel02 ;
