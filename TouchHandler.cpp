#include "TouchHandler.h"
#include "UIHandler.h"
#include "Config.h"
#include "UI.h"
#include "Logic.h"
#include "BackupData.h"
#include "Utils.h"
#include "Logger.h"

void EachFrameListener(int tx, int ty){
  switch(currentState){
    case STATE_HOME:
      EggIncubatorListener(tx, ty);
      LogMsg("BUTTON","EggIncubator Frame", tx, ty);
      break;
    case STATE_MAIN:
      LogMsg("BUTTON","MainFrame Frame", tx, ty);
      MainFrameListener(tx, ty);
      break;
    case STATE_SETUP:
      SetupListener(tx, ty);
      LogMsg("BUTTON","Setup Frame", tx, ty);
      if(currentList == LIST1){
        SetupCalibrationListListener(tx, ty);
        SetupCalibrationAdjustVariable(tx, ty);
        LogMsg("BUTTON","Calibration Frame", tx, ty);
      }
      if(currentList == LIST2){
        TimeAndDateSwitch(tx, ty);
        LogMsg("BUTTON","TimeAndDate Frame", tx, ty);
      }
      if(currentList == LIST3){
        OtherListener(tx, ty);
        LogMsg("BUTTON","Other Frame", tx, ty);
      }
      break;
    case STATE_MENU:
      MenuListener(tx, ty);
      LogMsg("BUTTON","Menu Frame", tx, ty);
      break;
    case STATE_TIME:
      TimeAndDateListener(tx, ty);
      LogMsg("BUTTON","TimeAndDate Frame", tx, ty);
      break;
    case STATE_CALIBRATION:
      CalibrationListener(tx, ty);
      LogMsg("BUTTON","Calibration Frame", tx, ty);
      break;
    case STATE_ABOUT:
      AboutListener(tx, ty);
      LogMsg("BUTTON","About Frame", tx, ty);
      break;
    case STATE_STATS:
      StatListener(tx, ty);
      LogMsg("BUTTON","Stats Frame", tx, ty);
      break;
  }
}

void TimeAndDateSwitch(int tx, int ty){
  switch(currentTimeAndDateState){
    case SHOW_TIME_INFO:
      LogMsg("BUTTON","Show Time Info Frame", tx, ty);
      showTimeInfoListener(tx, ty);
      break;
    case CHANGE_TIME_INFO:
      changeTimeInfoListener(tx, ty);
      LogMsg("BUTTON","Change Time Info Frame", tx, ty);
      break;
    case CHANGE_TIME_SOLAR:
      changeTimeSolarListener(tx, ty);
      LogMsg("BUTTON","Change Time Solar On And Off Frame", tx, ty);
      break;
  }
}


void EggIncubatorListener(int tx, int ty){
  LogMsg("BUTTON", "Egg Incubator Being Draw.");
  if(isTouchInsideCircle(240, 160, 75, tx, ty)){
    LogMsg("BUTTON", "Beginning Incubation");
    Serial.println("/> Action :: Clicked :: START BUTTON");
    SetupStartData();
    ConvertFormatDateToUI();
    SystemRunning = true;
    MotorDelayStart = millis();
    currentState = STATE_MAIN;
    BackupSystemData();
    EnergizeSolarTime();
    // delay(1000);
  }
  if(isTouchInsideCircle(379, 215, 55, tx, ty)){
    LogMsg("BUTTON", "About Button.");
    Serial.println("/> Action :: Clicked :: ABOUT");
    // RESET_SYSTEM();
    currentState = STATE_ABOUT;
  }
  if(isTouchInsideCircle(81, 235, 75, tx, ty)){
    LogMsg("BUTTON", "Configure Max and Min Temp Humid");
    Serial.println("/> Action :: Clicked :: SETUP");
    currentList = LIST1;
    currentState = STATE_SETUP;
  }
}

