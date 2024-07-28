#pragma once
#include <vector>
#include <raylib.h>

class Grid{
  public:
    Grid();
    void Initalize();
    void Print();
    void Draw();
    int grid[20][10];
  private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};