#include <raylib.h>
#include "grid.h"

int main()
{
    Color backgroundColor = Color{20, 160, 133, 255};

    const int screenWidth = 300+1;
    const int screenHeight = 600+1;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 4;
    grid.grid[17][8] = 7;
    grid.Print();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        grid.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}