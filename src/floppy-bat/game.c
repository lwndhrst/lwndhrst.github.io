#include "game.h"

#define SCORE_FONT_SIZE 64

void
init_game(Game *game, int screen_width, int screen_height)
{
    game->screen_width = screen_width;
    game->screen_height = screen_height;
    game->sprite_scale = screen_height / 100;

    game->score = 0;
    game->score_x = screen_width >> 3;
    game->score_y = game->score_x;

    init_player(&game->player, screen_width, screen_height, game->sprite_scale);
    init_obstacle_system(&game->obstacle_system, screen_width, screen_height, game->sprite_scale);
}

void
run_game(Game *game)
{
    bool game_over = false;
    while (!game_over && !WindowShouldClose())
    {
        float delta_time = GetFrameTime();

        update_player(&game->player, delta_time);
        update_obstacles(&game->obstacle_system, delta_time);
        game->score += calc_score(&game->obstacle_system, &game->player);

        game_over = check_collisions(&game->obstacle_system, &game->player) ||
                    check_out_of_bounds(&game->player, game->screen_width, game->screen_height);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_obstacles(&game->obstacle_system);
        draw_player(&game->player);

        DrawText(TextFormat("SCORE - %d", game->score),
                 game->score_x,
                 game->score_y,
                 SCORE_FONT_SIZE,
                 BLACK);

        EndDrawing();
    }
}

void
destroy_game(Game *game)
{
    destroy_obstacle_system(&game->obstacle_system);
}
