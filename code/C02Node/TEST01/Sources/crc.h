#ifndef 	__CRC_H
#define 	__CRC_H
#include "IO_Map.h"



void init_crc16(void) ;
void crc16_byte(uint8_t ch) ;
uint16_t crc16(uint8_t *p, uint8_t length);


extern uint8_t CRClo ;
extern uint8_t CRChi ;
#endif 
