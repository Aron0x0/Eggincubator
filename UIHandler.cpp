#include "UIHandler.h"
#include "TouchHandler.h"
#include "Config.h"
#include "UI.h"
#include <avr/wdt.h>

void setupData(){
  maxtemp = 37.5;
  mintemp = 35.5;
  maxhumid = 60;
  minhumid = 55;
  solarOnHour = 1;//29
  solarOnMinute = 0;
  solarOffHour = 0;//6
  solarOffMinute = 0;
  timertc.updateTime();
  DATE = String(timertc.month) + "/" + String(timertc.dayofmonth) + "/" + String(timertc.year);
  if(timertc.month >= 13 || timertc.dayofmonth >= 32 ) {
    timertc.setDS1302Time(0, 0, 0, 0, 0, 0, 2025);
  }
  changeHour = timertc.hours;
  if(changeHour >= 13){
    changeHour -= 12;
  }
  changeMinute = timertc.minutes;
  changeMonth = timertc.month;
  changeDay = timertc.dayofmonth;
  changeYear = timertc.year;
}

void UIinit() {
  tft.begin(tft.readID());
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  setupData();
  EggIncubatorFrame();
}

void FrameLoop() {
  p = ts.getPoint();
  pinMode(xm, OUTPUT);
  pinMode(yp, OUTPUT);

  if(currentState != lastState){
    drawCurrentScreen();
    lastState = currentState;
  }

  if (currentState == STATE_MAIN) {
    if(lasttemp != temp){
      // destroyTempHumidDisplay();
      // updateTempHumidDisplay();
      drawGaugeValue(TEMP_X, TEMP_Y, temp, 0, 50, RED, "c", true);
      lasttemp = temp; 
    }
    if(lasthumid != humid){
      drawGaugeValue(HUMID_X, HUMID_Y, humid, 0, 100, BLUE, "%", false);
      lasthumid = humid;
    }
    for(int i=0;i < DEVICE_COUNT;i++){
      if(deviceState[i] != lastdeviceState[i]){
        drawDeviceIndicators();
        lastdeviceState[i] = deviceState[i];
        // Serial.println("/> Update State UI Of Devices/.");
      }
    }

    updateUiClock(CLOCK, LASTCLOCK, 240, 20); // drawString("99/99 AM", 240, 20, 3, WHITE, true);
    // updateUiDevice();
  }

  if(currentState == STATE_SETUP){
    if(currentList != lastList){
      drawCurrentList();
      lastList = currentList;
    }
    if(currentList == LIST1){
      updateUIField(maxtemp, lastmaxtemp, 230, 115);
      updateUIField(mintemp, lastmintemp, 230, 168);
      updateUIField(maxhumid, lastmaxhumid, 250, 221);
      updateUIField(minhumid, lastminhumid, 250, 274);
      isSetupCalibrationFirstRun = false;
      if(currentListVar != lastListVar){
      }
    }
    if(currentList == LIST2){
      drawCurrentDateTimeFrame();
    }
  }
  if(p.z > minpressure && p.z < maxpressure){
    // int x = map(p.y, ts_maxy, ts_miny, 0, 490);
    // int y = map(p.x, ts_minx, ts_maxx, 0, 325); 
    int x = map(p.y, ts_miny, ts_maxy, 0, 490); // screen X
    int y = map(p.x, ts_maxx, ts_minx, 0, 325); 

    printTouchPoint(x, y);
    EachFrameListener(x, y);
  }
}

void drawCurrentList(){
  switch(currentList){
    case LIST1:
      CalibrationFrame();
      break;
    case LIST2:
      TimeAndDateFrame();
      break;
    case LIST3:
      OtherFrame();
      break;
  }
}

void drawCurrentDateTimeFrame(){
  if(currentTimeAndDateState != lastTimeAndDateState){
    switch(currentTimeAndDateState){
      case SHOW_TIME_INFO:
        TimeAndDateFrame();
        lastTimeAndDateState = currentTimeAndDateState;
        break;
      case CHANGE_TIME_INFO:
        changeTimeInfoFrame();
        lastTimeAndDateState = currentTimeAndDateState;
        break;
    }
  }
}

void drawCurrentScreen(){
  switch(currentState){
    case STATE_HOME:
      EggIncubatorFrame();
      break;
    case STATE_MAIN:
      // MainFrame();
      drawNewMainFrame();
      break;
    case STATE_STATS:
      StatFrame();
      break;
    case STATE_SETUP:
      SetupFrame();
      CalibrationFrame();
      break;
    case STATE_MENU:
      MenuFrame();
      break;
    case STATE_TIME:
      TimeAndDateFrame();
      break;
    case STATE_CALIBRATION:
      CalibrationFrame();
      break;
    case STATE_ABOUT:
      AboutFrame();
      break;
    
  }
}



void SetupCalibrationAdjustVariable(int tx, int ty){
  switch(currentListVar){
    case MAXTEMP:
      SetupCalibrationAdjustListener(&maxtemp, tx, ty);
      break;
    case MINTEMP:
      SetupCalibrationAdjustListener(&mintemp, tx, ty);
      break;
    case MAXHUMID:
      SetupCalibrationAdjustListener(&maxhumid, tx, ty);
      break;
    case MINHUMID:
      SetupCalibrationAdjustListener(&minhumid, tx, ty);
      break;
  }
}
