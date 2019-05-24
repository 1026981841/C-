#ifndef STRUCTS_H
#define STRUCTS_H
#include"reserve.h"

typedef struct Visitor {
	char ID[11];
	char pwd[11];
	char Tel[15];
	int num;
	int type;//0: normal, 1: kid, 2: elder, 3: soldier
	int MinAge, MaxAge;

}Visitor;

extern Visitor user;

typedef struct Admin {
	char ID[11];
	char pwd[11];
	char Tel[15];
	char Email[50];

}Admin;

extern Admin ad;

struct Spot {
	char ID[7];
	char name[50];
	char Intro[1000];
	
	float non_peak_discount;
	int price;

	bool Old;
	bool Child;

	int duration;
	float discount;
	int level;
	int MaxPeople[4][3];
	char belong[20];
	int MaintainCost;
	int tickets;
	int views;
	Spot *Pnext;
	
};

bool isPeak(Spot*);

void print_spot(Spot*);
void print_order(Purchase*);

void Visitor_struct_assign(Visitor *, Visitor *);
void Admin_struct_assign(Admin *, Admin *);

bool chk_Email(char*);

void edit_tourist_Tel(char*);
void edit_tourist_pwd(char*);


void editPwd (char *togo);//Admin
void editEmail(char *togo);//Admin
int getUserInfo(Visitor**);
int getSpotInfo(Spot**);
int getAdminInfo(Admin**);
int addSpot();

#endif