#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "bsp_drv8711.h"
#include "usmart.h"
//ALIENTEK Mini STM32开发板范例代码12
//USMART调试组件实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 
//LED状态设置函数
void led_set(u8 sta){
	LED1=sta;
} 
//函数参数调用测试函数
void test_fun(void(*ledset)(u8),u8 sta){
	ledset(sta);
}  	
int main(void){ 
	u16 adcx;
	float temp;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
    Adc_Init();		  		//ADC初始化
	LED_Init();				//初始化与LED连接的硬件接口
	TIM3_Int_Init(50-1,7200-1);//10Khz的计数频率，计数到5000为500ms 
	usmart_dev.init(72); 	//初始化USMART				 		   
  	while(1) {		 	  
		adcx=Get_Adc_Average(ADC_Channel_14, 10);
		printf(">>ADC VALUE: %d \n\r", adcx);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
        printf(">>VOL VALUE: %0.4f \n\r", temp);//显示ADC的值
		LED0=!LED0;
		delay_ms(500);	
	}											    
}	



