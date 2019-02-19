#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "bsp_drv8711.h"
#include "usmart.h"
//ALIENTEK Mini STM32�����巶������12
//USMART�������ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 
//LED״̬���ú���
void led_set(u8 sta){
	LED1=sta;
} 
//�����������ò��Ժ���
void test_fun(void(*ledset)(u8),u8 sta){
	ledset(sta);
}  	
int main(void){ 
	u16 adcx;
	float temp;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
    Adc_Init();		  		//ADC��ʼ��
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM3_Int_Init(50-1,7200-1);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	usmart_dev.init(72); 	//��ʼ��USMART				 		   
  	while(1) {		 	  
		adcx=Get_Adc_Average(ADC_Channel_14, 10);
		printf(">>ADC VALUE: %d \n\r", adcx);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
        printf(">>VOL VALUE: %0.4f \n\r", temp);//��ʾADC��ֵ
		LED0=!LED0;
		delay_ms(500);	
	}											    
}	



