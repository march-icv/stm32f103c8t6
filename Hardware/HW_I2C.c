#include "stm32f10x.h"                  // Device header

void HW_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	GPIO_InitTypeDef I2CPort_Structure;
	I2CPort_Structure.GPIO_Mode =GPIO_Mode_AF_OD;
	I2CPort_Structure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	I2CPort_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&I2CPort_Structure);
	
	I2C_InitTypeDef I2C_Structure;
	I2C_Structure.I2C_Ack = I2C_Ack_Enable;
	I2C_Structure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Structure.I2C_ClockSpeed = 50000;
	I2C_Structure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Structure.I2C_Mode = I2C_Mode_I2C;
	I2C_Structure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2,&I2C_Structure);
	I2C_Cmd(I2C2, ENABLE);
}

