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
#include "judge.h"

uint16_t ret=0,aa=0;//ָ�Ʒ���ֵ
int diretion=0;
uint16_t key_num=0;//����ң�ط���ֵ
unsigned int counter_1=0,counter_2=0;
unsigned int Counter=0,Compare=20;

int main(void)
{		
	//��ʼ������gpio
	gpio_init();
  Timer4_Init();
	//�����ʼ��
	Remote_Init();
///////////////////////
  Timer6_Init();
	extern const u8 BMP1[];
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	usart3_init(57600);

																										
	OLED_Init();
	OLED_Clear();
	OLED_ShowCH(0,0,"ָ��ģ����Գ���");
	OLED_ShowCH(16,2,"K1�����ָ��");
	OLED_ShowCH(16,4,"K3��ɾ��ָ��");
	OLED_ShowCH(16,6,"K5����ָ֤��");

	while(1)
	{																												
		delay_ms(100);
		key_num=Remote_Scan();//�ɼ����ⷵ��ֵ
		delay_ms(100);
		//�����ж�
		judge();	
	}
}

void TIM6_IRQHandler(void)
{
	
	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

		
	if(diretion>0)
	{
		 GPIO_SetBits(GPIOC,GPIO_Pin_0);					//PB.5 �����
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		 GPIO_SetBits(GPIOC,GPIO_Pin_4);					//PB.5 �����
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		counter_1++;
	}
	else
  {

		GPIO_SetBits(GPIOC,GPIO_Pin_1);					//PB.5 �����
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);					//PB.5 �����
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		if(counter_1>0)counter_1--;
	}
	Counter%=100;	//??????????0~99
	if(Counter<Compare)	//????????
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_2);	
		GPIO_SetBits(GPIOC,GPIO_Pin_6);	
		PAin(8)=1;
	}
	else				//????????
	{
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		PAin(8)=0;
	}
	if(counter_1<100000)Counter++;	
	
	
  
	if(diretion<0 && counter_1==0)
  {	
	  TIM_Cmd(TIM6, DISABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  }
	if(diretion>0 && counter_1==100000)
  {	
	  TIM_Cmd(TIM6, DISABLE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  }
	
//TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}
}
void TIM4_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
			
			counter_2%=60000;
			if(counter_2<30000)
			{
				counter_2++;
			}
			if(counter_2==30000)
			{
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			}
			}
}
