#define _CRT_SECURE_NO_WARNINGS
#include"io.h"
#include<cstdio>
#include<conio.h>
#include<cctype>
#include<cstring>
#include<cstdlib>

int Abs(int x) {
	return x < 0 ? -x : x;
}

int Max(int a, int b) {
	return a > b ? a : b;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

void system_flush() {
	system("cls");
	srand(time(0));
	char cmd[20];
	strcpy(cmd, "color ");
	int len = strlen(cmd);
	int t1 = rand() % 16;
	int t2;
	int ok;
	do {
		ok = 1;
		t1 = 4 + rand() % 4 + 8 * (rand() % 2);
		t2 = rand() % 4 + 8 * (rand() % 2);
		if(Abs(t1 - t2) == 1 || (Abs(t1 - t2) >= 6 && Abs(t1 - t2) <= 10))
			ok = 0;
		if(t2 == 8)
			ok = 0;
	} while(!ok);

	cmd[len] = t1 < 10 ? '1' + t1 - 1 : 'a' + t1 - 10;
	cmd[len + 1] = t2 < 10 ? '1' + t2 - 1 : 'a' + t2 - 10;
	cmd[len + 2] = 0;
	system(cmd);
}

void file_error(int t) {//0: failed open a file, 1: failed reading a file
	if(t == 0)
		printf("Failed to open the file\n");
	if(t == 1)
		printf("Failed to read the file\n");

	system("pause");
	exit(0);
}

void illegal_input_error(int t) {//-1: empty input, 0: selection non-exist, 1: id length overflow, 2: id contains non alnum chars 3: pwd length overflow
	//if(t == -1)
	//	printf("Please enter your input!\n");
	if(t == -1)
		return;
	//if(t == 0)
	//	printf("Please enter the right selection!\n");
	if(t == 0)
		return;
	if(t == 1)
		printf("Your ID should be more than 6 characters and no more than 10 characters!\n");
	if(t == 2)
		printf("Your ID should contains only numbners, lowercase and uppercase lattin letters!\n");
	if(t == 3)
		printf("Your password should be more than 6 characters and no more than 10 characters!\n");

	printf("Press any key to continue\n");
	system("pause");
	printf("\n");
}

int read_identification() {
	// 0: no inputs after enter, 1 : a, 2 : b, 3 : illegal, -1 : quit
	char c = '\0';
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c) 
		return 0;
	c = tolower(c);
	if(c != 'a' && c != 'b' && c != 'q') return 3;
	if(c == 'q') return -1;
	return c - 'a' + 1;
}

int read_tourist_choice() {
	//0: no inputs, -1: quit, 1, 2: a, b, 3: c, 4: d, 5: e, 6: f, 7: illegal
	char c = '\0';
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'q') return -1;
	if(c < 'a' || c > 'f') return 7;
	return c - 'a' + 1;
}

int read_admin_choice() {
	//0: no inputs, -1: quit, 1, 2, 3, 4: a, b, c, d, 5: illegal
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c < 'a' || c > 'd')
		return 5;
	return c - 'a' + 1;
}

int read_query_choice() {
	//0: no inputs after enter, 1: a, 2: b,  3: c, 4: d, 5: illegal, -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c != 'q' && (c < 'a' || c > 'd'))
		return 5;
	if(c == 'q')
		return -1;
	return c - 'a' + 1;
}

int read_sort_choice() {
	//0: no inputs, 1: a, 2: b, 3: illegal, -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	if(c == 'q')
		return -1;
	if(c < 'a' || c > 'b')
		return 3;
	return c - 'a' + 1;
}

int pre_or_nxt() {
	//0: no inputs after enter, 1: a, 2: d, 3: o, 4: illegal -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	if(!c) return 0;
	setbuf(stdin, NULL);
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c == 'o') return 3;
	if(c != 'a' && c != 'd')
		return 4;
	return 1 + (c != 'a');
}

int confirm_or_quit() {
	//0: no input, 1: confirm, 2: illegal, -1: quit
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'c')
		return 1;
	if(c == 'q')
		return -1;
	return 2;
}

int read_add_spot_choice() {
	//0: no input, 1: k, 2: f, 3: illegal, -1: quit
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c == 'k') return 1;
	if(c == 'f') return 2;
	return 3;
}

int modify_or_confirm() {
	//0: no input, 1: c, 2: m, 3: illegal, -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;

	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c == 'c')
		return 1;
	if(c == 'm')
		return 2;
	return 3;
}

int read_too_much_text_choice() {
	//0: no input, 1: c, 2: b, 3; illegal, -1: quit
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
	return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c == 'c')
		return 1;
	if(c == 'b')
		return 2;
	return 3;
}

