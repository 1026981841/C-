#define _CRT_SECURE_NO_WARNINGS
#include"structs.h"
#include"IO.h"
#include"add_spot.h"
#include"reserve.h"
#include<cstring>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<cctype>
#include<cassert>


void Visitor_struct_assign(Visitor *dest, Visitor *source) {
	strcpy(dest->ID, source->ID);
	strcpy(dest->pwd, source->pwd);
	strcpy(dest->Tel, source->Tel);
	dest->num = source->num;
	dest->type = source->type;
	dest->MinAge = source->MinAge;
	dest->MaxAge = source->MaxAge;
}


void Admin_struct_assign(Admin *dest, Admin *source) {
	strcpy(dest->ID, source->ID);
	strcpy(dest->pwd, source->pwd);
	strcpy(dest->Tel, source->Tel);
	strcpy(dest->Email, source->Email);
}

void print_spot(Spot* sp) {
	system_flush();
	print_stars();
	printf("Spot ID: %s\n", sp->ID);
	printf("Spot Name: %s\n", sp->name);
	printf("Spot Introduction: %s\n", sp->Intro);
	printf("Price: In Peak: %.2f\n", 1.0f * sp->price);
	printf("Not in Peak: %.2f\n", sp->price * sp->non_peak_discount);
	printf("Time needed to visit this spot: %d hours\n", sp->duration);
	printf("Discount for special people: %.2f\n", sp->discount);
	printf("Level: ");
	for(int i = 0; i < sp->level; i++)
		putchar('A');
	printf("\n");
	printf("Spot belongs to %s\n", sp->belong);
	printf("\n");
	printf("Cost to maintain this area: $%d\n", sp->MaintainCost);
	printf("This place is %s for children and %s for elders\n", sp->Child ? "good" : "bad", sp->Old ? "good" : "bad");
	printf("There are %d tickets left for this spot\n", sp->tickets);
	print_stars();
}

bool isPeak(Spot *sp) {
	return sp->tickets <= 500;
}

void get_ID(tm purchase, char* ID)/*参：订单生成的时间，用户ID，返：按PPT要求所示的格式的ID*/
{
	char a[5][100];
	char s[100];
	_itoa_s(purchase.tm_year + 1900, a[4], 10);
	_itoa_s(purchase.tm_mon + 1, a[3], 10);
	_itoa_s(purchase.tm_mday, a[2], 10);
	_itoa_s(purchase.tm_hour, a[1], 10);
	_itoa_s(purchase.tm_min, a[0], 10);

	for(int i = 0; i < 4; i++) {
		strcat(a[i + 1], a[i]);
	}
	strcat(ID, a[4]);
}

void print_order(Purchase *p) {
	system_flush();
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_cnt = getSpotInfo(sp);
	print_stars();
	char ID[30];
	strncpy(ID, p->Visitor_ID, 30);
	get_ID(p->purchase_Time, ID);
	printf("Order ID: %s\n", ID);
	printf("%d spots in total\n", p->spot_number);
	for(int i = 0; i < p->spot_number; i++) {
		printf("    ");
		printf("Spot ID & name: %s ", p->s[i]);
		for(int j = 0; j < spot_cnt; j++) {
			if(strcmp(sp[j]->ID, p->s[i]) == 0) {
				printf("%s", sp[j]->name);
				break;
			}
		}
		printf("\n");
	}
	printf("%d people in total\n", p->number_of_people);
	printf("Total price: %.2f\n", p->total_price);
	printf("Ordered time: %d %d %d\n", p->purchase_Time.tm_year + 1900, p->purchase_Time.tm_mon + 1, p->purchase_Time.tm_mday);
	printf("Departure time: %d: %d: %d\n", p->tm.tm1_year, p->tm.tm1_mon, p->tm.tm1_day);
	print_stars();

	for(int i = 0; i < 30; i++) {
		free(sp[i]);
	}
}

bool chk_Email(char *Email) {
	int p1 = -1, p2 = -1;
	int len = strlen(Email);
	for(int i = 0; i < len; i++) {
		if(Email[i] == '@') {
			p1 = i;
			break;
		}

	}
	for(int i = 0; i < len; i++) {
		if(Email[i] == '.') {
			p2 = i;
			break;
		}
	}

	if(p1 == -1 || p2 == -1)
		return false;
	if(p1 >= p2)
		return false;
	for(int i = 0; i < len; i++) {
		if(i == p1 || i == p2) continue;
		if(!isalnum(Email[i]))
			return false;
	}
	return true;
}

