#include <reg52.h>
#include "stdio.h"
#include "LCD1602.h"

uint Disp[2][16] = {0};

sbit key1 = P2 ^ 5;
sbit key2 = P2 ^ 6;
sbit key3 = P2 ^ 7;

uint testValue = 0;

void Timer0Init(void);

int main()
{
    LcdInit();
    Timer0Init();
    sprintf((char *)Disp[0], "first display   ");
    LcdShowStr(0, 0, Disp[0]);
    while (1)
    {
        sprintf((char *)Disp[1], "distance:%2d     ", testValue);
        LcdShowStr(0, 1, Disp[1]);
    }
}

void KeyScan()
{
    static int keyCount = 0;
    static int keyState = 0;
    if (key1 == 0 && keyState == 0) //按键按下
    {
        keyCount++;
        if (keyCount > 2 && key1 == 0 && keyState == 0) //加两次类似延迟10ms，不好解释
        {
            /*ToDo:按键按下执行的操作*/
            testValue++;

            keyState = 1;
        }
    }
    else if (key2 == 0 && keyState == 0)
    {
        keyCount++;
        if (keyCount > 2 && key2 == 0 && keyState == 0)
        {
            /*ToDo:按键按下执行的操作*/
            testValue--;

            keyState = 1;
        }
    }
    else if (key3 == 0 && keyState == 0)
    {
        keyCount++;
        if (keyCount > 2 && key3 == 0 && keyState == 0)
        {
            /*ToDo:按键按下执行的操作*/
            testValue = 0;

            keyState = 1;
        }
    }
    else if (key1 == 1 && key2 == 1 && key3 == 1 && keyState == 1) //当所有按键都处于抬起状态，状态刷新
    {
        keyCount = 0;
        keyState = 0;
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
    TL0 = 0x78; //设置定时0初始值
    TH0 = 0xEC; //设置定时0初始值
    KeyScan();
}
