/**************************************************
/* @file         main.c
* @author       Lcalin
* @version      V1.0
* @date         2021.12.15
* @brief        测试alps机芯电磁铁
* @details      
* @par History  见如下说明
*                 
* version:	V0.1:  测试alps机芯电磁铁
*				   效果：  按下按键K3开始播放，按下按键K2快进
*									按下按键K3停止所有动作
*
* version:	V0.2:  2021.12.17更新
*										1.添加磁带检测功能
*										2.添加
*										
*				   效果：  

原理图
P14--------按键K1
P15--------按键K2
P16--------按键K3
P21--------控制电磁铁的继电器信号输出，高电平启动，低电平停止
P22--------磁带检测，开机后若无磁带，机芯不动作
P23--------开机复位，使机芯回到停止状态

**************************************************/
#include <reg52.h>
#include <intrins.h>

sbit key1 = P1^4;			//停止键
sbit key2 = P1^5;			//快进键
sbit key3 = P1^6;			//正面播放
//sbit key4 = P1^7;			//反面播放
//sbit key5 = P3^5;			//快退键


sbit relay = P2^1;		//继电器输出
sbit check = P2^2;		//磁带检测


int stop = 1;				//停止标志位
int play = 0;				//播放标志位
int speed = 0;			//快进标志位

int num;
/**********************函数声明********************/
void dalayms(int z);
void keyscan();
void click();
/**********************主函数**********************/
void main()
{
	relay = 0;
	while(1)
	{
		if(check==0)		//磁带检测
		{
			keyscan();
		}

	}
}	

/**********************函数定义********************/
//void flow()
//{
//	if(stop==1)
//	{
//		relay = 0;
//	}
//}

void dalayms(int z)		//延时函数定义
{
	int i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}

void keyscan()		//按键检测定义
{
	if(key1==0)		//停止键定义
	{
		dalayms(10);
		if(key1==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key1);		//等待按键释放
			
			if((play==0&&speed==0)&&(stop==1))		//如果此时不在播放，快进等状态，电磁铁无动作
				{
					relay = 0;
					dalayms(100);
				}
			
			if(play==1)		//如果此时为播放，电磁铁吸合两次
				{
					click();
					dalayms(100);
					click();
					play = 0;
					stop = 1;
				}
				
			if(speed==1)		//如果此时为快进，电磁铁吸合一次
				{
					click();
					speed = 0;
					stop = 1;
				}
		}
	}

	if(key2==0)		//快进键定义
	{
		dalayms(10);
		if(key2==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key2);		//等待按键释放
			
			if(play==0)
			{
				click();			
				dalayms(600);
				click();
				speed = 1;
				stop = 0;			
			}
			
			if(play==1)
			{
				click();
				play = 0;
				speed = 1;
				stop = 0;
			}
		}
	}
	
	if(key3==0)		//播放键定义
	{
		dalayms(10);
		if(key3==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key3);		//等待按键释放
			
			if(speed==1)
			{
				click();
				dalayms(100);
				click();
				speed = 0;
				play = 1;
				stop = 0;				
			}

			if(speed==0)
			{	
				click();
				play = 1;
				stop = 0;
			}
		}
	}
}	

void click()			//电磁铁吸合一次
{
	relay = 1;
	dalayms(50);   //50ms为吸合一次时间，200ms正反带
	relay = 0;	
}

