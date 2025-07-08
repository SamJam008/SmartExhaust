#define BLYNK_TEMPLATE_ID "TMPL3SwOLMe5c"
#define BLYNK_TEMPLATE_NAME "Smart Exhaust Iot"
#define BLYNK_AUTH_TOKEN "Y_izwdxaGlxLmrlSUUYplyT1nv962dpe"


#include <Arduino.h>
#include "DHT.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


// === Blynk Credentials ===
char auth[] = "Y_izwdxaGlxLmrlSUUYplyT1nv962dpe";        // Replace with your Blynk auth token
char ssid[] = "SomyaPhone";               // Replace with your Wi-Fi SSID
char pass[] = "crude_oil_08";


// === Sensor Pins ===
#define MQ135_PIN         36
#define MQ9_PIN           39
#define DHTPIN            5
#define DHTTYPE           DHT11
DHT dht(DHTPIN, DHTTYPE);


// === Power Detection ===
#define MAIN_SENSE_PIN    34
#define MAIN_THRESHOLD    2048   // ~2.5V on 12-bit ADC


// === Fan Control ===
#define FAN_RELAY_PIN     27


// === Manual Switch ===
#define MANUAL_SWITCH_PIN 14


// === Fan Thresholds (adjust as needed) ===
#define MQ135_THRESHOLD   900   // Example: adjust per your environment
#define MQ9_THRESHOLD     400


void setup() {
  Serial.begin(115200);
  delay(2000);  // Give time for Serial to come online
  Serial.println("🔧 Booting...");


  pinMode(MAIN_SENSE_PIN, INPUT);
  pinMode(FAN_RELAY_PIN, OUTPUT);
  digitalWrite(FAN_RELAY_PIN, LOW);


  pinMode(MANUAL_SWITCH_PIN, INPUT_PULLUP);


  delay(2000);  //  Give time before initializing DHT
  dht.begin();  //  DHT11 initialized safely


    // Connect to WiFi and Blynk
  
Serial.print("Connecting to WiFi");
 WiFi.begin(ssid, pass);


while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("\n Connected to WiFi!");


  Blynk.config(auth);
  if (!Blynk.connect(5000)) {  // Wait 5 seconds max
    Serial.println(" Failed to connect to Blynk. Restarting...");
    delay(2000);
    ESP.restart();  // Restart if Blynk fails
  }




  Serial.println(" Setup complete.\n");
}


void loop() {
   Blynk.run();
     if (!Blynk.connected()) {
    Serial.println(" Not connected to Blynk cloud");
  } else {
    Serial.println(" Connected to Blynk cloud");
  }


  Serial.println(" Loop running...");


  // === Power Detection ===
  int powerADC = analogRead(MAIN_SENSE_PIN);
  bool isOnMainPower = (powerADC >= MAIN_THRESHOLD);
  Serial.printf("🔌 Power ADC: %d → %s\n", powerADC, isOnMainPower ? "Main Adapter" : "Battery");
 Blynk.virtualWrite(V5, isOnMainPower ? "Main Adapter" : "Battery");  //  Send power info




  // === Sensor Readings ===
  int mq135_val = analogRead(MQ135_PIN);
  int mq9_val = analogRead(MQ9_PIN);
  Serial.printf(" MQ135 Reading: %d\n", mq135_val);
  Serial.printf(" MQ9 Reading: %d\n", mq9_val);


  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(" DHT11: Failed to read!");
  } else {
    Serial.printf(" Temp: %.1f °C,  Humidity: %.1f %%\n", temperature, humidity);
  }


  // === Manual Switch Logic ===
  bool manualSwitchPressed = digitalRead(MANUAL_SWITCH_PIN) == LOW;
  Serial.printf(" Manual Switch: %s\n", manualSwitchPressed ? "Pressed (Override Fan ON)" : "Released");


 Blynk.virtualWrite(V1, mq135_val);
  Blynk.virtualWrite(V2, mq9_val);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V4, humidity);
  // === Fan Logic ===
  bool fanShouldRun = false;


  if (manualSwitchPressed) {
    fanShouldRun = true;
    Serial.println(" Manual override → Fan ON");
  } else if (isOnMainPower && (mq135_val > MQ135_THRESHOLD || mq9_val > MQ9_THRESHOLD)) {
    fanShouldRun = true;
    Serial.println(" Sensor threshold passed & main power available → Fan ON");
  } else {
    fanShouldRun = false;
    Serial.println(" Conditions not met → Fan OFF");
  }


  digitalWrite(FAN_RELAY_PIN, fanShouldRun ? HIGH : LOW);
   Blynk.virtualWrite(V0, fanShouldRun ? 1 : 0);
  Serial.printf(" Fan State: %s\n", fanShouldRun ? "ON" : "OFF");




  Serial.println("-------------------------\n");
  delay(2000);  // loop delay
}
