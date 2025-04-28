# 🐣 Egg Incubator using Arduino Mega

A DIY automatic egg incubator project built using Arduino Mega, designed to regulate temperature, humidity, and timing with a visual interface on a 3.5" TFT touch display.

## 🧰 Components Used

- Arduino Mega 2560
- RMH RTC DS1302 (with **VirtuabotixRTC** library)
- DHT22 (Temperature & Humidity Sensor) – using **DHT** library
- 3 x Relay Module (Heater, Motor, Solar)
- 1 x Mosfet Controlled Humidifier
- 3.5" TFT LCD Shield – using **MCUFRIEND_kbv**
- Touch Input – using **TouchScreen** library
- Jumper wires, breadboard, power supply, etc.

## 🔧 Features

- 📆 Real-time date and time tracking (DS1302)
- 🌡️ Live temperature & humidity monitoring (DHT22)
- 🔌 Relay-based control for heater, humidifier, and fan/light
- 🖥️ Colorful GUI on 3.5" TFT LCD
- 👆 Touch interaction for simple UI or settings (optional)
- 🕒 Scheduled control with RTC, even during power loss

## 🛠 Libraries Used

Make sure you have these installed in the Arduino IDE:

- `DHT` by Adafruit (for DHT22 sensor)
- `VirtuabotixRTC` (for DS1302)
- `MCUFRIEND_kbv` (for TFT screen)
- `TouchScreen` (for touchscreen input)

## 📁 Project Structure


## 🔌 Wiring Overview

| Component       | Arduino Mega Pin | Notes                          |
|----------------|------------------|--------------------------------|
| **RTC CLK**     | 23               | `#define CLK 23`               |
| **RTC DAT**     | 25               | `#define DAT 25`               |
| **RTC RST**     | 27               | `#define RST 27`               |
| **Relay – Solar**   | 29               | `#define IOSOLAR 29`           |
| **Relay – Heater**  | 31               | `#define IOHEATER 31`          |
| **Relay – Synchronous Motor** | 33           | `#define IOMOTOR 33`           |
| **Relay – Humidifier** | 35         | `#define IOHUMID 35`           |
| **DHT22 Sensor** | 49               | `#define IODHT 49`             |
| **DHT22 Sensor** | 51               | `#define IODHT 51`             |
| **DHT Type**     | —                | `#define DHTTYPE DHT22`        |
| **TFT LCD**      | Shield Pins      | Uses multiple Mega pins (plug-in shield) |
| **TouchScreen**  | A1–A4            | Shared with TFT, configured via `TouchScreen.h` |

## 🚀 Getting Started

1. Open `Eggincubator.ino` in the Arduino IDE.
2. Install the required libraries listed above.
3. Connect all components as per the wiring plan.
4. Upload the sketch to your Arduino Mega.
5. Watch real-time data on the screen and interact via touch!

## 🌱 Future Improvements

- Add calibration or settings menu via touchscreen
- Store settings using EEPROM
- Add a buzzer for alarms (overheat, low humidity)
- Integrate an SD card for logging data
- Adding Android Software to Optimize and Calibrate the Incubator. Make the debugging for ERROR more easier.

## 📸 Preview

> *(Add your build photos or TFT screenshots here!)*

## 📜 License

Open-source and free to use for educational or personal use.

---

