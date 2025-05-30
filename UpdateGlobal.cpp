#include "UpdateGlobal.h"
#include "Config.h"
#include "Logic.h"

void UpdateSystemSensorData(){
  // temp = (dht.readTemperature() + dhtback.readTemperature()) / 2; 
  // humid = (dht.readHumidity() + dhtback.readHumidity()) / 2; 
  temp = dht.readTemperature();
  humid = dht.readHumidity();
  BatteryVoltage = readBatteryVoltage(IOBATTERY); 
  // BatteryVoltage = 0.0; 
  BatteryLevel = getBatteryPercentage(BatteryVoltage);
  isDoorOpen = digitalRead(IODOOR);

  bool currentDoorState = digitalRead(IODOOR);
  if (currentDoorState != isDoorOpen && currentDoorState != isLastDoorOpen) {
    if (DelayFunction(DOOR, 2000)) {
      isDoorOpen = currentDoorState;
      isLastDoorOpen = isDoorOpen;
    }
  }
}