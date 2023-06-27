#include <pebble.h>
#include "resources/Numbers.h"
#include "resources/Palettes.h"
#include "resources/Sprites.h"
#include "pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

#define NUM_VRAMS 2
#define NUM_BACKGROUNDS 4
#define SCREEN_WIDTH 184
#define SCREEN_HEIGHT 184
#define SCREEN_X_OFFSET (SCREEN_WIDTH - PBL_DISPLAY_WIDTH) / 2
#define SCREEN_Y_OFFSET (SCREEN_HEIGHT - PBL_DISPLAY_HEIGHT) / 2

#define TIME_TILE_X 3
#define TIME_TILE_Y 6
#define TIME_Y_SHIFT 4
#define TIME_LAYER 2

#define SPRITE_BOTTOM_Y 152
#define FRAMES_PER_SPRITE 4
#define WALK_FRAMES FRAMES_PER_SPRITE - 1
#define TOTAL_SPRITES 28
#define NUM_SPRITE_ACTORS 2

#define FRAME_DURATION 125

typedef enum {
    AS_WALK_ON,
    AS_WALK,
    AS_WALK_OFF,
    AS_OFFSCREEN
} ActorState;

typedef struct {
    uint8_t sprite_index;
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t base_sprite;
    uint8_t walk_frame;
    uint8_t center_x;
    ActorState state;
} SpriteActor;


static Window *s_window;
static GBC_Graphics *s_gbc_graphics;
static AppTimer *s_frame_timer;
SpriteActor sprite_actors[NUM_SPRITE_ACTORS];

static bool changing_sprites = false;

static void load_tilesheet(uint32_t tilesheet_resource_id, uint8_t tilesheet_start_offset, uint8_t vram_start_offset, uint8_t vram_bank) {
    // Calculate how many tiles are on the tilesheet
    ResHandle handle = resource_get_handle(tilesheet_resource_id);
    size_t res_size = resource_size(handle);
    uint16_t tiles_to_load = res_size / GBC_TILE_NUM_BYTES;

    GBC_Graphics_load_from_tilesheet_into_vram(s_gbc_graphics, tilesheet_resource_id, tilesheet_start_offset, 
                                                tiles_to_load, vram_start_offset, vram_bank);
}

static void create_palettes() {
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(s_gbc_graphics, p, BG_PALETTES[p]);
        GBC_Graphics_set_sprite_palette_array(s_gbc_graphics, p, SPRITE_PALETTES[p]);
    }
}

static void load_map(uint32_t map_resource_id, uint8_t *target_map) {
    ResHandle handle = resource_get_handle(map_resource_id);
    size_t res_size = resource_size(handle);
    uint16_t tiles_to_load = res_size / GBC_TILE_NUM_BYTES;
    resource_load_byte_range(handle, 0, target_map, tiles_to_load * GBC_TILE_NUM_BYTES);
}

static void draw_number(uint8_t background, uint8_t tile_x, uint8_t tile_y, char number) {
    uint8_t number_value;
    if (number == ':') {
        number_value = 10;
    } else {
        number_value = number - '0';
    }

    uint8_t tile, attr;
    for (uint8_t y = 0; y < NUMBER_HEIGHT; y++) {
        for (uint8_t x = 0; x < NUMBER_WIDTH; x++) {
            tile = NUMBER_TILES[number_value][x + y * NUMBER_WIDTH];
            attr = NUMBER_ATTRS[number_value][x + y * NUMBER_WIDTH];
            GBC_Graphics_bg_set_tile_and_attrs(s_gbc_graphics, background, x + tile_x, y + tile_y, tile, attr);
        }
    }
}