void edit_tourist_Tel(char *togo) {
	system_flush();
	printf("Please enter new Tel\n");
	char buff[1000];
	bool ok = true;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q') {
			return;
		}
		if(len != 11) {
			printf("Please enter exactly 11 characters!\n");
			ok = false;
		}
	} while(!ok);
	strcpy(togo, buff);

	Visitor *vs[30];
	for(int i = 0; i < 30; i++) {
		vs[i] = (Visitor*)malloc(sizeof(Visitor));
	}
	int vis_cnt = getUserInfo(vs);
	FILE *fout = fopen("UserInfo.txt", "w+");
	for(int i = 0; i < vis_cnt; i++) {
		if(strcmp(user.ID, vs[i]->ID) == 0) {
			fwrite(&user, sizeof(Visitor), 1, fout);
		} else {
			fwrite(vs[i], sizeof(Visitor), 1, fout);
		}
	}

	fclose(fout);

	printf("Modification successful!\n");
	printf("Press any key to continue\n");
	system("pause");
}

void edit_tourist_pwd(char *togo) {
	system_flush();
	printf("Please enter new password: (more than 1 and no more than 10 characters) (or q to quit)\n");
	char buff[1000];
	bool ok;
	do {
		buff[0] = 0;
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return;
		if(len == 1) {
			system_flush();
			printf("There should be more than 1 characters! Please try again (or q to quit)\n");
			ok = false;
		}
		if(len > 10) {
			system_flush();
			printf("There should be no more than 10 characters! Please try again (or q to quit)\n");
			ok = false;
		}

	} while(!ok);
	strncpy(togo, buff, 15);

	Visitor *vs[30];
	for(int i = 0; i < 30; i++) {
		vs[i] = (Visitor*)malloc(sizeof(Visitor));
	}
	int vis_cnt = getUserInfo(vs);
	FILE *fout = fopen("UserInfo.txt", "w+");
	for(int i = 0; i < vis_cnt; i++) {
		if(strcmp(user.ID, vs[i]->ID) == 0) {
			fwrite(&user, sizeof(Visitor), 1, fout);
		} else {
			fwrite(vs[i], sizeof(Visitor), 1, fout);
		}
	}

	fclose(fout);

	printf("Modification successful!\n");
	printf("Press any key to continue\n");
	system("pause");
}


void editPwd(char * togo) {
	system_flush();
	printf("Please enter new password: (more than 1 and no more than 10 characters) (or q to quit)\n");
	char buff[1000];
	bool ok;
	do {
		buff[0] = 0;
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return;
		if(len == 1) {
			system_flush();
			printf("There should be more than 1 characters! Please try again (or q to quit)\n");
			ok = false;
		}
		if(len > 10) {
			system_flush();
			printf("There should be no more than 10 characters! Please try again (or q to quit)\n");
			ok = false;
		}
		
	} while(!ok);
	strncpy(togo, buff, 15);
	
	Admin *ads[30];
	for(int i = 0; i < 30; i++) {
		ads[i] = (Admin*)malloc(sizeof(Admin));
	}
	int ad_cnt = getAdminInfo(ads);
	FILE *fout = fopen("AdminInfo.txt", "w+");
	for(int i = 0; i < ad_cnt; i++) {
		if(strcmp(ad.ID, ads[i]->ID) == 0) {
			fwrite(&ad, sizeof(Admin), 1, fout);
		} else {
			fwrite(ads[i], sizeof(Admin), 1, fout);
		}
	}

	fclose(fout);

	printf("Modification successful!\n");
	printf("Press any key to continue\n");
	system("pause");
}

