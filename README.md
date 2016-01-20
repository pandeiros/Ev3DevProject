# LEG0 EV3 Mindstorms robot system written in C++ using ev3dev library.

_v0.2 - Updated January 19, 2016_

## Table od Contents

- [Files structure](#files-structure)
- [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Build](#build)
    - [Deploy](#deploy)
- [Documentation](#documentation)
    - [HTML](#html)
    - [LaTeX](#latex)


# Files structure
#### *root*
Contains this `README.md` file, `Praca.pdf` thesis file and `generate_all` script, which cleans all generated files, then build all project configurations and generate new documentation and pdf files.
#### doc
Doxygen generated documentation, both in HTML and in LaTeX (converted into pdf file). There is also generating script: `doc_gen` which do all the work.
#### include
All application's header files.
#### latex
Thesis' latex files and script generating it: `latex_gen`.
#### nbproject
Essential Makefiles and NetBeans project configuration.
#### src
All application's source files and program entry point.
#### sync
Useful directory to synchronize quickly synchronize executables with multiple remote devices. Use `sync_all` script to do it after compiling the application.
# Installation

## Prerequisites
- **System** - Unix based system.
- **Compiler** - `arm-linux-gnueabi-g++` for device target compilation and `g++` for desktop compilation.

## Build
Use Makefile with one specified configuration, `all` parameter to compile every configuration or run `generate_all` script to do everything at once (until You have all needed components installed).
## Deploy
Use `sync/sync_all` script. Edit it and adjust to Your needs.

# Documentation
Requires Doxygen installed.
## HTML
Open `doc/html/index.html` to start browsing through documentation.
## LaTeX
There is also a pdf version located here: `doc/Ev3Dev.pdf`.