void MainFrameListener(int tx, int ty){
  if(isTouchInsideCircle(240, 280, 40, tx, ty)){
    LogMsg("BUTTON", "Showing Status Info");
    currentState = STATE_STATS;
  }
}
void SetupListener(int tx, int ty){
  if(isTouchInsideRectangle(428, 0, 52, 56, tx, ty)){
    LogMsg("BUTTON", "Setup Exit Button.");
    Serial.println("/> Action :: Clicked :: Setup Exit Button");
    currentState = STATE_HOME;
    isSetupCalibrationFirstRun = true;
  }
  if(isTouchInsideRectangle(22, 49, 127, 39, tx, ty)){
    LogMsg("BUTTON", "Calibration Button.");
    Serial.println("/> Action :: Clicked :: Calibration Button");
    // currentTimeAndDateState = SHOW_TIME_INFO;
    currentList = LIST1;
  }
  if(isTouchInsideRectangle(163, 49, 154, 39, tx, ty)){
    LogMsg("BUTTON", "Time & Date Button.");
    Serial.println("/> Action :: Clicked :: Time & Date Button");
    isSetupCalibrationFirstRun = true;
    currentTimeAndDateState = SHOW_TIME_INFO;
    lastTimeAndDateState = SHOW_TIME_INFO;
    currentList = LIST2;
  }
  if(isTouchInsideRectangle(331, 49 , 127, 39, tx, ty)){
    LogMsg("BUTTON", "Other's Button.");
    Serial.println("/> Action :: Clicked :: Other's Button");
    isSetupCalibrationFirstRun = true;
    currentList = LIST3;
  }
}
void AboutListener(int tx, int ty){
  if(isTouchInsideRectangle(428, 0, 52, 56, tx, ty)){
    LogMsg("BUTTON", "About Exit Button.");
    Serial.println("/> Action :: Clicked :: About Exit Button");
    currentState = STATE_HOME;
  }
  if(isTouchInsideCircle(447, 292, 20, tx, ty)){
    currentState = STATE_HOME;
  }
}
void MenuListener(int tx, int ty){
  if(isTouchInsideRectangle(428, 0, 52, 56, tx, ty)){
    LogMsg("BUTTON", "Menu Exit Button.");
    Serial.println("/> Action :: Clicked :: Menu Exit Button");
    currentState = STATE_HOME;
  }
}
void TimeAndDateListener(int tx, int ty){
  if(isTouchInsideRectangle(428, 0, 52, 56, tx, ty)){
    LogMsg("BUTTON", "TimeDate Exit Button.");
    Serial.println("/> Action :: Clicked :: TimeDate Exit Button");
    currentState = STATE_HOME;
  }
}
void CalibrationListener(int tx, int ty){
  if(isTouchInsideRectangle(428, 0, 52, 56, tx, ty)){
    LogMsg("BUTTON", "Calibration Exit Button.");
    Serial.println("/> Action :: Clicked :: Calibration Exit Button");
    currentState = STATE_HOME;
  }
}

void StatListener(int tx, int ty){
  if(isTouchInsideRectangle(426, 13, 40, 40, tx, ty)){
    LogMsg("BUTTON", "Stats Exit Button.");
    Serial.println("/> Action :: Clicked :: Stats Exit Button");
    currentState = STATE_MAIN;
  }
  if(isTouchInsideCircle(99, 235, 37, tx, ty)){
    LogMsg("BUTTON", "Turn On Led@");
    if(digitalRead(LEDINSIDE)){
      LogMsg("BUTTON","Turning On LEDINSIDE", tx, ty);
      drawCircleWithFrame(99, 235, 37, GREEN, "LED", BLACK, 2, BLACK, 80);
      digitalWrite(LEDINSIDE, LOW);
    }else if(!digitalRead(LEDINSIDE)){
      LogMsg("BUTTON","Turning Off LEDINSIDE", tx, ty);
      drawCircleWithFrame(99, 235, 37, RED, "LED", BLACK, 2, BLACK, 80);
      digitalWrite(LEDINSIDE, HIGH);
    }
    // delay(800);
  }
  if(isTouchInsideCircle(396, 235, 37, tx, ty)){
    LogMsg("BUTTON", "Reset Button.");
    Serial.println("/> ACTION :: CLICKED :: RESET");
    SystemRunning = false;
    beginHour = 0;
    beginMinute = 0;
    beginDay = 0;
    beginMonth = 0;
    beginYear = 0;
    ClearBackupSystemData();
    delay(50);
    RESET_SYSTEM();
  }
}

