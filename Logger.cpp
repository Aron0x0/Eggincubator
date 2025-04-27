#include <SPI.h>
#include <SD.h>
#include "Config.h"

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8
#define SD_CS    4

File data;

bool ExternalStorageInit(){
  pinMode(SD_CS, OUTPUT);

  if(!SD.begin(SD_CS)){
    Serial.println("/> No External Storage!");
    return false;
  } else {
    data = SD.open("data.txt", FILE_WRITE);
    if(data) {
      data.println("DATE, Time, Temperature, Humidity");
      data.close();
    }
    return true;
  }
}

void WriteExternalStorage(){
  data = SD.open("data.txt", FILE_WRITE);
  if(data) {
    data.print(DATE);data.print(",");
    data.print(CLOCK);data.print(",");
    data.print(temp);data.print(",");
    data.print(humid);data.println();
    data.close();
  }else {
    Serial.println("/> ERROR: Failed to load File in External_Storage!");
  }
}

