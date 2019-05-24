#define _CRT_SECURE_NO_WARNINGS
#include"io.h"
#include"structs.h"
#include"reserve.h"
#include"foo.h"
#include<cstdio>
#include<conio.h>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<cassert>

Visitor user;
Admin ad;
Res* ShoppingCart = NULL;
int record = 0;

void init() {
	//something
}

void standby() {
	printf("Press c to continue or q to quit\n");
	char c = 0;
	while(!c) {
		do {
			c = _getch();
		} while(!isalnum(c));
		if(!c)
			illegal_input_error(-1);
		else {
			c = tolower(c);
			if(c != 'c' && c != 'q') {
				illegal_input_error(0);
				c = 0;
			}
			if(c == 'q')
				exit(0);
			if(c == 'c') {
				//nothing
			}
		}
	}
}

int tourist_login() {
	system_flush();

	char ID[11], pwd[11];
	int result = read_tourist_id(ID);
	if(result == 0)
		return 0;
	result = read_tourist_pwd(ID, pwd);
	if(result == 0)
		return 0;

	bool ok = tourist_login_chk(ID, pwd);
	if(!ok) {
		printf("ID or password error!\n");
		standby();
		return 0;
	}

	return welcome_tourist();
}

int welcome_tourist() {
	system_flush();
	print_stars();
	printf("Welcome back, %s !\n", user.ID);
	print_stars();
	standby();
	system_flush();

	while(1) {
		system_flush();
		print_stars();
		printf("What would you like to do?\n");
		print_stars();
		printf("\n\n");

		printf("Please select your choice:\n");
		printf("a)Query attractions\n"
			   "b)Sort and display attractions\n"
			   "c)Check&confirm order\n"
			   "d)Check&Modify order\n"
			   "e)Edit tourist information\n"
			   "f)Check history order\n"
			   "q)Quit\n");
		int id = read_tourist_choice();
		while(id == 0 || id == 7) {
			if(id == 0) {
				illegal_input_error(-1);
			}
			if(id == 7) {
				illegal_input_error(0);
			}
			id = read_tourist_choice();
		}
		if(id == -1)
			break;

		if(id == 1) {
			query();
		}
		if(id == 2) {
			Sort();
		}
		if(id == 3) {
			confirm_order();
		}
		if(id == 4) {
			//modify order
			modify_order();
		}
		if(id == 5) {
			//Edit info
			tourist_edit_info();
		}
		if(id == 6) {
			//history order
			chk_history_order();
		}
	}

	return 0;
}

int spot_query() //根据景点名字进行查询
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++) 
	{
		sp[i] = (Spot*)malloc(sizeof(Spot));
		memset(sp[i], 0, sizeof(Spot));
	}

	int spot_cnt = getSpotInfo(sp);

	if(spot_cnt == 0) 
	{
		printf("No spot information!\n");
		system("pause");
		return 1;
	}

	int cur = 0;           //定义目前的景点在结构体中的下标
	while(1) 
	{                         
		print_spot(sp[cur]);
		printf("\n\n");

		printf("Your choice:\n");

		if(cur > 0) 
			printf("a)Previous Spot   ");
		else
		{
			for (int i = 0; i < 16; i++)
				putchar(' ');
		}

		if(cur < spot_cnt - 1)
			printf("d)Next Spot ");
		else 
		{
			for(int i = 0; i < 9; i++)
				putchar(' ');
		}

		printf("q)Quit\n");

		int id;//ID控制用户输入。cur控制景点的索引

		do {
			id = read_spot_management_choice();
			if(id == 3) 
				illegal_input_error(1);
		} while(id == 0 || id == 3);

		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else 
				cur--;
		}

		if(id == 2) 
		{
			if(cur == spot_cnt - 1) 
			{
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else 
				cur++;
		}
	}

	for(int i = 0; i < 30; i++)
		free(sp[i]);

	return 1;
}

