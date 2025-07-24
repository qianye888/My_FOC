#include "usart.h"	
#include <stdio.h>

int USAR_RxData;
uint8_t USAR_RxFlag;
uint8_t Receive_Flag;

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout; 
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
    USART3->DR = (u8) ch;      
	return ch;
}
#endif 

void uart1_init(u32 Baudrate)
{
	//���ô��ڲ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//����GPIOA9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����GPIOA10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baudrate;//���ò�����ΪBaudrate
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������-��ʹ������
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//����Ϊ����+����ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ��No��У��(��)  Odd��У��  EvenżУ��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ��1λֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ���8λ(��Ϊ�˳�������У��λ)
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����RXNE��־λ��NVIC�����
	
	USART_Cmd(USART1, ENABLE);//ʹ�ܴ��� 
}

void uart2_init(u32 Baudrate)
{
	//���ô��ڲ���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//����GPIOA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//����GPIOA10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baudrate;//���ò�����ΪBaudrate
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������-��ʹ������
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//����Ϊ����+����ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ��No��У��(��)  Odd��У��  EvenżУ��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ��1λֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ���8λ(��Ϊ�˳�������У��λ)
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//����RXNE��־λ��NVIC�����
	
	USART_Cmd(USART2, ENABLE);//ʹ�ܴ��� 
}


void uart3_init(u32 Baudrate)
{
	//���ô��ڲ���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����GPIOB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//����GPIOB11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baudrate;//���ò�����ΪBaudrate
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������-��ʹ������
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//����Ϊ����+����ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ��No��У��(��)  Odd��У��  EvenżУ��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ��1λֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ���8λ(��Ϊ�˳�������У��λ)
	USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//����RXNE��־λ��NVIC�����
	
	USART_Cmd(USART3, ENABLE);//ʹ�ܴ��� 
}
/*----------------------����Ϊ����(Txd)�йغ���-----------------------------*/

void USAR3_SendByte(uint8_t Byte)//��Tx���ŷ���һ���ֽ�����-(ֻ֧��16����������0x41='A')
{
	USART_SendData(USART3, Byte);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);//�ȴ����ݴ������
}

void USAR2_SendByte(uint8_t Byte)//��Tx���ŷ���һ���ֽ�����-(ֻ֧��16����������0x41='A')
{
	USART_SendData(USART2, Byte);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);//�ȴ����ݴ������
}

void USAR1_SendByte(uint8_t Byte)//��Tx���ŷ���һ���ֽ�����-(ֻ֧��16����������0x41='A')
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//�ȴ����ݴ������
}


void USAR_SendArray(uint8_t *Array, uint16_t Length)//��Tx���ŷ�����ǰ�������������� USAR_SendArray(Array,5)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		USAR2_SendByte(Array[i]);
	}
}

void USAR_SendString(char *String)//��Tx���ŷ����ַ���
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		USAR2_SendByte(String[i]);
	}
}

uint32_t USAR_Pow(uint32_t X, uint32_t Y)//��Tx���ŷ���һ������(����)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void USAR_SendNumber(uint32_t Number, uint8_t Length)//��Tx���ŷ���һ������
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		USAR2_SendByte(Number / USAR_Pow(10, Length - i - 1) % 10 + '0');
	}
}	


/*----------------------����Ϊ����(Rxd)�йغ���-----------------------------*/

uint8_t USAR_GetRxFlag(void)//�õ��������ݵı�־λ
{
	if(USAR_RxFlag == 1)
	{
		USAR_RxFlag=0;
		return 1;
	}
	return 0;
}

uint8_t USAR_GetRxData(void)//�õ����յ������ݵ�ֵ
{
	return USAR_RxData;
}



void USART2_IRQHandler(void)			 
{
	if (USART_GetITStatus(USART2,USART_IT_RXNE) == SET)//������ڽ��յ�����
	{
		USAR_RxData = USART_ReceiveData(USART2);//�������ݸ���ȫ�ֱ���USAR_RxData
		USAR_RxFlag = 1;
		
		
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
