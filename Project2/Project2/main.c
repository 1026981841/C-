#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"Print.h"
#include"user.h"


int main()
{
	struct Spot stu[30];
	//int index[30];//��ÿһ���ṹ�嶼��ţ����ݱ�ż����������ṹ��
	//for (int input_output = 0; input_output < 30; input_output++)
	//	index[input_output] = input_output;
	int sign = getSpotInf(stu);//�������ļ��е�������������Ϣ��stu�У����ؾ������

	char name_input[15];
	int sign = 30;
	int *index =NULL;
	int index_fin;//�������շ��빺�ﳵ������
	int a;//��Ϊswitch�Ĳ���
	int yes_no;//��Ϊ�ж��Ƿ�ѭ���Ĳ���

	while (1)
	{
		while (1)
		{
			printf("If you want to query by name please press 1:\n");
			printf("If you want to query by Remaining tickets please press 2:\n");
			printf("If you want to query by area please press 3:\n");
			printf("If you want to query by discount informations please press 4:\n");
			printf("If you want to sort by price please press 5:\n");
			printf("If you want to sort by the number of votes remaining please press 6:\n");
			printf("If you want to find recommended information please press 7:\n");

			scanf("%d", &a);

			switch (a)
			{
			case 1:
				index = name1(stu, name_input, sign);
				break;
			case 2:
				index = tickets1(stu, sign);
				break;
			case 3:
				index = belong1(stu, sign);
				break;
			case 4:
				index = discount1(stu, sign);
				break;
			case 5:
				index = price_rank(stu, sign);
				break;
			case 6:
				index = ticket_rank(stu, sign);
				break;
			case 7:
				index = recommend1(stu, sign);
				break;
			default:
				printf("error input!!Please en-enter\n");
				break;
			}

			if (index == NULL)
				continue;
			else
				break;

		}

		printf("******************************************************************************************************\n");
		printf("If you want to select the scenic spots which displayed at the top of the screen,please press the sign:\n");
		printf("If you want to query again ,please press 'q':\n");
		index_fin = reservation1(index, stu, visitor, yes_no);//��Ҫ�������ж�����û��ṹ���������user������������������������������������
		tm1 reservation2();
		
	}

	return index_fin;

}