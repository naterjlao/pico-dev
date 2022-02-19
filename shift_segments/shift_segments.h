#ifndef _SEGMENT_DECODER_H_
#define _SEGMENT_DECODER_H_

const unsigned char HEX_SEGMENT_LOOKUP[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73};
const unsigned char SHIFT_REG_MAPPING[] = {0x20, 0x4, 0x8, 0x80, 0x2, 0x40, 0x10, 0x1};

#if 0
const uint LED_PIN_A = 14; 
const uint LED_PIN_B = 10;
const uint LED_PIN_C = 19;
const uint LED_PIN_D = 17;
const uint LED_PIN_E = 16;
const uint LED_PIN_F = 13;
const uint LED_PIN_G = 20;
const uint LED_PIN_DP = 18;
const uint LED_PIN_COLON = 9;

const uint LED_PIN_A_MASK = 0x1 << 6;
const uint LED_PIN_B_MASK = 0x1 << 5;
const uint LED_PIN_C_MASK = 0x1 << 4;
const uint LED_PIN_D_MASK = 0x1 << 3;
const uint LED_PIN_E_MASK = 0x1 << 2;
const uint LED_PIN_F_MASK = 0x1 << 1;
const uint LED_PIN_G_MASK = 0x1 << 0;
const uint LED_PIN_DP_MASK = 0x1 << 7;

const unsigned char HEX_SEGMENT_LOOKUP[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73};
const size_t HEX_SEGMENT_LOOKUP_LEN = sizeof(HEX_SEGMENT_LOOKUP) / sizeof(unsigned char);

const uint DIGIT_SOURCE[] = {15, 12, 11, 21};
const size_t DIGIT_SOURCE_LEN = sizeof(DIGIT_SOURCE) / sizeof(uint);
const uint COLON_SOURCE = 22;

#endif
#endif