static void load_time() {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Write the current hours and minutes into a buffer
    static char time_buffer[8];
    strftime(time_buffer, sizeof(time_buffer), clock_is_24h_style() ?
                                            "%H:%M" : "%I:%M", tick_time);

    draw_number(TIME_LAYER, TIME_TILE_X + 0 * NUMBER_WIDTH + 0, TIME_TILE_Y, time_buffer[0]);
    draw_number(TIME_LAYER, TIME_TILE_X + 1 * NUMBER_WIDTH + 1, TIME_TILE_Y, time_buffer[1]);
    draw_number(TIME_LAYER, TIME_TILE_X + 2 * NUMBER_WIDTH + 1, TIME_TILE_Y, time_buffer[2]);
    draw_number(TIME_LAYER, TIME_TILE_X + 3 * NUMBER_WIDTH + 1, TIME_TILE_Y, time_buffer[3]);
    draw_number(TIME_LAYER, TIME_TILE_X + 4 * NUMBER_WIDTH + 2, TIME_TILE_Y, time_buffer[4]);
}

static void generate_backgrounds() {
    // Load BG 0
    load_map(RESOURCE_ID_DATA_BG_0_TILEMAP, s_gbc_graphics->bg_tilemaps + 0 * GBC_TILEMAP_NUM_BYTES);
    load_map(RESOURCE_ID_DATA_BG_0_ATTRMAP, s_gbc_graphics->bg_attrmaps + 0 * GBC_ATTRMAP_NUM_BYTES);
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, 0, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);

    // Load BG 1
    load_map(RESOURCE_ID_DATA_BG_1_TILEMAP, s_gbc_graphics->bg_tilemaps + 1 * GBC_TILEMAP_NUM_BYTES);
    load_map(RESOURCE_ID_DATA_BG_1_ATTRMAP, s_gbc_graphics->bg_attrmaps + 2 * GBC_ATTRMAP_NUM_BYTES);
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, 1, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);

    // Set up BG 2
    for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
        for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
            GBC_Graphics_bg_set_tile_hidden(s_gbc_graphics, TIME_LAYER, x, y, true);
        }
    }
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, TIME_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET + TIME_Y_SHIFT);
    load_time();

    // Hide BG 3
    GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, 3, false);
}

static void initialize_sprite_actor(SpriteActor *sprite_actor, uint8_t sprite_index) {
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);

    uint8_t sprite_num = ((rand() % TOTAL_SPRITES) / FRAMES_PER_SPRITE) * FRAMES_PER_SPRITE;
    uint8_t *sprite_data = SPRITE_DATA[sprite_num];
    sprite_actor->base_sprite = sprite_num;
    sprite_actor->sprite_index = sprite_index;
    sprite_actor->width = GBC_TILE_WIDTH << sprite_data[4];
    sprite_actor->height = GBC_TILE_HEIGHT << sprite_data[5];
    sprite_actor->center_x = (bounds.size.w / 2) - sprite_actor->width / 2 + GBC_SPRITE_OFFSET_X;
    sprite_actor->x = GBC_SPRITE_OFFSET_X - sprite_actor->width;
    sprite_actor->y = SPRITE_BOTTOM_Y - sprite_actor->height + GBC_SPRITE_OFFSET_Y - SCREEN_Y_OFFSET;
    sprite_actor->state = AS_OFFSCREEN;
}

static void render_sprite_actor(SpriteActor *sprite_actor) {
    uint8_t sprite_data_pos = sprite_actor->base_sprite + sprite_actor->walk_frame;
    GBC_Graphics_oam_set_sprite(s_gbc_graphics,
                                sprite_actor->sprite_index,
                                sprite_actor->x,
                                sprite_actor->y,
                                SPRITE_DATA[sprite_data_pos][2],
                                SPRITE_DATA[sprite_data_pos][3],
                                SPRITE_DATA[sprite_data_pos][4],
                                SPRITE_DATA[sprite_data_pos][5],
                                0,
                                0);
    GBC_Graphics_oam_set_sprite_hidden(s_gbc_graphics, sprite_actor->sprite_index, sprite_actor->state == AS_OFFSCREEN);
}

static void render_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        render_sprite_actor(&sprite_actors[i]);
    }
}

static void sprite_actor_take_step(SpriteActor *sprite_actor) {
    sprite_actor->walk_frame = sprite_actor->walk_frame + 1;
    if (sprite_actor->walk_frame > WALK_FRAMES) {
        sprite_actor->walk_frame = 1;
    }
}

