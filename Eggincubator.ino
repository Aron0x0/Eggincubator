#include "UIHandler.h"
#include "Logic.h"
#include "UpdateGlobal.h"
#include "Logger.h"
#include "BackupData.h"

void setup() {
  Serial.begin(9600);
  UIinit();
  LogicInit();
  ExternalStorageInit();
  // timertc.setDS1302Time(0, 56, 21, 4, 1, 5, 2025);
  ReadBackupSystemData();
  if(SystemRunning){
    currentState = STATE_MAIN;
    Serial.println(beginHour);
    Serial.println(beginMinute);
    Serial.println(beginMonth);
    Serial.println(beginDay);
    Serial.println(beginYear);
    FORMATDATE = "";
    TOFORMATDATE = "";
    PredictedEndDay(beginHour, beginMinute, beginMonth, beginDay, beginYear, TotalOperatingDay);
    ConvertFormatDateToUI();
    MotorDelayStart = millis();
  }
}

void loop() {
  timertc.updateTime();
  SystemTimeUpdate();
  if(SystemRunning) {
    UpdateSystemSensorData();
    SensorDevice();
    UpdateDeviceState();
    }
  FrameLoop();
}
