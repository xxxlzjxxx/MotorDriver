#include "mct8316.h"
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
void MCT8316_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				 
	GPIO_Init(GPIOA, &GPIO_InitStructure);					

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				 
	GPIO_Init(GPIOC, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
//配置MCT8316
	MCT8316_DRVOFF 	= 0;
	MCT8316_DIR		= 0;
	MCT8316_BRAKE	= 0;
	
	IIC_Init();
	
//	MCT8316_Write32bit(ISD_CONFIG_ADDR, 	0X6F04C100);
//	MCT8316_Write32bit(MOTOR_STARTUP1_ADDR, 0X38C8D197);
//	MCT8316_Write32bit(MOTOR_STARTUP2_ADDR, 0X1A399990);
//	MCT8316_Write32bit(CLOSED_LOOP1_ADDR,	0X11466200);
//	MCT8316_Write32bit(CLOSED_LOOP2_ADDR, 	0X02A6E4B0);
//	MCT8316_Write32bit(CLOSED_LOOP3_ADDR, 	0X4CC40101);
//	MCT8316_Write32bit(CLOSED_LOOP4_ADDR, 	0X000CE944);
//	MCT8316_Write32bit(CONST_SPEED_ADDR, 	0X00A00504);
//	MCT8316_Write32bit(CONST_PWR_ADDR, 		0X5DC04C84);
//	MCT8316_Write32bit(PROFILE_150_DEG_TWO_ADDR,   0X36DB6DA6);
//	MCT8316_Write32bit(PROFILE_150_DEG_THREE_ADDR, 0X36DB6D80);
//	MCT8316_Write32bit(TRAP_CONFIG1_ADDR, 0X054BA106);
//	MCT8316_Write32bit(TRAP_CONFIG2_ADDR, 0X2A880000);
//	MCT8316_Write32bit(FAULT_CONFIG1_ADDR, 0X78F43025);
//	MCT8316_Write32bit(FAULT_CONFIG2_ADDR, 0X7947A009);
//	MCT8316_Write32bit(GD_CONFIG1_ADDR, 0X1C440000);
//	MCT8316_Write32bit(GD_CONFIG2_ADDR, 0X14000000);
//	MCT8316_Write32bit(PIN_CONFIG1_ADDR, 0X2D720600);
//	MCT8316_Write32bit(PIN_CONFIG2_ADDR, 0X080C0000);
//	MCT8316_Write32bit(DEVICE_CONFIG_ADDR, 0X7FFF0000);
//	MCT8316_Write32bit(PERI_CONFIG_ADDR, 0X00000000);
	
//	MCT8316_Write32bit(0xE6, 0x80000000);
//	
//	delay_ms(100);
}

//在MCT8316指定地址读出一个32位数据,无CRC校验
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u32 MCT8316_Read32bit(u8 Addr)
{				  
	u8 temp=0;
	u16 i = 0;
	u32 data = 0;
	
    IIC_Start();
	IIC_Send_Byte(0X00);   		//发送器件地址0XC0 
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte(0X90);   		//发送低地址
	IIC_Wait_Ack();
	delay_us(100);
    IIC_Send_Byte(0X00);   		//发送低地址
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte(Addr);   	//发送地址
	IIC_Wait_Ack();
	delay_us(100);
	
	IIC_Start();  
	IIC_Send_Byte(0X01);      	//进入接收模式
	IIC_Wait_Ack();
	delay_us(100);
	
    temp = IIC_Read_Byte(1);
	data = temp | data;					//byte0
	delay_us(100);
	
    temp = IIC_Read_Byte(1);
	data = ((u32)temp << 8) | data;		//byte1
	delay_us(100);
	
    temp = IIC_Read_Byte(1);
	data = ((u32)temp << 16) | data;	//byte2
	delay_us(100);
	
    temp = IIC_Read_Byte(1);
	data = ((u32)temp << 24) | data;	//byte3
	delay_us(100);
	
    IIC_Stop();//产生一个停止条件	    
	
	return data;
}
//在MCT8316指定地址写一个32位数据,无CRC校验
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u32 MCT8316_Write32bit(u8 Addr, uint32_t Value)
{				  
	u8 temp=0;
	u32 data = 0;
	
    IIC_Start(); 
	IIC_Send_Byte(0X00);   		
	IIC_Wait_Ack();
	delay_us(100);
    IIC_Send_Byte(0X10);   		
	IIC_Wait_Ack();
	delay_us(100);
    IIC_Send_Byte(0X00);   		
	IIC_Wait_Ack();
	delay_us(100);
    IIC_Send_Byte(Addr);   		//发送地址			   	 
	IIC_Wait_Ack(); 
	delay_us(100);
	IIC_Send_Byte((uint8_t)Value);   			//发送发送DB0 
	IIC_Wait_Ack();
	delay_us(100);	
    IIC_Send_Byte((uint8_t)(Value >> 8));   	//发送DB1
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte((uint8_t)(Value >> 16));   	//发送DB2
	IIC_Wait_Ack();
	delay_us(100);	
	IIC_Send_Byte((uint8_t)(Value >> 24));   	//发送DB3
	IIC_Wait_Ack();
	delay_us(100);
	
    IIC_Stop();//产生一个停止条件	    
	
	return data;
}




