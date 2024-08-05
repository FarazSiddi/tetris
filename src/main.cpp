#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

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
    Color backgroundColor = darkBlue;

    const int screenWidth = 700;
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("fonts/monogram.ttf", 264, 0, 0);

    Game game = Game();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(backgroundColor);
        DrawTextEx(font, "Score", {565, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {570, 175}, 38, 2, WHITE);
        if(game.gameOver)
        {
            DrawTextEx(font, "Game Over", {520, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({520, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {520 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({520, 215, 170, 180}, 0.3, 6, lightBlue);
        
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}