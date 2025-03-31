#include <HTTPClient.h>
#include <ArduinoJson.h>

struct TempoData {
  String today_color;
  String tomorrow_color;
  int today_number;
  int tomorrow_number;
};

TempoData get_tempo_data() {
  TempoData data;
  HTTPClient http;
  
  http.begin("https://www.api-couleur-tempo.fr/api/tempo");
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    data.today_color = doc["today"]["color"].as<String>();
    data.tomorrow_color = doc["tomorrow"]["color"].as<String>();
    data.today_number = doc["today"]["dayNumber"].as<int>();
    data.tomorrow_number = doc["tomorrow"]["dayNumber"].as<int>();
  }
  
  http.end();
  return data;
}

void tempo_setup() {
  // Initialisation si nécessaire
}