void SetupCalibrationListListener(int tx, int ty){// 101, 154, 207, 260 (x = 170) (170, 45)
  if(isTouchInsideRectangle(170, 101, 170, 45, tx, ty)){
    destroyAndDrawValues(String(maxtemp), String(lastmaxtemp), 230, 115, 3, WHITE, GREEN);
    destroyAndDrawValues(String(mintemp), String(lastmintemp), 230, 168, 3, WHITE, BLACK);
    destroyAndDrawValues(String(maxhumid), String(lastmaxhumid), 250, 221, 3, WHITE, BLACK);
    destroyAndDrawValues(String(minhumid), String(lastminhumid), 250, 274, 3, WHITE, BLACK);

    LogMsg("BUTTON", "Increase MaxTemp.");
    Serial.print(" /> CalibraitonAdjustVariable :: Clicked :: MAXTEMP");
    currentListVar = MAXTEMP;
  }
  if(isTouchInsideRectangle(170, 154, 170, 45, tx, ty)){
    destroyAndDrawValues(String(mintemp), String(lastmintemp), 230, 168, 3, WHITE, GREEN);
    destroyAndDrawValues(String(maxtemp), String(lastmaxtemp), 230, 115, 3, WHITE, BLACK);
    destroyAndDrawValues(String(maxhumid), String(lastmaxhumid), 250, 221, 3, WHITE, BLACK);
    destroyAndDrawValues(String(minhumid), String(lastminhumid), 250, 274, 3, WHITE, BLACK);
    Serial.print(" /> CalibraitonAdjustVariable :: Clicked :: MINTEMP");
    currentListVar = MINTEMP;
  }
  if(isTouchInsideRectangle(170, 207, 170, 45, tx, ty)){
    destroyAndDrawValues(String(maxhumid), String(lastmaxhumid), 250, 221, 3, WHITE, GREEN);
    destroyAndDrawValues(String(maxtemp), String(lastmaxtemp), 230, 115, 3, WHITE, BLACK);
    destroyAndDrawValues(String(mintemp), String(lastmintemp), 230, 168, 3, WHITE, BLACK);
    destroyAndDrawValues(String(minhumid), String(lastminhumid), 250, 274, 3, WHITE, BLACK);

    LogMsg("BUTTON", "Increase MaxHumid Button.");
    Serial.print(" /> CalibraitonAdjustVariable :: Clicked :: MAXHUMID");
    currentListVar = MAXHUMID;
  }
  if(isTouchInsideRectangle(170, 260, 170, 45, tx, ty)){
    destroyAndDrawValues(String(minhumid), String(lastminhumid), 250, 274, 3, WHITE, GREEN);
    destroyAndDrawValues(String(maxtemp), String(lastmaxtemp), 230, 115, 3, WHITE, BLACK);
    destroyAndDrawValues(String(mintemp), String(lastmintemp), 230, 168, 3, WHITE, BLACK);
    destroyAndDrawValues(String(maxhumid), String(lastmaxhumid), 250, 221, 3, WHITE, BLACK);

    LogMsg("BUTTON", "Increase MinHumid Button.");
    Serial.print(" /> CalibraitonAdjustVariable :: Clicked :: MINHUMID");
    currentListVar = MINHUMID;
  }
}

