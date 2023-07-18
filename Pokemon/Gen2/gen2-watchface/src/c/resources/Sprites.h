#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define ETHAN_0 0
#define ETHAN_1 1
#define ETHAN_2 2
#define ETHAN_3 3

const uint8_t ETHAN_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // 0
    6, 1, 2, // 1
    12, 1, 2, // 2
    18, 1, 2, // 3
};

static uint16_t load_Ethan(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Ethan tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ETHAN_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Ethan palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, ETHAN_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = ETHAN_DATA;
    
    return num_loaded_tiles;
}

#define KRIS_0 0
#define KRIS_1 1
#define KRIS_2 2
#define KRIS_3 3

const uint8_t KRIS_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // 0
    6, 1, 2, // 1
    12, 1, 2, // 2
    18, 1, 2, // 3
};

static uint16_t load_Kris(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Kris tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_KRIS_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Kris palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, KRIS_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = KRIS_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 2

uint16_t (*LOAD_SPRITE_GROUP[2])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_Ethan,
    load_Kris,
};
