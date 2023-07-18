#include <pebble.h>
#include "resources/Backgrounds.h"
#include "resources/Sprites.h"
#include "resources/SpriteActor.h"
#include "resources/Defines.h"
#include "resources/PokemonSprites.h"
#include "pebble-gbc-graphics-advanced/pebble-gbc-graphics-advanced.h"

typedef struct ClaySettings {
    int CharacterSelection;
    int PokemonChoices[NUM_POKEMON_SPRITE_ACTORS];
    int PokemonSelections[NUM_POKEMON_SPRITE_ACTORS];
    int StepSeconds;
    int ChangeMinutes;
    bool ShowDate;
    bool AmericanDateFormat;
} ClaySettings;

static ClaySettings settings;

static Window *s_window;
static GBC_Graphics *s_gbc_graphics;
static AppTimer *s_frame_timer;

static uint8_t s_number_buffer[NUMBER_HEIGHT * NUMBER_WIDTH * TOTAL_NUMBERS * 2];
static uint8_t s_little_number_buffer[LITTLE_NUMBER_HEIGHT * LITTLE_NUMBER_WIDTH* TOTAL_LITTLE_NUMBERS * 2];

SpriteActor sprite_actors[NUM_SPRITE_ACTORS];
SpriteActor *trainer_sprite_actor = &sprite_actors[0];
SpriteActor *pokemon_sprite_actors = &sprite_actors[1];

uint8_t pokemon_data_buffers[NUM_POKEMON_SPRITE_ACTORS][NUM_POKEMON_FRAMES * SPRITE_DATA_BYTES_PER_FRAME];
static bool changing_sprites = false;
static bool sprite_stepping = false;
static uint16_t s_num_background_tiles;

static bool changing_backgrounds = false;
static short mask_level = 0;
static short mask_change = 1;

static uint8_t last_background_group;

static void initialize_sprites(uint16_t trainer_vram_offset);

static void draw_number(uint8_t background, uint8_t tile_x, uint8_t tile_y, char number) {
    int number_value;
    if (number == ':') {
        number_value = 10;
    } else if (number == ' ') {
        number_value = -1;
    } else {
        number_value = number - '0';
    }

    uint8_t tile, attr;
    int tile_index;
    for (uint8_t y = 0; y < NUMBER_HEIGHT; y++) {
        for (uint8_t x = 0; x < NUMBER_WIDTH; x++) {
            if (number_value >= 0) {
                tile_index = number_value * NUMBER_HEIGHT * NUMBER_WIDTH * 2 + x * 2 + y * NUMBER_WIDTH * 2;
                tile = s_number_buffer[tile_index];
                attr = s_number_buffer[tile_index + 1];
                GBC_Graphics_bg_set_tile_and_attrs(s_gbc_graphics, background, x + tile_x, y + tile_y, tile, attr);
            } else {
                GBC_Graphics_bg_set_tile_hidden(s_gbc_graphics, background, x + tile_x, y + tile_y, true);
            }
        }
    }
}

static void draw_little_number(uint8_t background, uint8_t tile_x, uint8_t tile_y, char number) {
    int number_value;
    if (number == '[') {
        number_value = 10;
    } else if (number == ']') {
        number_value = 11;
    } else if (number == ' ') {
        number_value = -1;
    } else {
        number_value = number - '0';
    }
    
    uint8_t tile, attr;
    int tile_index;
    for (uint8_t y = 0; y < LITTLE_NUMBER_HEIGHT; y++) {
        for (uint8_t x = 0; x < LITTLE_NUMBER_WIDTH; x++) {
            if (number_value >= 0) {
                tile_index = number_value * LITTLE_NUMBER_HEIGHT * LITTLE_NUMBER_WIDTH * 2 + x * 2 + y * LITTLE_NUMBER_WIDTH * 2;
                tile = s_little_number_buffer[tile_index];
                attr = s_little_number_buffer[tile_index + 1];
                GBC_Graphics_bg_set_tile_and_attrs(s_gbc_graphics, background, x + tile_x, y + tile_y, tile, attr);
            } else {
                GBC_Graphics_bg_set_tile_hidden(s_gbc_graphics, background, x + tile_x, y + tile_y, true);
            }
        }
    }
}