void SetupCalibrationAdjustListener(int* var, int tx, int ty){//x = 420 and y = 150, 250 (r = 40)
  if(isTouchInsideCircle(420, 150, 40, tx, ty)){
    *var+=1;
    LogMsg("BUTTON", "ADD Button -> "+String(*var));
    Serial.print("/> CalibrationAdjustListener :: Clicked :: ADD :: ");Serial.println(*var);
  }
  if(isTouchInsideCircle(420, 250, 40, tx, ty)){
    *var-=1;
    LogMsg("BUTTON", "MINUS Button -> "+String(*var));
    Serial.print("/> CalibrationAdjustListener :: Clicked :: MINUS :: ");Serial.println(*var);
  }
}
void SetupCalibrationAdjustListener(float* var, int tx, int ty){//x = 420 and y = 150, 250 (r = 40)
  if(isTouchInsideCircle(420, 150, 40, tx, ty)){
    *var+=.1;
    LogMsg("BUTTON", "ADD Button -> "+String(*var));
    Serial.print("/> CalibrationAdjustListener :: Clicked :: ADD :: ");Serial.println(*var);
  }
  if(isTouchInsideCircle(420, 250, 40, tx, ty)){
    *var-=.1;
    LogMsg("BUTTON", "MINUS Button -> "+String(*var));
    Serial.print("/> CalibrationAdjustListener :: Clicked :: MINUS :: ");Serial.println(*var);
  }
}

void showTimeInfoListener(int tx, int ty){
  if(isTouchInsideRectangle(300, 160, 158, 45, tx, ty)){
    Serial.println("/> ACTION :: CHANGETIME :: CLICKED ");
    LogMsg("BUTTON", "Change Time");changeHour, changeMinute, changeDay, changeMonth, changeYear;
    changeHour = 6;
    changeMinute = currMinute;
    changeDay = currDay;
    changeMonth = currMonth;
    changeYear = currYear;
    LogMsg("BUTTON", "CHANGING TIME ");
    currentTimeAndDateState = CHANGE_TIME_INFO;
  }
  if(isTouchInsideRectangle(299, 239, 158, 45, tx, ty)){
    Serial.println("/> ACTION :: CHANGESOLARTIME :: CLICKED");
    LogMsg("BUTTON", "Change Solar Time On and Off");
    // changeSolarOnHour = (isAmOrPm(currHour, currMinute)? currHour - 12 : currHour);
    changeSolarOnHour = 6;
    changeSolarOnMinute = currMinute;
    // changeSolarOffHour = (isAmOrPm(currHour, currMinute)? currHour - 12 : currHour);
    changeSolarOffHour = 6;
    changeSolarOffMinute = currMinute;
    currentTimeAndDateState = CHANGE_TIME_SOLAR;
  } 
}
void changeTimeInfoListener(int tx, int ty){
  if(isTouchInsideCircle(416, 204, 50, tx, ty)){
    Serial.println("/> ACTION :: SAVETIME :: CLICKED ");
    timertc.setDS1302Time(0, changeMinute, (changeAmPm? changeHour: (changeHour+12)), 0, changeDay, changeMonth, changeYear);
    // timertc.setDS1302Time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t dayofweek, uint8_t dayofmonth, uint8_t month, int year)
    Serial.println("/? Save.... Time....");
    currentTimeAndDateState = SHOW_TIME_INFO;
    // lastTimeAndDateState = SHOW_TIME_INFO;
    LogMsg("BUTTON","Saving Time For RTC", tx, ty);
  }
  if(isTouchInsideRectangle(47, 148, 51, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), GREEN, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM" : "PM"), BLACK, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
    currentChangeTime = CHANGE_HOUR;
  }
  if(isTouchInsideRectangle(114, 148, 51, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), GREEN, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM":"PM"), BLACK, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
    currentChangeTime = CHANGE_MINUTE;
  }
  if(isTouchInsideRectangle(181, 148, 51, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm? "AM": "PM"), GREEN, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
    currentChangeTime = CHANGE_AMPM;
  }
  if(isTouchInsideRectangle(22, 242, 51, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM":"PM"), BLACK, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), GREEN, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
    currentChangeTime = CHANGE_MONTH;
  }
  if(isTouchInsideRectangle(89, 242, 51, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM":"PM"), BLACK, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), GREEN, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
    currentChangeTime = CHANGE_DAY;
  }
  if(isTouchInsideRectangle(156, 242, 100, 46, tx, ty)){
    drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
    drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
    drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM":"PM"), BLACK, 3);
    drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
    drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
    drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), GREEN, 3);
    currentChangeTime = CHANGE_YEAR;
  }

  if(isTouchInsideCircle(320, 165, 40, tx, ty)){
    if(currentChangeTime == CHANGE_HOUR && changeHour >= 0 && changeHour <= 11){
      changeTimeInfoVariableListener(true);
    }
    if(currentChangeTime == CHANGE_MINUTE && changeMinute >= 0 && changeMinute <= 58){
      changeTimeInfoVariableListener(true);
    }
    if(currentChangeTime == CHANGE_AMPM){
      changeTimeInfoVariableListener(true);
    }
    if(currentChangeTime == CHANGE_MONTH && changeMonth >= 0 && changeMonth <= 11){
      changeTimeInfoVariableListener(true);
    }
    if(currentChangeTime == CHANGE_DAY && changeDay >= 0 && changeDay <= dayInMonth(changeMonth, changeYear)){
      changeTimeInfoVariableListener(true);
    }
    if(currentChangeTime == CHANGE_YEAR && changeYear >= 1990 && changeYear <= 2100){
      changeTimeInfoVariableListener(true);
    }
  }
  if(isTouchInsideCircle(320, 253, 40, tx, ty)){
    if(currentChangeTime == CHANGE_HOUR && changeHour >= 0 && changeHour <= 12){
      changeTimeInfoVariableListener(false);
    }
    if(currentChangeTime == CHANGE_MINUTE && changeMinute >= 0 && changeMinute <= 59){
      changeTimeInfoVariableListener(false);
    }
    if(currentChangeTime == CHANGE_AMPM){
      changeTimeInfoVariableListener(false);
    }
    if(currentChangeTime == CHANGE_MONTH && changeMonth >= 0 && changeMonth <= 12){
      changeTimeInfoVariableListener(false);
    }
    if(currentChangeTime == CHANGE_DAY && changeDay >= 0 && changeDay <= dayInMonth(changeMonth, changeYear)){
      changeTimeInfoVariableListener(false);
    }
    if(currentChangeTime == CHANGE_YEAR && changeYear >= 1990 && changeYear <= 2100){
      changeTimeInfoVariableListener(false);
    }
  }
}  

