#include <Arduino.h>

#include <string>

#include "AQM0802.hpp"

#ifndef COMMON_HPP
#define COMMON_HPP

#define LED_GREEN 0
#define LED_RED 14
#define LED_WHITE 15
#define LED_YELLOW 2

void SetupLCD(void);
void WriteLCD(uint8_t*, size_t, bool);
void PrintLCD(std::string, std::string);

struct Time {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

void ConnectWiFi(void);
uint8_t GetResult(void);
Time GetTime(void);

std::vector<uint8_t> Str2Utf8(const std::string& str);

#define INTERVAL_WAIT() delay(36000)

#endif