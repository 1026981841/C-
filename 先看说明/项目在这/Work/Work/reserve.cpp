#define _CRT_SECURE_NO_WARNINGS
#include"shoppingcart.h"
#include"IO.h"
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<conio.h>
#include<cstring>

extern Res* ShoppingCart;

void struct_tm1_assign(tm1 *t1, tm1 *t2) {
	t1->tm1_day = t2->tm1_day;
	t1->tm1_mon = t2->tm1_mon;
	t1->tm1_year = t2->tm1_year;
}

int getPurchaseInfo(Purchase **ps) {
	FILE *fin = fopen("PurInfo.txt", "r");
	int cnt = 0;
	while(fread(ps[cnt++], sizeof(Purchase), 1, fin), !feof(fin)) {}
	cnt--;
	fclose(fin);
	return cnt;
}

int order_spot(int id) {
	tm1 T;
	int nxt = get_time_input(&T);
	if(nxt == 0)
		return 0;
	if(nxt == -1)
		return 0;
	ShoppingCart = Buy(id, T);
	printf("Ordering successful!\n");
	printf("Press any key to continue\n");
	system("pause");
	return 1;
}

int confirm_order() {
	system_flush();
	print_stars();
	printf("Here are yur orders\n");
	print_stars();
	printf("\n");
	search_purchase(ShoppingCart);
	printf("Please enter your choice:\n");
	printf("c)Confirm\n"
		   "q)Quit\n");
	int id;
	do {
		id = read_confirm_choice();
	} while(id == 0 || id == 2);
	if(id == -1)
		return 0;
	if(ShoppingCart == NULL) {
		printf("Your haven't ordered yet!\n");
		printf("Press any key to continue\n");
		system("pause");
		return 0;
	}
	Purchase p;
	int result = check_out(ShoppingCart, &p);
	if(result < 0) {
		Spot *sp[30];
		for(int i = 0; i < 30; i++) {
			sp[i] = (Spot*)malloc(sizeof(Spot));
		}
		getSpotInfo(sp);
		printf("Spot %s has sold out!\n", sp[-result]->name);
		printf("Please modify your order\n");
		return 1;
	}

	FILE *fout = fopen("PurInfo.txt", "a+");
	fwrite(&p, sizeof(Purchase), 1, fout);
	fclose(fout);

	printf("Order confirmed!\n");
	printf("Press any key to continue\n");
	system("pause");
	
	return 1;
}

int modify_order() {
	system_flush();
	print_stars();
	printf("Your order:\n");
	print_stars();
	search_purchase(ShoppingCart);
	char buff[1000];
	bool ok = true;
	do {
		printf("\nWhich one do you want to remove? Please type it's ID (or q to quit):\n");
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q') {
			return 0;
		}
		if(len != 6) {
			system_flush();
			printf("You should enter exactly 6 characters! Please try again\n");
			printf("Press any key to continue\n");
			system("pause");
			ok = false;
		}
	} while(!ok);
	int result = del_shoppingcart(ShoppingCart, buff);
	if(result == 0) {
		system_flush();
		printf("There is no such spot! Please check your input\n");
		printf("Press any key to continue\n");
		system("pause");
		return 1;
	}

	system_flush();
	printf("Dleted successfully!\n");
	printf("Press any key to continue\n");
	system("pause");

	return 1;
}

int cancel_order(int idx) {
	//0: can't cancel, 1: can cancel
	Purchase *ps[50];
	for(int i = 0; i < 50; i++) {
		ps[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(ps);
	time_t rawtime = time(0);
	tm now_time = *localtime(&rawtime);
	if(ps[idx]->tm.tm1_year == now_time.tm_year + 1900 && ps[idx]->tm.tm1_mon == now_time.tm_mday + 1 && ps[idx]->tm.tm1_day + 1 <= now_time.tm_mday
	   || (ps[idx]->tm.tm1_year == now_time.tm_year + 1900 + 1 && ps[idx]->tm.tm1_mon == 1 && now_time.tm_mon + 1 == 12 && ps[idx]->tm.tm1_day== 31 && now_time.tm_mday < 2)) {
		system_flush();
		printf("Sorry, we cannot cancel your order since there less than 1 day before you departure\n");
		printf("Press any key to continue\n");
		system("pause");
	} else {
		FILE *fout = fopen("PurInfo.txt", "w+");
		for(int i = 0; i < pur_cnt; i++) if(i != idx) {
			fwrite(ps[i], sizeof(Purchase), 1, fout);
		}
		fclose(fout);

		Spot *sp[30];
		for(int i = 0; i < 30; i++) {
			sp[i] = (Spot*)malloc(sizeof(Spot));
		}
		int spot_cnt = getSpotInfo(sp);
		fout = fopen("SpotInfo.txt", "w+");
		for(int i = 0; i < spot_cnt; i++) {
			for(int j = 0; j < ps[idx]->spot_number; j++) {
				if(strcmp(sp[i]->ID, ps[idx]->s[j]) == 0) {
					sp[i]->tickets += ps[idx]->number_of_people;
					break;
				}
			}
			fwrite(sp[i], sizeof(Spot), 1, fout);
		}
		fclose(fout);
		for(int i = 0; i < 30; i++) {
			free(sp[i]);
		}
	}

	for(int i = 0; i < 50; i++) {
		free(ps[i]);
	}

	printf("Cancel successful!\n");
	printf("Press any key to continue\n");
	system("pause");

	return 1;

}