int read_spot_management_choice() {
	//0: no inputs after enter, 1: a, 2: d, 3: illegal -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c) return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c != 'a' && c != 'd')
		return 3;
	return 1 + (c != 'a');;
}

int read_personal_info_manage_choice() {
	//0: no inputs, 1: a, 2: b, 3: illegal, -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c != 'a' && c != 'b')
		return 3;
	return c - 'a' + 1;
}

int where_does_it_belong_to(char *where) {
	//0: quit, 1: good
	where[0] = 0;
	char buff[1000];
	bool ok = true;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(strlen(buff) > 20) {
			system_flush();
			printf("That's to many words! Try again\n");
			ok = false;
		} 
		if(len == 1 && buff[0] != 'q') {
			system_flush();
			printf("You should enter more than 1 character and less than 20 characters or q to quit\n");
		}
	} while(!ok);
	if(strlen(buff) == 1 && buff[0] == 'q')
		return 0;
	strncpy(where, buff, 20);
	return 1;
}

int read_modify_choice() {
	//0: no inputs, 1 - 13: a - m, 14: illegal, -1: quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);

	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c < 'a' || c > 'm')
		return 14;
	return c - 'a' + 1;
}

int read_tourist_edit_info_choice() {
	//0: no inputs, 1: a, 2: b, 3: illegal input
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;

	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c < 'a' || c > 'b')
		return 3;
	return c - 'a' + 1;
}

int read_confirm_choice() {
	//0: no inputs, 1: c, 2: illegal, -1: quit
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(c == 'c')
		return 1;
	if(c == 'q')
		return -1;
	return 2;
}

int read_admin_chk_order_info_choice() {
	//0: no input, 1: a, 2: b, 3: c, 4: illegal
	char c;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'q')
		return -1;
	if(c < 'a' || c > 'c')
		return 4;
	return c - 'a' + 1;
}


int is_it_ok() {
	//0:no input, 1: yes, 2: no, 3: illegal, -1; quit
	char c = 0;
	do {
		c = _getch();
	} while(!isalnum(c));
	setbuf(stdin, NULL);
	if(!c)
		return 0;
	c = tolower(c);
	if(c == 'y')
		return 1;
	if(c == 'n')
		return 2;
	if(c == 'q')
		return -1;
	return 3;
}

int read_tourist_id(char* togo) {
	printf("Please enter your tourist ID (q to quit)\n");
	char ID[1000];
	//check
	bool ok;
	do {
		setbuf(stdin, NULL);
		ok = true;
		if(!scanf("%s", ID)) {
			ok = false;
			illegal_input_error(-1);
		}
		int len = strlen(ID);
		if(len == 1 && ID[0] == 'q')
			return 0;
		if(len < 6 || len > 10) {
			illegal_input_error(1);
			ok = false;
		}
		for(int i = 0; i < len; i++) {
			if(!isalnum(ID[i])) {
				illegal_input_error(2);
				ok = false;
				break;
			}
		}
	} while(!ok);

	strncpy(togo, ID, 11);
	return 1;
}

int read_tourist_pwd(char *ID, char *togo) {
	char pwd[100];
	char c = 0;
	int len = 0;
	setbuf(stdin, NULL);
	while(1) {
		system("cls");
		printf("Please enter your tourist ID (q to quit)\n");
		printf("%s\n", ID);
		printf("Please enter your tourist password (q to quit)\n");
		if(len == 1 && pwd[0] == 'q')
			putchar('q');
		else for(int i = 0; i < len; i++)
			putchar('*');

		if(!(c = _getch()))
			continue;
		if(c == '\r') {
			if(len == 1 && pwd[0] == 'q')
				return 0;
			if(len < 6) {
				printf("Please enter your tourist password (q to quit)\n");
				printf("%s\n", ID);
				printf("Passwor should be more than 6 characters and less than 11 characters!\n");
				system("pause");
			} else {
				break;
			}
		} else if(c == '\b') {
			if(len) {
				printf("\b \b");
				len--;
			}
		} else if(len < 10) {
			pwd[len++] = c;
		}
	}
	pwd[len] = 0;

	printf("\n");
	strncpy(togo, pwd, 11);
	return 1;
}

