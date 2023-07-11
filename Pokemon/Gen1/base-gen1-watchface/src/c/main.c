#include <pebble.h>
#include "resources/Backgrounds.h"
#include "resources/Numbers.h"
#include "resources/Sprites.h"
#include "resources/SpriteActor.h"
#include "resources/Defines.h"
#include "pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

static Window *s_window;
static GBC_Graphics *s_gbc_graphics;
static AppTimer *s_frame_timer;

static uint8_t s_number_buffer[NUMBER_HEIGHT * NUMBER_WIDTH * TOTAL_NUMBERS * 2];

SpriteActor sprite_actors[NUM_SPRITE_ACTORS];
SpriteActor *trainer_sprite_actor = &sprite_actors[0];
SpriteActor *pokemon_sprite_actors = &sprite_actors[1];

uint8_t pokemon_data_buffers[NUM_POKEMON_SPRITE_ACTORS][NUM_POKEMON_FRAMES * SPRITE_DATA_BYTES_PER_FRAME];
static bool walking_on = false;
static bool sprite_stepping = false;

static bool changing_backgrounds = false;
static short mask_level = 0;
static short mask_change = 1;

static uint8_t last_background_group, last_sprite_group;

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

static uint16_t generate_backgrounds() {
    uint8_t new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    uint16_t loaded_tiles = (*LOAD_BACKGROUND_GROUP[new_background_group])(s_gbc_graphics, s_number_buffer);
    last_background_group = new_background_group;

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

    return loaded_tiles;
}

static void set_mask_palette() {
#if defined(PBL_COLOR)
    GBC_Graphics_set_bg_palette(s_gbc_graphics, MASK_PALETTE_NUM, 5, GColorBlackARGB8, GColorBlackARGB8, GColorDarkGrayARGB8, GColorLightGrayARGB8, GColorWhiteARGB8);
#else
    GBC_Graphics_set_bg_palette(s_gbc_graphics, MASK_PALETTE_NUM, 5, GBC_COLOR_BLACK, GBC_COLOR_BLACK, GBC_COLOR_ALPHA_GRAY, GBC_COLOR_GRAY, GBC_COLOR_WHITE);
#endif
}

static void generate_mask_layer() {
    load_tilesheet(s_gbc_graphics, RESOURCE_ID_DATA_MASK_TILESHEET, 0, MASK_VRAM_OFFSET, MASK_VRAM_NUM);

    set_mask_palette();

    for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
        for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
            GBC_Graphics_bg_set_tile(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_OFFSET);
            GBC_Graphics_bg_set_tile_palette(s_gbc_graphics, MASK_LAYER, x, y, MASK_PALETTE_NUM);
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_NUM);
        }
    }
    
    GBC_Graphics_alpha_mode_set_bg_enabled(s_gbc_graphics, MASK_LAYER, true);
    GBC_Graphics_alpha_mode_set_mode(s_gbc_graphics, MASK_LAYER, GBC_ALPHA_MODE_ADD);
    GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, false);
}

// I'll leave this here for now, but I'm not using it for this project
static void update_backgrounds() {
    uint8_t new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    while (NUM_BACKGROUND_GROUPS > 1 && new_background_group == last_background_group) {
        new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    }
    (*LOAD_BACKGROUND_GROUP[new_background_group])(s_gbc_graphics, s_number_buffer);
    last_background_group = new_background_group;

    load_time();
}

// TODO: Pokemanz
static void load_new_sprite(SpriteActor *sprite_actor) {
    uint8_t new_sprite_group = rand() % NUM_SPRITE_GROUPS;
    while (new_sprite_group == last_sprite_group) {
        new_sprite_group = rand() % NUM_SPRITE_GROUPS;
    }
    (*LOAD_SPRITE_GROUP[new_sprite_group])(s_gbc_graphics,
                                           sprite_actor->vram_bank, 
                                           sprite_actor->vram_bank_offset,
                                           sprite_actor->palette, 
                                           &(sprite_actor->num_sprites), 
                                           &(sprite_actor->data));
    last_sprite_group = new_sprite_group;
}

