#include "TMP75.h"
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
void tmp75_Init(void)
{	
	IIC_Init();
}

//��MCT8316ָ����ַ����һ��32λ����,��CRCУ��
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
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
//    if(TempCode & 0x200)  //���¶�
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



