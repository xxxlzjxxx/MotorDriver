#ifndef __TB67_H
#define __TB67_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define TB67_CLK 		PAout(5)	
#define TB67_DMODE0 	PBout(1)	
#define TB67_DMODE1 	PBout(10)	
#define TB67_DMODE2 	PBout(11)
#define TB67_VREF 		PAout(4)
#define TB67_DIR 		PAout(3)	
#define TB67_ENABLE_H 	PAout(7)	
#define TB67_RESET_L 	PBout(0)	
#define TB67_MO 		PAin(6)		//��Ƕȼ�������
#define TB67_FAULT 		PAin(2)		//����������,�ȹض�/�����ض�

void TB67_Init(void);//��ʼ��
		 				    
#endif



