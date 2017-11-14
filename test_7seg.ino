#include <TimerOne.h>
#include "digit.h"

// 加算/減算切り替えボタンの入力ピン番号
const int BUTTON = 8;

// ボタンの以前の状態
int prev_button_state = LOW;

int     digit = 0;    // 7seg 二桁で表示する数値
boolean point = true; // 7seg の小数点の表示状態
int     delta = 1;    // 数値の増分

// タイマのコールバック関数
void callback() {
  // 小数点の表示状態の ON/OFF を切り替える
  point = !point;

  // 小数点表示が ON になったとき、数値に増分を加える
  // 0.5 秒毎に ON/OFF が切り替わるので、1 秒毎に加算される
  if (point) {
    digit = (digit + delta) % 60;
  }
}

// 初期化
void setup() {
  // 加算/減算切り替えボタンのピンを入力に指定する
  pinMode(BUTTON, INPUT);

  // 7seg 制御の状態を初期化する
  digitInit();

  // タイマを 500,000 usec で初期化する
  Timer1.initialize(500000);
  // タイマにコールバック関数を設定する
  Timer1.attachInterrupt(callback);
}

// メインループ
void loop() {
  // ボタンの状態を取得する
  int button_state = digitalRead(BUTTON);

  // ボタンの状態が以前の状態と異なり、かつ、ボタンが押されている場合
  if (prev_button_state != button_state && button_state == HIGH) {
    // 増分を切り替える
    if (delta == 1) {
      delta = 59; // mod 60 しているので、事実上 -1
    } else {
      delta = 1;
    }
  }

  // 現在のボタンの状態を保存する
  prev_button_state = button_state;

  // 10 の位を表示する
  digitWrite(FIGURE_1, digit / 10, point);
  delay(10);

  // 1 の位を表示する（小数点は 10 の位の状態と ON/OFF を反対にする）
  digitWrite(FIGURE_2, digit % 10, !point);
  delay(10);
}
