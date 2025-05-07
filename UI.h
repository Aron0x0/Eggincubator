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
void StatFrame();
void drawNewMainFrame();
void drawDeviceIndicators();
void drawGaugeBase(int cx, int cy, const char* label, int minVal, int maxVal);

void drawGaugeValue(int cx, int cy, float value, int minVal, int maxVal, uint16_t color, const char* unit, bool showDecimal);
void drawRightTriangleAtCorner(int x, int y, int size, uint16_t color, int rotationDeg);

void drawCurrentDateTimeFrame();
void changeTimeInfoFrame();

void updateTempHumidDisplay();
void destroyTempHumidDisplay();
void updateUiClock(String time, String lasttime, int x, int y);
void updateUiDate(String date, String lastdate, int x ,int y);
void updateUIField(float value, float &lastValue, int x, int y);
void updateUIField(int value, int &lastValue, int x, int y);
void updateUiDevice();
void updateUiDevice(bool OnlyOnceRun);

void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size);
void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size, int frameColor);
void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size, int frameColor, int frameSize);
void drawCircleWithFrame(int x, int y, int r, int color, String label, int textColor, int size, int frameColor, int frameSize, int LabelAdjustment);
void drawRecWithFrame(int x, int y, int w, int h, int color, String label, int textColor, int size);
void destroyAndDrawValues(String msg, String lastmsg, int px, int py, int size, uint16_t DestroyColor, uint16_t DrawColor);

void drawCirclePixelByPixel(int xc, int yc, int r, uint16_t color);

void BlurEffectScreen();
void BlurEffect(int x, int y, int w, int h);
void drawHatchBlur(int x, int y, int w, int h);
void drawDimmedBox(int x, int y, int w, int h, uint16_t overlayColor);
void drawFakeBlurOverlay(int x, int y, int w, int h);

void drawString(String msg, int x, int y, uint16_t size);
void drawString(String msg, int x, int y, float size, uint16_t COLOR);
void drawString(String msg, int x, int y, int size, uint16_t COLOR, bool xcenter);
void drawString(String msg, int x, int y, int size, uint16_t COLOR, bool xcenter, bool ycenter);

void printTouchPoint(int x, int y);

#endif