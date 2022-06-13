#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"


int main(void)
{	
	u8 i,m;
	float t=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	Lcd_Init();			//��ʼ��OLED  
	LCD_Clear(WHITE);
	BACK_COLOR=WHITE;
//��ʾ��������
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

	while(1);
}
 





