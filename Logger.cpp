#include <SPI.h>
#include <SD.h>
#include "Config.h"  // Make sure DATE, CLOCK, temp, humid are defined here
#include "Logger.h"

#define SD_CS 53  // SD Chip Select pin for Arduino Mega

bool ExternalStorageInit() {
  bool res = true;
  if (!SD.begin(SD_CS)) {
    Serial.println("/> No External Storage!");
    res = false;
  } else {
    Serial.println("/> Good External Storage!");

    File data = SD.open("data.txt", FILE_WRITE);
    if (data) {
      if (data.size() == 0) {
        data.println("DATE,Time,Temperature,Humidity");
      }
      data.close();
      Serial.println("/? Creating data.txt...");
    } else {
      Serial.println("/> ERROR: Failed to create data.txt!");
      res = false;
    }
    File Log = SD.open("Log.txt", FILE_WRITE);
    if (Log) {
      if (Log.size() == 0) {
        Log.println("DATE,Time,ErrorType,ErrorCode,Message");
      }
      Log.close();
      Serial.println("/? Creating Log.txt...");
    } else {
      Serial.println("/> ERROR: Failed to create Log.txt!");
      res = false;
    }
  }
  return res;
}

void WriteExternalStorage() {
  File data = SD.open("data.txt", FILE_WRITE);
  
  if (data) {
    data.print(DATE);   data.print(",");
    data.print(CLOCK);  data.print(",");
    data.print(temp);   data.print(",");
    data.println(humid);
    data.close();
  } else {
    Serial.println("/> ERROR: Failed to open data.txt for writing!");
  }
}

void Log(String ErrorCode, char Type){
  String ErrorType;
  String Msg = GetErrorDescription(ErrorCode);
  switch(Type){ //e = Error Msg , d = Debug, a = Alert
    case 'e':
      ErrorType = "ERROR";
      break;
    case 'd':
      ErrorType = "DEBUG";
      break;
    case 'a':
      ErrorType = "ALERT";
      break;
    default:
      return;
      break;
  }
  File Log = SD.open("Log.txt", FILE_WRITE);
  if (Log) {
    Log.print(DATE);   Log.print(",");
    Log.print(CLOCK);  Log.print(",");
    Log.print(ErrorType); Log.print(",");
    Log.print(ErrorCode); Log.print(",");
    Log.print(Msg); Log.println();
    Log.close();
  } else {
    Serial.println("/> ERROR: Failed to open Log.txt for writing!");
  }
}

String GetErrorDescription(String ErrorCode) {
  if (ErrorCode == "SD01") return "SD card not detected or failed to initialize";
  else if (ErrorCode == "SD02") return "Failed to open data.txt";
  else if (ErrorCode == "SD03") return "Failed to open Log.txt";
  else if (ErrorCode == "SD04") return "Failed to write to file";
  else if (ErrorCode == "LOG01") return "Logging disabled due to full or locked SD";

  else if (ErrorCode == "TMP01") return "Temperature sensor not detected";
  else if (ErrorCode == "TMP02") return "Temperature reading out of range";
  else if (ErrorCode == "HUM01") return "Humidity sensor not detected";
  else if (ErrorCode == "HUM02") return "Humidity reading out of range";
  else if (ErrorCode == "SEN01") return "Sensor value inconsistent/fluctuating";

  else if (ErrorCode == "BAT01") return "Battery low";
  else if (ErrorCode == "BAT02") return "Battery critically low";
  else if (ErrorCode == "BAT03") return "Battery fully charged";
  else if (ErrorCode == "BAT04") return "Battery sensor not detected";
  else if (ErrorCode == "PWR01") return "Power supply voltage too low";
  else if (ErrorCode == "PWR02") return "Brown-out or unstable power";

  else if (ErrorCode == "RTC01") return "RTC module not detected";
  else if (ErrorCode == "RTC02") return "Time not set or invalid";

  else if (ErrorCode == "REL01") return "Heater relay failed to activate";
  else if (ErrorCode == "REL02") return "Heater relay stuck ON or OFF";
  else if (ErrorCode == "REL03") return "Heater over-temperature shutoff";
  else if (ErrorCode == "REL04") return "Humidifier relay failed to activate";
  else if (ErrorCode == "REL05") return "Humidifier relay stuck ON or OFF";
  else if (ErrorCode == "REL06") return "Humidity too high — humidifier shut down";
  else if (ErrorCode == "REL07") return "Solar mode relay failed to activate";
  else if (ErrorCode == "REL08") return "Solar mode logic conflict (e.g., night mode)";
  else if (ErrorCode == "REL09") return "Motor relay failed to activate";
  else if (ErrorCode == "REL10") return "Motor feedback not detected";
  else if (ErrorCode == "REL11") return "Motor overcurrent or overheating";
  else if (ErrorCode == "REL12") return "Relay GPIO/driver IC failure";

  else if (ErrorCode == "CFG01") return "Configuration file load failed";
  else if (ErrorCode == "CFG02") return "Configuration file contains invalid values";
  else if (ErrorCode == "SYS01") return "Unknown system error";
  else if (ErrorCode == "SYS02") return "Watchdog triggered reset";
  else if (ErrorCode == "INT01") return "Interrupt handler failed or overloaded";
  else if (ErrorCode == "BOOT01") return "Startup/boot sequence failed";

  else if (ErrorCode == "NET01") return "Wi-Fi not connected";
  else if (ErrorCode == "NET02") return "MQTT server unreachable";

  else return "Unknown error code";
}

