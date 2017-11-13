#include "digit.h"

static const int DIGITS[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
};

// 7seg 制御ピンの初期化
void digitInit() {
  // セグメント指定ピンを OUTPUT に指定、LOW で初期化
  // bit 0 => A, bit 1 => B, ..., bit 6 => G, bit 7 => DP
  DDRD = B11111111;
  PORTD = 0;

  // 桁指定ピンを OUTPUT に指定、LOW で初期化
  // bit 0 => DIG.1 (FIGURE_1), bit 1 => DIG.2 (FIGURE_2)
  DDRB = DDRB | B00000011;
  PORTB = PORTB & B11111100;
}

// 桁指定ビットを取得する
static byte figure_bits(byte figure) {
  // カソードコモンの 7seg のカソード側を NPN でドライブするので、
  // HIGH のときに有効になり、LOW のときに無効になる

  if (figure == FIGURE_1) {
    return B00000001; // DIG.1 を ON 、DIG.2 を OFF
  } else {
    return B00000010; // DIG.1 を OFF 、DIG.2 を ON
  }
}

// 数字を表示する
void digitWrite(byte figure, int digit, boolean point) {
  PORTB = PORTB & B11111100 | figure_bits(figure);
  PORTD = DIGITS[digit % 10] | (point ? B10000000 : 0);
}

