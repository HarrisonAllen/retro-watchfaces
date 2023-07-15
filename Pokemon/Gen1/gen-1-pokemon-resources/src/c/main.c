#include <pebble.h>
#include "pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

/*
 * This is the duration of a frame, in milliseconds (more or less)
 * E.g. a FRAME_DURATION of 33ms will give ~30 fps
 * For "as fast as possible" (i.e. render as soon as the
 * graphics engine has completed its last draw cycle),
 * use a FRAME_DURATION of 2. 
 * Aplite has a slower CPU than the rest, so it will get worse frame 
 * rate no matter what
 * Basalt and Chalk are very similar, Chalk is just barely slower
 * Diorite has similar performance to Basalt and Chalk, but may
 * need to be tweaked to get the same performance
 */
#define FRAME_DURATION 500

#define NUM_VRAMS 4
#define NUM_BACKGROUNDS 4

#define Y_OFFSET (PBL_DISPLAY_HEIGHT - 180) / 2
#define X_OFFSET (PBL_DISPLAY_WIDTH - 180) / 2

#define NUM_SPRITES 155
#define SPRITE_DATA_BYTES 19
#define SPRITE_BOTTOM_Y 130

static Window *s_window;
static GBC_Graphics *s_gbc_graphics;
static AppTimer *s_frame_timer;  // The timer used to setup the game step callback
static bool sprite_reverse;
static int sprite_min = X_OFFSET + GBC_SPRITE_OFFSET_X + 10;
static int sprite_max = X_OFFSET + GBC_SPRITE_OFFSET_X;
static int sprite_layer = NUM_BACKGROUNDS - 1;
static int sprite_index = 0;
static int sprite_num = 0;

static int s_character_selection = 0;

/**
 * Loads a tilesheet from the resources into a VRAM bank
 */
static void load_tilesheet() {
    // Calculate how many tiles are on the tilesheet
    ResHandle handle = resource_get_handle(RESOURCE_ID_DATA_SAMPLE_TILESHEET);
    size_t res_size = resource_size(handle);
    uint16_t tiles_to_load = res_size / GBC_TILE_NUM_BYTES;

    uint8_t tilesheet_start_offset = 0; // This is the tile on the tilesheet we want to start loading from
    uint8_t vram_start_offset = 0; // This is the tile in the VRAM we want to start loading into
    uint8_t vram_bank = 1; // The VRAM bank we want to store the tiles into
    GBC_Graphics_load_from_tilesheet_into_vram(s_gbc_graphics, RESOURCE_ID_DATA_SAMPLE_TILESHEET, tilesheet_start_offset, 
                                                tiles_to_load, vram_start_offset, vram_bank);
}

static void load_sprite(int sprite_num) {
    ResHandle data_handle = resource_get_handle(RESOURCE_ID_DATA_SPRITE_DATA);
    uint8_t data_buffer[SPRITE_DATA_BYTES];
    resource_load_byte_range(data_handle, sprite_num * SPRITE_DATA_BYTES, data_buffer, SPRITE_DATA_BYTES);
    uint16_t tilesheet_offset = (data_buffer[0] << 8) | data_buffer[1];
    uint8_t sprite_width = data_buffer[2] & 0x0F;
    uint8_t sprite_height = (data_buffer[2] & 0xF0) >> 4;
    uint16_t tiles_to_load = (sprite_width + 1) * (sprite_height + 1);
    GBC_Graphics_set_sprite_palette_array(s_gbc_graphics, 0, &data_buffer[3]);

    GBC_Graphics_load_from_tilesheet_into_vram(s_gbc_graphics, RESOURCE_ID_DATA_SPRITE_TILESHEET, tilesheet_offset, tiles_to_load, 0, 0);

    uint8_t sprite_pixel_width = (sprite_width + 1) * GBC_TILE_WIDTH;
    uint8_t sprite_pixel_height = (sprite_height + 1) * GBC_TILE_HEIGHT;
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    int sprite_x_offset = GBC_SPRITE_OFFSET_X + (bounds.size.w - sprite_pixel_width) / 2;
    int sprite_y_offset = SPRITE_BOTTOM_Y - sprite_pixel_height + GBC_SPRITE_OFFSET_Y;
    GBC_Graphics_oam_set_sprite(s_gbc_graphics, sprite_index, sprite_x_offset, sprite_y_offset, 0, GBC_Graphics_attr_make(0, 0, false, false, false), sprite_width, sprite_height, 0, 0);
}

/**
 * Sets palettes for the backgrounds and sprites. You may find this link helpful: https://developer.rebble.io/developer.pebble.com/guides/tools-and-resources/color-picker/index.html
 */
static void create_palettes() {
    GBC_Graphics_set_bg_palette(s_gbc_graphics, 0, 2, 0b11111111, 0b11111111);
}

static void generate_backgrounds() {
    load_tilesheet();
    for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
        for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, 0, x, y, 1);
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, 1, x, y, 1);
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, 2, x, y, 1);
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, 3, x, y, 1);
        }
    }
}

static void generate_sprite() {
    GBC_Graphics_oam_set_sprite(s_gbc_graphics, sprite_index, 30 + X_OFFSET + GBC_SPRITE_OFFSET_Y, 30 + Y_OFFSET + GBC_SPRITE_OFFSET_Y, 0, GBC_Graphics_attr_make(4, 0, false, false, false), 0, 0, 0, 0);
}

static void step() {
    sprite_num = (sprite_num + 1) % NUM_SPRITES;
    load_sprite(sprite_num);
    
    GBC_Graphics_render(s_gbc_graphics); // Render the screen every step
}

/**
 * The callback for the timer, this is where we call the game step
 */
static void frame_timer_handle(void* context) {
    s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    step();
}

/**
 * Handler for when the app loses or gains focus
 */
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

/**
 * Execute all of the graphics functions
 */
static void window_load(Window *window) {
    // Create the GBC_Graphics object
    s_gbc_graphics = GBC_Graphics_ctor(s_window, NUM_VRAMS, NUM_BACKGROUNDS);

    GBC_Graphics_set_screen_bounds(s_gbc_graphics, GBC_SCREEN_BOUNDS_FULL);

    // load_tilesheet();
    create_palettes();
    generate_backgrounds();
    // generate_sprite();
    load_sprite(sprite_num);

    // Setup the frame timer that will call the game step function
    s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    app_focus_service_subscribe(will_focus_handler);

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
