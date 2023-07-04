#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"
#include "Defines.h"

static void load_AquaticRuinZone(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load AquaticRuinZone tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_TILESHEET, 0, 0, 0);

    // Load AquaticRuinZone palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, AQUATICRUINZONE_PALETTES[p]);
    }

    // Load AquaticRuinZone tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load AquaticRuinZone numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_AQUATICRUINZONE_NUMBERMAPS, numbers_buffer);
}


static void load_EmeraldHillZone(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load EmeraldHillZone tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_TILESHEET, 0, 0, 0);

    // Load EmeraldHillZone palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, EMERALDHILLZONE_PALETTES[p]);
    }

    // Load EmeraldHillZone tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load EmeraldHillZone numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_EMERALDHILLZONE_NUMBERMAPS, numbers_buffer);
}


static void load_MysticCaveZone(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load MysticCaveZone tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_TILESHEET, 0, 0, 0);

    // Load MysticCaveZone palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, MYSTICCAVEZONE_PALETTES[p]);
    }

    // Load MysticCaveZone tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load MysticCaveZone numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_MYSTICCAVEZONE_NUMBERMAPS, numbers_buffer);
}

#define NUM_BACKGROUND_GROUPS 3

void (*LOAD_BACKGROUND_GROUP[3])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) = {
    load_AquaticRuinZone,
    load_EmeraldHillZone,
    load_MysticCaveZone,
};
