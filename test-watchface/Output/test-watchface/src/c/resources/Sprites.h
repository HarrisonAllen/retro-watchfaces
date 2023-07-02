#pragma once

#include <pebble.h>

#define SPRITE_DATA_SIZE 3
#define LUIGIBIG_STAND 0
#define LUIGIBIG_WALK0 1
#define LUIGIBIG_WALK1 2
#define LUIGIBIG_WALK2 3

uint8_t LUIGIBIG_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Stand
    8, 1, 2, // Walk0
    16, 1, 2, // Walk1
    24, 1, 2, // Walk2
};

static uint16_t load_LuigiBig(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load LuigiBig tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LUIGIBIG_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load LuigiBig palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_LUIGIBIG_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LUIGIBIG_DATA;
    
    return num_loaded_tiles;
}

#define LUIGIFIRE_STAND 0
#define LUIGIFIRE_WALK0 1
#define LUIGIFIRE_WALK1 2
#define LUIGIFIRE_WALK2 3

uint8_t LUIGIFIRE_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Stand
    8, 1, 2, // Walk0
    16, 1, 2, // Walk1
    24, 1, 2, // Walk2
};

static uint16_t load_LuigiFire(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load LuigiFire tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LUIGIFIRE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load LuigiFire palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_LUIGIFIRE_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LUIGIFIRE_DATA;
    
    return num_loaded_tiles;
}

#define LUIGISMALL_STAND 0
#define LUIGISMALL_WALK0 1
#define LUIGISMALL_WALK1 2
#define LUIGISMALL_WALK2 3

uint8_t LUIGISMALL_DATA[] = {
    // vram tile start, width, height
    0, 1, 1, // Stand
    4, 1, 1, // Walk0
    8, 1, 1, // Walk1
    12, 1, 1, // Walk2
};

static uint16_t load_LuigiSmall(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load LuigiSmall tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LUIGISMALL_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load LuigiSmall palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_LUIGISMALL_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LUIGISMALL_DATA;
    
    return num_loaded_tiles;
}

#define MARIOBIG_STAND 0
#define MARIOBIG_WALK0 1
#define MARIOBIG_WALK1 2
#define MARIOBIG_WALK2 3

uint8_t MARIOBIG_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Stand
    8, 1, 2, // Walk0
    16, 1, 2, // Walk1
    24, 1, 2, // Walk2
};

static uint16_t load_MarioBig(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load MarioBig tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MARIOBIG_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MarioBig palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIOBIG_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MARIOBIG_DATA;
    
    return num_loaded_tiles;
}

#define MARIOFIRE_STAND 0
#define MARIOFIRE_WALK0 1
#define MARIOFIRE_WALK1 2
#define MARIOFIRE_WALK2 3

uint8_t MARIOFIRE_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Stand
    8, 1, 2, // Walk0
    16, 1, 2, // Walk1
    24, 1, 2, // Walk2
};

static uint16_t load_MarioFire(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load MarioFire tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MARIOFIRE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MarioFire palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIOFIRE_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MARIOFIRE_DATA;
    
    return num_loaded_tiles;
}

#define MARIOSMALL_STAND 0
#define MARIOSMALL_WALK0 1
#define MARIOSMALL_WALK1 2
#define MARIOSMALL_WALK2 3

uint8_t MARIOSMALL_DATA[] = {
    // vram tile start, width, height
    0, 1, 1, // Stand
    4, 1, 1, // Walk0
    8, 1, 1, // Walk1
    12, 1, 1, // Walk2
};

static uint16_t load_MarioSmall(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load MarioSmall tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MARIOSMALL_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MarioSmall palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIOSMALL_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MARIOSMALL_DATA;
    
    return num_loaded_tiles;
}

#define MARIOWEIRD_STAND 0
#define MARIOWEIRD_WALK0 1
#define MARIOWEIRD_WALK1 2
#define MARIOWEIRD_WALK2 3

uint8_t MARIOWEIRD_DATA[] = {
    // vram tile start, width, height
    0, 1, 2, // Stand
    8, 1, 2, // Walk0
    16, 1, 2, // Walk1
    24, 1, 2, // Walk2
};

static uint16_t load_MarioWeird(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {
    // Load MarioWeird tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MARIOWEIRD_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MarioWeird palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIOWEIRD_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MARIOWEIRD_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 7

uint16_t (*LOAD_SPRITE_GROUP[7])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) = {
    load_LuigiBig,
    load_LuigiFire,
    load_LuigiSmall,
    load_MarioBig,
    load_MarioFire,
    load_MarioSmall,
    load_MarioWeird,
};
