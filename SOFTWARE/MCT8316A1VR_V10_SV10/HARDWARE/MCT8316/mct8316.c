#include "mct8316.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini�SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
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
	
//����MCT8316
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

//��MCT8316ָ����ַ����һ��32λ����,��CRCУ��
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u32 MCT8316_Read32bit(u8 Addr)
{				  
	u8 temp=0;
	u16 i = 0;
	u32 data = 0;
	
    IIC_Start();
	IIC_Send_Byte(0X00);   		//����������ַ0XC0 
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte(0X90);   		//���͵͵�ַ
	IIC_Wait_Ack();
	delay_us(100);
    IIC_Send_Byte(0X00);   		//���͵͵�ַ
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte(Addr);   	//���͵�ַ
	IIC_Wait_Ack();
	delay_us(100);
	
	IIC_Start();  
	IIC_Send_Byte(0X01);      	//�������ģʽ
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
	
    IIC_Stop();//����һ��ֹͣ����	    
	
	return data;
}
//��MCT8316ָ����ַдһ��32λ����,��CRCУ��
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
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
    IIC_Send_Byte(Addr);   		//���͵�ַ			   	 
	IIC_Wait_Ack(); 
	delay_us(100);
	IIC_Send_Byte((uint8_t)Value);   			//���ͷ���DB0 
	IIC_Wait_Ack();
	delay_us(100);	
    IIC_Send_Byte((uint8_t)(Value >> 8));   	//����DB1
	IIC_Wait_Ack();
	delay_us(100);
	IIC_Send_Byte((uint8_t)(Value >> 16));   	//����DB2
	IIC_Wait_Ack();
	delay_us(100);	
	IIC_Send_Byte((uint8_t)(Value >> 24));   	//����DB3
	IIC_Wait_Ack();
	delay_us(100);
	
    IIC_Stop();//����һ��ֹͣ����	    
	
	return data;
}




