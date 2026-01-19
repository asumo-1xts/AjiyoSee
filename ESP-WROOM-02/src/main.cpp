#include ".env.h"
#include "header.hpp"

const std::string project_name = "AjiyoSee";
const std::string project_ver = "v1.0.0";
const std::string status[5] = {"OPEN", "CLOSE", "SOLD OUT", "UNKNOWN",
                               "No X-API"};
char hhmm[11];

/**
 * @fn std::vector<uint8_t> Str2Utf8(const std::string &str)
 * @brief 文字列をASCII配列に変換する関数
 * @param str 変換する文字列
 * @return 変換後のASCII配列
 */
std::vector<uint8_t> Str2Utf8(const std::string& str) {
  std::vector<uint8_t> ans_utf8;
  for (char c : str) {
    ans_utf8.push_back(static_cast<uint8_t>(c));
  }
  return ans_utf8;
}

/**
 * @fn void HandleLED(uint8_t *vals)
 * @brief LEDを選んで光らせる関数
 * @param vals LEDの状態を格納した配列
 */
void HandleLED(std::array<uint8_t, 4> vals) {
  digitalWrite(LED_GREEN, vals[0]);
  digitalWrite(LED_RED, vals[1]);
  digitalWrite(LED_WHITE, vals[2]);
  digitalWrite(LED_YELLOW, vals[3]);
  delay(100);
}

/**
 * @fn void setup(void)
 * @brief Arduino式のsetup()関数
 */
void setup(void) {
  uint8_t i = 0;

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  HandleLED({LOW, LOW, LOW, LOW});

  Serial.begin(115200);
  SetupLCD();

  PrintLCD(project_name, project_ver);
  for (i = 0; i < 2; i++) {
    HandleLED({HIGH, LOW, LOW, LOW});
    HandleLED({HIGH, HIGH, LOW, LOW});
    HandleLED({HIGH, HIGH, HIGH, LOW});
    HandleLED({HIGH, HIGH, HIGH, HIGH});
    HandleLED({HIGH, HIGH, HIGH, LOW});
    HandleLED({HIGH, HIGH, LOW, LOW});
    HandleLED({HIGH, LOW, LOW, LOW});
    HandleLED({LOW, LOW, LOW, LOW});
  }

  ConnectWiFi();
}

/**
 * @fn void loop(void)
 * @brief Arduino式のloop()関数
 */
void loop(void) {
  PrintLCD("Getting", "info...");

  uint8_t result = GetResult();
  Time now = GetTime();
  snprintf(hhmm, sizeof(hhmm), "%02d:%02dJST", now.hour, now.minute);
  PrintLCD(status[result], hhmm);

  switch (result) {
    case 0:  // OPEN
      HandleLED({HIGH, LOW, LOW, LOW});
      break;
    case 1:  // CLOSE
      HandleLED({LOW, HIGH, LOW, LOW});
      break;
    case 2:  // SOLD OUT
      HandleLED({HIGH, HIGH, HIGH, LOW});
      break;
    case 3:  // UNKNOWN
      HandleLED({LOW, LOW, HIGH, LOW});
      break;
    case 4:  // No X-API
      HandleLED({LOW, LOW, LOW, HIGH});
      break;
    default:  // Error
      HandleLED({LOW, LOW, LOW, LOW});
      break;
  }

  INTERVAL_WAIT();

  aaa;
}