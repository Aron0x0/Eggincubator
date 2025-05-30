#include "Logic.h"
#include "Config.h"
#include "Utils.h"
#include "Logger.h"
#include "UI.h"
#include "BackupData.h"

void LogicInit() {
  dht.begin();
  SetupDeviceIO();
  ConvertTimeToUI();
  Serial.print("/> LOG :: CONVERT :: TIMEUI :: ");Serial.println(CLOCK);
  LogMsg("CONVERT", "TIMEUI", 0, 0);
}

void SystemTimeUpdate(){
  timertc.updateTime();
  currHour = timertc.hours;
  currMinute = timertc.minutes;
  currDay = timertc.dayofmonth;
  currMonth = timertc.month;
  currYear = timertc.year;

  if(currHour != lastHour || currMinute != lastMinute){
    ConvertTimeToUI();
    lastHour = currHour; lastMinute = currMinute;
  }
  if(DATE != LASTDATE){
    if(currentState == STATE_MAIN){
      updateUiDate(DATE, LASTDATE, 400, 35);
    }
    DATE = String(currMonth) + "/" + String(currDay) + "/" + String(currYear);
    LASTDATE = DATE;
  }
  if(DelayFunction(DEVICES, SecondsToMillis(100))){
    DebugDeviceStates();
    // PrintDateNow();
  }

  if(DelayFunction(EXTERNAL_STORAGE, 10000)){
    WriteExternalStorage();
    Serial.println("/! Writing....");
    LogMsg("WRITING", "Getting data from the Sensors.");
  }
}

void RESET_SYSTEM(){
  Serial.println("/* LOG :: RESETING.....");
  LogMsg("RESET", "Resseting Arduino Run Time.", 0,0);
  delay(500);
  digitalWrite(IORESET, HIGH);
  delay(50);
  digitalWrite(IORESET, LOW);
}

void PrintDateNow(){
  Serial.print("/> ");Serial.print(currHour);Serial.print(":");
  Serial.print(currMinute);Serial.print(", ");
  Serial.print(currDay);Serial.print(", ");
  Serial.print(currMonth);Serial.print(", ");
  Serial.print(currYear);Serial.print("\n");
  Serial.print("Time: ");
  Serial.print(timertc.hours);
  Serial.print(":");
  Serial.print(timertc.minutes);
  Serial.print(":");
  Serial.print(timertc.seconds);
  
  Serial.print("  Date: ");
  Serial.print(timertc.dayofmonth);
  Serial.print("/");
  Serial.print(timertc.month);
  Serial.print("/");
  Serial.println(timertc.year);
}


void ConvertTimeToUI(){
  int DisplayHour = currHour;
  String suffix =" AM";
  if(currHour == 0){
    DisplayHour = 12;
  }else if(currHour == 12){
    suffix = " PM";
  }else if(currHour > 12){
    DisplayHour = currHour - 12;
    suffix = " PM";
  }
  String MinuteStr = currMinute < 10 ? "0" + String(currMinute): String(currMinute);
  CLOCK = String(DisplayHour) + ":" + MinuteStr + suffix;
}

String ConvertTimeToUI(int hour, int minute){
  int DisplayHour = hour;
  String suffix =" AM";
  if(hour == 0){
    DisplayHour = 12;
  }else if(hour == 12){
    suffix = " PM";
  }else if(hour > 12){
    DisplayHour = hour - 12;
    suffix = " PM";
  }
  String MinuteStr = minute < 10 ? "0" + String(minute): String(minute);
  return (String(DisplayHour) + ":" + MinuteStr + suffix);
}
bool isAmOrPm(int hour, int minute){
  String suffix ="AM";
  if(hour == 0){
  }else if(hour == 12){
    suffix = "PM";
  }else if(hour > 12){
    suffix = "PM";
  }
  return suffix;
}

