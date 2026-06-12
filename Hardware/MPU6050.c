#include "MPU6050.h"
#include "MyI2C.h"
#include "Delay.h"

MPU6050_DataTypeDef MPU6050_Data;

void MPU6050_WriteByte(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(Data);
    MyI2C_ReceiveAck();
    MyI2C_Stop();
}

uint8_t MPU6050_ReadByte(uint8_t RegAddress)
{
    uint8_t Data;

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceiveAck();
    Data = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return Data;
}

uint8_t MPU6050_ReadID(void)
{
    return MPU6050_ReadByte(MPU6050_WHO_AM_I);
}

void MPU6050_ReadRaw(void)
{
    uint8_t dataH;
    uint8_t dataL;

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(MPU6050_ACCEL_XOUT_H);
    MyI2C_ReceiveAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceiveAck();

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.AccX = (int16_t)((dataH << 8) | dataL);

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.AccY = (int16_t)((dataH << 8) | dataL);

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.AccZ = (int16_t)((dataH << 8) | dataL);

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.TempRaw = (int16_t)((dataH << 8) | dataL);
    MPU6050_Data.Temperature = (MPU6050_Data.TempRaw / 340.0f) + 36.53f;

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.GyroX = (int16_t)((dataH << 8) | dataL);

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    MPU6050_Data.GyroY = (int16_t)((dataH << 8) | dataL);

    dataH = MyI2C_ReceiveByte();
    MyI2C_SendAck(0);
    dataL = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();
    MPU6050_Data.GyroZ = (int16_t)((dataH << 8) | dataL);
}

void MPU6050_Init(void)
{
    MyI2C_Init();
    Delay_ms(100);

    MPU6050_WriteByte(MPU6050_PWR_MGMT_1, 0x01);
    Delay_ms(10);
    MPU6050_WriteByte(MPU6050_SMPLRT_DIV, 0x07);
    MPU6050_WriteByte(MPU6050_CONFIG, 0x06);
    MPU6050_WriteByte(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteByte(MPU6050_ACCEL_CONFIG, 0x10);
    MPU6050_WriteByte(MPU6050_INT_ENABLE, 0x00);

    MPU6050_Data.AccX = 0;
    MPU6050_Data.AccY = 0;
    MPU6050_Data.AccZ = 0;
    MPU6050_Data.GyroX = 0;
    MPU6050_Data.GyroY = 0;
    MPU6050_Data.GyroZ = 0;
    MPU6050_Data.TempRaw = 0;
    MPU6050_Data.Temperature = 0.0f;
}
