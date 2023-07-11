#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define FEMALE_WALK0 0
#define FEMALE_WALK1 1
#define FEMALE_WALK2 2
#define FEMALE_WALK3 3

const uint8_t FEMALE_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Female(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Female tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_FEMALE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Female palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, FEMALE_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = FEMALE_DATA;
    
    return num_loaded_tiles;
}

#define MALE_WALK0 0
#define MALE_WALK1 1
#define MALE_WALK2 2
#define MALE_WALK3 3

const uint8_t MALE_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Walk0
    6, 1, 2, // Walk1
    12, 1, 2, // Walk2
    18, 1, 2, // Walk3
};

static uint16_t load_Male(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Male tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MALE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Male palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, MALE_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MALE_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 2

uint16_t (*LOAD_SPRITE_GROUP[2])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_Female,
    load_Male,
};