void changeTimeInfoVariableListener(bool arrow){
  switch(currentChangeTime){
    case CHANGE_HOUR:
      changeTimeVariableEditor(&changeHour, arrow);
      drawRecWithFrame(47, 148, 51, 46, WHITE, String(changeHour), BLACK, 3);
      break;
    case CHANGE_MINUTE:
      changeTimeVariableEditor(&changeMinute, arrow);
      drawRecWithFrame(114, 148, 51, 46, WHITE, String(changeMinute), BLACK, 3);
      break;
    case CHANGE_AMPM:
      changeTimeVariableEditor(&changeAmPm, arrow);
      drawRecWithFrame(181, 148, 51, 46, WHITE, (changeAmPm ? "AM":"PM"), BLACK, 3);
      break;
    case CHANGE_MONTH:
      changeTimeVariableEditor(&changeMonth, arrow);
      drawRecWithFrame(22, 242, 51, 46, WHITE, String(changeMonth), BLACK, 3);
      break;
    case CHANGE_DAY:
      changeTimeVariableEditor(&changeDay, arrow);
      drawRecWithFrame(89, 242, 51, 46, WHITE, String(changeDay), BLACK, 3);
      break;
    case CHANGE_YEAR:
      changeTimeVariableEditor(&changeYear, arrow);
      drawRecWithFrame(156, 242, 100, 46, WHITE, String(changeYear), BLACK, 3);
      break;
  }
}

