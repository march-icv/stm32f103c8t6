#ifndef MPU6050_H
#define MPU6050_H

#include "MPU6050_Reg.h"

void MPU6050_Init(void);
void MPU6050_Send_Reg(uint8_t Reg, uint8_t Byte);
uint8_t MPU6050_Read_Reg(uint8_t Byte);
void MPU6050_Re_Data(int16_t data[7]);

#endif
