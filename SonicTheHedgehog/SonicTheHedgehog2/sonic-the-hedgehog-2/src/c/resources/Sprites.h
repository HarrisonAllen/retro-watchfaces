#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define KNUCKLES_RUN0 0
#define KNUCKLES_RUN1 1
#define KNUCKLES_RUN2 2
#define KNUCKLES_RUN3 3

const uint8_t KNUCKLES_DATA[] = {
    // vram tile start, width, height
    0, 3, 3, // Run0
    64, 3, 3, // Run1
    128, 3, 3, // Run2
    192, 3, 3, // Run3
};

static uint16_t load_Knuckles(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Knuckles tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_KNUCKLES_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Knuckles palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, KNUCKLES_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = KNUCKLES_DATA;
    
    return num_loaded_tiles;
}

#define SONIC_RUN0 0
#define SONIC_RUN1 1
#define SONIC_RUN2 2
#define SONIC_RUN3 3

const uint8_t SONIC_DATA[] = {
    // vram tile start, width, height
    0, 3, 3, // Run0
    64, 3, 3, // Run1
    128, 3, 3, // Run2
    192, 3, 3, // Run3
};

static uint16_t load_Sonic(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Sonic tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_SONIC_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Sonic palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, SONIC_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = SONIC_DATA;
    
    return num_loaded_tiles;
}

#define TAILS_RUN0 0
#define TAILS_RUN1 1
#define TAILS_RUN2 2
#define TAILS_RUN3 3

const uint8_t TAILS_DATA[] = {
    // vram tile start, width, height
    0, 3, 3, // Run0
    64, 3, 3, // Run1
    128, 3, 3, // Run2
    192, 3, 3, // Run3
};

static uint16_t load_Tails(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Tails tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_TAILS_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Tails palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, TAILS_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = TAILS_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 3

uint16_t (*LOAD_SPRITE_GROUP[3])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_Knuckles,
    load_Sonic,
    load_Tails,
};
