# Smart Exhaust Fan (IoT Project)

An ESP32-based smart exhaust fan system using temperature, humidity, air quality, gas, and fire sensors. It automatically activates the fan and sends alerts using the Blynk platform.

## Components Used
- ESP32
- DHT22 (Temperature & Humidity)
- MQ-135 (Air Quality)
- MQ-2 (Gas)
- Flame Sensor
- PIR Sensor
- 5V Relay Module
- 12V DC Fan

## Features
- Fan turns ON when thresholds are exceeded
- Fan turns OFF when air quality is normal
- Emergency handling even in case on power power shortage: Fire, gas leaks
- Remote monitoring via Blynk
- Manual control from mobile app

## Blynk Dashboard
- Real-time temperature, humidity, gas levels
- Manual override switch
- Alerts 

## How It Works
- Sensors detect environmental data
- ESP32 makes decisions
- Relay module activates fan
- Blynk app reflects real-time data

## File Structure
- `SmartFan_Code.ino` – Arduino code
- `blynk_setup.md` – Guide to configure Blynk
- `circuit_diagram.jpg` – Wiring diagram
- `sensors_used.md` – How sensors work

## Dashboard
![dashboard](images/dashboard_ss.jpg)

## Getting Started
1. Connect all components (see diagram)
2. Upload code using Arduino IDE
3. Configure Blynk app
4. Power your setup


## ✍️ Author
Somya Gupta
"# SmartExhaust" 
