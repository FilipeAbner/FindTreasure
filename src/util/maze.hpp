#pragma once
#define _MAZE_HPP_
#include <vector>
// Global Structures
struct Maze
{
    std::vector<std::vector<char>> grid;
    int rows;
    int cols;
    int startRow;
    int startCol;
    int treasures = 0;
};
