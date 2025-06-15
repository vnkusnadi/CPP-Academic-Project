# C++-Academic-Project
#### Welcome to my collection of academic C++ projects! 👨‍💻 This repository showcases three projects I built as part of my coursework at HKUST for COMP2011. Each project strengthened my skills in programming fundamentals, problem-solving, and system simulation. Below you can find descriptions, key takeaways, and how to run each project

<br>
<br>

## 📘 Project 1: TurnBased-Game-Simulation.cpp

#### 🔍 Description

This project is a simulation of a turn-based strategy game featuring warriors on a 2D grid. Each warrior can move, fight, and shoot in multiple directions based on commands provided. The simulation handles input, action parsing, direction validation, and game logic like health tracking and player interaction.

#### 🎯 What I Learned

- Enums & Constants: Used enumerations and constants to manage game logic clearly.
- 2D Arrays: Learned map representation and manipulation.
- Function Design: Practiced breaking down large functionality into modular functions.
- Game Simulation Logic: Implemented combat mechanics, collision detection, and boundary checking.

#### ▶️ How to Run
    $ g++ TurnBased-Game-Simulation.cpp -o game
    $ ./game

Input should be provided via standard input or redirected from a file.



## 💣 Project 2: MineSweeper-Game-With-Recursion.cpp

#### 🔍 Description
A simplified console version of Minesweeper! It uses recursion to reveal empty cells and calculate surrounding mines. The game supports loading from files and interactive exploration.

#### 🎯 What I Learned
- Recursion: Practiced pure recursive solutions for flood-fill and count operations.
- File I/O: Worked with file reading for map initialization.
- Game State Logic: Learned how to design game mechanics like mine detection and recursive reveals.

#### ▶️ How to Run
    $ g++ MineSweeper-Game-With-Recursion.cpp -o minesweeper
    $ ./minesweeper
###### Load maps via:
    $ ./minesweeper < testcase/input1.txt

## 🌐 Project 3: Social-Networking-Platform-Prototype.cpp

#### 🔍 Description
This project simulates a simple backend for a social network. It supports user creation, post publishing, liking/unliking posts, and deleting users. It uses dynamic arrays and linked lists for flexible memory usage.

#### 🎯 What I Learned
- Linked Lists: Built user and like relationships with custom pointer-based structures.
- Dynamic Arrays: Managed dynamic memory and resizing.
- Memory Management: Carefully tracked and deleted memory to avoid leaks.
- System Interaction: Built a full user-interaction loop with robust input handling.

#### ▶️ How to Run
    $ g++ Social-Networking-Platform-Prototype.cpp -o socialnet
    $ ./socialnet
  
Follow the menu prompts to interact with the system.


## 🛠️ Development Tools
  - Language: C++ (Standard: C++11/C++14)
  - Compiler: g++ (MinGW/GCC)
  - Platform: Windows 10 / Linux (tested via WSL & Ubuntu)

## 🧠 Future Improvements
  - 🗺️ Add UI to the Turn-Based Game.
  - 🐛 Add undo/redo and difficulty scaling to Minesweeper.
  - 📱 Expand social network to include comments, timestamps, and friend requests.

## Thanks for exploring my projects! Feel free to fork or give suggestions. 😊
