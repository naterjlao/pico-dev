#ifndef _SEGMENT_DECODER_H_
#define _SEGMENT_DECODER_H_

const uint LED_PIN_A = 11; 
const uint LED_PIN_B = 10;
const uint LED_PIN_C = 20;
const uint LED_PIN_D = 19;
const uint LED_PIN_E = 18;
const uint LED_PIN_F = 12;
const uint LED_PIN_G = 13;
const uint LED_PIN_DP = 21;

const uint LED_PIN_A_MASK = 0x1 << 6;
const uint LED_PIN_B_MASK = 0x1 << 5;
const uint LED_PIN_C_MASK = 0x1 << 4;
const uint LED_PIN_D_MASK = 0x1 << 3;
const uint LED_PIN_E_MASK = 0x1 << 2;
const uint LED_PIN_F_MASK = 0x1 << 1;
const uint LED_PIN_G_MASK = 0x1 << 0;
const uint LED_PIN_DP_MASK = 0x1 << 7;

const unsigned char HEX_SEGMENT_LOOKUP[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73};

#endif