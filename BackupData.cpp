#include "BackupData.h"
#include "Config.h"
#include <EEPROM.h>

#define INIT_MARKER_ADDR 100
#define INIT_MARKER 0xAB

void BackupSystemData() {
  EEPROM.update(INIT_MARKER_ADDR, INIT_MARKER);
  EEPROM.write(0, SystemRunning);
  EEPROM.write(1, beginHour);
  EEPROM.write(2, beginMinute);
  EEPROM.write(3, beginDay);
  EEPROM.write(4, beginMonth);
  EEPROM.put(5, beginYear);  // Stores 2 bytes
  EEPROM.write(7, solarOnHour);
  EEPROM.write(8, solarOnMinute);
  EEPROM.write(9, solarOffHour);
  EEPROM.write(10, solarOffMinute);
}

void ClearBackupSystemData() {
  for (int i = 0; i <= 15; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.write(INIT_MARKER_ADDR, 0);
}

void ReadBackupSystemData() {
  if (EEPROM.read(INIT_MARKER_ADDR) != INIT_MARKER) return;
  SystemRunning = EEPROM.read(0);
  beginHour     = EEPROM.read(1);
  beginMinute   = EEPROM.read(2);
  beginDay      = EEPROM.read(3);
  beginMonth    = EEPROM.read(4);
  EEPROM.get(5, beginYear);
  solarOnHour   = EEPROM.read(7);
  solarOnMinute = EEPROM.read(8);
  solarOffHour  = EEPROM.read(9);
  solarOffMinute= EEPROM.read(10);
}
void BackupSystemTime(){
  EEPROM.update(INIT_MARKER_ADDR, INIT_MARKER);
  EEPROM.write(11, currHour);
  EEPROM.write(12, currMinute);
  EEPROM.write(13, currDay);
  EEPROM.write(14, currMonth);
  EEPROM.write(15, currYear);
}
void BackupSystemTime(bool READ_MEMORY){
  if (EEPROM.read(INIT_MARKER_ADDR) != INIT_MARKER) return;//unsigned int backupCurrHour, backupCurrMinute, backupCurrDay, backupCurrMonth, backupCurrYear;
  backupCurrHour = EEPROM.read(11);
  backupCurrMinute = EEPROM.read(12);
  backupCurrDay = EEPROM.read(13);
  backupCurrMonth = EEPROM.read(14);
  EEPROM.get(15, backupCurrYear);// 2 bytes
}
