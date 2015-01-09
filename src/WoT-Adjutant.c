#include <pebble.h>

#define NUM_MENU_ICONS 17
#define NUM_MENU_SECTIONS 3
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_SECTIONS 7
#define NUM_THIRD_MENU_SECTIONS 9

static Window *window;

static Layer *logo;
static TextLayer *text_layer_1, *text_layer_2;
static BitmapLayer *logo_layer;
static GBitmap *logo_bitmap;

static MenuLayer *menu_layer;

static GBitmap *menu_icons[NUM_MENU_ICONS];

//receive data

char nickname[16], personal_rating[16], battles_fought[16], victories[16], battles_survived[16], total_xp[16],
   avg_xp[16], max_xp[16], vehicles_destroyed[16], vehicles_spotted[16], damage_caused[16], hit_ratio[16],
   penetration_ratio[16], avg_damage_blocked[16], armor_use_efficiency[16], capture_points[16], defense_points[16];

enum {
  KEY_OK                    =  0,
  KEY_NICKNAME              =  1,
  KEY_PERSONAL_RATING       =  2,
  KEY_BATTLES_FOUGHT        =  3,
  KEY_VICTORIES             =  4,
  KEY_BATTLES_SURVIVED      =  5,
  KEY_TOTAL_XP              =  6,
  KEY_AVG_XP                =  7,
  KEY_MAXIMUM_XP            =  8,
  KEY_VEHICLES_DESTROYED    =  9,
  KEY_VEHICLES_SPOTTED      = 10,
  KEY_DAMAGE_CAUSED         = 11,
  KEY_HIT_RATIO             = 12,
  KEY_PENETRATION_RATIO     = 13,
  KEY_AVG_DAMAGE_BLOCKED    = 14,
  KEY_ARMOR_USE_EFFICIENCY  = 15,
  KEY_CAPTURE_POINTS        = 16,
  KEY_DEFENSE_POINTS        = 17
};

void process_tuple(Tuple *t)
{
  int key = t->key;
  int value = t->value->int8;
  char string_value[16];
    strcpy(string_value, t->value->cstring);

  switch(key) {
    case KEY_OK:
      if (value == 1)
      {
        layer_set_hidden((Layer *)logo, true);
        layer_set_hidden((Layer *)menu_layer, false);
      }
      break;
    case KEY_NICKNAME:
      strcat(nickname, string_value);
      break;
    case KEY_PERSONAL_RATING:
      strcat(personal_rating, string_value);
      break;
    case KEY_BATTLES_FOUGHT:
      strcat(battles_fought, string_value);
      break;
    case KEY_VICTORIES:
      strcat(victories, string_value);
      break;
    case KEY_BATTLES_SURVIVED:
      strcat(battles_survived, string_value);
      break;
    case KEY_TOTAL_XP:
      strcat(total_xp, string_value);
      break;
    case KEY_AVG_XP:
      strcat(avg_xp, string_value);
      break;
    case KEY_MAXIMUM_XP:
      strcat(max_xp, string_value);
      break;
    case KEY_VEHICLES_DESTROYED:
      strcat(vehicles_destroyed, string_value);
      break;
    case KEY_VEHICLES_SPOTTED:
      strcat(vehicles_spotted, string_value);
      break;
    case KEY_DAMAGE_CAUSED:
      strcat(damage_caused, string_value);
      break;
    case KEY_HIT_RATIO:
      strcat(hit_ratio, string_value);
      break;
    case KEY_PENETRATION_RATIO:
      strcat(penetration_ratio, string_value);
      break;
    case KEY_AVG_DAMAGE_BLOCKED:
      strcat(avg_damage_blocked, string_value);
      break;
    case KEY_ARMOR_USE_EFFICIENCY:
      strcat(armor_use_efficiency, string_value);
      break;
    case KEY_CAPTURE_POINTS:
      strcat(capture_points, string_value);
      break;
    case KEY_DEFENSE_POINTS:
      strcat(defense_points, string_value);
      break;
  }
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
  (void) context;

  Tuple *t = dict_read_first(iter);
  while(t != NULL){
    process_tuple(t);
    t = dict_read_next(iter);
  }
}

