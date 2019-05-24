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
	//int index[30];//将每一个结构体都编号，传递编号即传递整个结构体
	//for (int input_output = 0; input_output < 30; input_output++)
	//	index[input_output] = input_output;
	int sign = getSpotInf(stu);//函数从文件中导出景点所有信息到stu中，返回景点个数

	char name_input[15];
	int sign = 30;
	int *index =NULL;
	int index_fin;//储存最终放入购物车的索引
	int a;//作为switch的参数
	int yes_no;//作为判断是否循环的参数

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
		index_fin = reservation1(index, stu, visitor, yes_no);//需要主函数中定义的用户结构数代替参数user？？？？？？？？？？？？？？？？？？
		tm1 reservation2();
		
	}

	return index_fin;

}