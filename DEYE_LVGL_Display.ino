#include <Arduino.h>
#include "lvgl_setup.h"
#include "wifi_ntp.h"
#include "deye_reader.h"
#include "edf_tempo.h"
#include "weather.h"
#include "ui.h"

// Variables globales
DeyeData deyeData;
TempoData tempoData;
WeatherData weatherData;

void setup() {
  Serial.begin(115200);
  
  // Initialisation LVGL
  lvgl_setup();
  
  // Connexion WiFi
  wifi_setup();
  
  // Configuration NTP
  ntp_setup();
  
  // Initialisation API Tempo
  tempo_setup();
  
  // Initialisation météo
  weather_setup();
  
  // Initialisation interface utilisateur
  ui_init();
  
  // Initialisation communication avec DEYE
  deye_setup();
}

void loop() {
  lv_timer_handler(); // Gestion LVGL
  
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000) { // Mise à jour toutes les 5 secondes
    lastUpdate = millis();
    
    // Mise à jour des données
    update_ntp_time();
    deyeData = read_deye_data();
    tempoData = get_tempo_data();
    weatherData = get_weather_data();
    
    // Mise à jour de l'interface
    update_main_screen(deyeData, tempoData, weatherData);
  }
  
  delay(5);
}