void ConvertFormatDateToUI(){
  FORMATDATE = FormatMonth(beginMonth) + " "+String(beginDay)+", "+String(beginYear);
  TOFORMATDATE = FormatMonth(toThisMonth) + " "+String(toThisDay)+", "+String(toThisYear);
  Serial.println(FORMATDATE);
  Serial.println(TOFORMATDATE);
}
String ConvertFormatDateToUI(bool currentDate){
  String FORMATED = FormatMonth(currMonth) + " "+String(currDay)+", "+String(currYear);
  return FORMATED;
}

String ConvertFormatDateToUI(bool currentDate, bool Acronym){
  String FORMATED = FormatMonth(currMonth, true) + " "+String(currDay)+", "+String(currYear);
  return FORMATED;
}

void SetupStartData(){
  beginHour = timertc.hours;
  beginMinute = timertc.minutes;
  beginDay = timertc.dayofmonth;
  beginMonth = timertc.month;
  beginYear = timertc.year;
  PredictedEndDay(beginHour, beginMinute, beginMonth, beginDay, beginYear, TotalOperatingDay);
  LogMsg("INITDATA", "Configuring Time and Date from RTC");
}

void SetupDeviceIO(){
  pinMode(IOHEATER, OUTPUT);
  pinMode(IOHUMID, OUTPUT);
  pinMode(IOSOLAR, OUTPUT);
  pinMode(IOINVERTER, OUTPUT);
  pinMode(LEDINSIDE, OUTPUT);
  pinMode(IOMOTOR, OUTPUT);
  pinMode(IORESET, OUTPUT);
  pinMode(IOHUMIDAC, OUTPUT);
  pinMode(IODOOR, INPUT);
  digitalWrite(IORESET, LOW);
  digitalWrite(LEDINSIDE, HIGH);
  digitalWrite(IOHUMIDAC, LOW);
  digitalWrite(IOSOLAR, HIGH);
  digitalWrite(IOINVERTER, HIGH);
  digitalWrite(IOMOTOR, HIGH);
  digitalWrite(IOHEATER, HIGH);
  digitalWrite(IOHUMIDAC, HIGH);
  LogMsg("INITIO", "Configuring Analog and Didigtal IO (INPUT OUTPUT), (LOW, HIGH)");
}

void DebugDeviceStates() {
  Serial.println("/> Debugging..........................BEGIN");
  const char* deviceNames[DEVICE_COUNT] = {"MOTOR", "HUMID", "HEATER", "SOLAR"};
  const uint8_t ioPins[DEVICE_COUNT] = {IOMOTOR, IOHUMID, IOHEATER, IOSOLAR};

  for (int i = 0; i < DEVICE_COUNT; i++) {
    bool currentIOState = digitalRead(ioPins[i]);
    bool internalState = deviceState[i];

    Serial.print(deviceNames[i]);
    Serial.print(" | Expected: ");
    Serial.print(internalState ? "ON" : "OFF");
    Serial.print(" | Actual: ");
    Serial.print(currentIOState ? "ON" : "OFF");

    if (currentIOState != internalState) {
      Serial.println(" Mismatch!");
      LogMsg("RELAY", ("Mismatch from IO -> " + String(deviceNames[i]) + " -> (Expected: "+ internalState + ", Actual: " + currentIOState + ")"));
    } else {
      Serial.println(" Okey!");
      LogMsg("RELAY", ("Good from IO -> "+ String(deviceNames[i]) + " -> (Expected: " + internalState + ", Actual: " + currentIOState +")"));
    }
  }
  Serial.println("/> Debugging..........................END");
}

void UpdateDeviceState(){
  // digitalWrite(IOSOLAR, deviceState[SOLAR] ? LOW : HIGH);
  digitalWrite(IOHEATER, deviceState[HEATER] ? LOW : HIGH);
  digitalWrite(IOMOTOR, deviceState[MOTOR] ? LOW : HIGH);
  digitalWrite(IOHUMIDAC, deviceState[HUMID] ? LOW : HIGH);
  digitalWrite(IOINVERTER, deviceState[INVERTER] ? LOW : HIGH);
}

