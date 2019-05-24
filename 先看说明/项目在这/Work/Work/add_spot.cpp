#define _CRT_SECURE_NO_WARNINGS
#include"add_spot.h"
#include"IO.h"
#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cassert>

int ModifyID(Spot *cand) {
	system_flush();
	printf("Please enter spot ID: (q to quit)\n");
	char buff[1000];
	bool ok = true;
	do {
		ok = lets_enter_something(buff, 0, 6);
		int len = strlen(buff);
		if(len == 1 && buff[0] == 'q')
			return 0;
		if(len != 6) {
			system_flush();
			printf("You should enter exactly 6 characters! Please try again\n");
			printf("Press any key to continue\n");
			system("pause");
		}
	} while(!ok);
	strncpy(cand->ID, buff, 6);
	
	return 1;
}

int ModifyName(Spot *cand) {
	system_flush();
	printf("Please enter spot name: (q to quit)\n");
	bool ok = true;
	char buff[1000];
	do {
		getchar();
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
	
	strncpy(cand->name, buff, 50);

	return 1;
}

int ModifyIntro(Spot *cand) {
	system_flush();
	printf("What approach do you want to enter spot introduction?\n");
	printf("Please select your choice: (if there are too many words, you might want to try f) )\n");
	printf("k)From Keyboard\n"
		   "f)From File\n"
		   "q)Quit\n");

	bool ok = true;
	char buff[1000];
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
			strncpy(cand->Intro, buff, 950);
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
					strncpy(cand->Intro, buff, 950);
					break;
				} else if(id == 2) {
					continue;
				} else {
					//oof
					assert(false);
				}
			} else {
				strncpy(cand->Intro, buff, 950);
				break;
			}
		} else {
			//oof
			assert(false);
		}
	}
	return 1;
}

int ModifyPrice(Spot *cand) {
	system_flush();
	printf("Please enter the price (peak) (or -1 to quit):\n");
	float price;
	bool ok = true;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &price) == 1);
		if(price != -1) {
			system_flush();
			printf("You should enter a positive value or -1 to quit! Please try again\n");
			ok = false;
		}
	} while(!ok);
	if(price == -1)
		return 0;
	cand->price = price;
	return 1;
}

int ModifyForChild(Spot *cand) {
	system_flush();
	printf("Is it ok for children (y for yes, n for no, q to quit)?\n");
	bool ok = true;
	do {
		ok = is_it_ok();
		if(ok == 0)
			illegal_input_error(-1);
		if(ok == 3)
			illegal_input_error(0);
	} while(ok == 0 || ok == 3);
	if(ok == -1)
		return 0;
	cand->Child = (ok == 1);
	return 1;
}

int ModifyForOld(Spot *cand) {
	system_flush();
	printf("Is it ok for elder (y for yes, n for no, q to quit)?\n");
	bool ok = true;
	do {
		ok = is_it_ok();
		if(ok == 0)
			illegal_input_error(-1);
		if(ok == 3)
			illegal_input_error(0);
	} while(ok == 0 || ok == 3);
	if(ok == -1)
		return 0;
	cand->Child = (ok == 1);
	return 1;
}

int ModifyDuration(Spot *cand) {
	system_flush();
	//!!!!!!!!!!!!!!!something
	printf("How much time does it take to explore it (hour) (or -1 to quit) ?\n");
	bool ok = true;
	float duration;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &duration) == 1);
		if(duration <= 0 && duration != -1) {
			system_flush();
		printf("You should enter a positive value or -1 to quit! Please try again\n");
			ok = false;
		}
	} while(!ok);
	if(duration == -1)
		return 0;
	cand->duration = duration;
	return 1;
}

int ModifyDiscount(Spot *cand) {
	system_flush();
	printf("What is the discount for special people (like children, soldier, elder) (or -1 to quit)?\n");
	bool ok = true;
	float discount;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &discount) == 1);
		if((discount < 0  && discount !=  -1)|| discount > 1) {
			ok = false;
			system_flush();
			printf("It should be more than 0 and less than 1 or -1 to quit!\n");
			printf("Please try again\n");
		}
	} while(!ok);
	if(discount == -1)
		return 0;
	cand->discount = discount;
	return 1;
}

int ModifyLevel(Spot *cand) {
	system_flush();
	printf("Please enter spot level (or -1 to quit)\n");
	float level;
	bool ok = true;
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
	cand->level = level;
	return 1;
}

int ModifyMaxPeople(Spot *cand) {
	system_flush();
	const char *seasons[] = {"Spring", "Summer", "Autumn", "Winter"};
	const char *pi[] = {"morning", "afternoon", "evening"};
	printf("Please enter how much people can this spot hold at most (4 seasons, morning, noon, evening each) (or -1 to quit)\n");
	bool ok = true;
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
					system_flush();
					printf("\n\nSeriously? Please try again\n");
				}
			} while(!ok);
			cand->MaxPeople[i][j] = MaxPeople;
		}
	}
	return 1;
}

int ModifyBelong(Spot *cand) {
	system_flush();
	printf("Please tell me where does it belong to?\n");
	char buff[1000];
	where_does_it_belong_to(buff);

	return 1;
}

int ModifyMaintain(Spot *cand) {
	system_flush();
	printf("Last step! How much it takes to maintain this spot (or -1 to quit)?\n");
	float maintain;
	bool ok = true;
	do {
		setbuf(stdin, NULL);
		ok = (scanf("%f", &maintain) == 1);
		if(maintain == -1)
			return 0;
		if(maintain < 0) {
			ok = false;
			system_flush();
			printf("You should enter a positive value or -1 to quit! Please try again\n");
		}
	} while(!ok);
	cand->MaintainCost = maintain;
	return 1;
}