static void step() {
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    if (!changing_sprites) {
        // Scroll backgrounds
        GBC_Graphics_bg_move(s_gbc_graphics, 0, 1, 0);
        GBC_Graphics_bg_move(s_gbc_graphics, 1, 2, 0);
    }

    // Update time
    load_time();

    if (!changing_sprites) { // Walk in place
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK) {
                sprite_actor_take_step(&sprite_actors[i]);
                render_sprite_actor(&sprite_actors[i]);
            }
        }
    } else { // Move sprites
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK_ON) {
                sprite_actors[i].x += 4;
                if (sprite_actors[i].x >= sprite_actors[i].center_x) {
                    sprite_actors[i].x = sprite_actors[i].center_x;
                    sprite_actors[i].walk_frame = 0;
                    sprite_actors[i].state = AS_WALK;
                }
                sprite_actor_take_step(&sprite_actors[i]);
                render_sprite_actor(&sprite_actors[i]);
            } else if (sprite_actors[i].state == AS_WALK_OFF) {
                sprite_actors[i].x += 4;
                if (sprite_actors[i].x >= bounds.size.w + GBC_SPRITE_OFFSET_X) {
                    initialize_sprite_actor(&sprite_actors[i], i);
                } else {
                    sprite_actor_take_step(&sprite_actors[i]);
                }
                render_sprite_actor(&sprite_actors[i]);
            }
        }
    }
    GBC_Graphics_render(s_gbc_graphics);
}

static void frame_timer_handle(void* context) {
    step();

    changing_sprites = false;
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state == AS_WALK_ON || sprite_actors[i].state == AS_WALK_OFF) {
            changing_sprites = true;
            break;
        }
    }
    if (!changing_sprites) {
        s_frame_timer = NULL;
    } else {
        s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    }
}

static void start_changing_sprites() {
    changing_sprites = true;
    s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
}

static void generate_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        initialize_sprite_actor(&sprite_actors[i], i);
    }

    sprite_actors[0].state = AS_WALK_ON;

    render_sprites();
    start_changing_sprites();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed) {
    if (!changing_sprites) {
        if (tick_time->tm_min == 0) {
            for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
                if (sprite_actors[i].state == AS_OFFSCREEN) {
                    sprite_actors[i].state = AS_WALK_ON;
                } else if (sprite_actors[i].state == AS_WALK) {
                    sprite_actors[i].state = AS_WALK_OFF;
                }
            }
            start_changing_sprites();
        }
        step();
    }
}

static void will_focus_handler(bool in_focus) {
    if (!in_focus) {
        // If a notification pops up while the timer is firing
        // very rapidly, it will crash the entire watch :)
        // Stopping the timer when a notification appears will prevent this
        if (s_frame_timer != NULL) {
            app_timer_cancel(s_frame_timer);
        }
    } else {
        if (s_frame_timer != NULL) {
            s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
        }
    }
}

static void window_load(Window *window) {
    // Create the GBC_Graphics object
    s_gbc_graphics = GBC_Graphics_ctor(s_window, NUM_VRAMS, NUM_BACKGROUNDS);

    GBC_Graphics_set_screen_bounds(s_gbc_graphics, GBC_SCREEN_BOUNDS_FULL);

    load_tilesheet(RESOURCE_ID_DATA_BG_TILESHEET, 0, 0, 0);
    load_tilesheet(RESOURCE_ID_DATA_SPRITE_TILESHEET, 0, 0, 1);
    create_palettes();
    generate_backgrounds();
    GBC_Graphics_lcdc_set_sprite_layer_z(s_gbc_graphics, NUM_BACKGROUNDS-1);
    generate_sprites();

    // Setup the frame timer that will call the game step function
    // s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    app_focus_service_subscribe(will_focus_handler);

    // Setup time
    tick_timer_service_subscribe(MINUTE_UNIT, time_handler);

    // Display the graphics
    GBC_Graphics_render(s_gbc_graphics);
}

static void window_unload(Window *window) {
    // Destroy the GBC_Graphics object
    GBC_Graphics_destroy(s_gbc_graphics);
}

static void init(void) {
    s_window = window_create();

    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    const bool animated = true;
    window_stack_push(s_window, animated);
}

static void deinit(void) {
    window_destroy(s_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
