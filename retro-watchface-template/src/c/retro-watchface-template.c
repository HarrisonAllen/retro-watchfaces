#include <pebble.h>

#define Y_OFFSET (PBL_DISPLAY_HEIGHT - 180) / 2
#define X_OFFSET (PBL_DISPLAY_WIDTH - 180) / 2

static Window *s_main_window;
static BitmapLayer *s_template_layer;
static GBitmap *s_template_bitmap;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Watchface Resources
  // template
  s_template_layer = bitmap_layer_create(GRect(-2 + X_OFFSET, -2 + Y_OFFSET, 184, 184));
  s_template_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEMPLATE);
  bitmap_layer_set_bitmap(s_template_layer, s_template_bitmap);

  layer_add_child(window_layer, bitmap_layer_get_layer(s_template_layer));
}

static void main_window_unload(Window *window) {
  // unload bitmap layers
  if (s_template_layer != NULL)
    bitmap_layer_destroy(s_template_layer);
    
  // unload gbitmaps
  if (s_template_bitmap != NULL)
    gbitmap_destroy(s_template_bitmap);
}

static void init() {
  // setup window
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_set_background_color(s_main_window, GColorBlack);

  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