static void load_time() {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Write the current hours and minutes into a buffer
    static char time_buffer[8];
    strftime(time_buffer, sizeof(time_buffer), clock_is_24h_style() ?
                                            "%H:%M" : "%I:%M", tick_time);

    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 0 * NUMBER_WIDTH + 0, TIME_Y_TILE_OFFSET, time_buffer[0]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 1 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[1]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 2 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[2]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 3 * NUMBER_WIDTH + 1, TIME_Y_TILE_OFFSET, time_buffer[3]);
    draw_number(TIME_LAYER, TIME_X_TILE_OFFSET + 4 * NUMBER_WIDTH + 2, TIME_Y_TILE_OFFSET, time_buffer[4]);

    // Write the date into a buffer
    if (settings.ShowDate) {
        static char date_buffer[8];
        strftime(date_buffer, sizeof(date_buffer), settings.AmericanDateFormat ? "%m%d" : "%d%m", tick_time);
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 2 * LITTLE_NUMBER_WIDTH - 1, DATE_Y_TILE_OFFSET, '[');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 2 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, ']');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 0 * LITTLE_NUMBER_WIDTH, DATE_Y_TILE_OFFSET, date_buffer[0]);
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 1 * LITTLE_NUMBER_WIDTH, DATE_Y_TILE_OFFSET, date_buffer[1]);
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 3 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, date_buffer[2]);
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 4 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, date_buffer[3]);
    } else {
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 2 * LITTLE_NUMBER_WIDTH - 1, DATE_Y_TILE_OFFSET, ' ');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 2 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, ' ');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 0 * LITTLE_NUMBER_WIDTH, DATE_Y_TILE_OFFSET, ' ');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 1 * LITTLE_NUMBER_WIDTH, DATE_Y_TILE_OFFSET, ' ');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 3 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, ' ');
        draw_little_number(TIME_LAYER, DATE_X_TILE_OFFSET + 4 * LITTLE_NUMBER_WIDTH + 1, DATE_Y_TILE_OFFSET, ' ');
    }
}

static uint16_t generate_backgrounds() {
    uint8_t new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    uint16_t loaded_tiles = (*LOAD_BACKGROUND_GROUP[new_background_group])(s_gbc_graphics, s_number_buffer, s_little_number_buffer);
    last_background_group = new_background_group;

    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, BG_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, FG_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET);

    // Set up Time layer
    for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
        for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
            GBC_Graphics_bg_set_tile_hidden(s_gbc_graphics, TIME_LAYER, x, y, true);
        }
    }
    GBC_Graphics_bg_set_scroll_pos(s_gbc_graphics, TIME_LAYER, SCREEN_X_OFFSET, SCREEN_Y_OFFSET + TIME_Y_PIXEL_SHIFT);
    load_time();

    return loaded_tiles;
}

static void set_mask_palette() {
#if defined(PBL_COLOR)
    GBC_Graphics_set_bg_palette(s_gbc_graphics, MASK_PALETTE_NUM, 5, GColorBlackARGB8, GColorBlackARGB8, GColorDarkGrayARGB8, GColorLightGrayARGB8, GColorWhiteARGB8);
#else
    GBC_Graphics_set_bg_palette(s_gbc_graphics, MASK_PALETTE_NUM, 5, GBC_COLOR_BLACK, GBC_COLOR_BLACK, GBC_COLOR_ALPHA_GRAY, GBC_COLOR_GRAY, GBC_COLOR_WHITE);
#endif
}

static void generate_mask_layer() {
    load_tilesheet(s_gbc_graphics, RESOURCE_ID_DATA_MASK_TILESHEET, 0, MASK_VRAM_OFFSET, MASK_VRAM_NUM);

    set_mask_palette();

    for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
        for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
            GBC_Graphics_bg_set_tile(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_OFFSET);
            GBC_Graphics_bg_set_tile_palette(s_gbc_graphics, MASK_LAYER, x, y, MASK_PALETTE_NUM);
            GBC_Graphics_bg_set_tile_vram_bank(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_NUM);
        }
    }
    
    GBC_Graphics_alpha_mode_set_bg_enabled(s_gbc_graphics, MASK_LAYER, true);
    GBC_Graphics_alpha_mode_set_mode(s_gbc_graphics, MASK_LAYER, GBC_ALPHA_MODE_ADD);
    GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, false);
}

