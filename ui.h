#include <lvgl.h>

// Styles
static lv_style_t style_box;
static lv_style_t style_title;
static lv_style_t style_value;
static lv_style_t style_unit;

// Objets LVGL
lv_obj_t *main_screen;
lv_obj_t *detail_screen;

// Éléments main screen
lv_obj_t *time_label;
lv_obj_t *weather_label;
lv_obj_t *tempo_today;
lv_obj_t *tempo_tomorrow;
lv_obj_t *grid_power_label;
lv_obj_t *pv_power_label;
lv_obj_t *daily_prod_label;
lv_obj_t *daily_cons_label;
lv_obj_t *daily_grid_label;
lv_obj_t *battery_soc_label;
lv_obj_t *battery_power_label;

void ui_init() {
  // Création des styles
  lv_style_init(&style_box);
  lv_style_set_bg_color(&style_box, lv_color_hex(0x2A2A2A));
  lv_style_set_bg_opa(&style_box, LV_OPA_COVER);
  lv_style_set_radius(&style_box, 10);
  lv_style_set_pad_all(&style_box, 5);
  
  lv_style_init(&style_title);
  lv_style_set_text_color(&style_title, lv_color_hex(0xAAAAAA));
  lv_style_set_text_font(&style_title, &lv_font_montserrat_14);
  
  lv_style_init(&style_value);
  lv_style_set_text_color(&style_value, lv_color_white());
  lv_style_set_text_font(&style_value, &lv_font_montserrat_24);
  
  lv_style_init(&style_unit);
  lv_style_set_text_color(&style_unit, lv_color_hex(0xAAAAAA));
  lv_style_set_text_font(&style_unit, &lv_font_montserrat_14);
  
  // Création des écrans
  main_screen = lv_obj_create(NULL);
  detail_screen = lv_obj_create(NULL);
  
  // Configuration écran principal
  create_main_screen();
  create_detail_screen();
  
  // Afficher l'écran principal
  lv_scr_load(main_screen);
}

void create_main_screen() {
  lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE);
  
  // En-tête (heure, météo, tempo)
  lv_obj_t *header = lv_obj_create(main_screen);
  lv_obj_set_size(header, 460, 60);
  lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 10);
  lv_obj_add_style(header, &style_box, 0);
  lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  
  time_label = lv_label_create(header);
  lv_label_set_text(time_label, "00:00");
  
  weather_label = lv_label_create(header);
  lv_label_set_text(weather_label, "20°C Ensoleillé");
  
  tempo_today = lv_obj_create(header);
  lv_obj_set_size(tempo_today, 40, 40);
  lv_obj_set_style_bg_color(tempo_today, lv_color_hex(0x0000FF), 0);
  lv_obj_t *today_label = lv_label_create(tempo_today);
  lv_label_set_text(today_label, "30");
  lv_obj_center(today_label);
  
  tempo_tomorrow = lv_obj_create(header);
  lv_obj_set_size(tempo_tomorrow, 40, 40);
  lv_obj_set_style_bg_color(tempo_tomorrow, lv_color_hex(0xFF0000), 0);
  lv_obj_t *tomorrow_label = lv_label_create(tempo_tomorrow);
  lv_label_set_text(tomorrow_label, "31");
  lv_obj_center(tomorrow_label);
  
  // Corps - données DEYE
  lv_obj_t *grid = lv_obj_create(main_screen);
  lv_obj_set_size(grid, 460, 380);
  lv_obj_align(grid, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_add_style(grid, &style_box, 0);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
  
  // Ajout des éléments de données...
  // (Voir la suite pour le détail complet)
}

void update_main_screen(const DeyeData &data, const TempoData &tempo, const WeatherData &weather) {
  // Mise à jour de l'heure
  lv_label_set_text(time_label, timeClient.getFormattedTime().c_str());
  
  // Mise à jour météo
  String weather_text = String(weather.temperature, 1) + "°C " + weather.condition;
  lv_label_set_text(weather_label, weather_text.c_str());
  
  // Mise à jour Tempo
  lv_obj_set_style_bg_color(tempo_today, get_tempo_color(tempo.today_color), 0);
  lv_label_set_text(lv_obj_get_child(tempo_today, 0), String(tempo.today_number).c_str());
  
  lv_obj_set_style_bg_color(tempo_tomorrow, get_tempo_color(tempo.tomorrow_color), 0);
  lv_label_set_text(lv_obj_get_child(tempo_tomorrow, 0), String(tempo.tomorrow_number).c_str());
  
  // Mise à jour données DEYE
  lv_label_set_text(grid_power_label, String(data.grid_power, 1).c_str());
  lv_label_set_text(pv_power_label, String(data.pv_power_total, 1).c_str());
  // ... autres mises à jour
}

lv_color_t get_tempo_color(String color) {
  if (color == "blue") return lv_color_hex(0x0000FF);
  if (color == "white") return lv_color_hex(0xFFFFFF);
  if (color == "red") return lv_color_hex(0xFF0000);
  return lv_color_hex(0xAAAAAA);
}