//draw menu

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;

    case 1:
      return NUM_SECOND_MENU_SECTIONS;

    case 2:
      return NUM_THIRD_MENU_SECTIONS;

    default:
      return 0;
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer, "WoT Adjutant");
      break;

    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "Overall Results");
      break;

    case 2:
      menu_cell_basic_header_draw(ctx, cell_layer, "Battle Performance");
      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {
    case 0:

      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Nickname", nickname, menu_icons[0]);
          break;
      }
      break;

    case 1:

      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Personal Rating", personal_rating, menu_icons[1]);
          break;

        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "Battles Fought", battles_fought, menu_icons[2]);
          break;

        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Victories", victories, menu_icons[3]);
          break;

        case 3:
          menu_cell_basic_draw(ctx, cell_layer, "Battles Survived", battles_survived, menu_icons[4]);
          break;

        case 4:
          menu_cell_basic_draw(ctx, cell_layer, "Total XP", total_xp, menu_icons[5]);
          break;

        case 5:
          menu_cell_basic_draw(ctx, cell_layer, "Avg XP", avg_xp, menu_icons[6]);
          break;

        case 6:
          menu_cell_basic_draw(ctx, cell_layer, "Maximum XP", max_xp, menu_icons[7]);
          break;      
      }
      break;

    case 2:

      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Vehicles Destroed", vehicles_destroyed, menu_icons[8]);
          break;

        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "Vehicles Spotted", vehicles_spotted, menu_icons[9]);
          break;

        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Damage Caused", damage_caused, menu_icons[10]);
          break;

        case 3:
          menu_cell_basic_draw(ctx, cell_layer, "Hit Ratio", hit_ratio, menu_icons[11]);
          break;

        case 4:
          menu_cell_basic_draw(ctx, cell_layer, "Penetration ratio", penetration_ratio, menu_icons[12]);
          break;

        case 5:
          menu_cell_basic_draw(ctx, cell_layer, "Av. damage blocked", avg_damage_blocked, menu_icons[13]);
          break;

        case 6:
          menu_cell_basic_draw(ctx, cell_layer, "Armor-use efficiency", armor_use_efficiency, menu_icons[14]);
          break;

        case 7:
          menu_cell_basic_draw(ctx, cell_layer, "Capture Points", capture_points, menu_icons[15]);
          break;

        case 8:
          menu_cell_basic_draw(ctx, cell_layer, "Defense Points", defense_points, menu_icons[16]);
          break;
      }
  }
}

static TextLayer* init_text_layer(GRect location, GColor colour, GColor background, const char *res_id, GTextAlignment alignment)
{
  TextLayer *layer = text_layer_create(location);
  text_layer_set_text_color(layer, colour);
  text_layer_set_background_color(layer, background);
  text_layer_set_font(layer, fonts_get_system_font(res_id));
  text_layer_set_text_alignment(layer, alignment);

  return layer;
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  logo = layer_create(bounds);
  layer_add_child(window_get_root_layer(window), (Layer *)logo);

  logo_layer = bitmap_layer_create(GRect(32,7,80,91));
  logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_LOGO);
  bitmap_layer_set_bitmap(logo_layer, logo_bitmap);
  layer_add_child((Layer *)logo, bitmap_layer_get_layer(logo_layer));

  text_layer_1 = init_text_layer(GRect(0, 100, 144, 35), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_28_BOLD", GTextAlignmentCenter);
  text_layer_set_text(text_layer_1, "WoT Adjutant");
  layer_add_child((Layer *)logo, text_layer_get_layer(text_layer_1));

  text_layer_2 = init_text_layer(GRect(0, 130, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_14", GTextAlignmentCenter);
  text_layer_set_text(text_layer_2, "Loading...");
  layer_add_child((Layer *)logo, text_layer_get_layer(text_layer_2));


  menu_icons[0]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);
  menu_icons[1]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_2);
  menu_icons[2]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_3);
  menu_icons[3]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_4);
  menu_icons[4]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_5);
  menu_icons[5]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_6);
  menu_icons[6]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_7);
  menu_icons[7]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_8);
  menu_icons[8]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_9);
  menu_icons[9]  = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_10);
  menu_icons[10] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_11);
  menu_icons[11] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_12);
  menu_icons[12] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_13);
  menu_icons[13] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_14);
  menu_icons[14] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_15);
  menu_icons[15] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_16);
  menu_icons[16] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_17);

  menu_layer = menu_layer_create(bounds);

  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
  });

  menu_layer_set_click_config_onto_window(menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
  layer_set_hidden((Layer *)menu_layer, true);
}

static void window_unload(Window *window) {
  menu_layer_destroy(menu_layer);

  for (int i = 0; i < NUM_MENU_ICONS; i++) {
    gbitmap_destroy(menu_icons[i]);
  }

  layer_destroy(logo);
  gbitmap_destroy(logo_bitmap);
  bitmap_layer_destroy(logo_layer);
  text_layer_destroy(text_layer_1);
  text_layer_destroy(text_layer_2);
}

int main(void) {
  window = window_create();

  app_message_register_inbox_received(in_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true);

  app_event_loop();

  window_destroy(window);
}