#pragma once

#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
#include <DHT.h>
#include <virtuabotixRTC.h>

#define CLK 22
#define DAT 24
#define RST 26
// #define CLK 22
// #define DAT 23
// #define RST 24


#define IOSOLAR 31
#define IOHUMIDAC 33
#define LEDINSIDE 35
#define IOINVERTER 37
#define IOHEATER 39
#define IOMOTOR 41 // 29
#define IOHUMID 43
#define IOBUZZER 42
#define IODOOR 45
#define IODHT 46 // 49
#define IODHTBACK 44 // 49
#define IORESET 48
#define IOBATTERY A15
#define DHTTYPE DHT22

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

#define yp A1
#define xm A2
#define ym 7
#define xp 6

#define ts_minx 187
#define ts_maxx 947
#define ts_miny 179
#define ts_maxy 968

#define minpressure 10
#define maxpressure 1000

#define RADIUS 90
#define TEMP_X 120
#define TEMP_Y 160
#define HUMID_X 360
#define HUMID_Y 160

enum FrameState {
  STATE_HOME,
  STATE_MAIN,
  STATE_MENU,
  STATE_SETUP,
  STATE_ABOUT,
  STATE_TIME,
  STATE_CALIBRATION,
  STATE_STATS
};

enum SetupList {
  LIST1,
  LIST2,
  LIST3
};

enum TimeAndDate {
  SHOW_TIME_INFO,
  CHANGE_TIME_INFO,
  CHANGE_TIME_SOLAR
};

enum ChangeTime {
  CHANGE_MINUTE,
  CHANGE_HOUR,
  CHANGE_AMPM,
  CHANGE_DAY,
  CHANGE_MONTH,
  CHANGE_YEAR,
  CHANGE_COUNT
};

enum ChangeTimeSolar {
  CHANGE_SOLAR_ON_HOUR,
  CHANGE_SOLAR_ON_MINUTE,
  CHANGE_SOLAR_ON_AMPM,
  CHAGNE_SOLAR_OFF_HOUR,
  CHANGE_SOLAR_OFF_MINUTE,
  CHANGE_SOLAR_OFF_AMPM,
  CHANGE_SOLAR_COUNT
};

enum SetupCalibrationList {
  MAXTEMP,
  MINTEMP,
  MAXHUMID,
  MINHUMID,
  NONE
};

enum DeviceState {
  MOTOR,
  HUMID,
  HEATER,
  SOLAR,
  INVERTER, 
  DEVICE_COUNT
};


enum Debug {
  DEVICES,
  EXTERNAL_STORAGE,
  DOOR,
  BATTERY,
  BATTERYLEVEL,
  DEVICES_COUNT
};

struct TimeExecution {
  String name;
  unsigned long DelayTime;
  unsigned long DurationTime;
  unsigned long startTime;
  bool active;
};

extern bool isBatteryGood;
extern float BatteryVoltage;
extern int BatteryLevel, lastBatteryLevel;
extern bool LASTMOTOR, LASTHUMID, LASTHEATER, LASTSOLAR;
extern unsigned long MotorDelayStart;
extern unsigned long MotorActiveStart;
extern unsigned long MotorLastTime;
extern float MotorDelay;
extern float MotorActiveDuration;

extern MCUFRIEND_kbv tft;
extern TouchScreen ts;
extern TSPoint p;
extern virtuabotixRTC timertc;//CLock, IO, CeR_ST
extern DHT dht, dhtback;

extern bool isBeeping, buzzerOn;
extern int beepTarget, beepCount;
extern unsigned long beepGap, beepDuration, lastToggleTime;
extern ChangeTimeSolar currentChangeTimeSolar, lastChangeTimeSolar;
extern ChangeTime currentChangeTime, lastChangeTime;
extern TimeAndDate currentTimeAndDateState, lastTimeAndDateState;
extern FrameState currentState, lastState;
extern SetupList currentList, lastList;
extern SetupCalibrationList currentListVar, lastListVar;
extern uint8_t TEXT_COLOR;
extern float maxtemp, lastmaxtemp, mintemp, lastmintemp;
extern int maxhumid, lastmaxhumid, minhumid, lastminhumid;
extern float temp, lasttemp;
extern int humid, lasthumid;
extern bool isSetupCalibrationFirstRun;
extern String DATE, LASTDATE, CLOCK, LASTCLOCK;
extern String FORMATDATE, LASTFORMATDATE, TOFORMATDATE, LASTTOFORMATDATE;
extern uint16_t changeHour, changeMinute, changeDay, changeMonth, changeYear;
extern bool changeAmPm;
extern unsigned int changeSolarOnHour, changeSolarOnMinute, changeSolarOffHour, changeSolarOffMinute;
extern bool changeSolarOnAmPm, changeSolarOffAmPm;
extern uint16_t inverterStartHour, inverterStartMinute, inverterEndHour, inverterEndMinute;
extern bool HumidBjtSwitchRun;
extern bool SystemRunning;
extern bool timeExecution[];
extern bool deviceState[DEVICE_COUNT];
extern bool lastdeviceState[DEVICE_COUNT];
extern bool devices[DEVICE_COUNT];
extern bool isDoorOpen, isLastDoorOpen;
extern bool isMotorPositionDefault, isLastMotorPositionDefault;
extern float MotorGoingFront;

extern unsigned long timeExecutionDelay[DEVICE_COUNT];
extern unsigned long functionDelayTracker[DEVICE_COUNT];

extern uint8_t solarOnHour, solarOnMinute, solarOffHour, solarOffMinute;
// extern uint8_t temp, humid, maxtemp, mintemp, maxhumid, minhumid;
extern uint16_t currHour, currMinute, currDay, currMonth, currYear;
extern uint16_t lastHour, lastMinute, lastDay, lastMonth, lastYear;
extern uint16_t beginHour, beginMinute, beginDay, beginMonth, beginYear;
extern uint16_t toThisHour, toThisMinute, toThisDay, toThisMonth, toThisYear;
extern unsigned int backupCurrHour, backupCurrMinute, backupCurrDay, backupCurrMonth, backupCurrYear;


extern const uint8_t Candling[2];
extern const uint8_t UpdateHumid;
extern const uint16_t TotalOperatingDay;
