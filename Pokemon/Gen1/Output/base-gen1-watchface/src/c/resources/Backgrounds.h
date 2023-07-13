#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"
#include "Defines.h"

static uint16_t load_Route1(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load Route1 tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_TILESHEET, 0, 0, 0);

    // Load Route1 palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, ROUTE1_PALETTES[p]);
    }

    // Load Route1 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load Route1 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_ROUTE1_NUMBERMAPS, numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_Route1~bw(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load Route1~bw tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_TILESHEET, 0, 0, 0);

    // Load Route1~bw palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, ROUTE1~BW_PALETTES[p]);
    }

    // Load Route1~bw tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load Route1~bw numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_ROUTE1~BW_NUMBERMAPS, numbers_buffer);
    return loaded_tiles;
}

#define NUM_BACKGROUND_GROUPS 2

uint16_t (*LOAD_BACKGROUND_GROUP[2])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) = {
    load_Route1,
    load_Route1~bw,
};
