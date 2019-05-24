#pragma once
#include"struct.h"
#include<stdio.h>
#include<time.h>
#include<string.h>


int* name1(struct Spot *stu, char* name_input, int sign)//按照名称查询
{
	int index1[30] = { -1 };//储存索引
	int index1_sign = 0;//储存索引下标
	int b = 0;//用于判断是否有结构体索引输出
	int r;

	while (1)
	{
		scanf("%s", name_input);
		for (int a = 0; a < sign; a++)
		{
			r = strcmp(name_input, stu[a].name);
			if (r = 0)
			{
				printf("****\n");
				printf("%-2.d *\n", a);
				printf("****\n");

				printf("Find informations!!\n");
				Print(stu[a]);
				index1[index1_sign] = a;
				index1_sign++;
				stu[a].views++;
				b = 1;
				break;
			}
			else
				continue;
		}
		if (b == 0)
		{
			printf("erroe input!!Please re-enter:\n");
			continue;
		}
		if (b == 1)
			break;
	}
	return index1;
}

int* tickets1(struct Spot *stu, int sign)//按照有无票查询
{
	int index1[30] = { -1 };//储存索引
	int index1_sign = 0;//储存索引下标
	int b = 0;//用于判断是否有结构体索引输出

	for (int a = 0; a < sign; a++)
	{
		if (stu->tickets > 0)
		{
			printf("****\n");
			printf("%-2.d *\n", a);
			printf("****\n");

			Print(stu[a]);
			index1[index1_sign] = a;
			index1_sign++;
			stu[a].views++;
			b = 1;
		}
		else
			continue;
	}
	if (b == 0)
		printf("Sorry!!Tickets are sold out\n");

	return index1;
}

int* belong1(struct Spot *stu, int sign)//按照所属地查询
{
	int belong_input;//用于储存用户输入的所属地
	int index1[30] = { -1 };//储存索引
	int index1_sign = 0;//储存索引下标
	int b = 0;//用于判断是否有结构体索引输出

	while (1)
	{
		printf("if you want to go East please press 1\n");
		printf("if you want to go West please press 2\n");
		printf("if you want to go North please press 3\n");
		printf("if you want to go South please press 4\n");
		printf("plesse input the area of the scenic spot: ");
		scanf("%d", &belong_input);
		if (belong_input == 1 || belong_input == 2 || belong_input == 3 || belong_input == 4)
			break;
		else
		{
			printf("error!!\nPlease read the prompt message and re-enter it\n");
			continue;
		}
	}
	for (int a = 0; a < sign; a++)
	{
		if (stu[a].belong == belong_input)
		{
			printf("****\n");
			printf("%-2.d *\n", a);
			printf("****\n");

			Print(stu[a]);
			index1[index1_sign] = a;
			index1_sign++;
			stu[a].views++;
			b = 1;
		}
		else
			continue;
	}
	if (b == 0)
		printf("Sorry!!there is no scenic spot here\n");

	return index1;
}

int* discount1(struct Spot *stu, int sign)//按照折扣信息查询
{
	int index1[30] = { -1 };//储存索引
	int index1_sign = 0;//储存索引下标
	int b = 0;//用于判断是否有结构体索引输出

	for (int a = 0; a < sign; a++)
	{
		if (stu[a].discount < 1)
		{
			printf("****\n");
			printf("%- 2.d *\n", a);
			printf("****\n");

			Print(stu[a]);
			index1[index1_sign] = a;
			index1_sign++;
			stu[a].views++;
			b = 1;
		}
		else
			continue;
	}
	if (b == 0)
		printf("Sorry!!Tickets are sold out\n");

	return index1;
}

int* recommend1(struct Spot *stu, int sign)//按照访问量排序景点
{
	struct Spot views_rank[30];
	getSpotInf(views_rank);
	int index1[30] = { -1 };//储存索引
	int index1_sign = 0;//储存索引下标

	int max;//储存最大值
	int max_index;//储存最大值参数

	int i;//外循环参数
	int ii;//内循环参数

	for (i = 0; i < (sign - 1); i++)
	{
		max = views_rank[i].views;
		max_index = i;
		for (ii = i + 1; ii < sign; ii++)
		{
			if (views_rank[ii].views > max)
			{
				max = views_rank[ii].views;
				max_index = ii;
			}
		}
		views_rank[max_index].views = views_rank[i].views;
		views_rank[i].views = max;
		index1[index1_sign] = max_index;
		index1_sign++;

		printf("****\n");
		printf("%- 2.d *\n", i);
		printf("****\n");
		Print(views_rank[i]);
	}
	return index1;
}

int reservation1(int *index1 , Spot *stu ,Vistor vis , int yes_no)//预定
{
	int index1_fin = -1;//最终的索引
	int index1_sign = 0;//保存下标
	int b = 0; //判断是否选定了景点
	char a1;//作为参数
	
	while (1)
	{
		scanf("%c", &a1);
		if (a1 == 'q')
		{
			yes_no = 0;
			break;
		}
		for (; index1[index1_sign] < 30; index1_sign++)
		{
			if (index1[index1_sign] == a1 || vis.num >stu[index1_sign].tickets || vis.num == stu[index1_sign].tickets)
			{
				yes_no = 1;
				index1_fin = index1_sign;
				stu[index1_sign].tickets = stu[index1_sign].tickets - vis.num;
				break;
			}
			else
			{
				printf("The sign which you put is not exist,please en-enter it:\n");
				continue;
			}
		}
	}
	return index1_fin;
}
tm1 reservation2()//用户输入时间
{	
	tm1 input;
	while (1)
	{
		printf("Please input the year you want to go\n");
		scanf("%d\n", &input.tm1_year);
		if (input.tm1_year < 0)
		{
			printf("erreo input!!\n");
			continue;
		}
		else
			break;
	}

	while (1)
	{
		printf("Please input the month you want to go\n");
		scanf("%d\n", &input.tm1_mon);
		if (input.tm1_mon < 0)
		{
			printf("erreo input!!\n");
			continue;
		}
		else
			break;
	}
	while (1)
	{
		printf("Please input the date you want to go\n");
		scanf("%d\n", &input.tm1_day);
		if (input.tm1_day < 0)
		{
			printf("erreo input!!\n");
			continue;
		}
		else
			break;
	}
	return input;
}

int compare(const void* a, const void* b)/*不需调用*/
{
	Spot* pa = (Spot*)a;
	Spot* pb = (Spot*)b;
	int num1 = pa->tickets;
	int num2 = pb->tickets;
	return num1 - num2;
}

int* ticket_rank(struct Spot* stu, int sign)//按余票量排序并打印
{
	int index1[30] = { -1 };
	int i, b;

	for (i = 0; i <= sign; i++)
		index1[i] = i;

	qsort(index1, sign, sizeof(int), compare);
	for (i = 0; i <= stu; i++)
	{
		b = index1[i];
		Print(stu[b]);
	}
	return index1;
}

int* price_rank(struct Spot* stu, int sign)/*形参：全部景点头指针，功能：按价格排序并打印*/
{
	int index1[30] = { -1 };
	int i, b;

	for (i = 0; i <= sign; i++)
		index1[i] = i;

	qsort(index1, sign, sizeof(int), compare);
	for (i = 0; i <= sign; i++)
	{
		b = index1[i];
		Print(stu[b]);
	}
	return index1;
}
