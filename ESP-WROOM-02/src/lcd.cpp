#include <Wire.h>

#include "header.hpp"

/**
 * @fn void WriteLCD(uint8_t *cmd, size_t len, bool row)
 * @brief LCDにコマンドまたはデータを書き込む関数
 * @param cmd 書き込むコマンドまたはデータの配列
 * @param len コマンドまたはデータの配列長
 * @param row 行選択（true: 1行目、false: 2行目）
 */
void WriteLCD(uint8_t* cmd, size_t len, bool row) {
  size_t i;
  for (i = 0; i < len; i++) {
    Wire.beginTransmission(ADDR);
    Wire.write(row ? FIRST_LINE : SECOND_LINE);
    Wire.write(cmd[i]);
    Wire.endTransmission();
    WRITE_WAIT();
  }
}

/**
 * @fn void SetupLCD(void)
 * @brief LCDを初期化する関数
 */
void SetupLCD(void) {
  uint8_t cmd_init[] = CMD_INIT;
  Wire.begin(PIN_SDA, PIN_SCL);
  POWERON_WAIT();
  WriteLCD(cmd_init, sizeof(cmd_init), true);
  CLEAR_WAIT();
}

/**
 * @fn void PrintLCD(std::string row1, std::string row2)
 * @brief LCDに2行まとめて表示する関数
 * @param row1 1行目の表示内容
 * @param row2 2行目の表示内容
 */
void PrintLCD(std::string row1, std::string row2) {
  uint8_t command_clear[1] = {CLEAR_HEX};  // 画面クリア
  uint8_t command_enter[1] = {ENTER_HEX};  // カーソルセット
  std::vector<uint8_t> row1_uint8 = Str2Utf8(row1);
  std::vector<uint8_t> row2_uint8 = Str2Utf8(row2);

  WriteLCD(command_clear, sizeof(command_clear), true);
  WriteLCD(command_enter, sizeof(command_enter), true);
  WriteLCD(row1_uint8.data(), row1_uint8.size(), false);
  WriteLCD(command_enter, sizeof(command_enter), true);
  WriteLCD(row2_uint8.data(), row2_uint8.size(), false);
}