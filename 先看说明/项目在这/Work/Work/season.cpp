#define _CRT_SECURE_NO_WARNINGS
#include"structs.h"
#include"season.h"
#include<stdio.h>
#include<cassert>
#include<time.h>

int MaxPeople_Current(int a[4][3])/*形参为tm时间结构体和相关景点最大人数分布的二维数组，返回值为对应时间的最大人数*/
{
	time_t now = time(NULL);
	tm info = *localtime(&now);
	int month = info.tm_mon + 1;
	int hour = info.tm_hour;
	if((month <= 2) || month == 12) {
		if(hour >= 7 && hour < 11) {
			return a[0][0];
		} else if(hour >= 11 && hour < 18) {
			return a[0][1];
		}
		return a[0][2];
	} else if(month >= 3 && month <= 5) {
		if(hour >= 7 && hour < 11) {
			return a[1][0];
		} else if(hour >= 11 && hour < 6) {
			return a[1][1];
		}
		return a[1][2];
	} else if(month >= 6 && month <= 8) {
		if(hour >= 7 && hour < 11) {
			return a[2][0];
		} else if(hour >= 11 && hour < 6) {
			return a[2][1];
		}
		return a[2][2];
	} else if(month >= 9 && month <= 11) {
		if(hour >= 7 && hour < 11) {
			return a[3][0];
		} else if(hour >= 11 && hour < 6) {
			return a[3][1];
		}
		return a[3][2];
	}
	assert(false);
	return -1;
}