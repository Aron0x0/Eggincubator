#include <SPI.h>
#include <SD.h>
#include "Config.h"  // Make sure DATE, CLOCK, temp, humid are defined here

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
      Serial.println("Wrting...");
    } else {
      Serial.println("/> ERROR: Failed to create data.txt!");
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
