#include "player.h"

#define GRAVITY 9.81f

void
init_player(Player *player, int screen_width, int screen_height, int sprite_scale)
{
    Vector2 position = {(float)(screen_width >> 2), (float)(screen_height >> 1)};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 25.0f * GRAVITY * sprite_scale};

    player->position = position;
    player->velocity = velocity;
    player->acceleration = acceleration;

    player->tap_strength = 75.0f * sprite_scale;

    player->spritesheet = LoadTexture(TextFormat("%s/spritesheets/bat.png", ASSETS_PATH));
    player->sprite_width = 16 * sprite_scale;
    player->sprite_height = 16 * sprite_scale;
    player->time_since_tap = 0.0f;

    player->hitbox_offset_top = player->sprite_height >> 2;
    player->hitbox_offset_bot = player->sprite_height >> 2;
    player->hitbox_offset_top = player->sprite_width >> 2;
    player->hitbox_offset_bot = player->sprite_width >> 2;
}

void
update_player(Player *player, float delta_time)
{
    player->time_since_tap += delta_time;

    if (IsKeyPressed(KEY_SPACE))
    {
        player->velocity.y -= player->tap_strength;
        player->time_since_tap = 0.0f;
    }

    player->velocity.y += delta_time * player->acceleration.y;
    player->position.y += delta_time * player->velocity.y;
}

void
draw_player(Player *player)
{
    Rectangle player_rect = {player->position.x, player->position.y, player->sprite_width, player->sprite_height};

    const int frame_width = 16;
    const int frame_height = 16;
    const int num_frames = 4;

    Rectangle frames[num_frames];
    for (int i = 0; i < num_frames; ++i)
    {
        frames[i] = (Rectangle){i * frame_width, 0, frame_width, frame_height};
    }

    float rotation = player->velocity.y * 0.025f;

    if (player->time_since_tap > 0.35f)
    {
        DrawTexturePro(player->spritesheet, frames[0], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else if (player->time_since_tap > 0.25f)
    {
        DrawTexturePro(player->spritesheet, frames[3], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else if (player->time_since_tap > 0.1f)
    {
        DrawTexturePro(player->spritesheet, frames[2], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
    else
    {
        DrawTexturePro(player->spritesheet, frames[1], player_rect, (Vector2){0, 0}, rotation, WHITE);
    }
}

bool
check_out_of_bounds(Player *player, int screen_width, int screen_height)
{
    return player->position.y + player->hitbox_offset_top < 0.0f ||
           screen_height + player->hitbox_offset_bot < player->position.y + player->sprite_height;
}
