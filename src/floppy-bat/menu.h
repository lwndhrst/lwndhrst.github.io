#pragma once

#include <raylib.h>

typedef enum {
    SCENE_MAIN_MENU,
    SCENE_GAME,
    SCENE_QUIT,
} Scene;

Scene main_menu(int screen_width, int screen_height);
Scene game_over_menu(int screen_width, int screen_height, int score);
