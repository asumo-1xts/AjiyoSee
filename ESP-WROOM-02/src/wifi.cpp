#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include ".env.h"  //!< SSIDとPASSWORDを定義しているファイル
#include "header.hpp"

const char* ssid = SSID;          //!< 外部に公開しないよう注意
const char* password = PASSWORD;  //!< 外部に公開しないよう注意
const char* host = "ajiyosee.vercel.app";
const char* url = "/result.txt";
const long gmtOffset_sec = 9 * 3600;  // JST = UTC+9
const int daylightOffset_sec = 0;

/**
 * @fn void ConnectWiFi(void)
 * @brief Wi-Fiへの接続を行う関数
 */
void ConnectWiFi(void) {
  Serial.println();
  Serial.println("Connecting to Wi-Fi...");
  PrintLCD("Wi-Fi...", "");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connected to Wi-Fi.");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("MAC address: %s\n", WiFi.macAddress().c_str());
  PrintLCD("Wi-Fi...", "Wi-Fi OK");
  delay(500);
}

/**
 * @fn uint8_t GetResult(void)
 * @brief https://ajiyosee.vercel.app/result.txt から販売状況を取得する関数
 * @return 販売状況のコード
 */
uint8_t GetResult(void) {
  String line;
  WiFiClientSecure client;
  client.setInsecure();
  Serial.println();

  // 接続に失敗した場合は3（UNKNOWN）を返す
  if (!client.connect(host, 443)) {
    Serial.println("HTTPS connection failed.");
    return 3;
  }
  // 情報をリクエスト
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +
               "\r\n" + "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
  // シリアルモニタにリクエスト結果を表示
  while (client.connected() || client.available()) {
    if (client.available()) {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
  }
  client.stop();

  char result_char = line[0];  // 販売状況のコード
  uint8_t result_uint8 = static_cast<uint8_t>(result_char - '0');
  Serial.printf("\nResult: %d\n", result_uint8);
  return result_uint8;
}

/**
 * @fn Time GetTime(void)
 * @brief NTPサーバーから現在時刻を取得する関数
 * @return 現在時刻の構造体
 */
Time GetTime(void) {
  configTime(gmtOffset_sec, daylightOffset_sec, "ntp.nict.jp",
             "ntp.jst.mfeed.ad.jp", "pool.ntp.org");

  struct tm timeinfo;
  Time t = {0, 0, 0, 0, 0, 0};

  if (getLocalTime(&timeinfo)) {
    t.year = timeinfo.tm_year + 1900;
    t.month = timeinfo.tm_mon + 1;
    t.day = timeinfo.tm_mday;
    t.hour = timeinfo.tm_hour;
    t.minute = timeinfo.tm_min;
    t.second = timeinfo.tm_sec;
  }

  // シリアルモニタにYYYY/MM/DD HH:MM:SS形式で表示
  Serial.printf("\nCurrent time: %04d/%02d/%02d %02d:%02d:%02d\n", t.year,
                t.month, t.day, t.hour, t.minute, t.second);

  return t;
}