#include <pebble.h>
#include "resources/Backgrounds.h"
#include "resources/Numbers.h"
#include "resources/Sprites.h"
#include "resources/SpriteActor.h"
#include "resources/Defines.h"
#include "pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

// TODO: Overhaul

static Window *s_window;
static GBC_Graphics *s_gbc_graphics;
static AppTimer *s_frame_timer;

static uint8_t s_number_buffer[NUMBER_HEIGHT * NUMBER_WIDTH * TOTAL_NUMBERS * 2];

SpriteActor sprite_actors[NUM_SPRITE_ACTORS];
static bool changing_sprites = false;

static void draw_number(uint8_t background, uint8_t tile_x, uint8_t tile_y, char number) {
    uint8_t number_value;
    if (number == ':') {
        number_value = 10;
    } else {
        number_value = number - '0';
    }

    uint8_t tile, attr;
    int tile_index;
    for (uint8_t y = 0; y < NUMBER_HEIGHT; y++) {
        for (uint8_t x = 0; x < NUMBER_WIDTH; x++) {
            tile_index = number_value * NUMBER_HEIGHT * NUMBER_WIDTH * 2 + x * 2 + y * NUMBER_WIDTH * 2;
            tile = s_number_buffer[tile_index];
            attr = s_number_buffer[tile_index + 1];
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

    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 0 * NUMBER_WIDTH + 0, TIME_Y_TILE_OFFSET, time_buffer[0]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 1 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[1]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 2 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[2]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 3 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[3]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 4 * NUMBER_WIDTH + 2, TIME_Y_TILE_OFFSET, time_buffer[4]);
}

static void generate_backgrounds() {
    (*LOAD_BACKGROUND_GROUP[rand() % NUM_BACKGROUND_GROUPS])(s_gbc_graphics, s_number_buffer);

    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, BG_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, FG_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);

    // Set up Time layer
    for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
        for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
            GBC_Graphics_bg_set_tile_hidden(s_gbc_graphics, TIME_LAYER, x, y, true);
        }
    }
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, TIME_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET + TIME_Y_PIXEL_SHIFT);
    load_time();
}

static void load_new_sprite(SpriteActor *sprite_actor) {
    (*LOAD_SPRITE_GROUP[rand() % NUM_SPRITE_GROUPS])(s_gbc_graphics,
                                                     sprite_actor->vram_bank, 
                                                     sprite_actor->vram_bank_offset,
                                                     sprite_actor->palette, 
                                                     &(sprite_actor->num_sprites), 
                                                     &(sprite_actor->data));
}

static void step() {
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    if (!changing_sprites) {
        // Scroll backgrounds
        GBC_Graphics_bg_move(s_gbc_graphics, BG_LAYER, BG_STEP_SIZE, 0);
        GBC_Graphics_bg_move(s_gbc_graphics, FG_LAYER, FG_STEP_SIZE, 0);
    }

    // Update time
    load_time();

    if (!changing_sprites) { // Walk in place
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK) {
                sprite_actor_take_step(&sprite_actors[i]);
                sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
            }
        }
    } else { // Move sprites
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK_ON) {
                sprite_actors[i].x += SPRITE_STEP_SIZE;
                if (sprite_actors[i].x >= sprite_actors[i].center_x) {
                    sprite_actors[i].x = sprite_actors[i].center_x;
                    sprite_actors[i].frame = 0;
                    sprite_actors[i].state = AS_WALK;
                } else {
                    sprite_actor_take_step(&sprite_actors[i]);
                }
                sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
            } else if (sprite_actors[i].state == AS_WALK_OFF) {
                sprite_actors[i].x += SPRITE_STEP_SIZE;
                if (sprite_actors[i].x >= bounds.size.w + GBC_SPRITE_OFFSET_X) {
                    load_new_sprite(&sprite_actors[i]);
                    sprite_actor_reset(&sprite_actors[i]);
                } else {
                    sprite_actor_take_step(&sprite_actors[i]);
                }
                sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
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

static void render_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
    }
}

static void initialize_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        uint8_t vram_bank = 1 + i;
        uint8_t vram_start_offset = 0;
        uint8_t palette_num = i;
        uint8_t num_sprites;
        const uint8_t *sprite_data;
        (*LOAD_SPRITE_GROUP[rand() % NUM_SPRITE_GROUPS])(s_gbc_graphics, vram_bank, vram_start_offset, palette_num, &num_sprites, &sprite_data);

        sprite_actor_init(&sprite_actors[i], 
                        s_gbc_graphics,
                        i,
                        vram_bank,
                        vram_start_offset,
                        num_sprites,
                        sprite_data,
                        palette_num);
    }

    sprite_actors[0].state = AS_WALK_ON;
    sprite_actors[0].hidden = false;

    render_sprites();
    start_changing_sprites();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed) {
    if (!changing_sprites) {
        if (UPDATE_EVERY_SECOND ? (tick_time->tm_sec == 0) : (tick_time->tm_min == 0)) {
            for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
                if (sprite_actors[i].state == AS_OFFSCREEN) {
                    sprite_actors[i].state = AS_WALK_ON;
                    sprite_actors[i].hidden = false;
                } else if (sprite_actors[i].state == AS_WALK) {
                    sprite_actors[i].state = AS_WALK_OFF;
                }
            }
            start_changing_sprites();
        }
        step();
    }
    
    // Update time
    load_time();
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

    generate_backgrounds();
    GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, false);
    GBC_Graphics_lcdc_set_sprite_layer_z(s_gbc_graphics, NUM_BACKGROUNDS-1);
    initialize_sprites();

    // Setup the frame timer that will call the game step function
    s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    app_focus_service_subscribe(will_focus_handler);

    // Setup time
    tick_timer_service_subscribe(UPDATE_EVERY_SECOND ? SECOND_UNIT : MINUTE_UNIT, time_handler);

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