void editEmail(char * togo) {
	system_flush();
	printf("Please enter new Email: (more than 1 and no more than 10 characters) (or q to quit)\n");
	char buff[1000];
	bool ok;
	do {
		buff[0] = 0;
		setbuf(stdin, NULL);
		ok = (scanf("%s", buff) == 1);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return;
		if(len == 1) {
			system_flush();
			printf("There should be more than 1 characters! Please try again (or q to quit)\n");
			ok = false;
		}
		if(len > 25) {
			system_flush();
			printf("There should be no more than 25 characters! Please try again (or q to quit)\n");
			ok = false;
		}
		if(!chk_Email(buff)) {
			printf("Please enter with the right formula (q to quit)\n");
			ok = false;
		}

	} while(!ok);
	strncpy(togo, buff, 15);

	Admin *ads[30];
	for(int i = 0; i < 30; i++) {
		ads[i] = (Admin*)malloc(sizeof(Admin));
	}
	int ad_cnt = getAdminInfo(ads);
	FILE *fout = fopen("AdminInfo.txt", "w+");
	for(int i = 0; i < ad_cnt; i++) {
		if(strcmp(ad.ID, ads[i]->ID) == 0) {
			fwrite(&ad, sizeof(Admin), 1, fout);
		} else {
			fwrite(ads[i], sizeof(Admin), 1, fout);
		}
	}

	fclose(fout);

	printf("Modification successful!\n");
	printf("Press any key to continue\n");
	system("pause");
}

int getSpotInfo(Spot** ps) {
	FILE* fin = fopen("SpotInfo.txt", "r");
	if(!fin)
		file_error(0);

	int cnt = 0;
	fread(ps[cnt++], sizeof(Spot), 1, fin);
	while(!feof(fin)) {
		fread(ps[cnt++], sizeof(Spot), 1, fin);
	}
	cnt--;
	fclose(fin);
	return cnt;
}

int getAdminInfo(Admin **ads) {
	FILE *fin = fopen("AdminInfo.txt", "r");
	if(!fin)
		file_error(0);

	int cnt = 0;
	fread(ads[cnt++], sizeof(Admin), 1, fin);
	while(!feof(fin)) {
		fread(ads[cnt++], sizeof(Admin), 1, fin);
	}
	cnt--;
	fclose(fin);
	return cnt;
}

int getUserInfo(Visitor **vs) {
	FILE *fin = fopen("UserInfo.txt", "r");
	if(!fin)
		file_error(0);

	int cnt = 0;
	while(fread(vs[cnt++], sizeof(Visitor), 1, fin), !feof(fin)) {
		//
	}
	cnt--;
	fclose(fin);

	return cnt;
}


int modify(Spot *cand) {
	//1: modify, 0: stop
	system_flush();
	printf("What do you want to modify? Please enter your choice\n");
	printf("a)ID\n"
	"b)Name\n"
	"c)Introduction\n"
	"d)Price\n"
	"e)Discount when not in peak\n"
	"f)Is it ok for elders\n"
	"g)Is it ok for children\n"
	"h)Time needed to take to explore\n"
	"i)Discount for special people\n"
	"j)Level\n"
	"k)People limit in different times\n"
	"l)Where does it belong to\n"
	"m)Maintain cost\n"
		   "q)Quit and confirm：\n");

	int id;
	do {
		id = read_modify_choice();
	} while(id == 0 || id == 14);
	if(id == -1)
		return 0;
	switch(id) {
		case 1:
			ModifyID(cand);
			break;
		case 2:
			ModifyName(cand);
			break;
		case 3:
			ModifyIntro(cand);
			break;
		case 4:
			ModifyPrice(cand);
			break;
		case 5:
			ModifyDiscount(cand);
			break;
		case 6:
			ModifyForOld(cand);
			break;
		case 7:
			ModifyForChild(cand);
			break;
		case 8:
			ModifyDuration(cand);
			break;
		case 9:
			ModifyDiscount(cand);
			break;
		case 10:
			ModifyLevel(cand);
			break;
		case 11:
			ModifyMaxPeople(cand);
			break;
		case 12:
			ModifyBelong(cand);
			break;
		case 13:
			ModifyMaintain(cand);
			break;
		case -1:
			return 0;
		default: 
			break;
	}
	return 1;
}

bool chk_modify(Spot *cand) {
	Spot *sp[30];
	for(int i = 0; i < 30; i++) {
		sp[i] = (Spot*)malloc(sizeof(Spot));
	}
	int spot_num = getSpotInfo(sp);
	for(int i = 0; i < spot_num; i++) {
		if(strcmp(cand->name, sp[i]->name) == 0 || strcmp(cand->ID, sp[i]->ID) == 0) {
			return false;
		}
	}
	return true;
}

