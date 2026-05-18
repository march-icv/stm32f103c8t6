#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
	int16_t data[7];
	OLED_Init();
	MPU6050_Init();
	OLED_ShowHexNum(1,1,MPU6050_Read_Reg(MPU6050_WHO_AM_I),2);
	while(1)
	{
		MPU6050_Re_Data(data);
		OLED_ShowSignedNum(1,5,data[3],5);
		OLED_ShowSignedNum(2,1,data[0],5);
		OLED_ShowSignedNum(3,1,data[1],5);
		OLED_ShowSignedNum(4,1,data[2],5);
		OLED_ShowSignedNum(2,9,data[4],5);
		OLED_ShowSignedNum(3,9,data[5],5);
		OLED_ShowSignedNum(4,9,data[6],5);
	}
}
