#include "UIHandler.h"
#include "Logic.h"
#include "UpdateGlobal.h"
#include "Logger.h"
#include "BackupData.h"

void setup() {
  delay(500);
  Serial.begin(9600);
  UIinit();
  LogicInit();
  ExternalStorageInit();
  // checkTimeRtc();
  // timertc.setDS1302Time(0, 29, 17, 1, 5, 6, 2025);
  // RESET_SYSTEM();
  // ClearBackupSystemData();
  ReadBackupSystemData();
  // checkTimeRtc();
  if(SystemRunning){
    LogMsg("BACKUP", "Reading EEPROM data....");
    BackupSystemTime();
    PredictedEndDay(beginHour, beginMinute, beginMonth, beginDay, beginYear, TotalOperatingDay);
    ConvertFormatDateToUI();
    MotorDelayStart = millis();
    currentState = STATE_MAIN;
    if(solarOnHour != solarOffHour && solarOnMinute != solarOffMinute){
      EnergizeSolarTime();
      Serial.println("Energizing The Inverter!");
      delay(5000);
    }
  }
  // BackupSystemTime();
  checkTimeRtc();
}

void loop() {
  timertc.updateTime();
  // BackupSystemTime();
  // checkTimeRtc();
  SystemTimeUpdate();
  updateBuzzer();
  if(SystemRunning) {
    UpdateSystemSensorData();
    SensorDevice();
    UpdateDeviceState();
    }
  FrameLoop();
}
