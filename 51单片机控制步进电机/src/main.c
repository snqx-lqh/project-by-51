#include "reg52.h"

sbit DIR1 = P2 ^ 0;
sbit CLK1 = P2 ^ 1;

sbit MotorA1 = P1 ^ 4;
sbit MotorB1 = P1 ^ 5;
sbit MotorC1 = P1 ^ 6;
sbit MotorD1 = P1 ^ 7;

#define CW 0
#define CCW 1
#define STOP 2

void Timer0Init(void);
void Motor1Turn(unsigned char motorState);
void Motor2Turn(unsigned char motorState);

int main()
{
    Timer0Init();
    while (1)
    {
    }
}

void Timer0Init(void) //5毫秒@12.000MHz
{
    TMOD = 0x01; //设置定时器模式
    TL0 = 0x78;  //设置定时0初始值
    TH0 = 0xEC;  //设置定时0初始值
    TF0 = 0;     //清除TF0标志
    TR0 = 1;     //定时器0开始计时
    ET0 = 1;
    EA = 1;
}

void Timer0() interrupt 1
{
    static int counts = 0;

    TL0 = 0x78; //设置定时0初始值
    TH0 = 0xEC; //设置定时0初始值
    counts++;
    if (counts > 1)
    {
        Motor1Turn(CW);
        Motor2Turn(CCW);

        counts = 0;
    }
}

void Motor1Turn(unsigned char motorState)
{

    if (motorState == CW)
    {
        DIR1 = 1;
        CLK1 = !CLK1;
    }
    else if (motorState == CCW)
    {
        DIR1 = 0;
        CLK1 = !CLK1;
    }
    else
    {
        CLK1 = 0;
    }
}

void Motor2Turn(unsigned char motorState)
{
    static int motor1Step = 0;
    motor1Step++;
    if (motor1Step > 7)
    {
        motor1Step = 0;
    }
    if (motorState == CW)
    {
        if (motor1Step == 0)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 1;
        }
        else if (motor1Step == 1)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 1;
            MotorD1 = 1;
        }
        else if (motor1Step == 2)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 1;
            MotorD1 = 0;
        }
        else if (motor1Step == 3)
        {
            MotorA1 = 0;
            MotorB1 = 1;
            MotorC1 = 1;
            MotorD1 = 0;
        }
        else if (motor1Step == 4)
        {
            MotorA1 = 0;
            MotorB1 = 1;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 5)
        {
            MotorA1 = 1;
            MotorB1 = 1;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 6)
        {
            MotorA1 = 1;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 7)
        {
            MotorA1 = 1;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 1;
        }
    }

    else if (motorState == CCW)
    {
        if (motor1Step == 0)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 1;
        }
        else if (motor1Step == 1)
        {
            MotorA1 = 1;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 1;
        }
        else if (motor1Step == 2)
        {
            MotorA1 = 1;
            MotorB1 = 0;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 3)
        {
            MotorA1 = 1;
            MotorB1 = 1;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 4)
        {
            MotorA1 = 0;
            MotorB1 = 1;
            MotorC1 = 0;
            MotorD1 = 0;
        }
        else if (motor1Step == 5)
        {
            MotorA1 = 0;
            MotorB1 = 1;
            MotorC1 = 1;
            MotorD1 = 0;
        }
        else if (motor1Step == 6)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 1;
            MotorD1 = 0;
        }
        else if (motor1Step == 7)
        {
            MotorA1 = 0;
            MotorB1 = 0;
            MotorC1 = 1;
            MotorD1 = 1;
        }
    }
}