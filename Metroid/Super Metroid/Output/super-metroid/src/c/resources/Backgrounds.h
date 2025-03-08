#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"
#include "Defines.h"

static uint16_t load_brinstar(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load brinstar tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_TILESHEET, 0, 0, 0);

    // Load brinstar palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, BRINSTAR_PALETTES[p]);
    }

    // Load brinstar tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load brinstar numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_BRINSTAR_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_crateria(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load crateria tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_TILESHEET, 0, 0, 0);

    // Load crateria palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, CRATERIA_PALETTES[p]);
    }

    // Load crateria tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load crateria numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_CRATERIA_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_maridia(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load maridia tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_TILESHEET, 0, 0, 0);

    // Load maridia palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, MARIDIA_PALETTES[p]);
    }

    // Load maridia tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load maridia numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MARIDIA_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_norfair(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load norfair tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_TILESHEET, 0, 0, 0);

    // Load norfair palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, NORFAIR_PALETTES[p]);
    }

    // Load norfair tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load norfair numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_NORFAIR_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_norfair2(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load norfair2 tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_TILESHEET, 0, 0, 0);

    // Load norfair2 palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, NORFAIR2_PALETTES[p]);
    }

    // Load norfair2 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load norfair2 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_NORFAIR2_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}


static uint16_t load_tourian(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) {
    // Load tourian tilesheet
    uint16_t loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_TILESHEET, 0, 0, 0);

    // Load tourian palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, TOURIAN_PALETTES[p]);
    }

    // Load tourian tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load tourian numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_NUMBERMAPS, numbers_buffer);
    load_resource(gbc_graphics, RESOURCE_ID_DATA_TOURIAN_LITTLENUMBERMAPS, little_numbers_buffer);
    return loaded_tiles;
}

#define NUM_BACKGROUND_GROUPS 6

uint16_t (*LOAD_BACKGROUND_GROUP[6])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer, uint8_t *little_numbers_buffer) = {
    load_brinstar,
    load_crateria,
    load_maridia,
    load_norfair,
    load_norfair2,
    load_tourian,
};
