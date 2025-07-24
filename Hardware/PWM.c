#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "sys.h" 
/**********************
PWM���ú�����
��ע��TIM1ΪPWM�����
**********************/
void PWMFOC_Init(void)
{
	//PWM�����ų�ʼ��(PA8,9,10)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��RCC����GPIOʱ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHZ�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//���ö�ʱ������
	TIM_InternalClockConfig(TIM1);//TIM1ʹ���ڲ�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//APB2�����е�TIM1��Ϊʹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ�ӷ�ƵΪ1��Ƶ->Ӱ���˲���
	//TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//����Ϊ���ϼ���
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInitStructure.TIM_Period=3600-1;//�Զ���װ��ARR��ֵ 0<ARR<65535 ��**��
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1;//Ԥ��Ƶ��PSC��ֵ 0<PSC<65535��**��
	/*�˴�ΪƵ��8K*/
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);//��ʼ��ʱ����Ԫ
	
	
	//����PWM���������
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//��������Ƚ�ģʽΪPWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//REF��Чʱ������ߵ�ƽ(��Ч��ƽΪ�ߵ�ƽ)
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//����Ϊʹ��
	TIM_OCInitStructure.TIM_Pulse=0;//���á�CCR������ȽϼĴ���ֵ��**��
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//��Ϊ��TIM1��OC1ͨ��-PA8�����PWM����*��
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);//��Ϊ��TIM1��OC2ͨ��-PA9�����PWM����*��
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);//��Ϊ��TIM1��OC3ͨ��-PA10�����PWM����*��
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//�߼���ʱ��ר��--MOE�����ʹ��
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//OC1Ԥװ�ؼĴ���ʹ��
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);//OC2Ԥװ�ؼĴ���ʹ��
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);//OC3Ԥװ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(TIM1,ENABLE);//TIM1��ARR��Ԥװ�ؼĴ���ʹ��
	
	TIM_Cmd(TIM1,ENABLE);//������ʱ��1	
}

void PWM_SetCompare1(uint16_t Compare)//д��TIM1ͨ��1��CCR(ռ�ձ�)
{
	TIM_SetCompare1(TIM1,Compare);
}
void PWM_SetCompare2(uint16_t Compare)//д��TIM1ͨ��2��CCR(ռ�ձ�)
{
	TIM_SetCompare2(TIM1,Compare);
}
void PWM_SetCompare3(uint16_t Compare)//д��TIM1ͨ��3��CCR(ռ�ձ�)
{
	TIM_SetCompare3(TIM1,Compare);
}


void PWM_SetCompare4(uint16_t Compare)//д��TIM1ͨ��4��CCR(ռ�ձ�)
{
	TIM_SetCompare4(TIM1,Compare);
}
