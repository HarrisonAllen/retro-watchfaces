#pragma once

#include <pebble.h>
#include "Palettes.h"

#define SPRITE_DATA_SIZE 3
#define AIRSHOOTER_WALK1 0
#define AIRSHOOTER_WALK2 1
#define AIRSHOOTER_WALK3 2
#define AIRSHOOTER_WALK4 3

const uint8_t AIRSHOOTER_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_AirShooter(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load AirShooter tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_AIRSHOOTER_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load AirShooter palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, AIRSHOOTER_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = AIRSHOOTER_DATA;
    
    return num_loaded_tiles;
}

#define ATOMICFIRE_WALK1 0
#define ATOMICFIRE_WALK2 1
#define ATOMICFIRE_WALK3 2
#define ATOMICFIRE_WALK4 3

const uint8_t ATOMICFIRE_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_AtomicFire(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load AtomicFire tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ATOMICFIRE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load AtomicFire palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, ATOMICFIRE_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = ATOMICFIRE_DATA;
    
    return num_loaded_tiles;
}

#define BUBBLELEAD_WALK1 0
#define BUBBLELEAD_WALK2 1
#define BUBBLELEAD_WALK3 2
#define BUBBLELEAD_WALK4 3

const uint8_t BUBBLELEAD_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_BubbleLead(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load BubbleLead tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_BUBBLELEAD_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load BubbleLead palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, BUBBLELEAD_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = BUBBLELEAD_DATA;
    
    return num_loaded_tiles;
}

#define CRASHBOMBER_WALK1 0
#define CRASHBOMBER_WALK2 1
#define CRASHBOMBER_WALK3 2
#define CRASHBOMBER_WALK4 3

const uint8_t CRASHBOMBER_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_CrashBomber(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load CrashBomber tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_CRASHBOMBER_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load CrashBomber palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, CRASHBOMBER_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = CRASHBOMBER_DATA;
    
    return num_loaded_tiles;
}

#define ITEM_WALK1 0
#define ITEM_WALK2 1
#define ITEM_WALK3 2
#define ITEM_WALK4 3

const uint8_t ITEM_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_Item(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load Item tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ITEM_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load Item palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, ITEM_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = ITEM_DATA;
    
    return num_loaded_tiles;
}

#define LEAFSHIELD_WALK1 0
#define LEAFSHIELD_WALK2 1
#define LEAFSHIELD_WALK3 2
#define LEAFSHIELD_WALK4 3

const uint8_t LEAFSHIELD_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_LeafShield(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load LeafShield tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_LEAFSHIELD_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load LeafShield palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, LEAFSHIELD_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = LEAFSHIELD_DATA;
    
    return num_loaded_tiles;
}

#define MEGABUSTER_WALK1 0
#define MEGABUSTER_WALK2 1
#define MEGABUSTER_WALK3 2
#define MEGABUSTER_WALK4 3

const uint8_t MEGABUSTER_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_MegaBuster(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load MegaBuster tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MEGABUSTER_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MegaBuster palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, MEGABUSTER_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = MEGABUSTER_DATA;
    
    return num_loaded_tiles;
}

#define METALBLADE_WALK1 0
#define METALBLADE_WALK2 1
#define METALBLADE_WALK3 2
#define METALBLADE_WALK4 3

const uint8_t METALBLADE_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_MetalBlade(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load MetalBlade tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_METALBLADE_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load MetalBlade palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, METALBLADE_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = METALBLADE_DATA;
    
    return num_loaded_tiles;
}

#define QUICKBOOMERANG_WALK1 0
#define QUICKBOOMERANG_WALK2 1
#define QUICKBOOMERANG_WALK3 2
#define QUICKBOOMERANG_WALK4 3

const uint8_t QUICKBOOMERANG_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_QuickBoomerang(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load QuickBoomerang tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_QUICKBOOMERANG_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load QuickBoomerang palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, QUICKBOOMERANG_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = QUICKBOOMERANG_DATA;
    
    return num_loaded_tiles;
}

#define TIMESTOPPER_WALK1 0
#define TIMESTOPPER_WALK2 1
#define TIMESTOPPER_WALK3 2
#define TIMESTOPPER_WALK4 3

const uint8_t TIMESTOPPER_DATA[] = {
    // vram tile start, width, height
    0, 2, 2, // Walk1
    16, 2, 2, // Walk2
    32, 2, 2, // Walk3
    48, 2, 2, // Walk4
};

static uint16_t load_TimeStopper(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) {
    // Load TimeStopper tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_TIMESTOPPER_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load TimeStopper palette
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, TIMESTOPPER_PALETTES[0]);

    // Set number of sprites
    *num_sprites = 4;

    // Set sprite data
    *sprite_data = TIMESTOPPER_DATA;
    
    return num_loaded_tiles;
}

#define NUM_SPRITE_GROUPS 10

uint16_t (*LOAD_SPRITE_GROUP[10])(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, const uint8_t **sprite_data) = {
    load_AirShooter,
    load_AtomicFire,
    load_BubbleLead,
    load_CrashBomber,
    load_Item,
    load_LeafShield,
    load_MegaBuster,
    load_MetalBlade,
    load_QuickBoomerang,
    load_TimeStopper,
};
