#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <emscripten/console.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "boids.h"

static const int screen_width = 1920;
static const int screen_height = 1080;

static void init(void);
static void update(void);
static void draw(void);
static void draw_gui(Params *params);
static void update_and_draw(void);
static void cleanup(void);

typedef struct {
    SimulationData simulation_data_current;
    SimulationData simulation_data_updated;
    size_t num_boids;
    Params params;
    Camera3D camera;
    Mesh mesh;
    Matrix *transforms;
    Shader shader;
    Material material;
} Data;

static Data data;

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
    InitWindow(screen_width, screen_height, "boids | windhorst.dev");

    data.params.turn_factor = 0.1f;         // turn_factor
    data.params.visual_range = 40.0f;       // visual_range
    data.params.protected_range = 8.0f;     // protected_range
    data.params.centering_factor = 0.0005f; // centering_factor
    data.params.avoid_factor = 0.05f;       // avoid_factor
    data.params.matching_factor = 0.05f;    // matching_factor
    data.params.max_speed = 6.0f;           // max_speed
    data.params.min_speed = 3.0f;           // min_speed

    data.num_boids = 2000;
    boids_init(&data.simulation_data_current,
               &data.simulation_data_updated,
               data.num_boids,
               &data.params);

    data.camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    data.camera.target = (Vector3){0.0f, 0.0f, 1.0f};
    data.camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    data.camera.fovy = 45.0f;
    data.camera.projection = CAMERA_PERSPECTIVE;

    data.mesh = GenMeshCone(1.0f, 4.0f, 3);
    data.transforms = malloc(data.num_boids * sizeof(Matrix));

    const char *vert =
        "#version 100\n"
        "attribute vec3 vertexPosition;"
        "attribute mat4 instanceTransform;"
        "uniform mat4 mvp;"
        "void main()"
        "{"
        "    gl_Position = mvp * instanceTransform * vec4(vertexPosition, 1.0);"
        "}";

    const char *frag =
        "#version 100\n"
        "precision mediump float;"
        "void main()"
        "{"
        "    vec4 fragColor = vec4(0.4, 0.6, 0.7, 1.0);"
        "    gl_FragColor = fragColor;"
        "}";

    data.shader = LoadShaderFromMemory(vert, frag);
    data.shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(data.shader, "instanceTransform");
    data.shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(data.shader, "mvp");
    
    data.material = LoadMaterialDefault();
    data.material.shader = data.shader;
}

void
update(void)
{
    boids_run(&data.simulation_data_current,
              &data.simulation_data_updated,
              data.transforms,
              data.num_boids,
              &data.params,
              50.0f * GetFrameTime());

    SimulationData data_tmp = data.simulation_data_current;
    data.simulation_data_current = data.simulation_data_updated;
    data.simulation_data_updated = data_tmp;
}

void
draw(void)
{
    boids_draw(&data.camera,
               &data.mesh,
               &data.material,
               data.transforms,
               data.num_boids);
}

void
draw_gui(Params *params)
{
    const int slider_width = 200;
    const int slider_height = 20;
    const int slider_margin = 10;
    const int slider_spacing = slider_height + slider_margin;

    const Rectangle turn_factor_slider = {
        slider_margin,
        screen_height - slider_spacing * 6,
        slider_width,
        slider_height};
    const Rectangle visual_range_slider = {
        slider_margin,
        screen_height - slider_spacing * 5,
        slider_width,
        slider_height};
    const Rectangle protected_range_slider = {
        slider_margin,
        screen_height - slider_spacing * 4,
        slider_width,
        slider_height};
    const Rectangle centering_factor_slider = {
        slider_margin,
        screen_height - slider_spacing * 3,
        slider_width,
        slider_height};
    const Rectangle matching_factor_slider = {
        slider_margin,
        screen_height - slider_spacing * 2,
        slider_width,
        slider_height};
    const Rectangle avoid_factor_slider = {
        slider_margin,
        screen_height - slider_spacing,
        slider_width,
        slider_height};

    float turn_factor = params->turn_factor;
    float visual_range = params->visual_range;
    float protected_range = params->protected_range;
    float centering_factor = params->centering_factor;
    float matching_factor = params->matching_factor;
    float avoid_factor = params->avoid_factor;

    GuiSlider(turn_factor_slider, "", "turn_factor", &turn_factor, 0.0f, 0.2f);
    GuiSlider(visual_range_slider, "", "visual_range", &visual_range, 0.0f, 80.0f);
    GuiSlider(protected_range_slider, "", "protected_range", &protected_range, 0.0f, 16.0f);
    GuiSlider(centering_factor_slider, "", "centering_factor", &centering_factor, 0.0f, 0.001f);
    GuiSlider(matching_factor_slider, "", "matching_factor", &matching_factor, 0.0f, 0.1f);
    GuiSlider(avoid_factor_slider, "", "avoid_factor", &avoid_factor, 0.0f, 0.1f);

    params->turn_factor = turn_factor;
    params->visual_range = visual_range;
    params->protected_range = protected_range;
    params->centering_factor = centering_factor;
    params->matching_factor = matching_factor;
    params->avoid_factor = avoid_factor;
}

void
update_and_draw(void)
{
    update();
    draw();
    draw_gui(&data.params);
}

void
cleanup(void)
{
    boids_destroy(&data.simulation_data_current, &data.simulation_data_updated);

    CloseWindow();
}