// I'll leave this here for now, but I'm not using it for this project
static void update_backgrounds() {
    uint8_t new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    while (NUM_BACKGROUND_GROUPS > 1 && new_background_group == last_background_group) {
        new_background_group = rand() % NUM_BACKGROUND_GROUPS;
    }
    (*LOAD_BACKGROUND_GROUP[new_background_group])(s_gbc_graphics, s_number_buffer, s_little_number_buffer);
    last_background_group = new_background_group;

    load_time();
}

static void step() {
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    if (!changing_sprites && !changing_backgrounds) {
        // Scroll backgrounds
        GBC_Graphics_bg_move(s_gbc_graphics, BG_LAYER, BG_STEP_SIZE, 0);
        GBC_Graphics_bg_move(s_gbc_graphics, FG_LAYER, FG_STEP_SIZE, 0);
    }
    
    if (changing_backgrounds) {
        mask_level += mask_change;
        if (mask_level >= MASK_LEVELS - 1) {
            update_backgrounds();
            set_mask_palette();
            mask_change = -1;
        } else if (mask_level <= 0) {
            changing_backgrounds = false;
            GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, false);
        }
        
        for (uint8_t y = 0; y < GBC_TILEMAP_HEIGHT; y++) {
            for (uint8_t x = 0; x < GBC_TILEMAP_WIDTH; x++) {
                GBC_Graphics_bg_set_tile(s_gbc_graphics, MASK_LAYER, x, y, MASK_VRAM_OFFSET + mask_level);
            }
        }
    }

    // Update time
    load_time();

    if (!changing_sprites) { // Walk in place
        if (sprite_stepping) {
            for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
                if (sprite_actors[i].state == AS_WALK) {
                    sprite_actor_take_step(&sprite_actors[i]);
                    sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
                }
            }
            sprite_stepping = false;
        }
    } else { // Move sprites
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_WALK_ON) {
                sprite_actors[i].x += SPRITE_STEP_SIZE;
                if (sprite_actors[i].x >= sprite_actors[i].center_x) {
                    sprite_actors[i].x = sprite_actors[i].center_x;
                    sprite_actors[i].state = AS_WALK;
                } else {
                    sprite_actor_take_step(&sprite_actors[i]);
                }
                sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
            } else if (sprite_actors[i].state == AS_WALK_OFF) {
                sprite_actors[i].x += SPRITE_STEP_SIZE;
                if (sprite_actors[i].x >= bounds.size.w + GBC_SPRITE_OFFSET_X) {
                    sprite_actor_reset(&sprite_actors[i]);
                } else {
                    sprite_actor_take_step(&sprite_actors[i]);
                }
                sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
            }
        }
    }
    GBC_Graphics_render(s_gbc_graphics);
}

static void frame_timer_handle(void* context) {
    step();

    bool still_changing_sprites = false;
    bool needs_reinitialization = false;
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state == AS_WALK_ON || sprite_actors[i].state == AS_WALK_OFF) {
            still_changing_sprites = true;
        }
        if (sprite_actors[i].state == AS_OFFSCREEN) {
            needs_reinitialization = true;
        }
    }
    if (changing_sprites && !still_changing_sprites && needs_reinitialization) {
        initialize_sprites(s_num_background_tiles);
        still_changing_sprites = true;
    }
    changing_sprites = still_changing_sprites;
    if (!changing_sprites && !changing_backgrounds) {
        s_frame_timer = NULL;
    } else {
        s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    }
}

static void start_changing_sprites() {
    changing_sprites = true;
    if (s_frame_timer == NULL)
        s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
}

static void start_changing_backgrounds() {
    if (NUM_BACKGROUND_GROUPS > 1) {
        changing_backgrounds = true;
        mask_change = 1;
        mask_level = 0;
        GBC_Graphics_lcdc_set_bg_layer_enabled(s_gbc_graphics, MASK_LAYER, true);
        
        if (s_frame_timer == NULL)
            s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
    }
}

static void render_sprites() {
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        sprite_actor_render(&sprite_actors[i], s_gbc_graphics);
    }
}

