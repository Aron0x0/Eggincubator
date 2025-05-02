#include "Config.h"

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(xp, yp, xm, ym, 300);
TSPoint p;

virtuabotixRTC timertc(CLK, DAT, RST);// virtuabotixRTC(DATA, CLK, RST)
DHT dht(IODHT, DHTTYPE);

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

const uint8_t Candling[2] = {7, 14};
const uint8_t UpdateHumid = 19;
const uint16_t TotalOperatingDay = 21;

unsigned long MotorLastTime;
unsigned long MotorDelayStart = 0;
unsigned long MotorActiveStart = 0;
float MotorDelay = 10; 
float MotorActiveDuration = 24;// 60/2.5 = 24 seconds per rotation. // 60/3 = 20
