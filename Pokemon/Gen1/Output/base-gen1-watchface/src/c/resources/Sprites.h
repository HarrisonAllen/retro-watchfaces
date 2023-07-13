#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define LEAF_WALK0 0
#define LEAF_WALK1 1
#define LEAF_WALK2 2
#define LEAF_WALK3 3

const uint8_t LEAF_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Leaf(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Leaf tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LEAF_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Leaf palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, LEAF_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LEAF_DATA;
    
    return num_loaded_tiles;
}

#define LEAF~BW_WALK0 0
#define LEAF~BW_WALK1 1
#define LEAF~BW_WALK2 2
#define LEAF~BW_WALK3 3

const uint8_t LEAF~BW_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Leaf~bw(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Leaf~bw tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LEAF~BW_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Leaf~bw palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, LEAF~BW_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LEAF~BW_DATA;
    
    return num_loaded_tiles;
}

#define RED_WALK0 0
#define RED_WALK1 1
#define RED_WALK2 2
#define RED_WALK3 3

const uint8_t RED_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Red(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Red tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_RED_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Red palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, RED_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = RED_DATA;
    
    return num_loaded_tiles;
}

#define RED~BW_WALK0 0
#define RED~BW_WALK1 1
#define RED~BW_WALK2 2
#define RED~BW_WALK3 3

const uint8_t RED~BW_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Red~bw(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Red~bw tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_RED~BW_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Red~bw palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, RED~BW_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = RED~BW_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 4

uint16_t (*LOAD_SPRITE_GROUP[4])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_Leaf,
    load_Leaf~bw,
    load_Red,
    load_Red~bw,
};
