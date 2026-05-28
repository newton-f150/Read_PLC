#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// -------- WIFI CONFIG --------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// -------- BACKEND API --------
const char* serverUrl = "http://your-server.com/api";

// -------- DEVICE CONFIG --------
String device_id = "INC001";

// -------- SENSOR CONFIG --------
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// -------- RELAY CONFIG --------
#define RELAY_PIN 5

// -------- TARGET TEMP --------
float targetTemp = 37.5;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp)) {
    Serial.println("Failed to read sensor!");
    return;
  }

  Serial.println("Temp: " + String(temp));

  // -------- LOCAL CONTROL (IMPORTANT) --------
  if (temp < targetTemp) {
    digitalWrite(RELAY_PIN, HIGH); // Heater ON
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Heater OFF
  }

  // -------- SEND DATA TO SERVER --------
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(serverUrl) + "/data";
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{";
    jsonData += "\"device_id\":\"" + device_id + "\",";
    jsonData += "\"temperature\":" + String(temp) + ",";
    jsonData += "\"humidity\":" + String(humidity);
    jsonData += "}";

    int httpResponseCode = http.POST(jsonData);

    Serial.println("POST Response: " + String(httpResponseCode));

    http.end();
  }

  // -------- FETCH COMMANDS FROM SERVER --------
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(serverUrl) + "/command?device_id=" + device_id;
    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.println("Command: " + payload);

      // SIMPLE PARSE (you can improve this)
      if (payload.indexOf("heater_on") > 0) {
        digitalWrite(RELAY_PIN, HIGH);
      } else if (payload.indexOf("heater_off") > 0) {
        digitalWrite(RELAY_PIN, LOW);
      }
    }

    http.end();
  }

  delay(5000); // every 5 seconds
}