#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "HW_I2C.h"
void MPU6050_Send_Reg(uint8_t Reg, uint8_t Byte)
{
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_Slave_Address,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	I2C_SendData(I2C2,Reg);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	I2C_SendData(I2C2,Byte);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	I2C_GenerateSTOP(I2C2,ENABLE);
}
uint8_t MPU6050_Read_Reg(uint8_t Reg)
{
	uint8_t RRg;
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_Slave_Address,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	I2C_SendData(I2C2,Reg);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_Slave_Address,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	RRg=I2C_ReceiveData(I2C2);
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	return RRg;
}

void MPU6050_Init(void)
{
	HW_I2C_Init();
	MPU6050_Send_Reg(MPU6050_PWR_MGMT_1,0x01);
	MPU6050_Send_Reg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_Send_Reg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_Send_Reg(MPU6050_CONFIG,0x06);
	MPU6050_Send_Reg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_Send_Reg(MPU6050_ACCEL_CONFIG,0x18);
}

void MPU6050_Re_Data(int16_t data[7])
{
	uint8_t i;
	uint8_t temp[14];
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_Slave_Address,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	I2C_SendData(I2C2,MPU6050_ACCEL_XOUT_H);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_Slave_Address,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	for(i=0;i<14;i++)
	{
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
		temp[i]=I2C_ReceiveData(I2C2);
		if(i%2 == 1) data[i/2] = (temp[i-1]<<8) | temp[i];
		if(i==12){I2C_AcknowledgeConfig(I2C2,DISABLE);I2C_GenerateSTOP(I2C2,ENABLE);}
	}
	I2C_AcknowledgeConfig(I2C2,ENABLE);
}
