#include "Config.h"

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(xp, yp, xm, ym, 300);
TSPoint p;

virtuabotixRTC timertc(CLK, DAT, RST);// virtuabotixRTC(DATA, CLK, RST)
DHT dht(IODHT, DHTTYPE);
DHT dhtback(IODHTBACK, DHTTYPE);

ChangeTime currentChangeTime = CHANGE_COUNT;
ChangeTime lastChangeTime = CHANGE_COUNT;

ChangeTimeSolar currentChangeTimeSolar = CHANGE_SOLAR_COUNT;
ChangeTimeSolar lastChangeTimeSolar = CHANGE_SOLAR_COUNT;

TimeAndDate currentTimeAndDateState = SHOW_TIME_INFO;
TimeAndDate lastTimeAndDateState = SHOW_TIME_INFO;

FrameState currentState = STATE_HOME;
FrameState lastState = STATE_HOME;

SetupList currentList = LIST1;
SetupList lastList = LIST1;

bool LASTMOTOR = false;
bool LASTHUMID = false;
bool LASTHEATER = false;
bool LASTSOLAR = false;

bool isBatteryGood = false;

SetupCalibrationList currentListVar = NONE;
SetupCalibrationList lastListVar = NONE;

uint8_t TEXT_COLOR = BLACK;
float maxtemp, lastmaxtemp, mintemp, lastmintemp;
int maxhumid, lastmaxhumid, minhumid, lastminhumid;

float temp, lasttemp;
int humid, lasthumid;

bool isSetupCalibrationFirstRun = true;

String DATE, LASTDATE, CLOCK, LASTCLOCK;
String FORMATDATE, LASTFORMATDATE, TOFORMATDATE, LASTTOFORMATDATE;


bool SystemRunning = false;

// unsigned long DelayDevice[];
// unsigned long DurationDevice[];
bool timeExecution[] = {};
bool HumidBjtSwitchRun = true;

bool lastdeviceState[DEVICE_COUNT] = { false };
bool deviceState[DEVICE_COUNT] = { false }; 
bool devices[DEVICE_COUNT] = { false }; 


unsigned long timeExecutionDelay[DEVICE_COUNT] = {0};
unsigned long functionDelayTracker[DEVICE_COUNT] = {0};

uint8_t EditHour, lastEditHour, EditMinute, lastEditMinute;
uint16_t EditMonth, lastEditMonth, EditDay, lastEditDay, EditYear, LastEditYear;

uint8_t solarOnHour, solarOnMinute, solarOffHour, solarOffMinute;
// uint8_t temp, humid, maxtemp, mintemp, maxhumid, minhumid;
uint16_t currHour, currMinute, currDay, currMonth, currYear;
uint16_t lastHour, lastMinute, lastDay, lastMonth, lastYear;
uint16_t beginHour, beginMinute, beginDay, beginMonth, beginYear;
uint16_t toThisHour, toThisMinute, toThisDay, toThisMonth, toThisYear;
uint16_t changeHour, changeMinute, changeDay, changeMonth, changeYear;
bool changeAmPm;
unsigned int changeSolarOnHour, changeSolarOnMinute, changeSolarOffHour, changeSolarOffMinute;
bool changeSolarOnAmPm, changeSolarOffAmPm;
uint16_t inverterStartHour, inverterStartMinute, inverterEndHour, inverterEndMinute;
unsigned int backupCurrHour, backupCurrMinute, backupCurrDay, backupCurrMonth, backupCurrYear;

const uint8_t Candling[2] = {7, 14};
const uint8_t UpdateHumid = 19;
const uint16_t TotalOperatingDay = 21;

unsigned long MotorLastTime;
unsigned long MotorDelayStart = 0;
unsigned long MotorActiveStart = 0;
float MotorDelay = 7200; 
float MotorActiveDuration = 19;// 60/2.5 = 24 seconds per rotation. // 60/3 = 20
float MotorGoingFront = 9.4;
bool isMotorPositionDefault = true;
bool isLastisMotorPositionDefault = false;

bool isDoorOpen = false;
bool isLastDoorOpen = true;

int beepTarget = 0;
int beepCount = 0;
bool isBeeping = false;
bool buzzerOn = false;

float BatteryVoltage;
int BatteryLevel, lastBatteryLevel;


unsigned long lastToggleTime = 0;
unsigned long beepDuration = 200;   // Time buzzer stays ON
unsigned long beepGap = 300;        // Time between beeps