void changeTimeSolarListener(int tx, int ty){
  if(isTouchInsideCircle(412, 217, 40, tx, ty)){
    Serial.println("/? Saving Solar Time.....");
    solarOnHour = changeSolarOnHour+(changeSolarOnAmPm? 0 : 12);
    solarOnMinute = changeSolarOnMinute;
    solarOffHour = changeSolarOffHour+(changeSolarOffAmPm? 0 : 12);
    solarOffMinute = changeSolarOffMinute;
    Serial.print(solarOnHour);Serial.print(":");Serial.print(solarOnMinute);Serial.print(" -> ");
    Serial.print(solarOffHour);Serial.print(":");Serial.println(solarOffMinute);
    LogMsg("BUTTON","Saving Time For Turn On And Off, Solar Mode", tx, ty);
    currentTimeAndDateState = SHOW_TIME_INFO;
  }
  if(isTouchInsideRectangle(28, 149, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), GREEN, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    currentChangeTimeSolar = CHANGE_SOLAR_ON_HOUR;
  }
  if(isTouchInsideRectangle(121, 149, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), GREEN, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    currentChangeTimeSolar = CHANGE_SOLAR_ON_MINUTE;
  }
  if(isTouchInsideRectangle(214, 149, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), GREEN, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    currentChangeTimeSolar = CHANGE_SOLAR_ON_AMPM;
  }
  if(isTouchInsideRectangle(28, 242, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), GREEN, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    currentChangeTimeSolar = CHAGNE_SOLAR_OFF_HOUR;
  }
  if(isTouchInsideRectangle(121, 242, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), GREEN, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    currentChangeTimeSolar = CHANGE_SOLAR_OFF_MINUTE;
  }
  if(isTouchInsideRectangle(214, 242, 55, 55, tx, ty)){
    drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), GREEN, 3);
    currentChangeTimeSolar = CHANGE_SOLAR_OFF_AMPM;
  }

  if(isTouchInsideCircle(326, 172, 40, tx, ty)){
    bool arrow = true;
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_HOUR && changeSolarOnHour >= 0 && changeSolarOnHour <= 11){
      changeTimeVariableEditor(&changeSolarOnHour, arrow);
      drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
      Serial.println(changeSolarOnHour);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_MINUTE && changeSolarOnMinute >= 0 && changeSolarOnMinute <= 58){
      changeTimeVariableEditor(&changeSolarOnMinute, arrow);
      drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_AMPM){
      changeTimeVariableEditor(&changeSolarOnAmPm, arrow);
      drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHAGNE_SOLAR_OFF_HOUR && changeSolarOffHour >= 0 && changeSolarOffHour <= 11){
      changeTimeVariableEditor(&changeSolarOffHour, arrow);
      drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_OFF_MINUTE && changeSolarOffMinute >= 0 && changeSolarOffMinute <= 58){
      changeTimeVariableEditor(&changeSolarOffMinute, arrow);
      drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_OFF_AMPM){
      changeTimeVariableEditor(&changeSolarOffAmPm, arrow);
      drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    }
  }
  if(isTouchInsideCircle(326, 262, 40, tx, ty)){
    bool arrow = false;
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_HOUR && changeSolarOnHour >= 0 && changeSolarOnHour <= 12){
      changeTimeVariableEditor(&changeSolarOnHour, arrow);
      drawRecWithFrame(28, 149, 55, 55, WHITE, Str(changeSolarOnHour), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_MINUTE && changeSolarOnMinute >= 0 && changeSolarOnMinute <= 59){
      changeTimeVariableEditor(&changeSolarOnMinute, arrow);
      drawRecWithFrame(121, 149, 55, 55, WHITE, Str(changeSolarOnMinute), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_ON_AMPM){
      changeTimeVariableEditor(&changeSolarOnAmPm, arrow);
      drawRecWithFrame(214, 149, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHAGNE_SOLAR_OFF_HOUR && changeSolarOffHour >= 0 && changeSolarOffHour <= 12){
      changeTimeVariableEditor(&changeSolarOffHour, arrow);
      drawRecWithFrame(28, 242, 55, 55, WHITE, Str(changeSolarOffHour), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_OFF_MINUTE && changeSolarOffMinute >= 0 && changeSolarOffMinute <= 59){
      changeTimeVariableEditor(&changeSolarOffMinute, arrow);
      drawRecWithFrame(121, 242, 55, 55, WHITE, Str(changeSolarOffMinute), BLACK, 3);
    }
    if(currentChangeTimeSolar == CHANGE_SOLAR_OFF_AMPM){
      changeTimeVariableEditor(&changeSolarOffAmPm, arrow);
      drawRecWithFrame(214, 242, 55, 55, WHITE, (changeSolarOnAmPm? "AM": "PM"), BLACK, 3);
    }
  }
}

void changeTimeVariableEditor(int* var, bool arrow){
  if(arrow){
    *var += 1;
  } else {
    if(*var == 0){
      return;
    }else {
      *var -= 1;
    }
  }
  delay(100);
}

void changeTimeVariableEditor(bool* var, bool arrow){
  if(arrow){
    *var = true;
  } else {
    *var = false;
  }
  delay(100);
}



void OtherListener(int tx, int ty){
  if(isTouchInsideCircle(63, 162, 28, tx, ty)){
    if(!HumidBjtSwitchRun){
      LogMsg("TEST","Turning On Humid", tx, ty);
      humidSwitchOff();
      HumidBjtSwitchRun = true;
      digitalWrite(IOHUMIDAC, HIGH);
    }else if(HumidBjtSwitchRun){
      LogMsg("TEST","Turning Off Humid", tx, ty);
      digitalWrite(IOHUMIDAC, LOW);
      humidSwitchOn();
      HumidBjtSwitchRun = false;
    }
  }
  if(isTouchInsideCircle(153, 162, 28, tx, ty)){
    if(digitalRead(IOMOTOR)){
      LogMsg("TEST","Turning On Motor", tx, ty);
      digitalWrite(IOMOTOR, LOW);
    } else if(!digitalRead(IOMOTOR)){
      LogMsg("TEST","Turning Off Motor", tx, ty);
      digitalWrite(IOMOTOR, HIGH);
    }
  }
  if(isTouchInsideCircle(243, 162, 28, tx, ty)){
    if(digitalRead(IOHEATER)){
      LogMsg("TEST","Turning On Induction Heater", tx, ty);
      digitalWrite(IOHEATER, LOW);
    }else if(!digitalRead(IOHEATER)){
      LogMsg("TEST","Turning Off Induction Heater", tx, ty);
      digitalWrite(IOHEATER, HIGH);
    }
  }
  if(isTouchInsideCircle(333, 162, 28, tx, ty)){
    if(!digitalRead(IOSOLAR)){
      LogMsg("TEST","Turning On Solar Mode", tx, ty);
      digitalWrite(IOSOLAR, HIGH);
    }else {
      LogMsg("TEST","Turning Off Solar Mode", tx, ty);
      digitalWrite(IOSOLAR, LOW);
    }
    delay(1000);
  }
  if(isTouchInsideCircle(418, 162, 28, tx, ty)){
    if(!digitalRead(IOINVERTER)){
      digitalWrite(IOINVERTER, HIGH);
    } else {
      digitalWrite(IOINVERTER, LOW);
    }
  }
  
}

bool isTouchInsideCircle(int cx, int cy, int r, int tx, int ty) {
  long dx = tx - cx;
  long dy = ty - cy;
  return (dx * dx + dy * dy) <= (r * r);
}
// (x, y) Position, (w, h) Size of Button, (tx, ty) Touch Point
bool isTouchInsideRectangle(int x, int y, int w, int h, int tx, int ty) {
  return (tx >= x && tx <= (x + w) && ty >= y && ty <= (y + h));
}