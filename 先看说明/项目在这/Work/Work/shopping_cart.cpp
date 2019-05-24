#define _CRT_SECURE_NO_WARNINGS
#include"shoppingcart.h"
//#include"season.h"
#include"structs.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<cassert>

extern int record;
extern Res* ShoppingCart;

Spot get_spot_by_ID(char* ID)
{/*�Σ�����ID��������Ӧ����*/
	Spot* s[30];
	for(int i = 0; i < 30; i++) {
		s[i] = (Spot*) malloc(sizeof(Spot));
	}
	int a = getSpotInfo(s);
	int ans = -1;
	for(int i = 0; i < a; i++) {
		if(strcmp(ID, s[i]->ID) == 0) {
			//found
			ans = i;
			break;
		}
	}
	for(int i = 0; i < 30; i++) if(i != ans) {
		free(s[i]);
	}
	assert(ans != -1);
	return *s[ans];
}

Res* create_shoppingcart(char* spot_ID, tm1 time)
{/*�Σ���һ������ID,����ʱ�䣬���������Ĺ��ﳵͷָ��*/
	Res *Pnew;
	Spot spot;
	Pnew = (Res*)malloc(sizeof(Res));
	Pnew->departure_Time = time;
	strcpy(Pnew->Spot_ID, spot_ID);
	spot = get_spot_by_ID(spot_ID);
	if(isPeak(&spot)) {
		Pnew->price = spot.discount*spot.price*user.num;
	} else {
		Pnew->price = spot.discount*spot.price*user.num* spot.non_peak_discount;
	}
	Pnew->Pnext = NULL;

	return Pnew;
}

Res* get_shoppingcart(Res* cart, char* spot_ID, tm1 time)
{/*�Σ����ﳵͷָ�룬Ҫ��ӵľ���ṹ�壬����ʱ�䣬�����µĹ��ﳵͷָ�룬���ܣ�Ϊ���ﳵ����¾���*/
	Res *Phead;
	Spot spot;
	Phead = cart;
	while(cart->Pnext != NULL) {
		cart = cart->Pnext;
	}
	spot = get_spot_by_ID(spot_ID);
	cart = (cart->Pnext = (Res*)malloc(sizeof(Res)));
	if(isPeak(&spot)) {
		cart->price = spot.discount*spot.price*user.num;
	} else {
		cart->price = spot.discount*spot.price*user.num* spot.non_peak_discount;
	}
	cart->departure_Time = time;
	strcpy(cart->Spot_ID, spot_ID);
	cart->Pnext = NULL;

	return Phead;
}

void search_purchase(Res* cart)
{/*�Σ����ﳵ�����ܣ���ӡ���ﳵ�����о�������*/
	Res* Phead = cart;
	Spot   Obj;
	while(cart != NULL) {
		Obj = get_spot_by_ID(cart->Spot_ID);
		printf("%s %s\n", Obj.name, Obj.ID);
		cart = cart->Pnext;
	}
	cart = Phead;
}

void collect_ID(Res* cart, char s[][7], int n)/*�Σ����ﳵ�����ﳵ�еľ�����������ȫ������ID���Զ���ָ����ʽ��ţ�*/
{
	Res* Phead = cart;
	int i = 0;
	while(cart != NULL)

	{
		strcpy(s[i], cart->Spot_ID);
		cart = cart->Pnext;
		i++;
	}
	strcpy(s[i], "/0");
	cart = Phead;
}

Res*  Buy(int Index, tm1 T)
{/*�Σ������������û����ʸþ����ʱ�䣬���������Ĺ��ﳵ�����ܣ������ص�������Ϊ-1ʱ�����������ڹ��ﳵ�ﴴ��/��Ӿ���*/
	Spot *s[30];
	for(int i = 0; i < 30; i++) {
		s[i] = (Spot*)malloc(sizeof(Spot));
	}
	getSpotInfo(s);
	if(!record) {
		getSpotInfo(s);
		ShoppingCart = create_shoppingcart(s[Index]->ID, T);
		record++;
	} else {
		ShoppingCart = get_shoppingcart(ShoppingCart, s[Index]->ID, T);
		record++;
	}

	for(int i = 0; i < 30; i++) {
		free(s[i]);
	}

	return ShoppingCart;
}

int del_shoppingcart(Res* cart, char* spot_ID)/*�Σ����ﳵͷָ�룬Ҫɾ���ľ���ID�������µĹ��ﳵ*/
{
	Res* Phead = cart, *rTemp;
	if(!strcmp(spot_ID, cart->Spot_ID)) {
		rTemp = cart->Pnext;
		free(cart);
		ShoppingCart = rTemp;
	} else {
		rTemp = cart;
		cart = cart->Pnext;
		while(cart != NULL && strcmp(spot_ID, cart->Spot_ID)) {
			rTemp = rTemp->Pnext;
			cart = cart->Pnext;
		}
		if(cart == NULL) {
			return 0;
		}
		rTemp->Pnext = cart->Pnext;
		free(cart);
		ShoppingCart = rTemp;
	}

	record--;

	return 1;
}

bool early(tm1 t1, tm1 t2) {
	if(t1.tm1_year < t2.tm1_year) return true;
	if(t1.tm1_year == t2.tm1_year && t1.tm1_mon < t2.tm1_mon) return true;
	if(t1.tm1_year == t2.tm1_year && t1.tm1_mon == t2.tm1_mon && t1.tm1_day < t2.tm1_day) return true;
	return false;
}

void get_dep_time(Res*cart, tm1* time) {
	Res*Phead = cart;
	int i = 0;
	*time = cart->departure_Time;
	while(cart != NULL) {
		if(early(cart->departure_Time, *time))
			*time = cart->departure_Time;
		i++;
		cart = cart->Pnext;
	}
	cart = Phead;
}

int check_out(Res* cart, Purchase* p)
{/*�Σ����ﳵ���������ɵĶ��������ܣ������ص�����Ϊ - 1ʱ�����ô˺��������ɶ��� */
	//0: empty cart, 1: ok, -idx: sold out
	Res* Ptemp = cart;
	if(cart == NULL) return 0;
	char v[11];
	float pr = 0.0;
	time_t now = time(NULL);
	tm info = *localtime(&now);
	collect_ID(cart, p->s, record);
	get_dep_time(cart, &(p->tm));
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_cnt = getSpotInfo(sp);
	for(int i = 0; i < record; i++) {
		for(int j = 0; j < spot_cnt; j++) {
			if(strcmp(sp[j]->ID, p->s[i]) == 0) {
				if(sp[i] - user.num < 0) {
					//sold out
					return -i;
				}
				sp[i]->tickets -= user.num;
				break;
			}
		}
	}
	for(int i = 0; i < record; i++) {
		for(int j = 0; j < spot_cnt; j++) {
			if(strcmp(sp[j]->ID, p->s[i]) == 0) {
				sp[j]->tickets -= user.num;
				break;
			}
		}
	}

	FILE *fout = fopen("SpotInfo.txt", "w+");
	for(int i = 0; i < spot_cnt; i++) {
		fwrite(sp[i], sizeof(Spot), 1, fout);
	}
	fclose(fout);

	while(cart != NULL) {
		pr += cart->price;
		Ptemp = cart;
		cart = cart->Pnext;
		free(Ptemp);
	}
	strcpy(v, user.ID);
	p->spot_number = record;
	strcpy(p->Visitor_ID, user.ID);
	p->number_of_people = user.num;
	p->total_price = pr;
	p->purchase_Time = info;
	record = 0;

	for(int i = 0; i < 30; i++) {
		free(sp[i]);
	}
	return 1;
}
