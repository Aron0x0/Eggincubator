#ifndef UI_UTILS_H;
#define UI_UTILS_H;

#include "Config.h"

void MenuFrame();
void MainFrame();
void EggIncubatorFrame();
void drawCurrentScreen();
void destroyTempHumidDisplay();
void updateTempHumidDisplay();
void drawCurrentList();
void SetupFrame();
void AboutFrame();
void OtherFrame();
void TimeAndDateFrame();
void CalibrationFrame();

void updateTempHumidDisplay();
void destroyTempHumidDisplay();
void updateUiClock(String time, String lasttime, int x, int y);
void updateUIField(float value, float &lastValue, int x, int y);
void updateUIField(int value, int &lastValue, int x, int y);
void updateUiDevice();

void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size);
void drawRecWithFrame(int x, int y, int w, int h, int color, String label, int textColor, int size);
void destroyAndDrawValues(String msg, String lastmsg, int px, int py, int size, uint16_t DestroyColor, uint16_t DrawColor);

void drawCirclePixelByPixel(int xc, int yc, int r, uint16_t color);

void drawString(String msg, int x, int y, uint16_t size);
void drawString(String msg, int x, int y, float size, uint16_t COLOR);
void drawString(String msg, int x, int y, int size, uint16_t COLOR, bool center);

void printTouchPoint(int x, int y);

#endif