#ifndef __MCT8316_H
#define __MCT8316_H	 
#include "sys.h"
#include "myiic.h"

#define MCT8316_DRVOFF 		PDout(2)	
#define MCT8316_SPEED 		PAout(5)	
#define MCT8316_DIR 		PCout(10)
#define MCT8316_BRAKE 		PCout(11)	
#define MCT8316_FAULT 		PCin(12)		//报错反馈引脚,热关断/过流关断
#define MCT8316_FG			PAin(8)

//address
#define ISD_CONFIG_ADDR			0X80
#define MOTOR_STARTUP1_ADDR		0X82
#define MOTOR_STARTUP2_ADDR		0X84
#define CLOSED_LOOP1_ADDR		0X86
#define CLOSED_LOOP2_ADDR		0X88
#define CLOSED_LOOP3_ADDR		0X8A
#define CLOSED_LOOP4_ADDR		0X8C
#define CONST_SPEED_ADDR		0X8E
#define CONST_PWR_ADDR			0X90
#define PROFILE_150_DEG_TWO_ADDR	0X96
#define PROFILE_150_DEG_THREE_ADDR	0X98
#define TRAP_CONFIG1_ADDR		0X9A
#define TRAP_CONFIG2_ADDR		0X9C
#define FAULT_CONFIG1_ADDR		0X92
#define FAULT_CONFIG2_ADDR		0X94
#define GD_CONFIG1_ADDR			0XAC
#define GD_CONFIG2_ADDR			0XAE
#define PIN_CONFIG1_ADDR		0XA4
#define PIN_CONFIG2_ADDR		0XA6
#define DEVICE_CONFIG_ADDR		0XA8
#define PERI_CONFIG_ADDR		0XAA

void MCT8316_Init(void);//初始化
u32 MCT8316_Read32bit(u8 Addr);
u32 MCT8316_Write32bit(u8 Addr, uint32_t Value);
		 				    
#endif



