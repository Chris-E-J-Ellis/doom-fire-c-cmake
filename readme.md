# Doom Fire in C 

A version of the Doom Fire effect, inspired by the excellent article by [Fabien Sanglard](http://fabiensanglard.net/doom_fire_psx/).

Largely just a small project for some experimentation with CMake, naming conventions, and general malarky. Only tested on Windows.

## Requirements
- [SDL2](https://www.libsdl.org/) development libraries and headers should be extracted to `./libs/SDL2` folder
- [PDCurses](https://pdcurses.org/) libraries built for `wincon` (`libpdcurses.a` and `pdcurses.dll`) along with `panel.h` and `curses.h` headers should be extracted to `./PDCurses` folder
