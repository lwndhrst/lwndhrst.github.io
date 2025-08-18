#include <raylib.h>

#include <emscripten/console.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "game.h"
#include "menu.h"

static const int screen_width = 1920;
static const int screen_height = 1080;

static void init(void);
static void update(void);
static void draw(void);
static void update_and_draw(void);
static void cleanup(void);

static Scene scene;
static Game game;
bool game_over;
bool game_initialized;

int
main(void)
{
    init();

    emscripten_set_main_loop(update_and_draw, 0, 1);

    cleanup();

    return 0;
}

void
init(void)
{
    scene = SCENE_MAIN_MENU;
    game_over = false;
    game_initialized = false;

    InitWindow(screen_width, screen_height, "floppy bat | windhorst.dev");
}

void
update(void)
{
}

void
draw(void)
{
}

void
update_and_draw(void)
{
    // update();
    // draw();

    while (!WindowShouldClose())
    {
        switch (scene)
        {
        case SCENE_MAIN_MENU:
            scene = main_menu(screen_width, screen_height);
            break;
        case SCENE_GAME:
            init_game(&game, screen_width, screen_height);
            run_game(&game);
            destroy_game(&game);
            scene = game_over_menu(screen_width, screen_height, game.score);
            break;
        case SCENE_QUIT:
            cleanup();
            break;
        default:
            break;
        }
    }
}

void
cleanup(void)
{
    CloseWindow();
}
