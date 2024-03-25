#include "stm32f10x.h"                  // Device header

//void Timer6_Init(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//����tim2��ʱ��
////RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//����gpio��ʱ��
//	
//	
////	//gpioa��ʼ���ṹ��
////	/*********************************/
////	GPIO_InitTypeDef GPIO_InitStructure;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);
////	/****************************/
//	TIM_InternalClockConfig(TIM6);
//	
//	
//	//��ʼ��ʱ����Ԫ
//	/*****************************/
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
//	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARRĿ��
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//PSC��Ƶ
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�߼���ʱ���Ĺ���
//	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
//	/***********************************/
//	
//	//��ʼ������
////	/***************************************/
////	TIM_OCInitTypeDef TIM_OCInitStructure;
////	TIM_OCStructInit(&TIM_OCInitStructure);
////	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//pwmģʽ1
////	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��
////	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ��
////	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
////	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
////	/*********************/
//	//TIM_Cmd(TIM2, ENABLE);//ʹ��
//}

////void PWM_SetCompare3(uint16_t Compare)
////{
////	TIM_SetCompare3(TIM2, Compare);
////}











void Timer6_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_InternalClockConfig(TIM6);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36-1;
	//TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/////////////////NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
//TIM_Cmd(TIM6, ENABLE);  
}




//void Timer6_Init()
//{
//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = 5000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =7200-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����//}
//}





//void PWM_Init(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//����tim2��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//����gpio��ʱ��
//	
//	
//	//gpioa��ʼ���ṹ��
//	/*********************************/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	/****************************/
//	TIM_InternalClockConfig(TIM4);
//	
//	
//	//��ʼ��ʱ����Ԫ
//	/*****************************/
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
//	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARRĿ��
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//PSC��Ƶ
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�߼���ʱ���Ĺ���
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
//	/***********************************/
//	
//	//��ʼ������
//	/***************************************/
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//pwmģʽ1
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
//	/*********************/
//	TIM_Cmd(TIM2, ENABLE);//ʹ��
//}

//void PWM_SetCompare3(uint16_t Compare)
//{
//	TIM_SetCompare3(TIM2, Compare);
//}
