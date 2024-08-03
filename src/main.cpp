#include <raylib.h>
#include "game.h"

double lastUpdateTime = 0.0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

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
        if(EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(backgroundColor);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}