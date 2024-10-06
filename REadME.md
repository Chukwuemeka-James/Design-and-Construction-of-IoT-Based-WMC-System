# Design and Construction of IoT-Based Water Level Monitoring and Control System

This repository contains the code for our final year project, Design and Construction of IoT-Based Water Level Monitoring and Control System. This project was developed by my team as part of our degree program in Electrical and Electronic Engineering. The system is designed to monitor water levels in both overhead and underground tanks, and to control a water pump automatically. Additionally, it provides real-time feedback through an LCD display and the Blynk IoT platform for remote monitoring and control.

## Project Overview

The **IoT-Based Water Level Monitoring and Control System** is developed to:
- Monitor the water levels in overhead and underground water tanks using ultrasonic sensors.
- Automatically control the water pump based on predefined water levels.
- Alert users when water levels are critically low or high using a buzzer alarm.
- Display real-time water level data on an LCD screen.
- Allow remote monitoring and control via the Blynk IoT app.

## Components Used

1. **ESP32 Microcontroller**: Handles the logic for the system and connects to the Blynk IoT platform for remote monitoring.
2. **Ultrasonic Sensors (HC-SR04)**: Measure the water levels in both tanks.
3. **Relay Module**: Used to switch the water pump on and off based on the water levels.
4. **Buzzer**: Sounds an alarm when critical water levels are reached.
5. **LCD Display (I2C 20x4)**: Displays the real-time water levels of the tanks.
6. **Blynk IoT Platform**: Provides a user-friendly interface for remote monitoring and control of the system through a smartphone.

## Features

- **Automatic Water Pump Control**: The system automatically turns the pump ON when the overhead tank's water level drops below a predefined threshold and turns it OFF when the tank is full.
- **Real-time Water Level Monitoring**: The LCD display provides live readings of the water levels in both the overhead and underground tanks.
- **Remote Access via Blynk**: Users can monitor the system and control the pump remotely through the Blynk app.
- **Alarm System**: A buzzer sounds an alert if water levels are too high or too low.
- **Protection Mechanism**: Ensures the pump doesn't run when the underground tank is empty, preventing dry running.

## How the Code Works

### Setup
- The ESP32 connects to the local WiFi and interfaces with the Blynk platform to enable remote monitoring and control.
- Two ultrasonic sensors continuously monitor the water levels in the tanks by measuring the distance to the water surface.
- Based on the water levels, the relay module switches the water pump on or off to maintain the desired levels.

### Main Functions
1. **`measureDistance()`**: This function calculates the distance from the ultrasonic sensor to the water surface, providing the water level measurement.
2. **`Measurement2()`**: Checks the water level in the underground tank to ensure the pump only activates when there is sufficient water available.
3. **Pump Control Logic**: The pump automatically activates if the overhead tank's water level is low, and deactivates when it is full. If there’s insufficient water in the underground tank, the pump stays off to protect the system.

### Blynk IoT Integration
- The Blynk app displays real-time data, such as water levels in both tanks, on a smartphone.
- Users can control the water pump through the app, turning it on or off as needed.
- Blynk also provides notifications or alarms when the system detects critical water levels.

## Components and Connections

| Component            | Pin on ESP32  |
|----------------------|---------------|
| Ultrasonic Sensor 1 (Overhead Tank) | Trig: GPIO 26, Echo: GPIO 25 |
| Ultrasonic Sensor 2 (Underground Tank) | Trig: GPIO 5, Echo: GPIO 18  |
| Relay for Pump        | GPIO 4        |
| Buzzer                | GPIO 13       |
| LCD Display (I2C)     | SDA: GPIO 21, SCL: GPIO 22 |

## How to Use

### Prerequisites
- **Blynk Library**: Install the Blynk library via the Arduino Library Manager.
- **LiquidCrystal I2C Library**: Required for the I2C LCD display.
- **WiFi Credentials**: Enter your WiFi SSID and password in the code to connect to the internet.

### Setup Instructions
1. Clone this repository:
   ```
   git clone https://github.com/your-repo-url
   ```
2. Open the code in the Arduino IDE.
3. Connect your ESP32 board to the system, upload the code, and verify the serial output for troubleshooting.
4. Download the Blynk app on your smartphone and create a new project using the provided **Blynk Authentication Token**.
5. Set up widgets in the Blynk app to monitor the water levels and control the pump remotely.

### Operation
- Once powered on, the ultrasonic sensors begin measuring water levels.
- The real-time water levels are displayed on the LCD, and the pump will be automatically controlled based on these measurements.
- Critical alerts (high/low water levels) will trigger the buzzer, and notifications will be sent via the Blynk app.
- Remote control of the pump is possible through the Blynk app.

## Conclusion

This project demonstrates the integration of IoT, real-time monitoring, and automatic control in a practical water management system. It is an efficient and cost-effective solution for both domestic and industrial water level management, providing convenience through remote monitoring and automated controls.

---

## Acknowledgements

- I would like to thank my project supervisor for the guidance throughout the development of this project.
- A special thanks to my team members who where very active and made significant contributions to the developement of the project.
- Also, thanks to the Blynk community for their valuable resources and support.