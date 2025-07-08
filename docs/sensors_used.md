
# 📘 Sensors Used in Smart Exhaust Fan IoT Project

This document explains the key sensors used in your Smart Exhaust Fan project, how they work, and how they're connected to the ESP32. It matches the configuration and pins used in your provided source code.

---

## 🔹 1. DHT11 (Temperature & Humidity Sensor)

* Function: Measures ambient temperature and relative humidity
* Data Output: Digital
* ESP32 Pin: GPIO 5 (DHTPIN)
* Working Principle:

  * Uses a thermistor to measure temperature
  * Uses a capacitive humidity sensor
* Library Required: `DHT sensor library` by Adafruit
* Use Case: Triggers fan when temperature or humidity exceed thresholds

---

## 🔹 2. MQ-135 (Air Quality Sensor)

* Function: Detects various air pollutants (NH3, NOx, alcohol, benzene, smoke, CO2)
* Data Output: Analog (read via ADC)
* ESP32 Pin: GPIO 36 (MQ135\_PIN)
* Working Principle:

  * Contains a chemical-sensitive layer that changes resistance in response to gas concentrations
* Use Case: Fan activation when air quality drops below a safe threshold (value > 900)

---

## 🔹 3. MQ-9 (Gas Sensor)

* Function: Detects CO and combustible gases like LPG, CH4
* Data Output: Analog (read via ADC)
* ESP32 Pin: GPIO 39 (MQ9\_PIN)
* Working Principle:

  * Uses a tin dioxide (SnO2) sensitive layer with variable resistance based on gas exposure
* Use Case: Fan triggers when gas levels exceed safe limits (value > 400)

---

## 🔹 4. Power Sensing (Voltage Divider Input)

* Function: Detects whether system is running on main adapter or battery
* Data Output: Analog
* ESP32 Pin: GPIO 34 (MAIN\_SENSE\_PIN)
* Working Principle:

  * Reads voltage level via voltage divider and determines if value is above 2048 (\~2.5V on 12-bit ADC)
* Use Case: Ensures fan only operates on main power (not battery)

---

## 🔹 5. Manual Switch

* Function: Physical push button to manually override fan state
* Data Output: Digital (LOW when pressed)
* ESP32 Pin: GPIO 14 (MANUAL\_SWITCH\_PIN)
* Working Principle:

  * Reads digital input level from pull-up configured button pin
* Use Case: Forces fan ON when pressed regardless of sensor inputs

---

## 🔹 6. Fan Relay Control

* Function: Controls power to the exhaust fan
* Data Output: Digital Output
* ESP32 Pin: GPIO 27 (FAN\_RELAY\_PIN)
* Working Principle:

  * Activates relay module using digital HIGH signal
* Use Case: Automatically turns fan ON/OFF based on sensor and logic evaluation

---

## ✅ Sensor Notes

* ESP32 ADC pins read analog voltages in range 0–3.3V.
* MQ-135 and MQ-9 use analog read pins and may need calibration.
* DHT11 and button require stable digital input handling.
* Use pull-up resistors where necessary (e.g., manual switch).
* Sensor thresholds in code:

  * MQ135\_THRESHOLD = 900
  * MQ9\_THRESHOLD = 400
  * MAIN\_THRESHOLD = 2048

Let me know if you’d like a circuit diagram or visual table format for easier reference.
