#include <SPI.h>
#include <SD.h>
#include "Config.h"

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8
#define SD_CS    4

File data;

bool ExternalStorageInit() {
  bool res = true;
  pinMode(SD_CS, OUTPUT);

  digitalWrite(TFT_CS, HIGH);   // Disable TFT
  digitalWrite(SD_CS, LOW); 
  
  if (!SD.begin(SD_CS)) {
    Serial.println("/> No External Storage!");
    res = false;
  }

  File data = SD.open("data.txt", FILE_WRITE);
  if (data) {
    if (data.size() == 0) {  // Only write headers if file is empty
      data.println("DATE,Time,Temperature,Humidity");
    }
    data.close();
  } else {
    Serial.println("/> ERROR: Failed to create data.txt!");
    res = false;
  }
  digitalWrite(SD_CS, HIGH);    // Disable SD
  digitalWrite(TFT_CS, LOW);
  return res;
}

void WriteExternalStorage() {
  digitalWrite(TFT_CS, HIGH);   // Disable TFT
  digitalWrite(SD_CS, LOW);
  File data = SD.open("data.txt", FILE_WRITE);
  
  if (data) {
    data.print(DATE);  data.print(",");
    data.print(CLOCK); data.print(",");
    data.print(temp);  data.print(",");
    data.println(humid);
    data.close();
  } else {
    Serial.println("/> ERROR: Failed to open data.txt for writing!");
  }
  digitalWrite(SD_CS, HIGH);    // Disable SD
  digitalWrite(TFT_CS, LOW);
}


