#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "beep.h"
#include "timer.h"
#include "sram.h"
#include "touch.h" 
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
//#include "lv_kb_test.h"
#include "lv_calendar.h"
#include "rtc.h"


	
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	usmart_dev.init(84); 	//��ʼ��USMART
	My_RTC_Init();		 		//��ʼ��RTC
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	BEEP_Init();				//��������ʼ��
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//����WAKE UP�ж�,1�����ж�һ��

	TIM3_Int_Init(999,83);	//��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ1ms����������
	FSMC_SRAM_Init();		//��ʼ���ⲿsram
	tp_dev.init();			//��������ʼ��

	lv_init();						//lvglϵͳ��ʼ��
	lv_port_disp_init();	//lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	lv_port_indev_init();	//lvgl����ӿڳ�ʼ��,����lv_init()�ĺ���
	
	
	lv_calendar_start();
	
	
	
	
	while(1)
	{
		get_time();
		tp_dev.scan(0);//����ɨ��
		lv_task_handler();//lvgl������ 
		
	}
}