#include "digit.h"

static const int DIGIT_BITS[16] = {
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
  B01110111, // A
  B01111100, // b
  B00111001, // C
  B01011110, // d
  B01111001, // E
  B01110001  // F
};

static const byte POINT_BIT = B10000000;

static const byte FIGURE_1_BIT = B00010000;
static const byte FIGURE_2_BIT = B00100000;
static const byte FIGURE_MASK_BITS = B11111111 ^ FIGURE_1_BIT ^ FIGURE_2_BIT;

// 7seg 制御ピンの初期化
void digitInit() {
  // セグメント指定ピンを OUTPUT に指定、LOW で初期化
  // bit 0 => A, bit 1 => B, ..., bit 6 => G, bit 7 => DP
  DDRD = B11111111;
  PORTD = 0;

  // 桁指定ピンを OUTPUT に指定、LOW で初期化
  // bit 4 => DIG.1 (FIGURE_1), bit 5 => DIG.2 (FIGURE_2)
  DDRB = DDRB | FIGURE_1_BIT | FIGURE_2_BIT;
  PORTB = PORTB & FIGURE_MASK_BITS;
}

// 桁指定ビットを取得する
static byte figure_bits(byte figure) {
  // カソードコモンの 7seg のカソード側を NPN でドライブするので、
  // HIGH のときに有効になり、LOW のときに無効になる

  if (figure == FIGURE_1) {
    return FIGURE_1_BIT; // DIG.1 を ON 、DIG.2 を OFF
  } else {
    return FIGURE_2_BIT; // DIG.1 を OFF 、DIG.2 を ON
  }
}

// 数字を表示する
void digitWrite(byte figure, int digit, boolean point) {
  PORTB = PORTB & FIGURE_MASK_BITS | figure_bits(figure);
  PORTD = DIGIT_BITS[digit % 16] | (point ? POINT_BIT : 0);
}

