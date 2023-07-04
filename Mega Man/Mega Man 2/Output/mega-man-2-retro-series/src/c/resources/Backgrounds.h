#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Helpers.h"
#include "Palettes.h"
#include "Defines.h"

static void load_AirMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load AirMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_TILESHEET, 0, 0, 0);

    // Load AirMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, AIRMAN_PALETTES[p]);
    }

    // Load AirMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load AirMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_AIRMAN_NUMBERMAPS, numbers_buffer);
}


static void load_BubbleMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load BubbleMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_TILESHEET, 0, 0, 0);

    // Load BubbleMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, BUBBLEMAN_PALETTES[p]);
    }

    // Load BubbleMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load BubbleMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_BUBBLEMAN_NUMBERMAPS, numbers_buffer);
}


static void load_CrashMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load CrashMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_TILESHEET, 0, 0, 0);

    // Load CrashMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, CRASHMAN_PALETTES[p]);
    }

    // Load CrashMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load CrashMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_CRASHMAN_NUMBERMAPS, numbers_buffer);
}


static void load_FlashMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load FlashMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_TILESHEET, 0, 0, 0);

    // Load FlashMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, FLASHMAN_PALETTES[p]);
    }

    // Load FlashMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load FlashMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_FLASHMAN_NUMBERMAPS, numbers_buffer);
}


static void load_HeatMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load HeatMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_TILESHEET, 0, 0, 0);

    // Load HeatMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, HEATMAN_PALETTES[p]);
    }

    // Load HeatMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load HeatMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_HEATMAN_NUMBERMAPS, numbers_buffer);
}


static void load_MetalMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load MetalMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_METALMAN_TILESHEET, 0, 0, 0);

    // Load MetalMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, METALMAN_PALETTES[p]);
    }

    // Load MetalMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_METALMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_METALMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_METALMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_METALMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load MetalMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_METALMAN_NUMBERMAPS, numbers_buffer);
}


static void load_QuickMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load QuickMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_TILESHEET, 0, 0, 0);

    // Load QuickMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, QUICKMAN_PALETTES[p]);
    }

    // Load QuickMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load QuickMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_QUICKMAN_NUMBERMAPS, numbers_buffer);
}


static void load_WoodMan(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {
    // Load WoodMan tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_TILESHEET, 0, 0, 0);

    // Load WoodMan palettes
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, WOODMAN_PALETTES[p]);
    }

    // Load WoodMan tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_BACKGROUNDTILEMAP, BG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_BACKGROUNDATTRMAP, BG_LAYER);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_FOREGROUNDTILEMAP, FG_LAYER);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_FOREGROUNDATTRMAP, FG_LAYER);
    
    // Load WoodMan numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_WOODMAN_NUMBERMAPS, numbers_buffer);
}

#define NUM_BACKGROUND_GROUPS 8

void (*LOAD_BACKGROUND_GROUP[8])(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) = {
    load_AirMan,
    load_BubbleMan,
    load_CrashMan,
    load_FlashMan,
    load_HeatMan,
    load_MetalMan,
    load_QuickMan,
    load_WoodMan,
};