void SensorDevice(){
  if(SystemRunning){
    if(!isnan(temp) && !isnan(humid)){
      if(ctof(temp) > ctof(maxtemp - 1.5)){
        deviceState[HEATER] = false;
      }else if(ctof(temp) < ctof(mintemp)){
        deviceState[HEATER] = true;
      }
      if(humid > maxhumid){
        deviceState[HUMID] = false;
        if(!HumidBjtSwitchRun){
          humidSwitchOff();
          HumidBjtSwitchRun = true; 
        }
      }else if(humid < minhumid){
        deviceState[HUMID] = true;
        if(HumidBjtSwitchRun){
          humidSwitchOn();
          HumidBjtSwitchRun = false;
        }
      }
    }else{
      temp = 3; humid = 3;//3 = for Lost Connection on DHT22
      Log("TMP01", 'e');
    }
    if(BatteryLevel != lastBatteryLevel){
      LogMsg("BATTERY", String(BatteryLevel));
    }
    if(BatteryLevel == 100){
      Log("BAT03",'a');
    }else if(BatteryLevel < 10){
      Log("BAT01", 'a');
    }else if(BatteryLevel < 0){
      Log("BAT02", 'a');
    }
    // if(BatteryLevel <= 100 && BatteryLevel >= 10){
    //   Serial.println("Good Battery");
    //   if(isTimeInRange(currHour, currMinute, solarOnHour, solarOnMinute, solarOffHour, solarOffMinute)){
        // if(!deviceState[SOLAR]){
        //   LogMsg("SOLAR", "Switing Power to Inverter");
        // }
        // deviceState[SOLAR] = true;
        // Serial.println("/> Solar Mode Onn!!");
      // } else {
        // if(deviceState[SOLAR]){
        //   LogMsg("SOLAR", "Switching Back To Ac Outlet");
        // }
    //     deviceState[SOLAR] = false;
    //   }
    // } else {
      // if(DelayFunction(BATTERY, 60000)){
      //   Log("BAT01", 'a');
      //   Serial.println("Bad Battery!");
      // }
      // if(deviceState[SOLAR]){
      //   LogMsg("SOLAR", "Switching Back To Ac Outlet");
      // }
    //   deviceState[SOLAR] = false;
    // }
    if(isTimeInRange(currHour, currMinute, solarOnHour, solarOnMinute, solarOffHour, solarOffMinute)){
      deviceState[SOLAR] = true; 
      digitalWrite(IOHEATER, HIGH);
      digitalWrite(IOMOTOR, HIGH);
      digitalWrite(IOHUMIDAC, HIGH);
      digitalWrite(INVERTER, LOW);
      delay(1000);
      digitalWrite(IOSOLAR, LOW);
      delay(1000);
    } else {
      deviceState[SOLAR] = false;
      digitalWrite(IOSOLAR, HIGH);
    }
    if (isTimeInRange(currHour, currMinute, inverterStartHour, inverterStartMinute, inverterEndHour, inverterEndMinute)) {
      deviceState[INVERTER] = true;
    } else {
      deviceState[INVERTER] = false;
    }
    MotorRotateDefault(); 
    // if (!isDoorOpen) {
    //   if(isMotorPositionDefault){
    //     MotorRotateDefault(); 
    //   }
    //   else if (!isMotorPositionDefault) {
    //     LogMsg("DOOR", "The Door is Closed");
    //     Serial.println("Door is Closed");
    //     // digitalWrite(LEDINSIDE, HIGH);
    //     isMotorPositionDefault = true;
    //     MotorRotateGoingFront();
    //   }
    // } 
    // else if (isDoorOpen && isMotorPositionDefault) {
    //   MotorRotateGoingFront();
    //   Serial.println("Door is Opened");
    //   // digitalWrite(LEDINSIDE, LOW);
    //   LogMsg("DOOR", "The Door is Open.");
    //   isMotorPositionDefault = false;
    // }
  }
}

