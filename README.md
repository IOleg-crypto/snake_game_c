![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-%234D4D4D.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)
![Subtext](https://img.shields.io/badge/sublime%20text-%23FF9800.svg?&style=for-the-badge&logo=sublime%20text&logoColor=black)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
![Windows](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![Win](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white")
![VSCode](https://img.shields.io/badge/Vscode-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)

# Snake Game

A simple snake game implemented in C using the ncurses library.

## Introduction

This project is a classic snake game where the player controls a snake to collect berries on the screen. Each berry collected increases the length of the snake. The game is implemented in C and uses the ncurses library for handling the console interface.

## Features

- Snake movement and growth
- Berry collection
- Score display
- Screen boundaries wrapping
- Simple keyboard controls
- Game restart and exit options

## Installation

### Prerequisites

Make sure you have the following installed on your system:

- gcc (GNU Compiler Collection)
- ncurses library

You can install the ncurses library using the following commands:

For Debian/Ubuntu-based distributions:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

For RedHat/CentOS-based distributions:

```bash
sudo yum install ncurses-devel
```

For MSYS2 (on Windows):

1. Open the MSYS2 shell.
2. Update the package database and install the ncurses library:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-ncurses
```

# Building the Project

1. Clone the repository:

```bash
https://github.com/IOleg-crypto/snake_game_c.git
cd snake_game_c
```

2. Compile the project:

![alt text](image.png)
Don`t forget update paths in shell script to complie program

```bash
./build.sh
```

# Usage

```bash
start snake_game.exe
```

# Controls

- Arrow keys or W, A, S, D: Move the snake up, left, down, and right
- Q: Restart the game
- E: Exit the game