int read_admin_id(char* togo) {
	printf("Please enter your administrator ID (q to quit)\n");
	char ID[1000];
	//check
	bool ok;
	do {
		setbuf(stdin, NULL);
		ok = true;
		if(!scanf("%s", ID)) {
			ok = false;
			illegal_input_error(-1);
		}
		int len = strlen(ID);
		if(len == 1 && ID[0] == 'q')
			return 0;
		if(len < 6 || len > 10) {
			illegal_input_error(1);
			ok = false;
		}
		for(int i = 0; i < len; i++) {
			if(!isalnum(ID[i])) {
				illegal_input_error(2);
				ok = false;
				break;
			}
		}
	} while(!ok);

	strncpy(togo, ID, 11);
	return 1;
}

int read_admin_pwd(char *ID, char* togo) {

	char pwd[100];
	char c = 0;
	int len = 0;
	setbuf(stdin, NULL);
	while(1) {
		system("cls");
		printf("Please enter your tourist ID (q to quit)\n");
		printf("%s\n", ID);
		printf("Please enter your tourist password (q to quit)\n");
		if(len == 1 && pwd[0] == 'q')
			putchar('q');
		else for(int i = 0; i < len; i++)
			putchar('*');

		if(!(c = _getch()))
			continue;
		if(c == '\r') {
			if(len == 1 && pwd[0] == 'q')
				return 0;
			if(len < 6) {
				printf("Please enter your tourist password (q to quit)\n");
				printf("%s\n", ID);
				printf("Passwor should be more than 6 characters and less than 11 characters!\n");
				system("pause");
			} else {
				break;
			}
		} else if(c == '\b') {
			if(len) {
				printf("\b \b");
				len--;
			}
		} else if(len < 10) {
			pwd[len++] = c;
		}
	}
	pwd[len] = 0;

	printf("\n");
	strncpy(togo, pwd, 11);
	return 1;
}

bool tourist_login_chk(char *ID, char *pwd) {
	FILE *fin = fopen("UserInfo.txt", "r");
	if(!fin)
		file_error(0);

	Visitor v;
	do {
		fread(&v, sizeof(Visitor), 1, fin);
		if(strcmp(ID, v.ID) == 0 && strcmp(pwd, v.pwd) == 0) {
			Visitor_struct_assign(&user, &v);
			fclose(fin);
			return true;
		}
	} while(!feof(fin));

	fclose(fin);
	return false;
}

bool admin_login_chk(char *ID, char *pwd) {
	FILE *fin = fopen("AdminInfo.txt", "r");
	if(!fin)
		file_error(0);

	Admin AD;
	do {
		fread(&AD, sizeof(Admin), 1, fin);
		if(strcmp(ID, AD.ID) == 0 && strcmp(pwd, AD.pwd) == 0) {
			Admin_struct_assign(&ad, &AD);
			fclose(fin);
			return true;
		}
	} while(!feof(fin));

	fclose(fin);
	return false;
}

int get_time_input(tm1* T) {
	system_flush();
	printf("What is the time you want to departure?\n");
	int t;
	time_t rawtime = time(0);
	tm now_time = *localtime(&rawtime);
	bool ok = true;
	do {
		setbuf(stdin, NULL);
		printf("Please enter the year (or -1 to quit):\n");
		ok = (scanf("%d", &t) == 1);
		if(t == -1)
			return 0;
		if(t < now_time.tm_year + 1900 || t > now_time.tm_year + 1900 + 1) {
			system_flush();
			printf("\n\nSeriously? Please try again\n");
			ok = false;
		}
	} while(!ok);
	T->tm1_year = t;

	system_flush();
	do {
		setbuf(stdin, NULL);
		printf("Please enter the month (or -1 to quit):\n");
		ok = (scanf("%d", &t) == 1);
		if(t == -1)
			return 0;
		if((T->tm1_year == now_time.tm_year + 1900 && t < now_time.tm_mon + 1) || t > 12) {
			system_flush();
			printf("\n\nbSeriously? Please try again\n");
			ok = false;
		}
	} while(!ok);
	T->tm1_mon = t;

	system_flush();
	const int months[] = {-1, 31, now_time.tm_year % 4 ? 28 : 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	do {
		setbuf(stdin, NULL);
		printf("Please enter the day (or -1 to quit):\n");
		ok = (scanf("%d", &t) == 1);
		if(t == -1)
			return 0;
		if((T->tm1_mon == now_time.tm_mon + 1 && t < now_time.tm_mday)|| t > months[T->tm1_mon]) {
			printf("Error input! Please try again\n");
			ok = false;
		}
	} while(!ok);
	T->tm1_day = t;

	return 1;
}

bool lets_enter_something(char *buff, int minLen, int maxLen) {
	setbuf(stdin, NULL);
	buff[0] = 0;
	scanf("%s", buff);
	int len = strlen(buff);
	return len >= minLen && len <= maxLen;
}

void print_stars() {
	printf("*****************************************************");
	printf("\n");
}
