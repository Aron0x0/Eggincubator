#include "UI.h"
#include "Config.h"
#include "Utils.h"
#include "Logic.h"
#include "TouchHandler.h"
#include "UIHandler.h"

void EggIncubatorFrame(){
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.fillRect(81, 14, 318, 61, BLACK);
  drawString("Egg Incubator", 125, 33, 3, WHITE);
  tft.drawRect(87, 23, 305, 43, GRAY);
  tft.drawRect(81, 14, 318, 61, GRAY);
  drawCircleWithFrame(240, 160, 65, BLACK, "START", GREEN, 3);
  drawCircleWithFrame(379, 215, 55, BLACK, "ABOUT", RED, 2);
  drawCircleWithFrame(81, 235, 75, BLACK, "SETUP", CYAN, 4);
}
void MainFrame(){
  tft.fillScreen(GRAY);
  tft.drawRect(15, 12, 450, 295, BLACK);
  tft.drawRect(1, 1, 478, 318, BLACK);

  tft.drawLine(1, 1, 15, 12, BLACK);
  tft.drawLine(478, 318, 465, 307, BLACK);
  tft.drawLine(478, 1, 465, 12, BLACK);
  tft.drawLine(1, 318, 15, 307, BLACK);

  updateUiClock(CLOCK, LASTCLOCK, 240, 20);
  updateUiDate(DATE, LASTDATE, 400, 35);
  updateTempHumidDisplay();

  drawString("TEMPERATURE:", 40, 55, 3, WHITE);
  drawString("HUMIDITY:", 60, 175, 3, WHITE);
  drawRecWithFrame(280, 73, 151, 47, RED, "MOTOR", BLACK, 3);
  drawRecWithFrame(280, 127, 151, 47, RED, "HUMID", BLACK, 3);
  drawRecWithFrame(280, 181, 151, 47, RED, "HEAT", BLACK, 3);
  drawRecWithFrame(280, 235, 151, 47, RED, "SOLAR", BLACK, 3);
  // updateUiDevice(true);
}
void updateTempHumidDisplay(){
  drawString(String(temp)+"c", 30, 90, 7);
  drawString(String(humid)+"%", 90, 210, 7);
  lasttemp = temp; lasthumid = humid;
}
void destroyTempHumidDisplay(){
  drawString(String(lasttemp)+"c", 30, 90, 7, GRAY);
  drawString(String(lasthumid)+"%", 90, 210, 7, GRAY);
}

void SetupFrame(){
  tft.fillScreen(GRAY);
  drawString("Setup", 185, 12, 4);
  tft.fillRect(22, 49, 127, 39, BLACK);
  tft.fillRect(163, 49, 154, 39, BLACK);
  tft.fillRect(331, 49, 127, 39, BLACK);
  drawString("Calibration", 45, 63, 1, WHITE);
  drawString("Time & Date", 198, 63, 1, WHITE);
  drawString("Other's", 378, 63, 1, WHITE);
  tft.drawRect(5, 92, 467, 223, BLACK);
  tft.drawRect(6, 93, 465, 221, BLACK);
  
}

void AboutFrame(){
}
void MenuFrame(){
}
void TimeAndDateFrame(){
  tft.fillRect(7, 94, 463, 219, GRAY);

  tft.fillRect(38, 109, 206, 109, WHITE);
  tft.drawRect(38, 109, 206, 109, BLACK);
  drawString("DATE",141, 121, 2, BLACK, true, true);
  drawString("00/00/0000",141, 153, 2, BLACK, true, true);
  drawString("January 1, 2025",141, 184, 2, BLACK, true, true);

  tft.fillRect(38, 229, 206, 74, WHITE);
  tft.drawRect(38, 229, 206, 74, BLACK);
  drawString("TIME", 141, 248, 2, BLACK, true, true);
  drawString("12:08 AM", 141, 270, 2, BLACK, true, true);

  drawRecWithFrame(300, 160, 158, 45, WHITE, "Change Time", RED, 3);
  drawString("CHANGE TIME", 378, 185, 2, BLACK, true, true);
}
void changeTimeInfoFrame(){
  tft.fillRect(7, 94, 463, 219, GRAY);
  drawCircleWithFrame(393, 265, 35, WHITE, "SAVE", BLACK, 2);
  drawRecWithFrame(38, 109, 206, 109, WHITE, "", BLACK, 1);
  drawString("DATE", 141, 132, 2, BLACK, true, true);
  drawString("\"MONTH/DAY/YEAR\"", 141, 151, 1, BLACK, true, true);
  tft.drawRect(49, 169, 43, 35, BLACK);
  drawString("/", 101, 187, 3, BLACK, true, true);
  tft.drawRect(109, 169, 43, 35, BLACK);  
  drawString("/", 161, 187, 3, BLACK, true, true);
  tft.drawRect(169, 169, 65, 35, BLACK);


  drawRecWithFrame(38, 229, 206, 74, WHITE, "", BLACK, 1);
  drawString("TIME", 141, 248, 2, BLACK, true, true);
  // drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size)
  // drawRecWithFrame(int x, int y, int w, int h, int color, String label, int textColor, int size) 
}
void OtherFrame(){
  tft.fillRect(7, 94, 463, 219, BLACK);
}
void CalibrationFrame(){
  int xlistbox = 170;
  tft.fillRect(7, 94, 463, 219, GRAY);

  tft.fillRect(xlistbox, 101, 170, 45, WHITE);
  tft.fillRect(xlistbox, 154, 170, 45, WHITE);
  tft.fillRect(xlistbox, 207, 170, 45, WHITE);
  tft.fillRect(xlistbox, 260, 170, 45, WHITE);
  tft.drawRect(xlistbox, 101, 170, 45, BLACK);
  tft.drawRect(xlistbox, 154, 170, 45, BLACK);
  tft.drawRect(xlistbox, 207, 170, 45, BLACK);
  tft.drawRect(xlistbox, 260, 170, 45, BLACK);
  drawString("TEMP:", 30, 135, 4);
  drawString("HUMID:", 30, 240, 4);
  drawString("Max.", (xlistbox + 15), 120, 1);
  drawString("Min.", (xlistbox + 15), 173, 1);
  drawString("Max.", (xlistbox + 15), 226, 1);
  drawString("Min.", (xlistbox + 15), 279, 1);
  tft.fillCircle(420, 150, 40, WHITE);//x = 420 and y = 150, 250 (r = 40)
  tft.fillCircle(420, 250, 40, WHITE);
  tft.drawCircle(420, 150, 40, BLACK);
  tft.drawCircle(420, 250, 40, BLACK);
  tft.drawCircle(420, 150, 30, BLACK);
  tft.drawCircle(420, 250, 30, BLACK);
  drawString("+", 403, 127, 7);
  drawString("-", 403, 227, 7);
}


