#pragma once
#include "Config.h"

void LogicInit();
void SetupStartData();
void PrintDateNow();

void SystemTimeUpdate();
void SetupDeviceIO();
void DebugDeviceStates();
void UpdateDeviceState();
void SensorDevice();

void humidSwitchOff();
void humidSwitchOn();

void ConvertTimeToUI();
void ConvertFormatDateToUI();
String ConvertTimeToUI(int hour, int minute);
String FormatMonth(int month);

int dayInMonth(uint8_t month, uint16_t year);
void PredictedEndDay(uint8_t hour, uint8_t minute, uint16_t month, uint8_t day, uint16_t year, uint8_t addDays);
bool TimeDelayExecution(uint8_t deviceIndex, uint8_t IO, unsigned long interval, unsigned long duration);
bool DelayFunction(uint8_t deviceIndex, unsigned long delayInterval);
bool pulseRelayEvery(uint8_t deviceIndex, unsigned long interval, unsigned long duration);
bool isTimeInRange(uint8_t hour, uint8_t minute, uint8_t onHour, uint8_t onMinute, uint8_t offHour, uint8_t offMinute);
bool isLeafYear(uint16_t year);