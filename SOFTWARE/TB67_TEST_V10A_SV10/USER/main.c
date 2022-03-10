#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "tb67.h"
#include "usmart.h"
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
	u16 adcx;
	float temp;
    u16 arr;	
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
    Adc_Init();		  		//ADC初始化
	LED_Init();				//初始化与LED连接的硬件接口
	TB67_Init();

	usmart_dev.init(72); 	//初始化USMART
	
  	while(1) {		 	  
		adcx = Get_Adc_Average(ADC_Channel_1,10);
		arr = 50 - ((float)(45 * adcx)/4096);
		TIM3_Int_Init(arr-1,72-1);//设置为50K~100K频率，arr的值在5~50之间
		
		LED0=!LED0;
		delay_ms(500);	
	}											    
}	



