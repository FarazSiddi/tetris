#include <raylib.h>
#include "game.h"

int main()
{
    Color backgroundColor = Color{20, 160, 133, 255};

    const int screenWidth = 300+1;
    const int screenHeight = 600+1;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.HandleInput();
        BeginDrawing();
        ClearBackground(backgroundColor);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}