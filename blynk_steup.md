# 🚀 Blynk Setup Guide for Smart Exhaust Fan IoT Project

This guide helps you configure the Blynk platform to work with your ESP32-based Smart Exhaust Fan project.

---

## 1. Create Blynk Account

- Download the Blynk IoT app (iOS/Android)
- Sign up or log in at: https://blynk.cloud/

---

##  2. Create New Template

1. Go to the Blynk Web Dashboard
2. Click "Templates" > "Create New Template"
   - Template Name: Smart Exhaust Iot
   - Hardware: ESP32
   - Connection: WiFi
3. Copy the generated:
   - BLYNK_TEMPLATE_ID
   - BLYNK_TEMPLATE_NAME
   - BLYNK_AUTH_TOKEN

   Example 
   ```cpp
   #define BLYNK_TEMPLATE_ID "***"
   #define BLYNK_TEMPLATE_NAME "Smart Exhaust Iot"
   #define BLYNK_AUTH_TOKEN "***"
