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

    const int screenWidth = 500;
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);

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