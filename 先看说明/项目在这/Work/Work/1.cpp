int spot_query() //所有景点排列
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
	{
		sp[i] = (Spot*)malloc(sizeof(Spot));
		memset(sp[i], 0, sizeof(Spot));
	}

	int spot_num = getSpotInfo(sp);

	if (spot_num == 0)
	{
		printf("No spot information!\n");
		system("pause");
		return 1;
	}

	int cur = 0;           //定义目前的景点在结构体中的下标
	while (1)
	{
		print_spot(sp[cur]);
		printf("\n\n");

		printf("Your choice:\n");

		if (cur > 0)
			printf("a)Previous Spot   ");
		else
		{
			for (int i = 0; i < 16; i++)
				putchar(' ');
		}

		if (cur < spot_num - 1)
			printf("d)Next Spot ");
		else
		{
			for (int i = 0; i < 9; i++)
				putchar(' ');
		}

		printf("q)Quit\n");

		int id;//ID控制用户输入。cur控制景点的索引

		do {
			id = read_spot_management_choice();
			if (id == 3)
				illegal_input_error(1);
		} while (id == 0 || id == 3);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			}
			else
				cur--;
		}

		if (id == 2)
		{
			if (cur == spot_num - 1)
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

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 1;
}


int query_by_name(char *name) //通过名字查询
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_num = getSpotInfo(sp);//函数返回景点结构体个数
	int found = 0;

	for (int i = 0; i < spot_num; i++)
	{
		if (strcmp(sp[i]->name, name) == 0) //判断两个字符串是否相等
		{
			found = 1;
			system_flush();
			printf("Result found!\n");
			print_spot(sp[i]);
			printf("\n");
			print_stars();

			printf("Would you like to order this one (o to order, q to quit)?\n");
			while (1)
			{
				char c = 0;

				/*	do {
				c = getchar();
				} while (isspace(c));*///C位空白返回
				do {
					c = _getch();
				} while (!isalnum(c));

				c = tolower(c);//大小写转换

				if (c == 'o')
				{
					order_spot(i);//进入购物车
					break;
				}
				else if (c == 'q')
					break;
				else
					illegal_input_error(0);
			}
			break;
		}
	}

	if (found == 0) //当没有对应的景点名称时
	{
		system_flush();
		printf("There is no such spot!\n");
		printf("Press any key to continue\n");
		system("pause");
	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 1;
}

int query_by_ticket()//用过是否有票查询
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_num = getSpotInfo(sp);
	int fin[30], fin_num = 0;

	for (int i = 0; i < spot_num; i++) //将索引与结构体数组一一对应
	{
		if (sp[i]->tickets > 0)
			fin[fin_num++] = i;
	}

	int cur = 0;

	while (1)
	{
		system_flush();
		print_spot(sp[cur]);//打印函数
		printf("\n");
		if (cur > 0)
			printf("a)Previous   ");
		else
		{
			for (int i = 0; i < 11; i++)
				putchar(' ');
		}
		if (cur < fin_num - 1)
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
			if (id == 0)
				illegal_input_error(-1);
		} while (id == 0 || id == 4);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur--;
		}

		if (id == 2)
		{
			if (cur == fin_num - 1)
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur++;
		}
		if (id == 3)
			order_spot(cur);
	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 0;
}

int query_by_discount()//通过折扣信息查询
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));

	int spot_num = getSpotInfo(sp);
	int fin[30], fin_num = 0;

	for (int i = 0; i < spot_num; i++)
	{
		if (sp[i]->discount < 1.0f) //结构体中用float储存的
			fin[fin_num++] = i;
	}

	int cur = 0;

	while (1)
	{
		system_flush();
		print_spot(sp[cur]);
		printf("\n");
		if (cur > 0)
			printf("a)Previous   ");
		else
			for (int i = 0; i < 11; i++)
				putchar(' ');

		if (cur < fin_num - 1)
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
			if (id == 0)
				illegal_input_error(-1);
		} while (id == 0 || id == 4);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur--;
		}
		if (id == 2)
		{
			if (cur == fin_num - 1)
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur++;
		}
		if (id == 3)
			order_spot(cur);

	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 0;
}

int query_by_belong(char *belong)//通过所属地查询
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));


	int spot_num = getSpotInfo(sp);
	int found = 0;
	int fin[30], fin_num = 0;

	for (int i = 0; i < spot_num; i++)
	{
		if (strcmp(sp[i]->belong, belong) == 0)
		{
			found = 1;
			fin[fin_num++] = i;
		}
	}

	int cur = 0;
	while (1)
	{
		system_flush();
		print_spot(sp[cur]);
		printf("\n");

		if (cur > 0)
			printf("a)Previous   ");
		else
			for (int i = 0; i < 11; i++)
				putchar(' ');

		if (cur < fin_num - 1)
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
			if (id == 0)
				illegal_input_error(-1);
		} while (id == 0 || id == 4);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				printf("There is no previous spot!\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur--;
		}
		if (id == 2)
		{
			if (cur == fin_num - 1)
			{
				printf("There is no next spot\n");
				printf("Press any key to continus\n");
				system("pause");
			}
			else
				cur++;
		}
		if (id == 3)
			order_spot(cur);
	}

	if (found == 0)
	{
		system_flush();
		printf("There is no such spot!\n");
		printf("Press any key to continue\n");
		system("pause");
	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 3 * found;
}

