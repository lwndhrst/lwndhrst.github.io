#pragma once

#include <raylib.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float tap_strength;

    Texture2D spritesheet;
    int sprite_width;
    int sprite_height;
    float time_since_tap;

    int hitbox_offset_top;
    int hitbox_offset_bot;
    int hitbox_offset_left;
    int hitbox_offset_right;
} Player;

void init_player(Player *player, int screen_width, int screen_height, int sprite_scale);
void update_player(Player *player, float delta_time);
void draw_player(Player *player);

bool check_out_of_bounds(Player *player, int screen_width, int screen_height);
