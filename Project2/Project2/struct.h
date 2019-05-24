#ifndef STRUCTS_H
#define STRUCTS_H
#include<time.h>
#define bool int

typedef struct Visitor{
	char ID[11];
	char pwd[11];
	char Tel[15];
	int num;
	int type;//0: normal, 1: kid, 2: elder, 3: soldier
	int MaxAge, MinAge;
	struct Vistor *Pnext;
}Vistor;

//xtern Visitor user;
typedef struct Admin{
	char ID[11];
	char pwd[11];
	char Tel[15];
	char Email[50];
	struct Admin *Pnext;
}Admin;


typedef struct Spot{
	char ID[7];
	char name[15];
	char Intro[500];

	bool isPeak;
	int price;

	int duration;
	float discount;
	int level;
	int MaxPeople[4][3];
	int belong;
	int MaintainCost;
	bool Old;
	bool Child;
	int tickets;
	int views;
	struct Spot *Pnext;


}Spot;
 

//typedef struct Reservation{
//	char Spot_ID[7];
//	tm1 departure_Time;
//
//
//	struct Reservation* Pnext;
//}Res;


typedef struct Purchase{
	char** Spot_ID;/*购物车链表的头指针*/
	char Visitor_ID[7];
	//struct tm1 *purchase_Time;
	int day, mon, year;
	float price;
	int number_of_people;
	struct Purchase* Pnext;
}Pur;

typedef struct tm1{
	int tm1_day;
	int tm1_mon;
	int tm1_year;
}tm1;

typedef struct test {
	char **s;
}test;
bool chk_Tel();
bool chk_Email();

float calPrice();
float calDiscount();


void editTel (char *togo);
void editPwd (char *togo);
void editEmail (char *togo);

int getSpotInfo(Spot**);

#endif