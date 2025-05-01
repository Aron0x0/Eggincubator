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
  solarOnHour = 20;
  solarOnMinute = 0;
  solarOffHour = 6;
  solarOffMinute = 0;
  timertc.updateTime();
  DATE = String(timertc.month) + "/" + String(timertc.dayofmonth) + "/" + String(timertc.year);
  if(timertc.month >= 13 || timertc.dayofmonth >= 32 ) {
    timertc.setDS1302Time(0, 0, 0, 0, 0, 0, 2025);
    // wdt_enable(WDTO_15MS);
    // while(1);
  }
}

void UIinit() {
  tft.begin(tft.readID());
  tft.setRotation(1);
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
    if(lasttemp != temp || lasthumid != humid){
      destroyTempHumidDisplay();
      updateTempHumidDisplay();
    }

    updateUiClock(CLOCK, LASTCLOCK, 240, 20); // drawString("99/99 AM", 240, 20, 3, WHITE, true);
    updateUiDevice();
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
    int x = map(p.y, ts_maxy, ts_miny, 0, 490);
    int y = map(p.x, ts_minx, ts_maxx, 0, 325); 
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
      MainFrame();
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
