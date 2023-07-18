#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"
#include "Defines.h"

static uint16_t load_Route2(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load Route2 tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_TILESHEET, 0, 0, 0);

    // Load Route2 palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, ROUTE2_PALETTES[p]);
    }

    // Load Route2 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load Route2 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_ROUTE2_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}

#define NUM_BACKGROUND_GROUPS 1

uint16_t (*LOAD_BACKGROUND_GROUP[1])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) = {
    load_Route2,
};