static void step() {
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    if (!walking_on && !changing_backgrounds) {
        // Scroll backgrounds
        GBC_Graphics_bg_move(s_gbc_graphics, BG_LAYER, BG_STEP_SIZE, 0);
        GBC_Graphics_bg_move(s_gbc_graphics, FG_LAYER, FG_STEP_SIZE, 0);
    }
    
    if (changing_backgrounds) {
        mask_level += mask_change;
        if (mask_level >= MASK_LEVELS - 1) {
            update_backgrounds();
            set_mask_palette();
            mask_change = -1;
        } else if (mask_level <= 0) {
            changing_backgrounds = false;
            GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, false);
        }
        
        for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
            for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
                GBC_Graphics_bg_set_tile(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_OFFSET + mask_level);
            }
        }
    }

    // Update time
    load_time();

    if (!walking_on) { // Walk in place
        if (sprite_stepping) {
            for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
                if (sprite_actors[i].state == AS_WALK) {
                    sprite_actor_take_step(&sprite_actors[i]);
                    sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
                }
            }
            sprite_stepping = false;
        }
    } else { // Move sprites
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK_ON) {
                sprite_actors[i].x += SPRITE_STEP_SIZE;
                if (sprite_actors[i].x >= sprite_actors[i].center_x) {
                    sprite_actors[i].x = sprite_actors[i].center_x;
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

    walking_on = false;
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state == AS_WALK_ON) {
            walking_on = true;
            break;
        }
    }
    if (!walking_on && !changing_backgrounds) {
        s_frame_timer = NULL;
    } else {
        s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    }
}


static void start_walking_on() {
    walking_on = true;
    if (s_frame_timer == NULL)
        s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
}

static void start_changing_backgrounds() {
    if (NUM_BACKGROUND_GROUPS > 1) {
        changing_backgrounds = true;
        mask_change = 1;
        mask_level = 0;
        GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, true);
        
        if (s_frame_timer == NULL)
            s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    }
}

static void render_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
    }
}

static void initialize_sprites(uint16_t trainer_vram_offset) {
    // 1. Create trainer sprite actor
    // 2. Create pokemon sprite actors
    // 3. Calculate width of all sprite actors side by side
    // 4. Calculate center xs such that trainer is at most at right edge, but
    //    ideally the sprite group is in the center
    // 5. Distribute sprites equally
    // 6. Set all sprites visible and ready to walk on
    uint8_t vram_bank = 0;
    uint8_t vram_start_offset = trainer_vram_offset;
    uint8_t palette_num = 0;
    uint8_t num_sprites;
    const uint8_t *sprite_data;
    uint8_t new_sprite_group = rand() % NUM_SPRITE_GROUPS;
    (*LOAD_SPRITE_GROUP[new_sprite_group])(s_gbc_graphics, vram_bank, vram_start_offset, palette_num, &num_sprites, &sprite_data);
    sprite_actor_init(trainer_sprite_actor,
                        s_gbc_graphics,
                        0,
                        vram_bank,
                        vram_start_offset,
                        num_sprites,
                        sprite_data,
                        palette_num);
    
    
    for (uint8_t i = 0; i < NUM_POKEMON_SPRITE_ACTORS; i++) {
        vram_bank = i+1;
        vram_start_offset = 0;
        palette_num = i+1;
        // Load pokemon sprite, use data array pointers
        int pokemon_number = rand() % NUM_POKEMON;
        load_pokemon_sprite(s_gbc_graphics, pokemon_number, vram_bank, vram_start_offset, i+1, pokemon_data_buffers[i]);
        
        sprite_actor_init(&pokemon_sprite_actors[i], 
                        s_gbc_graphics,
                        i+1,
                        vram_bank,
                        vram_start_offset,
                        NUM_POKEMON_FRAMES,
                        pokemon_data_buffers[i],
                        palette_num);
    }

    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        sprite_actors[i].state = AS_WALK_ON;
        sprite_actors[i].hidden = false;
        sprite_actors[i].center_x = sprite_actors[i].center_x - i * sprite_actors[0].width;
        sprite_actors[i].x = sprite_actors[i].x - i * sprite_actors[0].width;
        sprite_actors[i].frame = i % sprite_actors[i].num_sprites;
    }

    render_sprites();
    start_walking_on();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed) {
    if (units_changed & HOUR_UNIT) {
        start_changing_backgrounds();
    }

    if (!walking_on) {
        // if (UPDATE_EVERY_SECOND ? (units_changed & MINUTE_UNIT) : (units_changed & HOUR_UNIT)) {
        //     for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        //         if (sprite_actors[i].state == AS_OFFSCREEN) {
        //             sprite_actors[i].state = AS_WALK_ON;
        //             sprite_actors[i].hidden = false;
        //         } else if (sprite_actors[i].state == AS_WALK) {
        //             sprite_actors[i].state = AS_WALK_OFF;
        //         }
        //     }
        //     start_walking_on();
        // }
        if (tick_time->tm_sec % SECONDS_BETWEEN_STEPS == 0) {
            sprite_stepping = true;
            step();
        }
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

    uint16_t loaded_tiles = generate_backgrounds();
    generate_mask_layer();
    GBC_Graphics_lcdc_set_sprite_layer_z(s_gbc_graphics, SPRITE_LAYER);
    initialize_sprites(loaded_tiles);

    // Setup the frame timer that will call the game step function
    s_frame_timer = NULL;
    app_focus_service_subscribe(will_focus_handler);

    // Setup time
    tick_timer_service_subscribe(SECOND_UNIT, time_handler);

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
