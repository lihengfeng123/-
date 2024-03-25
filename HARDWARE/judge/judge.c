#include "sys.h"
#include "delay.h"
#include "oled_iic.h"
#include "stdio.h"
#include "timer.h"
#include "as608.h"
#include "usart3.h"
#include "PWM.h"
#include "remote.h"
#include "timer4.h"
#include "gpio.h"
//#include "judge.h"

extern uint16_t ret,aa;//ָ�Ʒ���ֵ
extern int diretion;
extern uint16_t key_num;//����ң�ط���ֵ
extern uint32_t counter_1,counter_2;
extern unsigned int Counter,Compare;

//uint16_t ret=0,aa=0;//ָ�Ʒ���ֵ
//int diretion=0;
//uint16_t key_num=0;//����ң�ط���ֵ
//uint32_t counter_1=0,counter_2=0;
//unsigned int Counter=0,Compare=20;

int decied(void);

void judge(void){
if(key_num==104)//1����ָ��
		{
			int temp=0;
			temp = decied();
			if(temp==0)//�ж�
			{
				key_num=0;

						Add_FR();
						GPIO_SetBits(GPIOA,GPIO_Pin_8);
			
						key_num=0;

			}
			else {
				
			OLED_Clear();
			OLED_ShowCH(0,2,"fail");
			
			key_num=Remote_Scan();
			while(key_num!=144);
			key_num=0;	
			}
		}
		
		
		
	if(key_num==152)//2��ָ֤��
		{			
			OLED_Clear();
			OLED_ShowCH(32,2,"�밴��ָ");
			press_FR();
			if(ret==1)
			{
				//TIM_Cmd(TIM6, ENABLE);
				ret=0;
			}
		key_num=0;
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		}
		
		
	if(key_num==24)//5ɾ��ָ��
			
		{
		 OLED_Clear();
			Del_FR();
			key_num=0;
		}
			
		
	if(PCin(10)==1 && key_num==0 && counter_1==0)//�����Ҳ�������ָ����ɾ��ָ��
	{
		  OLED_Clear();
			OLED_ShowCH(32,2,"�밴��ָ");
			press_FR();
		if(ret==1)
		{
			
			diretion = 1;
		
			TIM_Cmd(TIM6, ENABLE);
			ret=0;
		}
	}
	
	if((counter_1<=100000&&key_num==82)||(PBin(8)==1))//���û���յ㰴������
	{
		key_num=0;
		diretion=-1;
		TIM_Cmd(TIM6, ENABLE);
		
	}
	
	
	if(counter_1==100000&&diretion>0)//�����Ƿ��յ�
	{
	
		if(counter_2==0)
			{
			TIM_Cmd(TIM4, ENABLE);
			}    //��ʼ��ʱ
		if(counter_2==30000)//��ʱһ�������˲���
		{
			counter_2=0;
			diretion=-1;
			TIM_Cmd(TIM4, DISABLE);		
			TIM_Cmd(TIM6, ENABLE);
			
		}
		if(key_num==82)//�˸������
		{
			key_num=0;
			counter_2=0;
			diretion=-1;
			TIM_Cmd(TIM4, DISABLE);		
			TIM_Cmd(TIM6, ENABLE);
		}
	}
	if(counter_1==0&&diretion<0)//�����Ƿ�ص��յ�
	{
		TIM_Cmd(TIM6, DISABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	}
}

int decied(void)
{
			int temp=0;

			OLED_Clear();
			OLED_ShowCH(0,2,"please enter");
			key_num=0;
			
			delay_ms(500);
			while(1){
			key_num=Remote_Scan();
			if(key_num!=0)break;}
			delay_ms(500);
			if(key_num!=104)
				temp=1;
			OLED_Clear();
			OLED_ShowCH(0,4,"*");
			key_num=0;
			
			delay_ms(500);
			while(1){
			key_num=Remote_Scan();
			if(key_num!=0)break;}
			delay_ms(500);
			if(key_num!=104)
				temp=1;
			OLED_Clear();
			OLED_ShowCH(0,4,"**");
			key_num=0;
			
			delay_ms(500);
			while(1){
			key_num=Remote_Scan();
			if(key_num!=0)break;}
			delay_ms(500);
			if(key_num!=104)
				temp=1;
			OLED_Clear();
			OLED_ShowCH(0,4,"***");//����111
			key_num=0;
			
			return temp;
	
}

