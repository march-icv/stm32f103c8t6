#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
uint8_t MyI2C_RANK(void);
void MyI2C_SANK(uint8_t temp);
void MyI2C_SendByte(uint8_t byte);
uint8_t MyI2C_ReByte(void);

#endif