static void initialize_sprites(uint16_t trainer_vram_offset) {
    uint8_t vram_bank = 0;
    uint8_t vram_start_offset = trainer_vram_offset;
    uint8_t palette_num = 0;
    uint8_t num_sprites;
    const uint8_t *sprite_data;
    uint8_t new_sprite_group;
    if (settings.CharacterSelection == CHARACTER_RANDOM) {
        new_sprite_group = rand() % NUM_SPRITE_GROUPS;
    } else {
        new_sprite_group = settings.CharacterSelection - 1;
    }
    (*LOAD_SPRITE_GROUP[new_sprite_group])(s_gbc_graphics, vram_bank, vram_start_offset, palette_num, &num_sprites, &sprite_data);
    sprite_actor_init(trainer_sprite_actor,
                        s_gbc_graphics,
                        0,
                        vram_bank,
                        vram_start_offset,
                        num_sprites,
                        sprite_data,
                        palette_num);
    
    
    for (uint8_t i = 0; i < NUM_POKEMON_SPRITE_ACTORS; i++) {
        vram_bank = i+1;
        vram_start_offset = 0;
        palette_num = i+1;
        int pokemon_number;
        if (settings.PokemonSelections[i] == POKEMON_RANDOM) {
            pokemon_number = rand() % NUM_POKEMON;
        } else {
            pokemon_number = settings.PokemonChoices[i];
        }
        load_pokemon_sprite(s_gbc_graphics, pokemon_number, vram_bank, vram_start_offset, i+1, pokemon_data_buffers[i]);
        
        sprite_actor_init(&pokemon_sprite_actors[i], 
                        s_gbc_graphics,
                        i+1,
                        vram_bank,
                        vram_start_offset,
                        NUM_POKEMON_FRAMES,
                        pokemon_data_buffers[i],
                        palette_num);
        if (settings.PokemonSelections[i] == POKEMON_NONE) {
            pokemon_sprite_actors[i].hidden = true;
            pokemon_sprite_actors[i].state = AS_HIDDEN;
        }
    }

    int total_width = 0;
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state != AS_HIDDEN) {
            total_width += sprite_actors[i].width + PIXELS_BETWEEN_SPRITES;
        }
    }
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    if (total_width > bounds.size.w) {
        total_width = bounds.size.w;
    } 
    int total_sprite_offset_x = (bounds.size.w / 2) + total_width / 2 + GBC_SPRITE_OFFSET_X;
    int sprite_offset_x = total_sprite_offset_x - PIXELS_BETWEEN_SPRITES;

    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state != AS_HIDDEN) {
            sprite_actors[i].state = AS_WALK_ON;
            sprite_actors[i].hidden = false;
            sprite_actors[i].center_x = sprite_offset_x - sprite_actors[i].width;
            sprite_actors[i].x = GBC_SPRITE_OFFSET_X - (total_sprite_offset_x - sprite_offset_x) - sprite_actors[i].width;
            sprite_offset_x -= (sprite_actors[i].width + PIXELS_BETWEEN_SPRITES);
            sprite_actors[i].frame = i % sprite_actors[i].num_sprites;
        }
    }

    render_sprites();
    start_changing_sprites();
}