int addSpot() {
	//something!!!!!!!!!!!!!!!
	//0:quit, 1: continu
	Spot cand;
	char buff[1000];

	system_flush();
	printf("Please enter spot ID (6 characters): (q to quit)\n");
	bool ok = true;
	do {
		ok = lets_enter_something(buff, 0, 6);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return 0;
		if(len != 6) {
			system_flush();
			printf("You should enter exactly 6 characters! Please try again\n");
			ok = false;
		}
	} while(!ok);
	strncpy(cand.ID, buff, 7);

	system_flush();
	printf("And spot name? (q to quit)\n");
	ok = true;
	do {
		setbuf(stdin, NULL);
		fgets(buff, 50, stdin);
		buff[strlen(buff) - 1] = 0;
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return 0;
		if(len <= 1 || len > 50) {
			system_flush();
			printf("You should enter more than 1 characters and less than 10 characters! Please try again\n");
			printf("Press any key to continue\n");
			system("pause");
		}
	} while(!ok);
	strncpy(cand.name, buff, 50);

	system_flush();
	printf("What approach do you want to enter spot introduction?\n");
	printf("Please select your choice: (if there are too many words, you might want to try f) )\n");
	printf("k)From Keyboard\n"
		   "f)From File\n"
		   "q)Quit\n");

	int id;
	do {
		id = read_add_spot_choice();
		if(id == 0)
			illegal_input_error(-1);
		if(id == 3)
			illegal_input_error(0);
	} while(id == 0 || id == 3);
	if(id == -1)
		return 0;
	while(1) {
		system_flush();
		if(id == 1) {
			printf("Please enter your text: (no more than 950 words)\n");
			do {
				ok = lets_enter_something(buff, 0, 950);
			} while(!ok);
			strncpy(cand.Intro, buff, 950);
			break;
		} else if(id == 2) {
			printf("Please do the following steps:\n");
			printf("1)Put your text in an empty txt file (no more than 950 words)\n"
				   "2)Put your file in root dir of this project\n"
				   "3)Type the file's name from keyboard (it should end with .suffix if it has)\n");
			do {
				ok = lets_enter_something(buff, 0, 100);
			} while(!ok);

			FILE *fin = fopen(buff, "r");
			if(!fin) {
				printf("Failed opening file!\n");
				printf("Please check if you've done the above steps correctly\n");
				standby();
				continue;
			}
			buff[0] = 0;
			char s[1000];
			while(fgets(s, 1000, fin)) {
				strncat(buff, s, 1000);
				if(strlen(buff) > 950)
					break;
			}
			fclose(fin);

			if(strlen(buff) > 950) {
				system_flush();
				printf("Too much text in the file\n");
				printf("You want to ?\n");
				printf("c)continue (cut your text to 950 words)\n"
					   "b)Back\n"
				"q)Quit\n");
			
				int id;
				do {
					id = read_too_much_text_choice();
				} while(id == 0 || id == 3);
				if(id == -1) {
					return 0;
				}

				if(id == 1) {
					strncpy(cand.Intro, buff, 950);
					break;
				}else if(id == 2) {
					continue;
				} else {
					//oof
					assert(false);
				}
			} else {
				strncpy(cand.Intro, buff, 950);
				break;
			}
		} else {
			//oof
			assert(false);
		}
	}


	system_flush();
	printf("Now please enter the price (peak) (or -1 to quit):\n");
	float price;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &price) == 1);
		if(price == -1)
			return 0;
		if(price < 0) {
			system_flush();
			printf("You should enter a positive value! Please try again\n");
			ok = false;
		}
	} while(!ok);
	cand.price = price;
	float non_peak_discount;
	printf("What is the discount when it isn't in peak?:\n");
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &non_peak_discount) == 1);
	} while(!ok);
	cand.non_peak_discount = non_peak_discount;

	system_flush();
	printf("OK! So is it ok for children (y for yes, n for no, q to quit)?\n");
	do {
		ok = is_it_ok();
		if(ok == 0)
			illegal_input_error(-1);
		if(ok == 3)
			illegal_input_error(0);
	} while(ok == 0 || ok == 3);
	if(ok == -1)
		return 0;
	cand.Child = (ok == 1);

	system_flush();
	printf("And for elders? (y for yes, n for no, q to quit)\n");
	do {
		ok = is_it_ok();
		if(ok == 0)
			illegal_input_error(-1);
		if(ok == 3)
			illegal_input_error(0);
	} while(ok == 0 || ok == 3);
	if(ok == -1)
		return 0;
	cand.Old = (ok == 1);

	system_flush();
	//!!!!!!!!!!!!!!!something
	printf("How much time does it take to explore it (hour) (or -1 to quit)?\n");
	float duration;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &duration) == 1);
		if(duration == -1)
			return 0;
		if(duration < 0) {
			system_flush();
			printf("You should enter a positive value! Please try again\n");
			ok = false;
		}
	} while(!ok);
	cand.duration = duration;

	system_flush();
	printf("What is the discount for special people (like children, soldier, elder) (or -1 to quit)?\n");
	float discount;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &discount) == 1);
		if(discount == -1)
			return 0;
		if(discount < 0 || discount > 1) {
			ok = false;
			system_flush();
			printf("It should be more than 0 and less than 1!\n");
			printf("Please try again\n");
		}
	} while(!ok);
	cand.discount = discount;

	system_flush();
	printf("And it's level (or -1 to quit)?\n");
	float level;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &level) == 1);
		if(level == -1)
			return 0;
		if(level < 1 || level > 5) {
			ok = false;
			system_flush();
			printf("It should be more than 1 and less than 5\n");
			printf("Please trye again\n");
		}
	} while(!ok);
	cand.level = level;

	system_flush();
	const char *seasons[] = {"Spring", "Summer", "Autumn", "Winter"};
	const char *pi[] = {"morning", "afternoon", "evening"};
	printf("Now please enter how much people can this spot hold at most (4 seasons, morning, noon, evening each) (-1 to quit)\n");
	for(int i = 0; i < 4; i++) {
		printf("%s:\n", seasons[i]);
		for(int j = 0; j < 3; j++) {
			printf("       %s:\n", pi[j]);
			float MaxPeople;
			do {
				setbuf(stdin, NULL);
				ok = (scanf("%f", &MaxPeople) == 1);
				if(MaxPeople == -1)
					return 0;
				if(MaxPeople < 0) {
					ok = false;
					printf("\n\nSeriously? Please try again\n");
				}
			} while(!ok);
			cand.MaxPeople[i][j] = MaxPeople;
		}
	}

	system_flush();
	printf("Excellent!! Now please tell me where does it belong to (-1 to quit) ?\n");
	if(where_does_it_belong_to(cand.belong) == 0)
		return 0;

	system_flush();
	printf("Last step! How much it takes to maintain this spot (-1 to quit)?\n");
	float maintain;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &maintain) == 1);
		if(maintain == -1)
			return 0;
		if(maintain < 0) {
			ok = false;
			printf("\n\nSeriously?\n");
		}
	} while(!ok);
	cand.MaintainCost = maintain;

	system_flush();
	printf("Please confirm your choice or make a modifications\n");
	printf("c)Confirm\n"
		   "m)Modify\n"
		   "q)Quit\n");
	do {
		id = modify_or_confirm();
		if(id == 0)
			illegal_input_error(-1);
		if(id == 3) 
			illegal_input_error(0);
	} while(id == 0 || id == 3);

	if(id == 1) {
		//confirm
	}
	if(id == 2) {
		//modify
		int nxt;
		do {
			nxt = modify(&cand);
		} while(nxt);
	}

	do {
		ok = chk_modify(&cand);
		if(!ok) {
			system_flush();
			printf("Name and ID can't repeat!\n");
			printf("Do your want to modify or quit (m to modify, q to quit)?\n");
			char c = 0;
			do {
				c = _getch();
				c = _getch();
			} while(!isalnum(c));
			c = tolower(c);
			
			if(c != 'm' && c != 'q') {
				system_flush();
				printf("Please enter the right choice!\n");
				printf("Press any key to continue\n");
				system("pause");
				continue;
			}
			
			if(c == 'm') {
				int nxt;
				do {
					nxt = modify(&cand);
				} while(nxt);
			}
			if(c == 'q') {
				return 1;
			}
		}
	} while(!ok);

	cand.tickets = 2000;
	cand.views = 0;
	cand.Pnext = NULL;

	FILE* fout = fopen("SpotInfo.txt", "a+");
	if(!fout) {
		file_error(0);
		exit(0);
	}
	fwrite(&cand, sizeof(Spot), 1, fout);
	fclose(fout);

	//done?

	system_flush();
	printf("Adding spot successfully!\n");
	printf("Press ank key to continue\n");
	system("pause");
	return 1;
}
