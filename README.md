# 🐣 Egg Incubator using Arduino Mega

A DIY automatic egg incubator project built using Arduino Mega, designed to regulate temperature, humidity, and timing with a visual interface on a 3.5" TFT touch display.

## 🧰 Components Used

- Arduino Mega 2560
- RMH RTC DS1302 (with **VirtuabotixRTC** library)
- DHT22 (Temperature & Humidity Sensor) – using **DHT** library
- 3 x Relay Module (Heater, Humidifier, Fan or Light)
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
| **RTC CLK**     | 22               | `#define CLK 22`               |
| **RTC DAT**     | 23               | `#define DAT 23`               |
| **RTC RST**     | 24               | `#define RST 24`               |
| **Relay – Solar**   | 25               | `#define IOSOLAR 25`           |
| **Relay – Heater**  | 26               | `#define IOHEATER 26`          |
| **Relay – Motor/Fan** | 27           | `#define IOMOTOR 27`           |
| **Relay – Humidifier** | 28         | `#define IOHUMID 28`           |
| **DHT22 Sensor** | 29               | `#define IODHT 29`             |
| **DHT Type**     | —                | `#define DHTTYPE DHT22`        |
| **TFT LCD**      | Shield Pins      | Uses multiple Mega pins (plug-in shield) |
| **TouchScreen**  | A1–A4            | Shared with TFT, configured via `TouchScreen.h` |

## 🚀 Getting Started

1. Open `egg_incubator.ino` in the Arduino IDE.
2. Install the required libraries listed above.
3. Connect all components as per the wiring plan.
4. Upload the sketch to your Arduino Mega.
5. Watch real-time data on the screen and interact via touch!

## 🌱 Future Improvements

- Add calibration or settings menu via touchscreen
- Store settings using EEPROM
- Add a buzzer for alarms (overheat, low humidity)
- Integrate an SD card for logging data

## 📸 Preview

> *(Add your build photos or TFT screenshots here!)*

## 📜 License

Open-source and free to use for educational or personal use.

---

