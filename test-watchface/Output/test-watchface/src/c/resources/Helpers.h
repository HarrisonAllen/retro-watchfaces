#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

static void load_tilesheet(GBC_Graphics *gbc_graphics, uint32_t tilesheet_resource_id, uint8_t tilesheet_start_offset, uint8_t vram_start_offset, uint8_t vram_bank) {
    // Calculate how many tiles are on the tilesheet
    ResHandle handle = resource_get_handle(tilesheet_resource_id);
    size_t res_size = resource_size(handle);
    uint16_t tiles_to_load = res_size / GBC_TILE_NUM_BYTES;

    GBC_Graphics_load_from_tilesheet_into_vram(gbc_graphics, tilesheet_resource_id, tilesheet_start_offset, 
                                                tiles_to_load, vram_start_offset, vram_bank);
}

static void load_map(GBC_Graphics *gbc_graphics, uint32_t map_resource_id, uint8_t *target_map) {
    ResHandle handle = resource_get_handle(map_resource_id);
    size_t res_size = resource_size(handle);
    resource_load_byte_range(handle, 0, target_map, res_size);
}

static void load_tilemap(GBC_Graphics *gbc_graphics, uint32_t tilemap_resource_id, uint8_t bg_num) {
    load_map(gbc_graphics, tilemap_resource_id, gbc_graphics->bg_tilemaps + bg_num * GBC_TILEMAP_NUM_BYTES);
}

static void load_attrmap(GBC_Graphics *gbc_graphics, uint32_t attrmap_resource_id, uint8_t bg_num) {
    load_map(gbc_graphics, attrmap_resource_id, gbc_graphics->bg_attrmaps + bg_num * GBC_TILEMAP_NUM_BYTES);
}

static void load_resource(GBC_Graphics *gbc_graphics, uint32_t resource_id, uint8_t *target_buffer) {
    ResHandle handle = resource_get_handle(resource_id);
    size_t res_size = resource_size(handle);
    resource_load(handle, target_buffer, res_size);
}