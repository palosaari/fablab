#include "DHTesp.h"

DHTesp dht11;

void setup() {
  Serial.begin(115200);
  Serial.println("Temperature test, input week");

//  analogSetAttenuation(ADC_0db);    // 1.0V max measured
//  analogSetAttenuation(ADC_2_5db);  // 1.3V max measured
//  analogSetAttenuation(ADC_6db);    // 1.9V max measured
  analogSetAttenuation(ADC_11db);   // 3.1V max measured

  // Initialize DHT11 temperature sensor, IO26
  dht11.setup(26, DHTesp::DHT11);
}

void loop() {
  // ESP32 default ADC resolution is 12 bits, values 0 - 4095.
  // If we assume curve is linear and all the other are correct then ADC value 0 is 0V
  // and value 4095 is 3.3V => analogRead() / 4095 * 3.3 = voltage on pin. Only in theory.
  // It is not that simple, see analogSetAttenuation()...

  // Read 10k NTC thermistor on IO4. It is connected as voltage divider, so at 25C it should be 0.5 * 3.3V = 1.65V
  unsigned int AdcValue = analogRead(4);
  
  // Get DHT11 data
  TempAndHumidity sensorData;
  sensorData = dht11.getTempAndHumidity();

  // Output is scaled somehow weird in order to plot it using Arduino Serial Plotter
  Serial.println("DHT11_Temperature:" + String(sensorData.temperature, 2) + " DHT11_Humidity:" + String(sensorData.humidity, 1)
                 + " NTC_analogRead/100:" + String(AdcValue/100.0) + " NTC_Voltagex10:" + String(3.1/4095 * AdcValue * 10));

  sleep(2);
}
