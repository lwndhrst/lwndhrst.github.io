#include <raylib.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/console.h>

#include <stdbool.h>
#include <stdio.h>

static const int screenWidth = 1920;
static const int screenHeight = 1080;

static void init(void);
static void update(void);
static void draw(void);
static void update_and_draw(void);
static void cleanup(void);

static bool nav_boids_callback(int eventType, const EmscriptenMouseEvent *e, void *userData);

int main(void)
{
    init();

    emscripten_set_main_loop(update_and_draw, 0, 1);

    cleanup();

    return 0;
}

void init(void)
{
    emscripten_set_click_callback("#nav-boids", 0, 1, nav_boids_callback);

    InitWindow(screenWidth, screenHeight, "windhorst.dev");
}

void update(void)
{
}

void draw(void)
{
    const char* text = "hello there! :3c";

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 50) / 2, GetScreenHeight() / 2, 50, GRAY);
    EndDrawing();
}

void update_and_draw(void)
{
    update();
    draw();
}


void cleanup(void)
{
    CloseWindow();
}

bool nav_boids_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
    emscripten_console_log("loading boids scene...");
    return 0;
}
