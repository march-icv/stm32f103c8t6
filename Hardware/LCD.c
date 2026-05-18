#include "stm32f10x.h"                  // Device header
#include "LCD_Font.h"

void Gui_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) >= 128) 
		{		
			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	PutPixel(x+j,y+i,fc);
								else {
									if (fc!=bc) PutPixel(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	PutPixel(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) PutPixel(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		}
		else
		s+=1; 
		
	}
}
