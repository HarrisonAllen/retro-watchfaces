#pragma once

#include <pebble.h>

#define NUM_VRAMS 4
#define NUM_BACKGROUNDS 4
#define SCREEN_WIDTH 184
#define SCREEN_HEIGHT 184
#define SCREEN_X_OFFSET (SCREEN_WIDTH - PBL_DISPLAY_WIDTH) / 2
#define SCREEN_Y_OFFSET (SCREEN_HEIGHT - PBL_DISPLAY_HEIGHT) / 2

#define BG_LAYER 0
#define FG_LAYER 1
#define TIME_LAYER 2
#define SPRITE_LAYER 2
#define MASK_LAYER 3

#define MASK_PALETTE_NUM (GBC_PALETTE_NUM_PALETTES - 1)
#define MASK_VRAM_NUM (NUM_VRAMS - 1)
#define MASK_LEVELS 5
#define MASK_VRAM_OFFSET (GBC_VRAM_BANK_NUM_TILES - 1 - MASK_LEVELS)

#define NUMBER_HEIGHT 5
#define NUMBER_WIDTH 3
#define TOTAL_NUMBERS 11

#define FRAME_DURATION 125 // In ms

#define UPDATE_EVERY_SECOND {update_every_second}

#define TIME_X_TILE_OFFSET 3
#define TIME_Y_TILE_OFFSET {time_y_tile_offset}
#define TIME_Y_PIXEL_SHIFT {time_y_pixel_shift}

#define NUM_SPRITE_ACTORS 2
#define SPRITE_BOTTOM_Y {sprite_bottom_y}
#define BG_STEP_SIZE {background_step_size}
#define FG_STEP_SIZE {foreground_step_size}
#define SPRITE_STEP_SIZE {sprite_step_size}