int admin_login() {
	system_flush();

	char ID[11], pwd[11];
	int result = read_admin_id(ID);
	if(result == 0)
		return 0;
	result = read_admin_pwd(ID, pwd);
	if(result == 0)
		return 0;

	bool ok = admin_login_chk(ID, pwd);
	if(!ok) {
		printf("ID or password error!\n");
		standby();
		return 0;
	}

	return welcome_admin();
}

int query_all_order() {
	Purchase *purs[30];
	for(int i = 0; i < 30; i++) {
		purs[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(purs);

	if(pur_cnt == 0) {
		system_flush();
		printf("No order found!\n");
		printf("Press any key to continue\n");
		system("pause");
		return 1;
	}

	int cur = 0;
	while(1) {
		system_flush();
		print_order(purs[cur]);
		printf("\n");
		if(cur > 0) {
			printf("a)Previous   ");
		} else {
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < pur_cnt - 1) {
			printf("d)Next   ");
		} else {
			for(int i = 0; i < 0; i++)
				putchar(' ');
		}
		printf("q)Quit\n");
		int id;
		do {
			id = pre_or_nxt();
		} while(id == 0 || id == 4);

		if(id == 1) {
			if(cur == 0) {
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur--;
			}
		}
		if(id == 2) {
			if(cur == pur_cnt - 1) {
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur++;
			}
		}
		if(id == -1)
			break;
	}

	for(int i = 0; i < 30; i++) {
		free(purs[i]);
	}
	return 1;
}

int chk_history_order() {
	Purchase *ps[50];
	for(int i = 0; i < 50; i++) {
		ps[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(ps);

	int ans[50], ans_cnt = 0;
	for(int i = 0; i < pur_cnt; i++) {
		if(strcmp(user.ID, ps[i]->Visitor_ID) == 0) {
			ans[ans_cnt++] = i;
		}
	}

	if(ans_cnt == 0) {
		system_flush();
		printf("You have no history order!\n");
		printf("Press any key to continue\n");
		system("pause");
	}

	int cur = 0;
	if(ans_cnt > 0) while(1) {
		system_flush();
		int idx = ans[cur];
		print_order(ps[idx]);
		printf("\n\n");

		if(cur > 0) {
			printf("a)Previous   ");
		} else {
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < ans_cnt - 1) {
			printf("b)Next   ");
		} else {
			for(int i = 0; i < 7; i++)
				putchar(' ');
		}
		printf("q)Quit\n");
		printf("o)Cancel this order if you still have at least 24 hours before depatture\n");

		int id;
		do {
			id = pre_or_nxt();
			if(id == 0)
				illegal_input_error(-1);
			if(id == 4)
				illegal_input_error(0);
		} while(id == 0 || id == 4);

		if(id == -1)
			break;
		if(id == 1) {
			if(cur == 0) {
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur--;
			}
		}
		if(id == 2) {
			if(cur == ans_cnt - 1) {
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur++;
			}
		}
		if(id == 3) {
			//cancel
			system_flush();
			printf("We will refund you wiout discount! Please confirm(c) or quit(q)\n");
			int id;
			do {
				id = confirm_or_quit();
				if(id == 0)
					illegal_input_error(-1);
				if(id == 2)
					illegal_input_error(0);
			} while(id == 0 || id == 2);
			
			if(id == -1)
				continue;
			if(id == 1) {
				cancel_order(idx);
				break;
			}
		}
	}

	for(int i = 0; i < 50; i++) {
		free(ps[i]);
	}

	return 1;
}

int sort_by_order_amount() {
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_cnt = getSpotInfo(sp);
	Purchase *ps[50];
	for(int i = 0; i < 50; i++) {
		ps[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(ps);

	int amount[30], res[30];
	memset(amount, 0, sizeof(amount));
	for(int i = 0; i < pur_cnt; i++) {
		for(int j = 0; j < ps[i]->spot_number; j++) {
			printf("%s\n", ps[i]->s[j]);
			for(int k = 0; k < spot_cnt; k++) {
				if(strcmp(sp[k]->ID, ps[i]->s[j]) == 0) {
					amount[k]++;
					break;
				}
			}
		}
	}
	for(int i = 0; i < pur_cnt; i++) {
		int jj = -1;
		for(int j = 0; j < pur_cnt; j++) {
			if(jj == -1 || amount[j] < amount[jj]) {
				jj = j;
			}
		}
		res[i] = jj;
	}

	int cur = 0;
	while(1) {
		system_flush();
		int idx = res[cur];
		print_spot(sp[idx]);
		printf("\nOrder amount: %d\n", amount[idx]);
		printf("\n");
		if(cur > 0) {
			printf("a)Previous   ");
		} else {
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < spot_cnt - 1) {
			printf("d)Next   ");
		} else {
			for(int i = 0; i < 7; i++)
				putchar(' ');
		}
		printf("q)Quit\n");
		
		int id;
		do {
			id = pre_or_nxt();
			if(id == 0)
				illegal_input_error(-1);
			if(id == 3 || id == 4)
				illegal_input_error(0);
		} while(id == 0 || id == 3 || id == 4);
		if(id == 1) {
			if(cur == 0) {
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur--;
			}
		}
		if(id == 2) {
			system_flush();
			printf("There is no next spot!\n");
			printf("Press any key to continue\n");
			system("pause");
		} else {
			cur++;
		}
		if(id == -1) {
			break;
		}
	}

	for(int i = 0; i < 30; i++) {
		free(sp[i]);
	}
	for(int i = 0; i < 50; i++) {
		free(ps[i]);
	}

	return 0;
}

int sort_by_numof_views() {
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_cnt = getSpotInfo(sp);
	Purchase *ps[50];
	for(int i = 0; i < 50; i++) {
		ps[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(ps);

	int people[30], res[30];
	memset(people, 0, sizeof(people));
	for(int i = 0; i < pur_cnt; i++) {
		for(int j = 0; j < ps[i]->spot_number; j++) {
			for(int k = 0; k < spot_cnt; k++) {
				if(strcmp(sp[k]->ID, ps[i]->s[j]) == 0) {
					people[k] += ps[i]->number_of_people;
					break;
				}
			}
		}
	}
	for(int i = 0; i < pur_cnt; i++) {
		int jj = -1;
		for(int j = 0; j < pur_cnt; j++) {
			if(jj == -1 || people[j] < people[jj]) {
				jj = j;
			}
		}
		res[i] = jj;
	}

	int cur = 0;
	while(1) {
		system_flush();
		int idx = res[cur];
		print_spot(sp[idx]);
		printf("\nNumber of views: %d\n", people[idx]);
		printf("\n");
		if(cur > 0) {
			printf("a)Previous   ");
		} else {
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < spot_cnt - 1) {
			printf("d)Next   ");
		} else {
			for(int i = 0; i < 7; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
			if(id == 0)
				illegal_input_error(-1);
			if(id == 3 || id == 4)
				illegal_input_error(0);
		} while(id == 0 || id == 3 || id == 4);
		if(id == 1) {
			if(cur == 0) {
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur--;
			}
		}
		if(id == 2) {
			system_flush();
			printf("There is no next spot!\n");
			printf("Press any key to continue\n");
			system("pause");
		} else {
			cur++;
		}
		if(id == -1) {
			break;
		}
	}

	for(int i = 0; i < 30; i++) {
		free(sp[i]);
	}
	for(int i = 0; i < 50; i++) {
		free(ps[i]);
	}

	return 0;
}

int sort_by_profit() {
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_cnt = getSpotInfo(sp);
	Purchase *ps[50];
	for(int i = 0; i < 50; i++) {
		ps[i] = (Purchase*)malloc(sizeof(Purchase));
	}
	int pur_cnt = getPurchaseInfo(ps);

	int res[30];
	float profit[30];
	memset(profit, 0, sizeof(profit));
	for(int i = 0; i < pur_cnt; i++) {
		for(int j = 0; j < ps[i]->spot_number; j++) {
			for(int k = 0; k < spot_cnt; k++) {
				if(strcmp(sp[k]->ID, ps[i]->s[j]) == 0) {
					profit[k] += sp[k]->price * sp[k]->discount * (isPeak(sp[k]) ? 1 : sp[k]->non_peak_discount);
					break;
				}
			}
		}
	}
	for(int i = 0; i < pur_cnt; i++) {
		int jj = -1;
		for(int j = 0; j < pur_cnt; j++) {
			if(jj == -1 || profit[j] < profit[jj]) {
				jj = j;
			}
		}
		res[i] = jj;
	}

	int cur = 0;
	while(1) {
		system_flush();
		int idx = res[cur];
		print_spot(sp[idx]);
		printf("\nProfit: %.2f\n", profit[idx]);
		printf("\n");
		if(cur > 0) {
			printf("a)Previous   ");
		} else {
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < spot_cnt - 1) {
			printf("d)Next   ");
		} else {
			for(int i = 0; i < 7; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
			if(id == 0)
				illegal_input_error(-1);
			if(id == 3 || id == 4)
				illegal_input_error(0);
		} while(id == 0 || id == 3 || id == 4);
		if(id == 1) {
			if(cur == 0) {
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} else {
				cur--;
			}
		}
		if(id == 2) {
			system_flush();
			printf("There is no next spot!\n");
			printf("Press any key to continue\n");
			system("pause");
		} else {
			cur++;
		}
		if(id == -1) {
			break;
		}
	}

	for(int i = 0; i < 30; i++) {
		free(sp[i]);
	}
	for(int i = 0; i < 50; i++) {
		free(ps[i]);
	}

	return 0;
}

int admin_chk_order_info() {
	system_flush();
	printf("You want to sort the spots by:\n");
	printf("a)Ordered amount\n"
		   "b)Number of views\n"
		   "c)Profit\n"
	"q)Quit\n");

	int id;
	do {
		id = read_admin_chk_order_info_choice();
		if(id == 0)
			illegal_input_error(-1);
		if(id == 4)
			illegal_input_error(0);
	} while(id == 0 || id == 4);

	if(id == 1) {
		//ordered amount
		sort_by_order_amount();
	}
	if(id == 2) {
		//num of views
		sort_by_numof_views();
	}
	if(id == 3) {
		//profit
		sort_by_profit();
	}

	return 0;
}

int welcome_admin() {
	system_flush();
	print_stars();
	printf("Welcome back, %s!\n", ad.ID);
	print_stars();
	printf("\n\n");
	printf("Please select your choice\n");
	printf("a)Order mangement\n"
	"b)Check users' order information\n"
	"c)Spot management\n"
	"d)Personal information management\n"
	"q)Quit\n");

	int id;
	do {

		id = read_admin_choice();
		if(id == 0)
			illegal_input_error(-1);
		if(id == 5) 
			illegal_input_error(0);
	} while(id == 0 || id == 5);
	if(id == -1)
		return 0;

	if(id == 1) {
		//order management
		query_all_order();
		return welcome_admin();
	} else if(id == 2) {
		//check user order info
		admin_chk_order_info();
		return welcome_admin();
	} else if(id == 3) {
		//spot management
		system_flush();
		printf("Please select your choice\n");
		printf("a)Spot query\n"
			   "b)Add a new spot\n"
			   "q)Quit\n");
		int id;
		do {
			id = read_query_choice();
		} while(id == 0 || id == 3);
		if(id == -1)
			return welcome_admin();

		if(id == 1) {
			//spot query
			int nxt = spot_query();
			return welcome_admin();
		} else if(id == 2) {
			//add spot
			int nxt = addSpot();
			return welcome_admin();
		} else {
			//no good
			assert(false);
		}
	} else if(id == 4) {
		//personal info
		system_flush();
		printf("What do you want to modify?\n");
		printf("a)Password\n"
			   "b)Email\n"
			   "q)Quit\n");
		int id;
		do {
			id = read_personal_info_manage_choice();
			if(id == 0) {
				illegal_input_error(-1);
			}
			if(id == 3) {
				illegal_input_error(0);
			}
		} while(id == 0 || id == 3);

		if(id == -1)
			return 0;
		if(id == 1) {
			//Pwd
			editPwd(ad.pwd);
		}
		if(id == 2) {
			//Email
			editEmail(ad.Email);
		}
		return welcome_admin();

	} else {
		//no good
		assert(0);
	}

	//nothing should be here!!!!
	return 0;
}

int welcome() {//-1: quit, 0: again
	system_flush();

	print_stars();
	printf("Welcome to group tourists attractions booking system!\n");
	print_stars();

	printf("Please select your identification:\n"
		   "a) Tourist\n"
		   "b) Administration\n"
		   "q) quit\n");

	int id = read_identification();
	while(id == 0 || id == 3) {
		if(id == 0) {
			illegal_input_error(-1);
		}
		if(id == 3) {
			illegal_input_error(0);
		}
		id = read_identification();
	}
	if(id == -1)
		return -1;

	if(id == 1) {
		return tourist_login();
	}
	if(id == 2) {
		return admin_login();
	}

	return 0;
}

int tourist_edit_info() {
	system_flush();
	printf("Please select your choice:\n");
	printf("a)Tel\n"
		   "b)Password\n"
		   "q)Quit\n");

	int id;
	do {
		id = read_tourist_edit_info_choice();
		if(id == 0)
			illegal_input_error(-1);
		if(id == 3)
			illegal_input_error(0);
	} while(id == 0 || id == 3);

	if(id == 1) {
		//Tel
		edit_tourist_Tel(user.Tel);
	}
	if(id == 2) {
		//Pwd
		edit_tourist_pwd(user.pwd);
	}

	return 0;
}

int query_by_name(char *name) //通过名字查询
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_cnt = getSpotInfo(sp);//函数返回景点结构体个数
	int found = 0;

	for(int i = 0; i < spot_cnt; i++) 
	{
		if(strcmp(sp[i]->name, name) == 0) //判断两个字符串是否相等
		{
			found = 1;
			system_flush();
			printf("Result found!\n");
			print_spot(sp[i]);
			printf("\n");
			print_stars();

			printf("Would you like to order this one (o to order, q to quit)?\n");
			while(1) 
			{
				char c = 0;
				
			/*	do {
					c = getchar();
				} while (isspace(c));*///C位空白返回
				do {
					c = _getch();
				} while(!isalnum(c));

				c = tolower(c);//大小写转换

				if(c == 'o') 
				{
					order_spot(i);//进入购物车
					break;
				}
				else if(c == 'q') 
					break;
				else
					illegal_input_error(0);
			}
			break;
		}
	}

	if(found == 0) //当没有对应的景点名称时
	{
		system_flush();
		printf("There is no such spot!\n");
		printf("Press any key to continue\n");
		system("pause");
	}

	for(int i = 0; i < 30; i++) 
		free(sp[i]);

	return 1;
}

int query_by_ticket() 
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++) 
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_cnt = getSpotInfo(sp);
	int ans[30], ans_cnt = 0;

	for(int i = 0; i < spot_cnt; i++) //将索引与结构体数组一一对应
	{
		if(sp[i]->tickets > 0) 
			ans[ans_cnt++] = i;
	}

	int cur = 0;

	while(1) 
	{
		system_flush();
		print_spot(sp[cur]);//打印函数
		printf("\n");
		if(cur > 0) 
			printf("a)Previous   ");
		else 
		{
			for(int i = 0; i < 11; i++)
				putchar(' ');
		}
		if(cur < ans_cnt - 1) 
			printf("d)Next   ");
		else 
		{
			for (int i = 0; i < 9; i++)
				putchar(' ');
		}

		printf("q)Quit\n");
		print_stars();
		printf("\nWould you like to order this one (o to order)?\n");
		print_stars();

		int id;
		do {
			id = pre_or_nxt();
			if(id == 0) 
				illegal_input_error(-1);
		} while(id == 0 || id == 4);

		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else 
				cur--;
		}

		if(id == 2) 
		{
			if(cur == ans_cnt - 1) 
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else 
				cur++;
		}
		if(id == 3) 
			order_spot(cur);
	}

	for(int i = 0; i < 30; i++) 
		free(sp[i]);

	return 0;
}

int query_by_discount() 
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++) 
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_cnt = getSpotInfo(sp);
	int ans[30], ans_cnt = 0;

	for(int i = 0; i < spot_cnt; i++) 
	{
		if(sp[i]->discount < 1.0f) //结构体中用float储存的
			ans[ans_cnt++] = i;
	}

	int cur = 0;

	while(1) 
	{
		system_flush();
		print_spot(sp[cur]);
		printf("\n");
		if(cur > 0) 
			printf("a)Previous   ");
		else 
			for(int i = 0; i < 11; i++)
				putchar(' ');

		if(cur < ans_cnt - 1) 
			printf("d)Next   ");
		else 
		{
			for(int i = 0; i < 9; i++)
				putchar(' ');
		}

		printf("q)Quit\n");
		print_stars();
		printf("\nWould you like to order this one (o to order)?\n");
		print_stars();

		int id;
		do {
			id = pre_or_nxt();
			if (id == 0)
				illegal_input_error(-1);
		} while(id == 0 || id == 4);

		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else
				cur--;
		}
		if(id == 2) 
		{
			if(cur == ans_cnt - 1) 
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else 
				cur++;
		}
		if(id == 3)
			order_spot(cur);
	
	}

	for(int i = 0; i < 30; i++) 
		free(sp[i]);

	return 0;
}

int query_by_belong(char *belong) 
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++) 
		sp[i] = (Spot*)malloc(sizeof(Spot));


	int spot_cnt = getSpotInfo(sp);
	int found = 0;
	int ans[30], ans_cnt = 0;

	for(int i = 0; i < spot_cnt; i++) 
	{
		if(strcmp(sp[i]->belong, belong) == 0) 
		{
			found = 1;
			ans[ans_cnt++] = i;
		}
	}

	int cur = 0;
	while(1) 
	{
		system_flush();
		print_spot(sp[cur]);
		printf("\n");

		if(cur > 0) 
			printf("a)Previous   ");
		else 
			for(int i = 0; i < 11; i++)
				putchar(' ');
	
		if(cur < ans_cnt - 1) 
			printf("d)Next   ");
		else 
		{
			for(int i = 0; i < 9; i++)
				putchar(' ');
		}

		printf("q)Quit\n");
		print_stars();
		printf("\nWould you like to order this one (o to order)?\n");
		print_stars();

		int id;
		do {
			id = pre_or_nxt();
			if(id == 0) 
				illegal_input_error(-1);
		} while(id == 0 || id == 4);

		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else
				cur--;
		}
		if(id == 2) 
		{
			if(cur == ans_cnt - 1) 
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			} 
			else 
				cur++;
		}
		if(id == 3) 
			order_spot(cur);
	}

	if(found == 0) 
	{
		system_flush();
		printf("There is no such spot!\n");
		printf("Press any key to continue\n");
		system("pause");
	}

	for(int i = 0; i < 30; i++)
		free(sp[i]);

	return 3 * found;
}

