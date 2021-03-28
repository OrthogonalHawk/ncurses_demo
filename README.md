# ncurses Demo Library

## Overview
This repo / library contains examples applications that I developed while learning
 more about the *ncurses* text-based User Interface (UI) library.

## Dependencies
The **ncurses_demo** library depends other FALCON repos. The following
 table lists the libraries and the currently supported version/tag/sha of each library.
 Note that other library versions may work as well, but the versions from this table
 are used in the current unit tests and builds.

|LIBRARY|TAG|
|:-----:|:---:|
|[falcon_makefiles](https://github.com/OrthogonalHawk/falcon_makefiles)|master|   <!-- REQUIRED_BUILD_DEPENDENCY -->

## Build Instructions
The following instructions will build the library on an NVIDIA Jetson Nano development kit:

```
$ mkdir ncurses_demo_env
$ cd ncurses_demo_env
$ git clone git@github.com:OrthogonalHawk/ncurses_demo.git
$ cd ncurses_demo
$ ./manage_dependencies.sh --download
$ TARGET=NATIVE make
```

## Issues & Versions
Library development is managed through the built-in GitHub tools at: [https://github.com/OrthogonalHawk/ncurses_demo](https://github.com/OrthogonalHawk/ncurses_demo)
