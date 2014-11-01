#include <pebble.h>

static Window *window;
static BitmapLayer *bitmap_layer;
static TextLayer *text_layer;
static GBitmap *bitmap;
static char text[8];

typedef enum {
  APP_KEY_INCOMING,
  APP_KEY_OUTGOING,
} AppKey;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOADING);
  bitmap_layer = bitmap_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, bounds.size.h - 40 } });
  bitmap_layer_set_bitmap(bitmap_layer, bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));

  clock_copy_time_string(text, sizeof(text));
  text_layer = text_layer_create((GRect) { .origin = { 0, bounds.size.h - 40 }, .size = { bounds.size.w, 40 } });
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text(text_layer, text);
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  bitmap_layer_destroy(bitmap_layer);
  gbitmap_destroy(bitmap);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
