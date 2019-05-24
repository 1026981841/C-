#ifndef RESERVE_H
#define RESERVE_H
#include<ctime>

typedef struct tm1 {
	int tm1_day;
	int tm1_mon;
	int tm1_year;
}tm1;

typedef struct Reservation {
	char Spot_ID[7];
	struct tm1 departure_Time;
	float price;
	struct Reservation* Pnext = NULL;
}Res;


typedef struct Purchase {
	char s[50][7];
	char purchase_id[100];
	int spot_number;
	char Visitor_ID[7];
	tm purchase_Time;
	float total_price;
	int number_of_people;
	tm1 tm;//departure time
}Purchase;

int order_spot(int);
int confirm_order();
int modify_order();
int cancel_order(int);
int getPurchaseInfo(Purchase**);

void struct_tm1_assign(tm1 *, tm1 *);

#endif