static void reload_sprites(uint16_t trainer_vram_offset) {
    uint8_t vram_bank = 0;
    uint8_t vram_start_offset = trainer_vram_offset;
    uint8_t palette_num = 0;
    uint8_t num_sprites;
    const uint8_t *sprite_data;
    uint8_t new_sprite_group;
    uint8_t old_frame_start = trainer_sprite_actor->frame;
    if (settings.CharacterSelection == CHARACTER_RANDOM) {
        new_sprite_group = rand() % NUM_SPRITE_GROUPS;
    } else {
        new_sprite_group = settings.CharacterSelection - 1;
    }
    (*LOAD_SPRITE_GROUP[new_sprite_group])(s_gbc_graphics, vram_bank, vram_start_offset, palette_num, &num_sprites, &sprite_data);
    sprite_actor_init(trainer_sprite_actor,
                        s_gbc_graphics,
                        0,
                        vram_bank,
                        vram_start_offset,
                        num_sprites,
                        sprite_data,
                        palette_num);
    
    
    for (uint8_t i = 0; i < NUM_POKEMON_SPRITE_ACTORS; i++) {
        vram_bank = i+1;
        vram_start_offset = 0;
        palette_num = i+1;
        int pokemon_number;
        if (settings.PokemonSelections[i] == POKEMON_RANDOM) {
            pokemon_number = rand() % NUM_POKEMON;
        } else {
            pokemon_number = settings.PokemonChoices[i];
        }
        load_pokemon_sprite(s_gbc_graphics, pokemon_number, vram_bank, vram_start_offset, i+1, pokemon_data_buffers[i]);
        
        sprite_actor_init(&pokemon_sprite_actors[i], 
                        s_gbc_graphics,
                        i+1,
                        vram_bank,
                        vram_start_offset,
                        NUM_POKEMON_FRAMES,
                        pokemon_data_buffers[i],
                        palette_num);
        if (settings.PokemonSelections[i] == POKEMON_NONE) {
            pokemon_sprite_actors[i].hidden = true;
            pokemon_sprite_actors[i].state = AS_HIDDEN;
        }
    }

    int total_width = 0;
    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state != AS_HIDDEN) {
            total_width += sprite_actors[i].width + PIXELS_BETWEEN_SPRITES;
        }
    }
    GRect bounds = GBC_Graphics_get_screen_bounds(s_gbc_graphics);
    int total_sprite_offset_x;
    if (total_width > bounds.size.w) {
        total_sprite_offset_x = bounds.size.w;
    } else {
        total_sprite_offset_x = (bounds.size.w / 2) + total_width / 2 + GBC_SPRITE_OFFSET_X;
    }
    int sprite_offset_x = total_sprite_offset_x - PIXELS_BETWEEN_SPRITES;

    for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
        if (sprite_actors[i].state != AS_HIDDEN) {
            sprite_actors[i].state = AS_WALK;
            sprite_actors[i].hidden = false;
            sprite_actors[i].center_x = sprite_offset_x - sprite_actors[i].width;
            sprite_actors[i].x = sprite_actors[i].center_x;
            sprite_offset_x -= (sprite_actors[i].width + PIXELS_BETWEEN_SPRITES);
            sprite_actors[i].frame = old_frame_start + (i % sprite_actors[i].num_sprites);
        }
    }

    render_sprites();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed) {
    if ((units_changed & MINUTE_UNIT) && (settings.ChangeMinutes > 0) && ((tick_time->tm_min % settings.ChangeMinutes) == 0)) {
        start_changing_backgrounds();
    }

    if (!changing_sprites) {
        if ((units_changed & MINUTE_UNIT) && (settings.ChangeMinutes > 0) && ((tick_time->tm_min % settings.ChangeMinutes) == 0)) {
            for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
                if (sprite_actors[i].state == AS_OFFSCREEN) {
                    sprite_actors[i].state = AS_WALK_ON;
                    sprite_actors[i].hidden = false;
                } else if (sprite_actors[i].state == AS_WALK) {
                    sprite_actors[i].state = AS_WALK_OFF;
                }
            }
            start_changing_sprites();
        } else if ((tick_time->tm_sec % settings.StepSeconds) == 0) {
            sprite_stepping = true;
            if (DEMO_MODE) {
                reload_sprites(s_num_background_tiles);
            }
            step();
        }
    }
    
    // Update time
    load_time();
}

static void will_focus_handler(bool in_focus) {
    if (!in_focus) {
        // If a notification pops up while the timer is firing
        // very rapidly, it will crash the entire watch :)
        // Stopping the timer when a notification appears will prevent this
        if (s_frame_timer != NULL) {
            app_timer_cancel(s_frame_timer);
        }
    } else {
        if (s_frame_timer != NULL) {
            s_frame_timer = app_timer_register(FRAME_DURATION, frame_timer_handle, NULL);
        }
    }
}

static void window_load(Window *window) {
    // Create the GBC_Graphics object
    s_gbc_graphics = GBC_Graphics_ctor(s_window, NUM_VRAMS, NUM_BACKGROUNDS);

    GBC_Graphics_set_screen_bounds(s_gbc_graphics, GBC_SCREEN_BOUNDS_FULL);

    s_num_background_tiles = generate_backgrounds();
    generate_mask_layer();
    GBC_Graphics_lcdc_set_sprite_layer_z(s_gbc_graphics, SPRITE_LAYER);
    initialize_sprites(s_num_background_tiles);

    // Setup the frame timer that will call the game step function
    s_frame_timer = NULL;
    app_focus_service_subscribe(will_focus_handler);

    // Setup time
    tick_timer_service_subscribe(SECOND_UNIT, time_handler);

    // Display the graphics
    GBC_Graphics_render(s_gbc_graphics);
}

