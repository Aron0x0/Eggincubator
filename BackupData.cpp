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
}

void ClearBackupSystemData() {
  for (int i = 0; i <= 6; i++) {
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
}