void StatFrame(){
  // ConvertFormatDateToUI();
  tft.fillRect(16, 13, 448, 293, GRAY);
  tft.drawRect(38, 74, 404, 89, BLACK);
  tft.drawRect(38, 190, 404, 89, BLACK);
  drawString("Stats", 240, 25, 4, BLACK, true);
  drawString("Solar Time", 131, 91, 2, YELLOW, true, true);
  drawString("Begin", 334, 91, 2, GREEN, true, true);
  drawString("End", 334, 129, 2, RED, true, true);

  drawString(FORMATDATE, 335, 110, 2, darkenColor(GREEN, 0.2), true, true);
  drawString(TOFORMATDATE, 335, 148, 2, darkenColor(RED, 0.2), true, true);
  drawString("Start:", 85, 114, 2, darkenColor(YELLOW, 0.2), true, true);
  drawString("End:", 85, 136, 2, darkenColor(YELLOW, 0.2), true, true);
  drawString((ConvertTimeToUI(solarOnHour, solarOnMinute)), 170, 114, 2, darkenColor(YELLOW, 0.2), true, true);
  drawString((ConvertTimeToUI(solarOffHour, solarOffMinute)), 170, 136, 2, darkenColor(YELLOW, 0.2), true, true);

  drawString("Error Handler", 240, 207, 2, RED, true, true);
  drawCircleWithFrame(396, 235, 37, WHITE, "DONE", darkenColor(YELLOW, 0.6), 2);
}

void updateUIField(float value, float &lastValue, int x, int y) {
  if (value != lastValue || isSetupCalibrationFirstRun) {
    destroyAndDrawValues(String(value), String(lastValue), x, y, 3, WHITE, BLACK);
    lastValue = value;
  }
}
void updateUIField(int value, int &lastValue, int x, int y) { 
  if (value != lastValue || isSetupCalibrationFirstRun) {
    destroyAndDrawValues(String(value), String(lastValue), x, y, 3, WHITE, BLACK);
    lastValue = value;
  }
}

void updateUiClock(String time, String lasttime, int x, int y){
  if(CLOCK != LASTCLOCK && currentState == STATE_MAIN){
    drawString(LASTCLOCK, 240, 20, 3, GRAY, true);
    drawString(CLOCK, 240, 20, 3, WHITE, true);
    Serial.print("/> LOG :: DRAWING :: CLOCK :: ");Serial.println(CLOCK);
    LASTCLOCK = CLOCK;
  }
}

void updateUiDate(String date, String lastdate, int x, int y){
  drawString(lastdate, x, y, 2, GRAY, true, true);
  drawString(date, x, y, 2, WHITE, true, true);
}
void updateUiDevice(){
  const char* deviceNames[DEVICE_COUNT] = {"MOTOR", "HUMID", "HEAT", "SOLAR"};
  const int deviceNamesPosition[DEVICE_COUNT] = {73, 127, 181, 235};

  for(int i = 0; i < DEVICE_COUNT; i++) {
    if(deviceState[i] != lastdeviceState[i]){
      if(deviceState[i]){
        drawRecWithFrame(280, deviceNamesPosition[i], 151, 47, GREEN, String(deviceNames[i]), BLACK, 3);
        lastdeviceState[i] = deviceState[i];
      }else{
        drawRecWithFrame(280, deviceNamesPosition[i], 151, 47, RED, String(deviceNames[i]), BLACK, 3);
        lastdeviceState[i] = deviceState[i];
      }
    }
  }
}
void updateUiDevice(bool OnlyOnceRun){
  const char* deviceNames[DEVICE_COUNT] = {"MOTOR", "HUMID", "HEAT", "SOLAR"};
  const int deviceNamesPosition[DEVICE_COUNT] = {73, 127, 181, 235};

  for(int i = 0; i < DEVICE_COUNT; i++) {
    if(deviceState[i]){
      drawRecWithFrame(280, deviceNamesPosition[i], 151, 47, GREEN, String(deviceNames[i]), BLACK, 3);
      lastdeviceState[i] = deviceState[i];
    }else{
      drawRecWithFrame(280, deviceNamesPosition[i], 151, 47, RED, String(deviceNames[i]), BLACK, 3);
      lastdeviceState[i] = deviceState[i];
    }
  }
}

