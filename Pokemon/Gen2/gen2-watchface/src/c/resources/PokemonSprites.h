#pragma once

#include <pebble.h>

static uint16_t load_pokemon_sprite(GBC_Graphics *gbc_graphics, int pokemon_number, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *sprite_data) {
    ResHandle data_handle = resource_get_handle(RESOURCE_ID_DATA_SPRITE_DATA);
    uint8_t data_buffer[BYTES_PER_POKEMON_DATA];
    resource_load_byte_range(data_handle, pokemon_number * BYTES_PER_POKEMON_DATA, data_buffer, BYTES_PER_POKEMON_DATA);
    uint16_t tilesheet_offset = (data_buffer[0] << 8) | data_buffer[1];
    uint8_t sprite_width = data_buffer[2] & 0x0F;
    uint8_t sprite_height = (data_buffer[2] & 0xF0) >> 4;
    uint16_t tiles_per_sprite = (sprite_width + 1) * (sprite_height + 1);
    for (uint8_t i = 0; i < NUM_POKEMON_FRAMES; i++) {
        sprite_data[0 + i * SPRITE_DATA_BYTES_PER_FRAME] = i * tiles_per_sprite;
        sprite_data[1 + i * SPRITE_DATA_BYTES_PER_FRAME] = sprite_width;
        sprite_data[2 + i * SPRITE_DATA_BYTES_PER_FRAME] = sprite_height;
    }
    uint16_t tiles_to_load = tiles_per_sprite * NUM_POKEMON_FRAMES;
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, &data_buffer[3]);

    GBC_Graphics_load_from_tilesheet_into_vram(gbc_graphics, RESOURCE_ID_DATA_SPRITE_TILESHEET, tilesheet_offset, tiles_to_load, vram_start_offset, vram_bank);
    
    return tiles_to_load;
}