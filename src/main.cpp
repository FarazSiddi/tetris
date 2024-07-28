#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main()
{
    Color backgroundColor = Color{20, 160, 133, 255};

    const int screenWidth = 300+1;
    const int screenHeight = 600+1;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.Print();

    TBlock block = TBlock();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        grid.Draw();
        block.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}