void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size){

  tft.fillCircle(x, y, r, color);
  tft.drawCircle(x, y, r, GRAY);
  tft.drawCircle(x, y, getPercent(r, 90), GRAY);
  tft.setTextSize(size); // adjust as needed
  tft.setTextColor(textColor);

  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(label, 0, 0, &x1, &y1, &w, &h);

  int textX = x - w / 2;
  int textY = y - h / 2;

  tft.setCursor(textX, textY);
  tft.print(label);
}

void drawRecWithFrame(int x, int y, int w, int h, int color, String label, int textColor, int size) {
  // Outer rectangle
  tft.fillRect(x, y, w, h, color);
  tft.drawRect(x, y, w, h, BLACK);

  // Inner frame (10% inset from all sides)
  int frameMarginX = getPercent(w, 5); // 5% margin left & right
  int frameMarginY = getPercent(h, 10); // 5% margin top & bottom

  int innerX = x + frameMarginX;
  int innerY = y + frameMarginY;
  int innerW = w - 2 * frameMarginX;
  int innerH = h - 2 * frameMarginY;

  tft.drawRect(innerX, innerY, innerW, innerH, BLACK);

  // Centered text
  tft.setTextSize(size);
  tft.setTextColor(textColor);

  int16_t x1, y1;
  uint16_t textW, textH;
  tft.getTextBounds(label, 0, 0, &x1, &y1, &textW, &textH);

  int textX = x + (w - textW) / 2;
  int textY = y + (h - textH) / 2;

  tft.setCursor(textX, textY);
  tft.print(label);
}

void destroyAndDrawValues(String msg, String lastmsg, int px, int py, int size, uint16_t DestroyColor, uint16_t DrawColor){
  drawString(lastmsg, px, py, size, DestroyColor);
  drawString(msg, px, py, size, DrawColor);
}

void drawString(String msg, int x, int y, uint16_t size){
  tft.setCursor(x, y);
  // tft.setFont(&Inter_28pt_ExtraBold8pt7b);
  tft.setTextColor(TEXT_COLOR);
  tft.setTextSize(size);
  tft.print(msg);
}
void drawString(String msg, int x, int y, float size, uint16_t COLOR){
  tft.setCursor(x, y);
  // tft.setFont(&Inter_28pt_ExtraBold8pt7b);
  tft.setTextColor(COLOR);
  tft.setTextSize(size);
  tft.print(msg);
}

void drawString(String msg, int x, int y, int size, uint16_t COLOR, bool xcenter){
  tft.setTextSize(size);
  tft.setTextColor(COLOR);

  // Get text width
  int16_t x1, y1;
  uint16_t textW, textH;
  tft.getTextBounds(msg, 0, 0, &x1, &y1, &textW, &textH);

  // Center horizontally
  int screenW = tft.width();
  int textX = (screenW - textW) / 2;

  // Use provided Y
  tft.setCursor(textX, y);
  tft.print(msg);
}

void drawString(String msg, int x, int y, int size, uint16_t COLOR, bool xcenter, bool ycenter){
  tft.setTextSize(size);
  tft.setTextColor(COLOR);

  // Get text bounds
  int16_t x1, y1;
  uint16_t textW, textH;
  tft.getTextBounds(msg, 0, 0, &x1, &y1, &textW, &textH);

  // Adjust so (x, y) is the center
  int textX = x - textW / 2;
  int textY = y - textH / 2;

  tft.setCursor(textX, textY);
  tft.print(msg);
}

void drawCirclePixelByPixel(int xc, int yc, int r, uint16_t color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Draw the 8 symmetric points
        tft.drawPixel(xc + x, yc + y, color);
        tft.drawPixel(xc - x, yc + y, color);
        tft.drawPixel(xc + x, yc - y, color);
        tft.drawPixel(xc - x, yc - y, color);
        tft.drawPixel(xc + y, yc + x, color);
        tft.drawPixel(xc - y, yc + x, color);
        tft.drawPixel(xc + y, yc - x, color);
        tft.drawPixel(xc - y, yc - x, color);

        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        // OPTIONAL: slow down animation
        // delay(5); // uncomment for visible drawing animation
    }
}

void printTouchPoint(int x, int y){
  Serial.print(" (");Serial.print(x);Serial.print(", ");Serial.print(y);
  Serial.println(")");
}