int query() 
{
	system_flush();
	print_stars();
	printf("You want to query by?\n");
	print_stars();
	printf("\n\n");

	printf("a)Attaractions' names\n"
		   "b)Wether tickets available\n"
		   "c)View spot\n"
		   "d)Discount\n"
		   "q)Quit\n");
	int id = read_query_choice();

	while(id == 0 || id == 5) 
	{
		if(id == 0) 
			illegal_input_error(-1);//0  5均为错误输入
		if(id == 5) 
			illegal_input_error(0);
		id = read_query_choice();//函数作用返回用户输入的指令，前进后退或者放弃与确认预定
	}
	if(id == -1)//Q (-1)表示返回上亿界面
		return -1;

	while(id == 1) 
	{
		system_flush();
		printf("Please enter spot's name (or q to quit): \n");
		char buff[1000];
		bool ok = true;
		do {
			setbuf(stdin, NULL);
			ok = fgets(buff, 1000, stdin);
			buff[strlen(buff) - 1] = 0;
			int len = strlen(buff);
			if(len == 1 && buff[0] == 'q')
				return 0;
			if(len <= 1 || len > 50) {
				system_flush();
				printf("You should enter more than 1 and less than 15 characters! Please try again\n");
				ok = false;
			}
		} while(!ok);
		id = query_by_name(buff);
	}

	while(id == 2)
		id = query_by_ticket();

	while(id == 3) 
	{
		system_flush();
		printf("Please enter where spot belong to (q to quit)\n");
		char buff[1000];
		bool ok = true;
		do {
			setbuf(stdin, NULL);
			ok = (scanf("%s", buff) == 1);
			int len = strlen(buff);
			if(len == 1 && buff[0] == 'q') {
				return 0;
			}
			if(len <= 1 || len > 20) {
				system_flush();
				printf("You should enter more than 1 and less than 20 characters (or q to quit)! Please try again\n");
				ok = false;
			}
		} while(!ok);
		id = query_by_belong(buff);
	}

	while(id == 4) 
		id = query_by_discount();

	return 1;
}

