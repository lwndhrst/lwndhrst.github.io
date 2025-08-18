#pragma once

#include <raylib.h>

#include "player.h"

typedef struct {
    float x;
    float prev_x;
    float top_y;
    float bot_y;
    float top_height;
    float bot_height;
} Obstacle;

typedef struct {
    int screen_width;
    int screen_height;

    float scroll_speed;
    float scroll_accel;

    int spacing_size;
    int opening_size;

    int num_obstacles;
    Obstacle *obstacles;

    Texture2D spritesheet;
    int sprite_width;
    int sprite_height;
} ObstacleSystem;

void init_obstacle_system(ObstacleSystem *obstacle_system, int screen_width, int screen_height, int sprite_scale);
void destroy_obstacle_system(ObstacleSystem *obstacle_system);

void update_obstacles(ObstacleSystem *obstacle_system, float delta_time);
void draw_obstacles(ObstacleSystem *obstacle_system);

bool check_collisions(ObstacleSystem *obstacle_system, Player *player);
int calc_score(ObstacleSystem *obstacle_system, Player *player);
