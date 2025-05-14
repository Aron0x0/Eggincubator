#pragma once

auto ctof = [] (float Value) -> float {
  return (Value * 9.0/5.0) + 32.0;
};

auto getPercent = [] (float Whole, float Percentage) -> float {
  return (Percentage / 100) * Whole;
};

auto SecondsToMillis = [](float timeInSeconds) -> unsigned long {
    return static_cast<unsigned long>(timeInSeconds * 1000);
};

auto MinutesToMillis = [](int timeInMinutes) -> unsigned long {
    return SecondsToMillis(static_cast<float>(timeInMinutes * 60));
};

template<typename T>
String Str(T value) {
  return String(value);
}

auto darkenColor = [](uint16_t color, float factor) -> uint16_t {
  uint8_t r = (color >> 11) & 0x1F;
  uint8_t g = (color >> 5) & 0x3F;
  uint8_t b = color & 0x1F;
  r = r * factor;
  g = g * factor;
  b = b * factor;
  return (r << 11) | (g << 5) | b;
};

auto brightenColor = [](uint16_t color, float factor) -> uint16_t {
  uint8_t r = (color >> 11) & 0x1F;
  uint8_t g = (color >> 5) & 0x3F;
  uint8_t b = color & 0x1F;

  r = min((int)(r * factor), 31);  // 5 bits max 0..31
  g = min((int)(g * factor), 63);  // 6 bits max 0..63
  b = min((int)(b * factor), 31);  // 5 bits max 0..31

  return (r << 11) | (g << 5) | b;
};