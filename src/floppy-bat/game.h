#pragma once

#include <raylib.h>

#include "obstacles.h"
#include "player.h"

typedef struct {
    Player player;
    ObstacleSystem obstacle_system;
    int screen_width;
    int screen_height;
    int sprite_scale;
    int score;
    int score_x;
    int score_y;
} Game;

void init_game(Game *game, int screen_width, int screen_height);
void run_game(Game *game);
void destroy_game(Game *game);
