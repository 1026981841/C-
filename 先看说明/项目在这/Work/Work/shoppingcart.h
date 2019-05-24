#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H
#include"reserve.h"
#include"structs.h"

Spot get_spot_by_ID(char* ID);

Res* get_shoppingcart(Res* cart, char* spot_ID, tm1 time);

int del_shoppingcart(Res* cart, char* spot_ID);

void search_purchase(Res* cart);

void collect_ID(Res* cart, char s[][7], int n);

Res*  Buy(int Index, tm1 T);

void get_dep_time(Res*cart, tm1* time);

int check_out(Res* cart, Purchase*);


#endif