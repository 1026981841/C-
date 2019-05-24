#pragma once
#include<stdio.h>
#include"struct.h"
#include"foo.h"
void Print(Spot spot)/*形参为单独的景点结构体，功能为将景点信息打印在屏幕上*/
{
	printf("name:%s\n", spot.name);

	if (spot.isPeak == true)
		printf("price:%f\n", spot.price*spot.discount);
	else
		printf("price:%f\n", spot.price*0.8*spot.discount);

	printf("intro:%s\n", spot.Intro);
	printf("time for sightseeing:%d\n", spot.duration);
	printf("level:%d\n", spot.level);
	printf("tickets remain:%d\n", spot.tickets);
	
	/*if (user.MinAge < 18 && (spot.Child ==false))
		printf("Attention!This senic spot is NOT for child.\n");

	if (user.MaxAge > 60 && (spot.Old ==false))
		printf("Attention!This senic spot is NOT for old man.\n");*/
}