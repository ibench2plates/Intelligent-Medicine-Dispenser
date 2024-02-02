# Medication Dispenser with Telegram Integration

This project implements a medication dispenser system with Telegram integration using an ESP32 microcontroller. The system allows users to request medication dispensing through a Telegram bot.

## Features

- Dispenses medication based on patients' last four digits of NRIC.
- Uses ultrasonic sensor for cup presence detection.
- Telegram bot integration for user interaction.

## Dependencies

- WiFi.h
- WiFiClientSecure.h
- UniversalTelegramBot.h
- ArduinoJson.h
- ESP32Servo.h

## Configuration

1. Replace the placeholder values in the code with your WiFi network credentials (`WIFI_SSID` and `WIFI_PASSWORD`).
2. Obtain a Telegram bot token from Botfather and replace the value of `BOT_TOKEN`.
3. Identify the chat ID for your Telegram user or group and replace the value of `CHAT_ID`.

## Hardware Setup

Connect the ESP32 pins to the ultrasonic sensor and servos as per your specific hardware setup.

## Usage

1. Flash the code onto your breadboard.
2. Connect the hardware components as per your setup.
3. Interact with the Telegram bot to request medication dispensing.

## Notes

- Adjust the `valid_id` array with user IDs and medication information.
- Modify the `spin_servo` function for specific servo control logic.
- Ensure proper handling of medication presence with the ultrasonic sensor.

