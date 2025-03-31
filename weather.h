#include <HTTPClient.h>
#include <ArduinoJson.h>

struct WeatherData {
  String condition;
  float temperature;
  float humidity;
};

WeatherData get_weather_data() {
  WeatherData data;
  HTTPClient http;
  
  // Utilisez votre API météo préférée (OpenWeatherMap, etc.)
  String url = "http://api.openweathermap.org/data/2.5/weather?q=Paris,fr&units=metric&appid=YOUR_API_KEY";
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    
    data.temperature = doc["main"]["temp"];
    data.humidity = doc["main"]["humidity"];
    data.condition = doc["weather"][0]["main"].as<String>();
  }
  
  http.end();
  return data;
}

void weather_setup() {
  // Initialisation si nécessaire
}