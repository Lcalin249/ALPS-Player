/**************************************************
/* @file         main.c
* @author       Lcalin
* @version      V1.0
* @date         2021.12.15
* @brief        ����alps��о�����
* @details      
* @par History  ������˵��
*                 
* version:	V0.1:  ����alps��о�����
*				   Ч����  ���°���K3��ʼ���ţ����°���K2���
*									���°���K3ֹͣ���ж���
*
* version:	V0.2:  2021.12.17����
*										1.��ӴŴ���⹦��
*										2.���
*										
*				   Ч����  

ԭ��ͼ
P14--------����K1
P15--------����K2
P16--------����K3
P21--------���Ƶ�����ļ̵����ź�������ߵ�ƽ�������͵�ƽֹͣ
P22--------�Ŵ���⣬���������޴Ŵ�����о������
P23--------������λ��ʹ��о�ص�ֹͣ״̬

**************************************************/
#include <reg52.h>
#include <intrins.h>

sbit key1 = P1^4;			//ֹͣ��
sbit key2 = P1^5;			//�����
sbit key3 = P1^6;			//���沥��
//sbit key4 = P1^7;			//���沥��
//sbit key5 = P3^5;			//���˼�


sbit relay = P2^1;		//�̵������
sbit check = P2^2;		//�Ŵ����


int stop = 1;				//ֹͣ��־λ
int play = 0;				//���ű�־λ
int speed = 0;			//�����־λ

int num;
/**********************��������********************/
void dalayms(int z);
void keyscan();
void click();
/**********************������**********************/
void main()
{
	relay = 0;
	while(1)
	{
		if(check==0)		//�Ŵ����
		{
			keyscan();
		}

	}
}	

/**********************��������********************/
//void flow()
//{
//	if(stop==1)
//	{
//		relay = 0;
//	}
//}

void dalayms(int z)		//��ʱ��������
{
	int i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}

void keyscan()		//������ⶨ��
{
	if(key1==0)		//ֹͣ������
	{
		dalayms(10);
		if(key1==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key1);		//�ȴ������ͷ�
			
			if((play==0&&speed==0)&&(stop==1))		//�����ʱ���ڲ��ţ������״̬��������޶���
				{
					relay = 0;
					dalayms(100);
				}
			
			if(play==1)		//�����ʱΪ���ţ��������������
				{
					click();
					dalayms(100);
					click();
					play = 0;
					stop = 1;
				}
				
			if(speed==1)		//�����ʱΪ��������������һ��
				{
					click();
					speed = 0;
					stop = 1;
				}
		}
	}

	if(key2==0)		//���������
	{
		dalayms(10);
		if(key2==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key2);		//�ȴ������ͷ�
			
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
	
	if(key3==0)		//���ż�����
	{
		dalayms(10);
		if(key3==0)
		{
			num++;
			if(num==60)
				num = 0;
			while(!key3);		//�ȴ������ͷ�
			
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

void click()			//���������һ��
{
	relay = 1;
	dalayms(50);   //50msΪ����һ��ʱ�䣬200ms������
	relay = 0;	
}

