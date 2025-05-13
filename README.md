[Leia esta página em português](README-ptbr.md)

# FindTreasure: 2D Maze Adventure in OpenGL

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.6-lightgrey)
![GLUT](https://img.shields.io/badge/GLUT-3.0-orange)
![stb\_image](https://img.shields.io/badge/stb__image-compatible-blue)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)


<p align="center">
  <img src="img/docs/gameplay.gif" alt="" />
</p>

##  Introduction

**FindTreasure** is an interactive application developed in C++ with OpenGL/GLUT, which challenges the player to explore a 2D maze, collecting treasures and avoiding obstacles. The project emphasizes fundamental concepts of computer graphics, modular design and handling of external files, consolidating essential skills for game development.

This project serves as a practical exercise in:

* **2D Computer Graphics**: rendering of shapes and textures using the OpenGL pipeline.

* **Modular Design**: clear separation of responsibilities in different modules (game logic, rendering, resource loading).

* **File Processing**: dynamic reading of maps from external TXT files.

### Input Format

The maze map is defined in a text file with the following format:

```
<N> <M> # Number of rows (N) and columns (M)
<start_row> <start_col> # Starting position of the player (row and column)
<row1> # Sequence of N rows, each with M elements separated by spaces
<row2>
...
<rowN>
```

Each element of the array can be:

* `0`: free space where the player can move.
* `1`: wall blocking the path.
* `*`: treasure that must be collected.

#### Example [entry](!src/entries/map.txt) file:
```txt
5 6
1 1
1 1 1 1 1 1 1
1 0 0 1 * 1
1 * 0 0 0 1
1 1 1 * 0 1
1 1 1 1 1 1
```

With this format, you can create and test multiple scenarios dynamically by simply changing or adding new map files.

### Assets
All visual resources for the project were obtained from public libraries or created and edited manually to ensure FindTreasure's own identity. Textures and icons used are licensed for free use or derived from open-source files, having undergone color, size and format adjustments to maintain aesthetic consistency and functionality in the OpenGL environment.

### Objectives and Features

* **Maze Rendering:** Reading maps in TXT format and converting them into a matrix to draw walls, paths and treasures.
* **Movement and Collision:** Player control via keyboard (`W`, `A`, `S`, `D`), with collision detection to prevent passing through walls.
* **Treasure Collection:** Logic for removing items from the map when collected, updating the score in real time.
* **User Interface (HUD):** Display of elapsed time and amount of treasures collected on the screen.
* **End of Game Screens:** Victory and defeat messages, showing final time and restart conditions.

### Project Structure

```
FindTreasure/
img/
├── assets/
│   ├── floor.png
│   ├── ...
├── docs/
│   ├── gameplay.gif
│   ├── ...             
src/
│   ├── main.cpp           
│   ├── game/
│   │   ├── game.cpp           
│   │   ├── game.hpp           
│   │   ├── textures.cpp           
│   │   ├── textures.hpp           
│   ├── util/
│   │   ├── adjust_directory.cpp           
│   │   ├── colors.hpp           
│   │   ├── maze.hpp           
└── 
```

### How to Run

1. **Prerequisites:**

    * C++ compiler compatible with C++11 or higher (e.g. gcc-13/g++-13).
    * CMake and build tools:

     ```bash
     sudo apt update
     sudo apt install gcc-13 g++-13 cmake build-essential
     ```
   * OpenGL Libraries and Utilities:

     ```bash
     sudo apt install libglew-dev freeglut3-dev mesa-utils
     ```
   * stb\_image library:

     ```bash
     sudo apt install libstb-dev
     ```
2. **Compilation:**

   ```bash
   make
   ```
3. **Execution:**

   ```bash
   make run
   ```
   ou
   ```bash
   make && ./build/jogo
   ```

### Suggestions for future improvements

* **Level System:** Implement multiple maps with increasing difficulty.
* **Enemies:** Add enemies that chase the player.
* **Animations and Effects:** Smooth transitions, particles when collecting treasure.

### Skills

* **Advanced C++ Programming:** Modularization, classes and methods, file and string handling.
* **OpenGL/GLUT:** 2D rendering pipeline, textures, buffer and coordinate manipulation.
* **Debugging and Optimization:** Timer management, efficient callbacks and collision logic.

## Developers

|   | Name             | Github                         | 
| -------------------------------------------------------------------------------------------- | ---------------- | ------------------------------ |
| <img src="https://avatars.githubusercontent.com/u/60756521"  width="100px" heigth="100px" /> | Filipe Abner     | https://github.com/FilipeAbner |
| <img src="https://avatars.githubusercontent.com/u/70250416?v=4"  width="100px" heigth="100px" /> | Lucas Freitas     | https://github.com/LucasFreitaslpf1 |