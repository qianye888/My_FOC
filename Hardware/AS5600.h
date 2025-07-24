#ifndef __AS5600_H_
#define __AS5600_H_

#include "sys.h"

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);


//AS5600地址存储
#define  RAW_Angle_Hi    0x0C
#define  RAW_Angle_Lo    0x0D
#define  AS5600_Address  0x36
#define  AS5600_CPR      4096

#define AS5600_ADDRESS		0x6C		//AS5600的I2C从机地址		
#define AS5600_ANGLE_H		0x0E
#define AS5600_ANGLE_L		0x0F

#define speedfil_1    0
#define anglefil    1
#define prefil      2
#define speedfil_2    9


//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;} //SDA切换为输入模式 
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;} //SDA切换为输出模式 
//IO操作函数
#define IIC_SCL    PBout(10) //SCL输出
#define IIC_SDA    PBout(11) //SDA输出	 
#define READ_SDA   PBin(11)  //SDA输入

extern float full_rotations;
extern float angle_prev;
extern float vel_angle_prev;
extern float angle_prev_Velocity;
extern float vel_angle_prev_Velocity;
extern unsigned long angle_prev_ts;
extern unsigned long vel_angle_prev_ts;

uint8_t AS5600_ReadReg(uint8_t RegAddress);
void AS5600_Init(void);
u16 AS5600_GetData(void);
//void delay_s(u32 i);


float get_Angle_360(void);
float get_Angle_2PI(void);
float get_Angle(void);
//float getVelocity(void);
float get_Speed(void);



#endif
