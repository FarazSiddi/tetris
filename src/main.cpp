#include <raylib.h>

int main()
{
    Color backgroundColor = Color{20, 160, 133, 255};

    const int screenWidth = 300;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}