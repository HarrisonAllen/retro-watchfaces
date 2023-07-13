#pragma once

#include <pebble.h>
#include "../pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"
#include "Sprites.h"
#include "Defines.h"

typedef enum {
    AS_WALK_ON,
    AS_WALK,
    AS_WALK_OFF,
    AS_OFFSCREEN
} ActorState;

typedef struct {
    uint8_t index;
    const uint8_t *data;
    uint8_t num_sprites;
    uint8_t width;
    uint8_t height;
    short x;
    short y;
    short center_x;
    uint8_t frame;
    uint8_t vram_bank_offset;
    uint8_t palette;
    uint8_t vram_bank;
    bool x_flip;
    bool y_flip;
    bool hidden;
    uint8_t mosaic_x;
    uint8_t mosaic_y;
    ActorState state;
} SpriteActor;

/**
 * Clamps a short variable between two uint16_t values
 * 
 * @param to_clamp The value to clamp
 * @param lower_bound The lower bound on the return value
 * @param uppper_bound The upper bound on the return value
 * 
 * @return The clamped value as uint8_t
 */
static uint16_t clamp_short_to_uint16_t(short to_clamp, uint16_t lower_bound, uint16_t upper_bound) {
    if (to_clamp < (short)lower_bound) {
        return lower_bound;
    }
    if (to_clamp > (short)upper_bound) {
        return upper_bound;
    }
    return (uint16_t) to_clamp;
}

static void sprite_actor_init(SpriteActor *sprite_actor, GBC_Graphics *gbc_graphics, uint8_t sprite_index, uint8_t vram_bank, 
                              uint8_t vram_bank_offset, uint8_t num_sprites, const uint8_t *sprite_data, uint8_t sprite_palette) {
    GRect bounds = GBC_Graphics_get_screen_bounds(gbc_graphics);

    sprite_actor->index = sprite_index;
    sprite_actor->data = sprite_data;
    sprite_actor->num_sprites = num_sprites;
    sprite_actor->width = GBC_TILE_WIDTH * (sprite_data[1] + 1);
    sprite_actor->height = GBC_TILE_HEIGHT * (sprite_data[2] + 1);
    sprite_actor->x = GBC_SPRITE_OFFSET_X - sprite_actor->width;
    sprite_actor->y = SPRITE_BOTTOM_Y - sprite_actor->height + GBC_SPRITE_OFFSET_Y - SCREEN_Y_OFFSET;
    sprite_actor->center_x = (bounds.size.w / 2) - sprite_actor->width / 2 + GBC_SPRITE_OFFSET_X;
    sprite_actor->vram_bank = vram_bank;
    sprite_actor->frame = 0;
    sprite_actor->vram_bank_offset = vram_bank_offset;
    sprite_actor->palette = sprite_palette;
    sprite_actor->x_flip = false;
    sprite_actor->y_flip = false;
    sprite_actor->hidden = true;
    sprite_actor->mosaic_x = 0;
    sprite_actor->mosaic_y = 0;
    sprite_actor->state = AS_OFFSCREEN;
    // TODO: Add sprite_actor->num_frames
    // And then have a frame state with:
    // - y offset
    // - x offset
    // - sprite_num
    // May need to do a malloc/free workflow
}

static void sprite_actor_render(SpriteActor *sprite_actor, GBC_Graphics *gbc_graphics) {
    const uint8_t *sprite_data = sprite_actor->data + sprite_actor->frame * SPRITE_DATA_SIZE;
    GBC_Graphics_oam_set_sprite(gbc_graphics,
                                sprite_actor->index,
                                clamp_short_to_uint16_t(sprite_actor->x, 0, GBC_SPRITE_MAX_X),
                                clamp_short_to_uint16_t(sprite_actor->y, 0, GBC_SPRITE_MAX_Y),
                                sprite_data[0] + sprite_actor->vram_bank_offset,
                                GBC_Graphics_attr_make(sprite_actor->palette,
                                                       sprite_actor->vram_bank, 
                                                       sprite_actor->x_flip, 
                                                       sprite_actor->y_flip, 
                                                       sprite_actor->hidden),
                                sprite_data[1],
                                sprite_data[2],
                                sprite_actor->mosaic_x,
                                sprite_actor->mosaic_y);
}

static void sprite_actor_take_step(SpriteActor *sprite_actor) {
    sprite_actor->frame = (sprite_actor->frame + 1) % sprite_actor->num_sprites;
}

static void sprite_actor_reset(SpriteActor *sprite_actor) {
    sprite_actor->x = GBC_SPRITE_OFFSET_X - sprite_actor->width;
    sprite_actor->frame = 0;
    sprite_actor->x_flip = false;
    sprite_actor->y_flip = false;
    sprite_actor->hidden = true;
    sprite_actor->mosaic_x = 0;
    sprite_actor->mosaic_y = 0;
    sprite_actor->state = AS_OFFSCREEN;
}