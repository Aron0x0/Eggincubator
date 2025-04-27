#include "UIHandler.h"
#include "Logic.h"
#include "UpdateGlobal.h"
#include "Logger.h"

void setup() {
  Serial.begin(9600);
  UIinit();
  LogicInit();
  ExternalStorageInit();
  // timertc.setDS1302Time(0, 8, 1, 5, 25, 4, 2025);
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
