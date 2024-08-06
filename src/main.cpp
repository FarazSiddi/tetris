#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include <vector>

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
        if(EventTriggered(game.delay))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(backgroundColor);
        DrawTextEx(font, "Score", {565, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Statistics", {5, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {570, 175}, 38, 2, WHITE);
        DrawTextEx(font, "Level", {565, 450}, 38, 2, WHITE);
        if(game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {520, 565}, 38, 2, WHITE);
        }
        DrawRectangleRounded({520, 55, 170, 60}, 0.3, 6, lightBlue); // score
        DrawRectangleRounded({520, 490, 170, 60}, 0.3, 6, lightBlue); // level

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {520 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({520, 215, 170, 180}, 0.3, 6, lightBlue); // next block

        char levelText[10];
        sprintf(levelText, "%d", game.level);
        DrawTextEx(font, levelText, {520 + (170 - textSize.x) / 2, 500}, 38, 2, WHITE);


        std::map<int, char> statisticsText = {{0, '0'}, {1, '0'}, {2, '0'}, {3, '0'}, {4, '0'}, {5, '0'}, {6, '0'}};

        DrawRectangleRounded({10, 55, 230, 535}, 0.3, 6, lightBlue); // statistics

        for(int i = 0; i < 7; i++)
        {
            char text[10];
            sprintf(text, "%d", game.statistics[i]);
            DrawTextEx(font, text, {110 + (170 - textSize.x) / 2, 75 + (i * 75)}, 38, 2, WHITE);
        }

        
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}