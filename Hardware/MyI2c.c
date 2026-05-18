#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MyI2C_Setting.h"


void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(MyI2C_Rcc_Port, ENABLE);
	
	GPIO_InitTypeDef MyI2C_Structure;
	MyI2C_Structure.GPIO_Mode = GPIO_Mode_Out_OD;
	MyI2C_Structure.GPIO_Pin = SCL_PIN | SDA_PIN;
	MyI2C_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MyI2C_Port,&MyI2C_Structure);
	
	GPIO_SetBits(MyI2C_Port,SCL_PIN | SDA_PIN);
}

void SCL_W(uint8_t level)
{
	if(level == 0) GPIO_ResetBits(MyI2C_Port,SCL_PIN);
	else GPIO_SetBits(MyI2C_Port, SCL_PIN);
	Delay_us(5);
}
void SDA_W(uint8_t level)
{
	if(level == 0) GPIO_ResetBits(MyI2C_Port,SDA_PIN);
	else GPIO_SetBits(MyI2C_Port, SDA_PIN);
	Delay_us(5);
}
uint8_t SDA_R(void)
{
	return (!!(GPIO_ReadInputDataBit(MyI2C_Port,SDA_PIN)));
}

void MyI2C_Start(void)
{
	SDA_W(1);
	SCL_W(1);
	SDA_W(0);
	SCL_W(0);
}	
void MyI2C_Stop(void)
{
	SDA_W(0);
	SCL_W(1);
	SDA_W(1);
}
uint8_t MyI2C_RANK(void)
{
	uint8_t temp;
	SDA_W(1);
	temp=!!(SDA_R());
	SCL_W(1);
	SCL_W(0);
	return temp;
}

void MyI2C_SANK(uint8_t temp)
{
	SDA_W(!!(temp));
	SCL_W(1);
	SCL_W(0);
}
void MyI2C_SendByte(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SDA_W(!!(byte&(0X80>>i)));
		SCL_W(1);
		SCL_W(0);
	}
}

uint8_t MyI2C_ReByte(void)
{
	uint8_t i,RD=0x00;
	SDA_W(1);
	for(i=0;i<8;i++)
	{
		SCL_W(1);
		if(SDA_R()== 1) RD |= (0x80>>i);
		SCL_W(0);
	}
	return RD;
}	
