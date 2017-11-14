// C-552SR-NW-A G/W
//
// see http://akizukidenshi.com/catalog/g/gI-00215/
//
// DIG.1      DIG.2
// +-A-+      +-A-+
// F   B      F   B
// +-G-+      +-G-+
// E   C      E   C
// +-D-+ .DP  +-D-+ .DP

// 1 DIG.1 E    18 DIG.1 F
// 2 DIG.1 D    17 DIG.1 G
// 3 DIG.1 C    16 DIG.1 A
// 4 DIG.1 DP   15 DIG.1 B
// 5 DIG.2 E    14 DIG.1 GND
// 6 DIG.2 D    13 DIG.2 GND
// 7 DIG.2 G    12 DIG.2 F
// 8 DIG.2 C    11 DIG.2 A
// 9 DIG.2 DP   10 DIG.2 B

#ifndef __DIGIT_H__
#define __DIGIT_H__

static const byte FIGURE_1 = 1; // left digit
static const byte FIGURE_2 = 2; // right digit

void digitInit();
void digitWrite(byte figure, int digit, boolean point);
void digitWriteSegments(byte figure, byte segments);

#endif//__DIGIT_H__

