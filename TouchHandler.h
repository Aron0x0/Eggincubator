#pragma once

void EachFrameListener(int tx, int ty);
void EggIncubatorListener(int tx, int ty);
void MainFrameListener(int tx, int ty);
void SetupListener(int tx, int ty);
void AboutListener(int tx, int ty);
void MenuListener(int tx, int ty);
void TimeAndDateListener(int tx, int ty);
void CalibrationListener(int tx, int ty);
void StatListener(int tx, int ty);

void OtherListener(int tx, int ty);
void TimeAndDateSwitch(int tx, int ty);
void showTimeInfoListener(int tx, int ty);
void changeTimeInfoListener(int tx, int ty);

void changeTimeInfoVariableListener(bool arrow);
void changeTimeVariableEditor(int* var, bool arrow);
void changeTimeVariableEditor(bool* var, bool arrow);
void changeTimeSolarListener(int tx, int ty);

void SetupCalibrationListListener(int tx, int ty);
void SetupCalibrationAdjustListener(int* var, int tx, int ty);
void SetupCalibrationAdjustListener(float* var, int tx, int ty);

bool isTouchInsideCircle(int cx, int cy, int r, int tx, int ty);
bool isTouchInsideRectangle(int x, int y, int w, int h, int tx, int ty);