#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "mct8316.h"
#include "TMP75.h"
#include "usmart.h"
#include "dac.h"
#include "myiic.h"
/*	ALIENTEK Mini STM32开发板范例代码12
	USMART调试组件实验  
	技术支持：www.openedv.com
	广州市星翼电子科技有限公司 	*/
 
//LED状态设置函数
void led_set(u8 sta){
	LED0=sta;
} 
//函数参数调用测试函数
void test_fun(void(*ledset)(u8),u8 sta){
	ledset(sta);
}  	
int main(void){ 
//	u32 value;
//	float temp;
//    u16 arr;	
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
    Adc_Init();		  		//ADC初始化
	LED_Init();				//初始化与LED连接的硬件接口
	Dac2_Init();
	Dac2_Set_Vol(1000);
//	MCT8316_Init();
	tmp75_Init();

	usmart_dev.init(72); 	//初始化USMART

//	MCT8316_Write32bit(0XE6, 0X40000000);
//	delay_ms(100);	
//	printf("ISD_CONFIG VALUE: 0x%x \r", MCT8316_Read32bit(ISD_CONFIG_ADDR));	
	while(1){
		printf("TMP75 VALUE: %f \r", tmp75_read_temp());
		delay_ms(1000);
	}
}	



