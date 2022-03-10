#ifndef __TB67_H
#define __TB67_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
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
#define TB67_MO 		PAin(6)		//电角度监视引脚
#define TB67_FAULT 		PAin(2)		//报错反馈引脚,热关断/过流关断

void TB67_Init(void);//初始化
		 				    
#endif



