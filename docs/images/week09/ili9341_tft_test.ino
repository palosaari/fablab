#include "DHTesp.h"
#include <Arduino_GFX_Library.h>

DHTesp dht11;

// TFT - ESP32 dispay data pins used
#define TFT_SCK    19
#define TFT_MOSI   18
#define TFT_MISO   22
#define TFT_CS     4
#define TFT_DC     17
#define TFT_RESET  16
#define TFT_LED    21

// https://techtutorialsx.com/2021/01/31/esp32-ili9341-display-hello-world/

Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println("TFT test, output week");

  // Initialize DHT11 temperature sensor, IO26
  dht11.setup(26, DHTesp::DHT11);

  // Power on TFT display light
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  // Initialize TFT display
  display.begin(); // Init
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setRotation(1); // Horizontal
}

void loop() {
  TempAndHumidity sensorData;
  sensorData = dht11.getTempAndHumidity();
  Serial.println("DHT11 Temperature:" + String(sensorData.temperature, 2) + " Humidity:" + String(sensorData.humidity, 1));

  // Use BOOT button to toggle TFT display light ON/OFF
  if (!digitalRead(0))
    digitalWrite(TFT_LED, !digitalRead(TFT_LED));

  display.setCursor(0, 10);
  display.fillScreen(BLACK);
  display.print("Sensor DHT11:\n" "Temperature " + String(sensorData.temperature, 1) + "C\n" + "Humidity    " + String(sensorData.humidity, 1) + "%");

  sleep(2);
}
