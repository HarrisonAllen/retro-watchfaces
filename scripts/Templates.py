BACKGROUND_TEMPLATE = \
"""
static void load_{background_group}(GBC_Graphics *gbc_graphics, uint8_t *numbers_buffer) {{
    // Load {background_group} tilesheet
    load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_TILESHEET, 0, 0, 0);

    // Load {background_group} palettes
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_PALETTES, palette_buffer);
    for (uint8_t p = 0; p < GBC_PALETTE_NUM_PALETTES; p++) {{
        GBC_Graphics_set_bg_palette_array(gbc_graphics, p, palette_buffer + p * GBC_PALETTE_NUM_BYTES);
    }}

    // Load {background_group} tilemaps and attrmaps
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_BACKGROUNDTILEMAP, 0);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_BACKGROUNDATTRMAP, 0);
    load_tilemap(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_FOREGROUNDTILEMAP, 1);
    load_attrmap(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_FOREGROUNDATTRMAP, 1);
    
    // Load {background_group} numbers
    load_resource(gbc_graphics, RESOURCE_ID_DATA_{uppercase_background_group}_NUMBERMAPS, numbers_buffer);
}}

"""

SPRITE_TEMPLATE = \
"""
static uint16_t load_{sprite_group}(GBC_Graphics *gbc_graphics, uint8_t vram_bank, uint8_t vram_start_offset, uint8_t palette_num, uint8_t *num_sprites, uint8_t **sprite_data) {{
    // Load {sprite_group} tilesheet
    uint16_t num_loaded_tiles = load_tilesheet(gbc_graphics, RESOURCE_ID_DATA_{uppercase_sprite_group}_TILESHEET, 0, vram_start_offset, vram_bank);

    // Load {sprite_group} palette
    uint8_t palette_buffer[GBC_PALETTE_BANK_NUM_BYTES];
    load_resource(gbc_graphics, RESOURCE_ID_DATA_{uppercase_sprite_group}_PALETTES, palette_buffer);
    GBC_Graphics_set_sprite_palette_array(gbc_graphics, palette_num, palette_buffer + palette_num * GBC_PALETTE_NUM_BYTES);

    // Set number of sprites
    *num_sprites = {num_sprites};

    // Set sprite data
    *sprite_data = {uppercase_sprite_group}_DATA;
    
    return num_loaded_tiles;
}}

"""

RESOURCE_TEMPLATE = {
    "type": "raw",
    "name": "DATA_{uppercase_resource_name}",
    "file": "{resource_location}"
}