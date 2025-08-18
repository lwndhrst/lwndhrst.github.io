#include "menu.h"

#define TITLE_FONT_SIZE 64
#define TEXT_FONT_SIZE (TITLE_FONT_SIZE >> 1)

Scene
main_menu(int screen_width, int screen_height)
{
    int x = screen_width >> 3;
    int y = x;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_S))
        {
            return SCENE_GAME;
        }

        if (IsKeyPressed(KEY_Q))
        {
            return SCENE_QUIT;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("MAIN MENU",
                 x,
                 y,
                 TITLE_FONT_SIZE,
                 BLACK);

        DrawText("[s] start game",
                 x,
                 y + TITLE_FONT_SIZE,
                 TEXT_FONT_SIZE,
                 BLACK);

        DrawText("[q] quit",
                 x,
                 y + TITLE_FONT_SIZE + TEXT_FONT_SIZE,
                 TEXT_FONT_SIZE,
                 BLACK);

        EndDrawing();
    }

    return SCENE_QUIT;
}

Scene
game_over_menu(int screen_width, int screen_height, int score)
{
    int x = screen_width >> 3;
    int y = x;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R))
        {
            return SCENE_GAME;
        }

        if (IsKeyPressed(KEY_B))
        {
            return SCENE_MAIN_MENU;
        }

        if (IsKeyPressed(KEY_Q))
        {
            return SCENE_QUIT;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("SCORE - %d", score),
                 x,
                 y,
                 TITLE_FONT_SIZE,
                 BLACK);

        DrawText("[r] retry",
                 x,
                 y + TITLE_FONT_SIZE,
                 TEXT_FONT_SIZE,
                 BLACK);

        DrawText("[b] back to menu",
                 x,
                 y + TITLE_FONT_SIZE + TEXT_FONT_SIZE,
                 TEXT_FONT_SIZE,
                 BLACK);

        DrawText("[q] quit",
                 x,
                 y + TITLE_FONT_SIZE + TEXT_FONT_SIZE * 2,
                 TEXT_FONT_SIZE,
                 BLACK);

        EndDrawing();
    }

    return SCENE_QUIT;
}
