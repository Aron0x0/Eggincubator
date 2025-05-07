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
  // timertc.setDS1302Time(0, 29, 17, 1, 5, 6, 2025);
  // RESET_SYSTEM();
  ReadBackupSystemData();
  if(SystemRunning){
    PredictedEndDay(beginHour, beginMinute, beginMonth, beginDay, beginYear, TotalOperatingDay);
    ConvertFormatDateToUI();
    MotorDelayStart = millis();
    currentState = STATE_MAIN;
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
