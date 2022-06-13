#include "TMP75.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void tmp75_Init(void)
{	
	IIC_Init();
}

//在MCT8316指定地址读出一个32位数据,无CRC校验
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
float tmp75_read_temp(void)
{
    unsigned short TempH    = 0;
    unsigned short TempL    = 0;
    unsigned short TempCode = 0;
    float   	   temp     = 0.0;

    IIC_Start();
    IIC_Send_Byte(0x9E);
    IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
    IIC_Send_Byte(0x9F);
    IIC_Wait_Ack();
    TempH = IIC_Read_Byte(1);
    TempL = IIC_Read_Byte(1);
    IIC_Stop();
	
    TempCode = ((TempH << 8) | TempL) >> 4;
	
	temp = 128 * (2047 - TempCode);
//    if(TempCode & 0x200)  //负温度
//    {
//      TempCode &= 0x1ff;
//      temp = ((float)TempCode - 512) / 4;
//    }
//    else
//    {
//      temp = (float)TempCode / 4;
//    } 
	
    IIC_SCL = 0;
    IIC_SDA = 0; 
	
    return (temp);
}



