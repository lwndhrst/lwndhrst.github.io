#include "raylib.h"

#include <emscripten/emscripten.h>

// get canvas size
EM_JS(int, canvas_get_width, (), {
  return canvas.width;
});
EM_JS(int, canvas_get_height, (), {
  return canvas.height;
});

// static const int screenWidth = 800;
// static const int screenHeight = 450;
static int screenWidth = 1920;
static int screenHeight = 1080;

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "windhorst.dev");

    InitGame();

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

    UnloadGame();

    CloseWindow();

    return 0;
}

void InitGame(void)
{
}

void UpdateGame(void)
{
}

void DrawGame(void)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("hello there! :3c", GetScreenWidth() / 2 - MeasureText("hello there! :3c", 20) / 2, GetScreenHeight() / 2, 20, GRAY);
    EndDrawing();
}

void UnloadGame(void)
{
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}
