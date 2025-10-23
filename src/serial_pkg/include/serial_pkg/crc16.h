#ifndef __CRC16_H_
#define __CRC16_H_

#include <stdint.h>


extern const uint16_t CRC16_table[256];   // 在头文件仅声明
uint16_t Get_CRC16(uint8_t *ptr, uint16_t len);
uint16_t CRC16_Check(const uint8_t *data, uint8_t len);

#endif