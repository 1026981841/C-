#ifndef IO_H
#define IO_H
#include"structs.h"
#include"reserve.h"

void system_flush();

void illegal_input_error(int);
void file_error(int);
int read_identification();
int read_tourist_choice();
int read_admin_choice();
int read_query_choice();
int read_sort_choice();
int pre_or_nxt();
int confirm_or_quit();
int read_add_spot_choice();
int modify_or_confirm();
int read_too_much_text_choice();
int read_spot_management_choice();
int read_personal_info_manage_choice();
int where_does_it_belong_to(char*);
int read_modify_choice();
int read_tourist_edit_info_choice();
int read_confirm_choice();
int read_admin_chk_order_info_choice();
int is_it_ok();
int read_tourist_id(char*);
int read_tourist_pwd(char*, char*);
bool tourist_login_chk(char*, char*);
void print_stars();
int read_admin_id(char*);
int read_admin_pwd(char*, char*);
bool admin_login_chk(char*, char*);
bool lets_enter_something(char *, int, int);
int get_time_input(tm1*);

//implemented in main
void standby();
int tourist_login();
int welcome_tourist();
int admin_login();
int welcome_admin();
int welcome();
int query();
int Sort();
int chk_history_order();
int tourist_edit_info();

#endif