int query()//查询页面
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

	while (id == 0 || id == 5)
	{
		if (id == 0)
			illegal_input_error(-1);//0  5均为错误输入
		if (id == 5)
			illegal_input_error(0);
		id = read_query_choice();//函数作用返回用户输入的指令，前进后退或者放弃与确认预定
	}
	if (id == -1)//Q (-1)表示返回上亿界面
		return -1;

	while (id == 1)
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
			if (len == 1 && buff[0] == 'q')
				return 0;
			if (len <= 1 || len > 50) {
				system_flush();
				printf("You should enter more than 1 and less than 15 characters! Please try again\n");
				ok = false;
			}
		} while (!ok);
		id = query_by_name(buff);
	}

	while (id == 2)
		id = query_by_ticket();

	while (id == 3)
	{
		system_flush();
		printf("Please enter where spot belong to (q to quit)\n");
		char buff[1000];
		bool ok = true;
		do {
			setbuf(stdin, NULL);
			ok = (scanf("%s", buff) == 1);
			int len = strlen(buff);
			if (len == 1 && buff[0] == 'q') {
				return 0;
			}
			if (len <= 1 || len > 20) {
				system_flush();
				printf("You should enter more than 1 and less than 20 characters (or q to quit)! Please try again\n");
				ok = false;
			}
		} while (!ok);
		id = query_by_belong(buff);
	}

	while (id == 4)
		id = query_by_discount();

	return 1;
}

int sort_by_price()//通过价格排序
{
	Spot *sp[30];

	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));
	int spot_num = getSpotInfo(sp);

	int fin[30], mark[30];
	//res[30] = 0;
	//mark[30] = 0;
	memset(mark, 0, sizeof(mark));

	for (int i = 0; i < spot_num; i++)//排序
	{
		int jj = -1;
		for (int j = 0; j < spot_num; j++) if (!mark[j])
		{
			if (jj == -1 || sp[j]->price < sp[jj]->price)
				jj = j;
		}
		mark[jj] = 1;
		fin[i] = jj;
	}

	int cur = 0;
	while (1)
	{
		system_flush();
		int index = fin[cur];
		print_spot(sp[index]);//按照排序后的结构体数组的顺序打印（一次一个）

		printf("\nWould you like to order this one (o to order)?\n");
		printf("\n");

		if (cur > 0)
			printf("a)Previous   ");
		else
		{
			for (int i = 0; i < 13; i++)
				putchar(' ');
		}

		if (cur < spot_num - 1)
			printf("d)Next   ");
		else
		{
			for (int i = 0; i < 9; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
		} while (id == 0 || id == 4);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			}
			else
				cur--;
		}

		if (id == 2)
		{
			if (cur == spot_num - 1)
			{
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			}
			else
				cur++;
		}
		if (id == 3)
			order_spot(index);
	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 0;
}

int sort_by_amount()//通过预定量排序
{
	Spot *sp[30];
	for (int i = 0; i < 30; i++)
		sp[i] = (Spot*)malloc(sizeof(Spot));
	int spot_num = getSpotInfo(sp);

	int fin[30], mark[30], amount[30];
	/*amount[30] = 0;
	mark[30] = 0;*/

	memset(amount, 0, sizeof(amount));
	memset(mark, 0, sizeof(mark));

	FILE *fin = fopen("PurInfo.txt", "r");
	if (!fin)
		file_error(0);
	Purchase p;
	while (fread(&p, sizeof(Purchase), 1, fin), !feof(fin)) {
		for (int i = 0; i < p.spot_number; i++) {
			for (int j = 0; j < spot_num; j++) {
				if (strcmp(sp[j]->ID, p.s[i]) == 0) {
					amount[j]++;
					break;
				}
			}
		}
	}
	for (int i = 0; i < spot_num; i++) {
		int jj = -1;
		for (int j = 0; j < spot_num; j++) if (!mark[j]) {
			if (jj == -1 || amount[j] < amount[jj]) {
				jj = j;
			}
		}
		fin[i] = jj;
		mark[jj] = 1;
	}

	int cur = 0;
	while (1)
	{
		system_flush();
		int index = fin[cur];
		print_spot(sp[index]);
		printf("\nWould you like to order this one (o to order)?\n");
		printf("\n");

		if (cur > 0)
			printf("a)Previous   ");
		else
		{
			for (int i = 0; i < 13; i++)
				putchar(' ');
		}
		if (cur < spot_num - 1)
			printf("d)Next   ");
		else
		{
			for (int i = 0; i < 9; i++)
				putchar(' ');
		}
		printf("q)Quit\n");

		int id;
		do {
			id = pre_or_nxt();
			if (id == 4)
				illegal_input_error(0);
		} while (id == 0 || id == 4);

		if (id == -1)
			break;
		if (id == 1)
		{
			if (cur == 0)
			{
				system_flush();
				printf("There is no previous spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			}
			else
				cur--;
		}
		if (id == 2)
		{
			if (cur == spot_num - 1)
			{
				system_flush();
				printf("There is no next spot!\n");
				printf("Press any key to continue\n");
				system("pause");
			}
			else
				cur++;
		}
		if (id == 3)
			order_spot(index);
	}

	for (int i = 0; i < 30; i++)
		free(sp[i]);

	return 0;
}

int Sort()//排序页面
{
	system_flush();
	printf("What do you want to sort by?\n");
	printf("a)Price\n");
	printf("b)Ordered amount\n");
	printf("q)Quit\n");

	int id;
	do {
		id = read_sort_choice();
	} while (id == 0 || id == 3);

	if (id == -1)
		return 0;
	if (id == 1)
		sort_by_price();
	else if (id == 2)
		sort_by_amount();

	return 0;
}