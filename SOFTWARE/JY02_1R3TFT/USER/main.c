#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "adc.h"
#include "led.h"
#include "key.h"


int main(void)
{	
	u8 i,m;
	float t = 0;
	float adcx = 0;
	char aa[6];


	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	uart_init(115200);
	Adc_Init();

	Lcd_Init();			//初始化OLED  
	LCD_Clear(WHITE);
	BACK_COLOR=WHITE;
//显示开机画面
	LCD_ShowString(8,10, "---------BLD25-24GN----------", BLACK);
	
	LCD_Fill(0,30,0+240,30+9,BLACK);
	
	LCD_ShowString(10,40, "HALL     : ", DARKBLUE);
	LCD_ShowString(10,60, "MAX SPEED:     RPM", DARKBLUE);
	LCD_ShowString(10,80, "MAX WATT :     W  ", DARKBLUE);
	
	LCD_Fill(0,100,0+240,100+9,BLACK);
	LCD_ShowString(10,118,"TEST	    :     !!!", RED);
	LCD_Fill(0,140,0+240,140+9,BLACK);
	
	LCD_ShowString(10,170,"Press SW2 to Start Test", BLACK);
	
	LCD_Fill(0,200,0+240,200+9,BLACK);
	LCD_ShowString(10,220, "VOLT:     V", BLUE);
	LCD_ShowString(140,220,"CURR:     A", BLUE);

	while(1){
		adcx = Get_Adc_Average(ADC_Channel_11,10);	//work_volt
		adcx = adcx * 11;
		sprintf(aa,"%2.3f",adcx);//浮点型数据转为指定格式的字符串
		LCD_ShowString(10+5*8, 220, aa, BLUE);

		adcx = Get_Adc_Average(ADC_Channel_10,10);	//work_curr
		adcx = (adcx - 1.65) * 0.132;
		sprintf(aa,"%2.3f",adcx);//浮点型数据转为指定格式的字符串
		LCD_ShowString(140+5*8, 220, aa, BLUE);
		
		delay_ms(300);
	}
}
 





