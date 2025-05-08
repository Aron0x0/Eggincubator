# ✅ Error Code Reference

This document lists all system error codes used in the project and their descriptions.

---

## 🧊 SD Card / Storage Errors

| Code   | Description                                   |
|--------|-----------------------------------------------|
| SD01   | SD card not detected or failed to initialize  |
| SD02   | Failed to open `data.txt`                     |
| SD03   | Failed to open `Log.txt`                      |
| SD04   | Failed to write to file                       |
| LOG01  | Logging disabled due to full or locked SD     |

---

## 🌡️ Sensor Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| TMP01  | Temperature sensor not detected              |
| TMP02  | Temperature reading out of range             |
| HUM01  | Humidity sensor not detected                 |
| HUM02  | Humidity reading out of range                |
| SEN01  | Sensor value inconsistent/fluctuating        |

---

## 🔋 Battery & Power Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| BAT01  | Battery low                                  |
| BAT02  | Battery critically low                       |
| BAT03  | Battery fully charged                        |
| BAT04  | Battery sensor not detected                  |
| PWR01  | Power supply voltage too low                 |
| PWR02  | Brown-out or unstable power                  |

---

## 🕒 RTC / Time Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| RTC01  | RTC module not detected                      |
| RTC02  | Time not set or invalid                      |

---

## ⚙️ Relay / Device Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| REL01  | Heater relay failed to activate              |
| REL02  | Heater relay stuck ON or OFF                 |
| REL03  | Heater over-temperature shutoff              |
| REL04  | Humidifier relay failed to activate          |
| REL05  | Humidifier relay stuck ON or OFF             |
| REL06  | Humidity too high — humidifier shut down     |
| REL07  | Solar mode relay failed to activate          |
| REL08  | Solar mode logic conflict (e.g., night mode) |
| REL09  | Motor relay failed to activate               |
| REL10  | Motor feedback not detected                  |
| REL11  | Motor overcurrent or overheating             |
| REL12  | Relay GPIO/driver IC failure                 |

---

## 🧠 System / Logic / Config Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| CFG01  | Configuration file load failed               |
| CFG02  | Configuration file contains invalid values   |
| SYS01  | Unknown system error                         |
| SYS02  | Watchdog triggered reset                     |
| INT01  | Interrupt handler failed or overloaded       |
| BOOT01 | Startup/boot sequence failed                 |

---

## 🌐 Network Errors

| Code   | Description                                  |
|--------|----------------------------------------------|
| NET01  | Wi-Fi not connected                          |
| NET02  | MQTT server unreachable                      |
