#define _CRT_SECURE_NO_WARNINGS
#include"foo.h"
#include"structs.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>


void err() {
	printf("err\n");
	exit(1);
}

void regisiter_visitor() {
	FILE* fout = fopen("UserInfo.txt", "a+");
	if(!fout) err();

	Visitor v;
	Visitor* fv = &v;
	printf("ID, pwd, tel, num, type, MaxAge, MinAge\n");
	scanf("%s %s %s %d %d %d %d", fv->ID, fv->pwd, fv->Tel, &fv->num, &fv->type, &fv->MaxAge, &fv->MinAge);
	fwrite(fv, sizeof(Visitor), 1, fout);
	fclose(fout);
}

void regisiter_admin() {
	FILE* fout = fopen("AdminInfo.txt", "a+");
	if(!fout) err();

	Admin ad;
	printf("ID, pwd, tel, email\n");
	scanf("%s %s %s %s", ad.ID, ad.pwd, ad.Tel, ad.Email);

	fwrite(&ad, sizeof(Admin), 1, fout);
	fclose(fout);
}


void regisiter_spot() {
	FILE *fin = fopen("Here.txt", "r");
	FILE *fout = fopen("SpotInfo.txt", "w+");
	char buff[1000];
	Spot sp;
	srand(time(0));
	for(int i = 0; i < 10; i++) {
		printf("%d\n", rand());
		printf("Generating spot %d\n", i + 1);
		system("@ping 127.0.0.1 -n 1 -w 1000 > nul");
		strcpy(sp.ID, "10000");
		sp.ID[5] = i + '0';
		sp.ID[6] = 0;
		fgets(buff, 1000, fin);
		strncpy(sp.name, buff, strlen(buff) - 1);
		sp.name[strlen(buff) - 1] = 0;
		fgets(buff, 1000, fin);
		strncpy(sp.Intro, buff, strlen(buff) - 1);
		sp.Intro[strlen(buff) - 1] = 0;
		sp.price = 500 + rand() % 1500;
		sp.Child = rand() % 2;
		sp.Old = rand() % 2;
		sp.duration = 1 + rand() % 12;
		sp.discount = 0.1f * (rand() % 8 + 2);
		sp.non_peak_discount = 0.1f * (rand() % 8 +2);
		sp.level = 4;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 3; j++) {
				srand(time(0) + i);
				sp.MaxPeople[i][j] = 500 + rand() % 1500;
			}
		}
		fgets(buff, 1000, fin);
		strncpy(sp.belong, buff, strlen(buff) - 1);
		sp.belong[strlen(buff) - 1] = 0;
		sp.MaintainCost = 200 + rand() % 2000;
		
		sp.tickets = 2000;
		fwrite(&sp, sizeof(Spot), 1, fout);
	}
	system("pause");
	system("cls");

	fclose(fin);
	fclose(fout);

}


void restore_admin_backup() {
	FILE* fin = fopen("AdminInfo_backup.txt", "r");
	FILE* fout = fopen("AdminInfo.txt", "w+");
	while(fread(&ad, sizeof(Admin), 1, fin), !feof(fin)) {
		fwrite(&ad, sizeof(Admin), 1, fout);
	}
	fclose(fin);
	fclose(fout);
	printf("Restored admin backup\n");
	system("pause");
}

void restore_spot_backup() {
	FILE* fin = fopen("SpotInfo_backup.txt", "r");
	FILE* fout = fopen("SpotInfo.txt", "w+");
	while(fread(&ad, sizeof(Admin), 1, fin), !feof(fin)) {
		fwrite(&ad, sizeof(Admin), 1, fout);
	}
	fclose(fin);
	fclose(fout);
	printf("Restored spot info backup\n");
	system("pause");
}

void restore_user_backup() {
	FILE *fin = fopen("UserInfo_backup.txt", "r");
	FILE *fout = fopen("UserInfo.txt", "w+");
	while(fread(&user, sizeof(Visitor), 1, fin), !feof(fin)) {
		fwrite(&user, sizeof(Visitor), 1, fout);
	}
	fclose(fin);
	fclose(fout);
	printf("Restored user info backup\n");
	system("pause");
}
