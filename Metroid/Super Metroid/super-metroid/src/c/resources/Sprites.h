#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define GRAVITYSUIT_01 0
#define GRAVITYSUIT_02 1
#define GRAVITYSUIT_03 2
#define GRAVITYSUIT_04 3

const uint8_t GRAVITYSUIT_DATA[] = {
    // vram tile start, width, height
    0, 7, 7, // 01
    64, 7, 7, // 02
    128, 7, 7, // 03
    192, 7, 7, // 04
};

static uint16_t load_GravitySuit(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load GravitySuit tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_GRAVITYSUIT_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load GravitySuit palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, GRAVITYSUIT_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = GRAVITYSUIT_DATA;
    
    return num_loaded_tiles;
}

#define POWERSUIT_01 0
#define POWERSUIT_02 1
#define POWERSUIT_03 2
#define POWERSUIT_04 3

const uint8_t POWERSUIT_DATA[] = {
    // vram tile start, width, height
    0, 7, 7, // 01
    64, 7, 7, // 02
    128, 7, 7, // 03
    192, 7, 7, // 04
};

static uint16_t load_PowerSuit(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load PowerSuit tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_POWERSUIT_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load PowerSuit palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, POWERSUIT_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = POWERSUIT_DATA;
    
    return num_loaded_tiles;
}

#define VARIASUIT_01 0
#define VARIASUIT_02 1
#define VARIASUIT_03 2
#define VARIASUIT_04 3

const uint8_t VARIASUIT_DATA[] = {
    // vram tile start, width, height
    0, 7, 7, // 01
    64, 7, 7, // 02
    128, 7, 7, // 03
    192, 7, 7, // 04
};

static uint16_t load_VariaSuit(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load VariaSuit tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_VARIASUIT_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load VariaSuit palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, VARIASUIT_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = VARIASUIT_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 3

uint16_t (*LOAD_SPRITE_GROUP[3])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_GravitySuit,
    load_PowerSuit,
    load_VariaSuit,
};