int sort_by_price() 
{
	Spot *sp[30];

	for(int i = 0; i < 30; i++) 
		sp[i] = (Spot*)malloc(sizeof(Spot));
	int spot_cnt = getSpotInfo(sp);

	int res[30], mark[30];
	//res[30] = 0;
	//mark[30] = 0;
	memset(mark, 0, sizeof(mark));

	for(int i = 0; i < spot_cnt; i++) 
	{
		int jj = -1;
		for(int j = 0; j < spot_cnt; j++) if(!mark[j]) 
		{
			if(jj == -1 || sp[j]->price < sp[jj]->price) 
				jj = j;
		}
		mark[jj] = 1;
		res[i] = jj;
	}

	int cur = 0;
	while(1) 
	{
		system_flush();
		int idx = res[cur];
		print_spot(sp[idx]);//按照排序后的结构体数组的顺序打印（一次一个）

		printf("\nWould you like to order this one (o to order)?\n");
		printf("\n");

		if(cur > 0) 
			printf("a)Previous   ");
		else 
		{
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}

		if(cur < spot_cnt - 1)
			printf("d)Next   ");
		else 
		{
			for(int i = 0; i < 9; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
		} while(id == 0 || id == 4);
		
		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else 
				cur--;
		}

		if(id == 2) 
		{
			if(cur == spot_cnt - 1) 
			{
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else
				cur++;
		}
		if(id == 3)
			order_spot(idx);
	}

	for(int i = 0; i < 30; i++) 
		free(sp[i]);

	return 0;
}

int sort_by_amount() 
{
	Spot *sp[30];
	for(int i = 0; i < 30; i++) 
		sp[i] = (Spot*)malloc(sizeof(Spot));
	int spot_cnt = getSpotInfo(sp);

	int res[30], mark[30], amount[30];
	/*amount[30] = 0;
	mark[30] = 0;*/

	memset(amount, 0, sizeof(amount));
	memset(mark, 0, sizeof(mark));

	FILE *fin = fopen("PurInfo.txt", "r");
	if(!fin)
		file_error(0);
	Purchase p;
	while(fread(&p, sizeof(Purchase), 1, fin), !feof(fin)) {
		for(int i = 0; i < p.spot_number; i++) {
			for(int j = 0; j < spot_cnt; j++) {
				if(strcmp(sp[j]->ID, p.s[i]) == 0) {
					amount[j]++;
					break;
				}
			}
		}
	}
	for(int i = 0; i < spot_cnt; i++) {
		int jj = -1;
		for(int j = 0; j < spot_cnt; j++) if(!mark[j]) {
			if(jj == -1 || amount[j] < amount[jj]) {
				jj = j;
			}
		}
		res[i] = jj;
		mark[jj] = 1;
	}

	int cur = 0;
	while(1) 
	{
		system_flush();
		int idx = res[cur];
		print_spot(sp[idx]);
		printf("\nWould you like to order this one (o to order)?\n");
		printf("\n");

		if(cur > 0) 
			printf("a)Previous   ");
		else 
		{
			for(int i = 0; i < 13; i++)
				putchar(' ');
		}
		if(cur < spot_cnt - 1) 
			printf("d)Next   ");
		else 
		{
			for(int i = 0; i < 9; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
			if(id == 4)
				illegal_input_error(0);
		} while(id == 0 || id == 4);

		if(id == -1)
			break;
		if(id == 1) 
		{
			if(cur == 0) 
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else 
				cur--;
		}
		if(id == 2) 
		{
			if(cur == spot_cnt - 1) 
			{
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			} 
			else
				cur++;
		}
		if(id == 3)
			order_spot(idx);
	}

	for(int i = 0; i < 30; i++)
		free(sp[i]);

	return 0;
}

int Sort() 
{
	system_flush();
	printf("What do you want to sort by?\n");
	printf("a)Price\n");
	printf("b)Ordered amount\n");
	printf("q)Quit\n");

	int id;
	do {
		id = read_sort_choice();
	} 
	while(id == 0 || id == 3);

	if(id == -1) 
		return 0;
	if(id == 1) 
		sort_by_price();
	else if(id == 2) 
		sort_by_amount();

	return 0;
}

void test() {

	FILE* fin = fopen("AdminInfo.txt", "r");
	while(fread(&ad, sizeof(Admin), 1, fin), !feof(fin)) {
		printf("%s\n%s\n%s\n%s\n", ad.ID, ad.pwd, ad.Tel, ad.Email);
		printf("\n");
	}
	fclose(fin);
	system("pause");
	exit(0);
}

void test1() {
	FILE *fin = fopen("UserInfo.txt", "r");
	while(fread(&user, sizeof(Visitor), 1, fin), !feof(fin)) {
		printf("User ID: %s\n", user.ID);
		printf("User password: %s\n", user.pwd);
		printf("User Tel: %s\n", user.Tel);
		printf("type: %d, num: %d, min age: %d, max age: %d\n", user.type, user.num, user.MinAge, user.MaxAge);
		printf("\n");
	}
	fclose(fin);
	system("pause");
	exit(0);
}

void test2() {
	FILE *fin = fopen("PurInfo.txt", "r");
	Purchase p;
	while(fread(&p, sizeof(Purchase), 1, fin), !feof(fin)) {
		//printf("")
	}
}

void test3() {
	FILE *fin = fopen("SpotInfo.txt", "r");
	Spot sp;
	while(fread(&sp, sizeof(Spot), 1, fin), !feof(fin)) {
		system_flush();
		print_spot(&sp);
		system("pause");
	}

	fclose(fin);
}

int main() {

	int t;
	do {
		t = welcome();
		if(t == 0) {
			continue;
		}
	} while(t != -1);

	return 0;
}
