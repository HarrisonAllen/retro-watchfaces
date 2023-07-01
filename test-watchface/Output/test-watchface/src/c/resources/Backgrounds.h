#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"


static void load_World1_1(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load World1_1 tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_TILESHEET, 0, 0, 0);

    // Load World1_1 palettes
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_PALETTES, palette_buffer);
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, palette_buffer + p * GBC_PALETTE_NUM_BYTES);
    }

    // Load World1_1 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_BACKGROUNDTILEMAP, 0);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_BACKGROUNDATTRMAP, 0);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_FOREGROUNDTILEMAP, 1);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_FOREGROUNDATTRMAP, 1);
    
    // Load World1_1 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_NUMBERMAPS, numbers_buffer);
}

static void load_World1_2(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load World1_2 tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_TILESHEET, 0, 0, 0);

    // Load World1_2 palettes
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_PALETTES, palette_buffer);
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, palette_buffer + p * GBC_PALETTE_NUM_BYTES);
    }

    // Load World1_2 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_BACKGROUNDTILEMAP, 0);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_BACKGROUNDATTRMAP, 0);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_FOREGROUNDTILEMAP, 1);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_FOREGROUNDATTRMAP, 1);
    
    // Load World1_2 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_NUMBERMAPS, numbers_buffer);
}
#define NUM_BACKGROUND_GROUPS 2

void (*LOAD_BACKGROUND_GROUP[2])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) = {
    load_World1_1,
    load_World1_2,
};
