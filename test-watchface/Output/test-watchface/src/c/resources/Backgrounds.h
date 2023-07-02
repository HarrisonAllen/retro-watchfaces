#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"


static void load_SuperMarioWorld(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load SuperMarioWorld tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_TILESHEET, 0, 0, 0);

    // Load SuperMarioWorld palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, SUPERMARIOWORLD_PALETTES[p]);
    }

    // Load SuperMarioWorld tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_BACKGROUNDTILEMAP, 0);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_BACKGROUNDATTRMAP, 0);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_FOREGROUNDTILEMAP, 1);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_FOREGROUNDATTRMAP, 1);
    
    // Load SuperMarioWorld numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_SUPERMARIOWORLD_NUMBERMAPS, numbers_buffer);
}


static void load_World1_1(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load World1_1 tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_WORLD1_1_TILESHEET, 0, 0, 0);

    // Load World1_1 palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, WORLD1_1_PALETTES[p]);
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
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, WORLD1_2_PALETTES[p]);
    }

    // Load World1_2 tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_BACKGROUNDTILEMAP, 0);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_BACKGROUNDATTRMAP, 0);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_FOREGROUNDTILEMAP, 1);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_FOREGROUNDATTRMAP, 1);
    
    // Load World1_2 numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WORLD1_2_NUMBERMAPS, numbers_buffer);
}

#define NUM_BACKGROUND_GROUPS 3

void (*LOAD_BACKGROUND_GROUP[3])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) = {
    load_SuperMarioWorld,
    load_World1_1,
    load_World1_2,
};