void MotorRotateDefault() {
  if (!deviceState[MOTOR] && (millis() - MotorDelayStart) >= SecondsToMillis(MotorDelay)) {
    deviceState[MOTOR] = true;
    MotorActiveStart = millis();
    LogMsg("MOTOR", "Turning On Synchhronous");
  }
  if (deviceState[MOTOR] && (millis() - MotorActiveStart) >= SecondsToMillis(MotorActiveDuration)) {
    deviceState[MOTOR] = false;
    MotorDelayStart = millis();
    LogMsg("MOTOR", "Turning Off Synchhronous");
  }
}

void MotorRotateGoingFront() {
  if (isDoorOpen && !deviceState[MOTOR] && (millis() - MotorDelayStart) >= 500) {  // Adjust delay if needed
    deviceState[MOTOR] = true;
    MotorActiveStart = millis();
    LogMsg("MOTOR", "Turning Toward the door.");
  }
  if (isDoorOpen && deviceState[MOTOR] && (millis() - MotorActiveStart) >= SecondsToMillis(MotorGoingFront)) {
    deviceState[MOTOR] = false;
    MotorDelayStart = millis();
    LogMsg("MOTOR", "Syncrhonous Not on default Position");
  }
}

bool DelayFunction(uint8_t deviceIndex, unsigned long delayInterval) {
  unsigned long now = millis();
  if ((now - functionDelayTracker[deviceIndex]) >= delayInterval) {
    functionDelayTracker[deviceIndex] = now;
    return true;
  }
  return false;
}

void PredictedEndDay(uint8_t hour, uint8_t minute, uint16_t month, uint8_t day, uint16_t year, uint8_t addDays){
  while(addDays > 0) {
    int endOfMonth = dayInMonth(month, year);
    if((day + addDays) > endOfMonth) {
      addDays -= (endOfMonth - day + 1);//1 is for adding day if begin is now not tommorrow
      day = 1;
      month++;
      if(month > 12) {
        month = 1;
        year++;
      }
    }else{
      day += addDays;
      addDays = 0;
    }
  }
  toThisHour = hour;
  toThisMinute = minute;
  toThisDay = day;
  toThisMonth = month;
  toThisYear = year;
}

bool isTimeInRange(uint8_t hour, uint8_t minute, uint8_t onHour, uint8_t onMinute, uint8_t offHour, uint8_t offMinute) {
  int now = hour * 60 + minute;
  int on = onHour * 60 + onMinute;
  int off = offHour * 60 + offMinute;

  if (on == off) return false; // same start & end — invalid

  if (on < off) {
    return now >= on && now < off;
  } else {
    return now >= on || now < off; // range spans over midnight
  }
}

