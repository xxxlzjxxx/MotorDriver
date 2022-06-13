#ifndef __TMP75_H
#define __TMP75_H	 
#include "sys.h"
#include "myiic.h"


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

void tmp75_Init(void);//≥ı ºªØ
float tmp75_read_temp(void);

		 				    
#endif



