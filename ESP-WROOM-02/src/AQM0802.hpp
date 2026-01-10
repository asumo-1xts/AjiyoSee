// Datasheet:
// https://akizukidenshi.com/goodsaffix/AQM0802.pdf

#ifndef AQM0802_HPP
#define AQM0802_HPP

#define PIN_SDA 13
#define PIN_SCL 12

#define ADDR 0x3e
#define CLEAR_HEX 0x01
#define ENTER_HEX 0xc0
#define FIRST_LINE 0x00   // 1行目の先頭のアドレス
#define SECOND_LINE 0x40  // 2行目の先頭のアドレス
#define CMD_INIT {0x38, 0x39, 0x14, 0x70, 0x56, 0x6c, 0x38, 0x0c, 0x01}

#define POWERON_WAIT() delay(50)            // > 40 ms
#define WRITE_WAIT() delayMicroseconds(30)  // > 26.3 us
#define CLEAR_WAIT() delay(2)               // > 1.08 ms

#endif