bool isLeafYear(uint16_t year){
  return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int dayInMonth(uint8_t month, uint16_t year) {
  if(month == 2){
    return isLeafYear(year)? 29: 28;
  }else if(month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
  }else{
    return 31;
  }
}

void humidSwitchOff(){
  // Serial.println("/? Turn OFF Humid!");  
  uint8_t processdelay = 80;
  digitalWrite(IOHUMID, HIGH);
  delay(processdelay);
  digitalWrite(IOHUMID, LOW);
  delay(processdelay);
  digitalWrite(IOHUMID, HIGH);
  delay(processdelay);
  digitalWrite(IOHUMID, LOW);
  // delay(processdelay);
}

void humidSwitchOn(){
  // Serial.println("/? Turn ON Humid!");
  uint8_t processdelay = 80;
  digitalWrite(IOHUMID, HIGH);
  delay(processdelay);
  digitalWrite(IOHUMID, LOW);
  // delay(processdelay);
}


void EnergizeSolarTime() {
  int onMinutes = solarOnHour * 60 + solarOnMinute;

  // Inverter ON 5 minutes before solar ON
  int start = onMinutes - 5;
  if (start < 0) start += 1440; // wrap around midnight

  inverterStartHour = start / 60;
  inverterStartMinute = start % 60;

  // Inverter OFF 5 minutes after solar ON
  int end = onMinutes + 5;
  if (end >= 1440) end -= 1440;

  inverterEndHour = end / 60;
  inverterEndMinute = end % 60;

  Serial.print("Inverter Active From: ");
  Serial.print(inverterStartHour); Serial.print(":");
  Serial.println(inverterStartMinute);
  Serial.print("To: ");
  Serial.print(inverterEndHour); Serial.print(":");
  Serial.println(inverterEndMinute);
}

float readRawVoltage(int analogPin){
  int raw = analogRead(analogPin);
  return raw;
}

float readBatteryVoltage(int analogPin) {
  int raw = analogRead(analogPin);
  float voltage = (raw / 1023.0) * 5.0;
  float batteryVoltage = voltage * ((10.0 + 3.3) / 3.3); // voltage divider formula
  return batteryVoltage;
}

int getBatteryPercentage(float voltage) {
  float maxVoltage = 13.6;
  float minVoltage = 12.8;
  int percentage = (int)(((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100.0);
  return constrain(percentage, 0, 100);
}

// Call this to trigger beeping n times
void beep(int count) {
  beepTarget = count;
  beepCount = 0;
  isBeeping = true;
  buzzerOn = false;
  lastToggleTime = millis();
}

void updateBuzzer() {
  if (!isBeeping) return;

  unsigned long now = millis();

  if (!buzzerOn && beepCount < beepTarget && (now - lastToggleTime >= beepGap)) {
    tone(IOBUZZER, 1000);  // Start tone
    buzzerOn = true;
    lastToggleTime = now;
  }

  if (buzzerOn && (now - lastToggleTime >= beepDuration)) {
    noTone(IOBUZZER);      // Stop tone
    buzzerOn = false;
    lastToggleTime = now;
    beepCount++;
  }

  if (beepCount >= beepTarget) {
    isBeeping = false;
    noTone(IOBUZZER);  // Make sure it's off
  }
}

String FormatMonth(int month){
  switch(month){
    case 1:
      return "January";
      break;
    case 2:
      return "February";
      break;
    case 3:
      return "March";
      break;
    case 4:
      return "April";
      break;
    case 5:
      return "May";
      break;
    case 6:
      return "June";
      break;
    case 7:
      return "July";
      break;
    case 8:
      return "August";
      break;
    case 9:
      return "September";
      break;
    case 10:
      return "October";
      break;
    case 11:
      return "November";
      break;
    case 12:
      return "December";
      break;
  }
}

String FormatMonth(int month, bool Acronym){
  switch(month){
    case 1:
      return "Jan";
      break;
    case 2:
      return "Feb";
      break;
    case 3:
      return "March";
      break;
    case 4:
      return "Apr";
      break;
    case 5:
      return "May";
      break;
    case 6:
      return "June";
      break;
    case 7:
      return "July";
      break;
    case 8:
      return "Aug";
      break;
    case 9:
      return "Sep";
      break;
    case 10:
      return "Oct";

      break;
    case 11:
      return "Nov";
      break;
    case 12:
      return "Dec";
      break;
  }
}
void checkTimeRtc(){
  // if(timertc.hours == 0 && timertc.minutes == 1 && timertc.month == 1 && timertc.dayofmonth == 1 && timertc.year == 2000){
  //   BackupSystemTime(true);
  //   timertc.setDS1302Time(0, backupCurrMinute, backupCurrHour, 0, backupCurrDay, backupCurrMonth, backupCurrYear);
  // }
  if(timertc.dayofmonth == 1 && timertc.month == 1 && timertc.year == 2000){
    timertc.setDS1302Time(0, 30, 6, 0, 16, 5, 2025);
  }
}