static void window_unload(Window *window) {
    // Destroy the GBC_Graphics object
    GBC_Graphics_destroy(s_gbc_graphics);
}

static void default_settings() {
    settings.CharacterSelection = CHARACTER_RANDOM;
    settings.PokemonSelections[0] = POKEMON_RANDOM;
    settings.PokemonChoices[0] = 0;
    settings.PokemonSelections[1] = POKEMON_RANDOM;
    settings.PokemonChoices[1] = 3;
    settings.PokemonSelections[2] = POKEMON_RANDOM;
    settings.PokemonChoices[2] = 6;
    settings.StepSeconds = 1;
    settings.ChangeMinutes = 1;
    settings.ShowDate = true;
    settings.AmericanDateFormat = true;
}

static void load_settings() {
    default_settings();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

static void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
    if (!changing_sprites) {
        for (uint8_t i = 0; i < NUM_SPRITE_ACTORS; i++) {
            if (sprite_actors[i].state == AS_OFFSCREEN) {
                sprite_actors[i].state = AS_WALK_ON;
                sprite_actors[i].hidden = false;
            } else if (sprite_actors[i].state == AS_WALK) {
                sprite_actors[i].state = AS_WALK_OFF;
            }
        }
        start_changing_sprites();
    }
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
    Tuple *character_selection_t = dict_find(iter, MESSAGE_KEY_CharacterSelection);
    if (character_selection_t) {
        settings.CharacterSelection = atoi(character_selection_t->value->cstring);
    }

    Tuple *pokemon_selection_1_t = dict_find(iter, MESSAGE_KEY_PokemonSelection1);
    if (pokemon_selection_1_t) {
        settings.PokemonSelections[0] = atoi(pokemon_selection_1_t->value->cstring);
    }

    Tuple *pokemon_choice_1_t = dict_find(iter, MESSAGE_KEY_PokemonChoice1);
    if (pokemon_choice_1_t) {
        settings.PokemonChoices[0] = atoi(pokemon_choice_1_t->value->cstring);
    }

    Tuple *pokemon_selection_2_t = dict_find(iter, MESSAGE_KEY_PokemonSelection2);
    if (pokemon_selection_2_t) {
        settings.PokemonSelections[1] = atoi(pokemon_selection_2_t->value->cstring);
    }

    Tuple *pokemon_choice_2_t = dict_find(iter, MESSAGE_KEY_PokemonChoice2);
    if (pokemon_choice_2_t) {
        settings.PokemonChoices[1] = atoi(pokemon_choice_2_t->value->cstring);
    }

    Tuple *pokemon_selection_3_t = dict_find(iter, MESSAGE_KEY_PokemonSelection3);
    if (pokemon_selection_3_t) {
        settings.PokemonSelections[2] = atoi(pokemon_selection_3_t->value->cstring);
    }

    Tuple *pokemon_choice_3_t = dict_find(iter, MESSAGE_KEY_PokemonChoice3);
    if (pokemon_choice_3_t) {
        settings.PokemonChoices[2] = atoi(pokemon_choice_3_t->value->cstring);
    }

    Tuple *step_seconds_t = dict_find(iter, MESSAGE_KEY_StepSeconds);
    if (step_seconds_t) {
        settings.StepSeconds = atoi(step_seconds_t->value->cstring);
    }

    Tuple *change_minutes_t = dict_find(iter, MESSAGE_KEY_ChangeMinutes);
    if (change_minutes_t) {
        settings.ChangeMinutes = atoi(change_minutes_t->value->cstring);
    }
    
    Tuple *show_date_t = dict_find(iter, MESSAGE_KEY_ShowDate);
    if(show_date_t) {
        settings.ShowDate = show_date_t->value->int32 == 1;
    }
    
    Tuple *american_date_t = dict_find(iter, MESSAGE_KEY_AmericanDateFormat);
    if(american_date_t) {
        settings.AmericanDateFormat = american_date_t->value->int32 == 1;
    }

    save_settings();
}

static void init(void) {
    load_settings();
    app_message_register_inbox_received(inbox_received_handler);
    app_message_open(128, 128);
    s_window = window_create();

    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    const bool animated = true;
    window_stack_push(s_window, animated);
}

static void deinit(void) {
    window_destroy(s_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
