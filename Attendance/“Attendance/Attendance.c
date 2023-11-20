#include"Attendance.h"

void Staff(PInfo**head)
{
	system("cls");
	loadStaff(*head);
	int temp = 1;
	char option;
	do
	{
		system("cls");
		printf("请输入选项\n");
		printf("--------------------------\n");
		printf("         1.创建账号       \n");
		printf("         2.登录账号       \n");
		printf("       0.返回选择界面     \n");
		option = getch();
		system("cls");
		switch (option)
		{
		case '1':
		{
			PushBack(*head,0);
			break;
		}
		case '2':
		{
			PInfo*current=StuffAccount(* head);
			system("cls");
			if (current!=NULL)
			{
				int tem = 1;
				do
				{
					system("cls");
					MenuStuff();
					char op = getch();
					switch (op)
					{
					case '1':
					{
						system("cls");
						printf("打卡\n");
						CheckIntime(head, current);
						system("pause");
						break;
					}
					case '2':
					{
						system("cls");
						printf("请假\n");
						RequestLeave(head, current);
						system("pause");
						break;
					}
					case '3':
					{
						system("cls");
						printf("签退\n");
						CheckOutTime(head, current);
						system("pause");
						break;
					}
					case '4':
					{
						system("cls");
						printf("考勤记录");
						system("pause");
						break;
					}
					case '0':
					{
						system("cls");
						printf("退出登录");
						tem = 0;
						break;
					}
					default:
					{
						system("cls");
						printf("输入错误请重新输入：\n");
						system("pause");
					}
					}
				} while (tem);
			}
			else
			{
				printf("登陆失败");
			}
			break;
		}
		case '0':
		{
			printf("程序退出\n");
			temp = 0;
			break;
		}
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (temp);


	SaveStaff(*head);
}
void Admin(PInfo** head)
{
	loadStaff(*head);
	int temp = 1;
	char option;
	do
	{
		system("cls");
		printf("请输入选项\n");
		printf("--------------------------\n");
		printf("         1.注册账号       \n");
		printf("         2.登录账号       \n");
		printf("       0.返回选择界面     \n");
		option = getch();
		switch (option)
		{
		case '1':
		{
			PushBack(*head,1);
			break;
		}
		case '2':
		{
			if (AdminAccount(*head))
			{

				int tem = 1;
				char op;
				do
				{
					system("cls");
					MenuAdmin();
					op = getch();
					switch (op)
					{
					case '1':
					{
						system("cls");
						printf("增加员工\n");
						PushBack(*head,0);
						break;
					}
					case '2':
					{
						system("cls");
						printf("查看员工信息\n");
						PrintData(*head);
						system("pause");
						break;
					}case '3':
					{
						system("cls");
						PopMid(* head);
						system("pause");
						break;
					}case '4':
					{
						system("cls");
						printf("修改员工信息\n");
						UpdateStaffInfo(*head);
						system("pause");
						break;
					}case '5':
					{
						system("cls");
						printf("请假批准\n");
						approveLeaveRequest(*head);
						system("pause");
						break;
					}case '0':
					{
						system("cls");
						printf("退出登录\n");
						tem = 0;
						break;
					}
					default:
					{
						system("cls");
						printf("输入错误请重新输入：\n");
						system("pause");
						break;
					}
					}

				} while (tem);
			}
			break;
		}
		case '0':
		{
			printf("程序退出\n");
			temp = 0;
			break;
		}
		default:
			printf("输入错误，请重新输入\n");
			system("pause");
			break;
		}
	} while (temp);
	

	SaveStaff(*head);
}

int AdminAccount(PInfo* head)
{
	system("cls");
	int op = 1;
	char c;
	while (op)
	{
		system("cls");
		printf("请输入你管理员账号：\n");
		char Account[20];
		scanf("%s", Account);
		printf("请输入密码：\n");
		char Password[20];
		scanf("%s", Password);
		PInfo* current = head;
		while (current->next != NULL)
		{
			current = current->next;
			if (strcmp(current->data.account, Account) == 0)
				if (strcmp(current->data.password, Password) == 0)
					if (current->data.judge == 1)
						return 1;

		}
		int a = 1;
		printf("账号或密码存在错误\n");
		while (a)
		{
			printf("----------------------------\n");
			printf("          请选择           :\n");
			printf("       1.重新输入           \n");
			printf("       0.退出程序           \n");
			c = getch();
			switch (c)
			{
			case '1':
			{
				a = 0;
				break;
			}
			case '0':
			{
				op = 0;
				a = 0;
				break;
			}
			default:
			{
				system("cls");
				printf("输入错误，请重新输入\n");
				break;
			}
			}
		}
	}
	return 0;
}
void loadStaff(PInfo* head)
{
	FILE* file = fopen("data.txt", "r");
	if (!file) 
	{
		printf("没有员工文件,跳过读取\n");
		return;
	}
	if (!head)
	{
		return;
	}
	PInfo* staff =(PInfo*) malloc(sizeof(PInfo));
	staff->next = NULL;
	PInfo* move = head;
	while (fread(&staff->data, sizeof(PInfo), 1, file) == 1)
	{
		move->next = staff;
		move = move->next;
		staff = (PInfo*)malloc(sizeof(PInfo));
		staff->next = NULL;
	}
	free(staff);
	fclose(file);
	printf("读取成功\n");
	
}
void SaveStaff(PInfo* head)
{
	FILE* file = fopen("data.txt", "w");
	if (!file)
	{
		printf("无法创建员工文件\n");
		return;
	}
	if (!head)
	{
		return;
	}
	PInfo* move = head->next;  // 跳过头节点
	while (move != NULL)
	{
		fwrite(&move->data, sizeof(PInfo), 1, file);
		move = move->next;
	}
	fclose(file);
	printf("保存成功\n");
}


void PushBack(PInfo*head,int judge)
{
	loadStaff(head);
	PInfo* tem = (PInfo*)malloc(sizeof(PInfo));
	if (!tem)
	{
		printf("内存分配失败\n");
		return;
	}
	InfoDate PersonData;
	printf("请输入账户：\n");
	scanf("%s", PersonData.account);
	printf("请输入用户名：\n");
	scanf("%s", PersonData.user);

	PInfo* current = head;
	while (current != NULL)
	{
		if (strcmp(current->data.account, PersonData.account) == 0)
		{
			printf("账户名已存在\n");
			system("pause");
			return;
		}
		if (strcmp(current->data.user, PersonData.user) == 0)
		{
			printf("用户名已存在\n");
			system("pause");
			return;
		}
		current = current->next;
	}

	printf("请输入密码：\n");
	scanf("%s", PersonData.password);
	tem->next = NULL;
	tem->data.leave = 0;
	tem->data.time.checkIn = 0;
	tem->data.time.checkOut = 0;
	tem->data.judge = judge;
	strcpy(tem->data.account, PersonData.account);
	strcpy(tem->data.password, PersonData.password);
	strcpy(tem->data.user, PersonData.user);

	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = tem;
	SaveStaff(head);
	printf("注册成功");
	system("pause");
}
void PrintData(PInfo* head)
{
	loadStaff(head);
	if (!head)
	{
		return;
	}
	int op = 1;
	while (op)
	{
		system("cls");
		printf("1.查看全部人员信息\n");
		printf("2.查看某一人信息\n");
		printf("0.退出\n");
		char c = getch();
		switch (c)
		{
		case '1':
		{
			system("cls");
			PInfo* current = head;
			while (current->next != NULL)
			{
				current = current->next;
				printf("账号:");
				printf("%s    ", current->data.account);
				printf("密码:");
				printf("%s    ", current->data.password);
				printf("用户名:");
				printf("%s    ", current->data.user);
				printf("共计成功打卡%d次   ", current->data.time.checkIn);
				printf("共计成功签退%d次   ", current->data.time.checkOut);
				if (current->data.judge == 1)
					printf("管理员   ");
				else
					printf("员工   ");
				printf("\n");
			}
			system("pause");
			break;
		}
		case '2':
		{
			int opt = 1;
			PInfo* cur = head;
			while (opt)
			{
				system("cls");
				printf("请输入您要查看员工的用户名:\n");
				char s[50];
				scanf("%s", s);
				while (strcmp(cur->data.user, s) != 0&&cur->next!=NULL)
					cur = cur->next;
				if (strcmp(cur->data.user, s) == 0)
					opt = 0;
				else
				{
					system("cls");
					printf("输入错误，请重新输入");
					cur = head;
					system("pause");
				}
			}
			printf("账号:");
			printf("%s    ", cur->data.account);
			printf("密码:");
			printf("%s    ", cur->data.password);
			printf("用户名:");
			printf("%s    ", cur->data.user);
			printf("共计成功打卡%d次   ", cur->data.time.checkIn);
			printf("共计成功签退%d次   ", cur->data.time.checkOut);
			if (cur->data.judge == 1)
				printf("管理员   ");
			else
				printf("员工   ");
			system("pause");
			break;
		}
		case '0':
		{
			op = 0;
			break;
		}
		default:
		{
			printf("输入错误，请重新输入：\n");
			system("pause");
			break;
		}
		}
	}
	
	SaveStaff(head);
	
}

void PopMid(PInfo*head)
{
	loadStaff(head);
	int op = 1;
	while (op)
	{
		system("cls");
		PInfo* cur = head->next;
		PInfo* tem = head;
		printf("1.删除用户\n");
		printf("0.退出\n");
		char c = getch();
		switch (c)
		{
		case '1':
		{
			system("cls");
			printf("请输入需要删除用户的用户名：\n");
			char s[100];
			scanf("%s", s);
			while (cur->next != NULL)
			{
				if (strcmp(cur->data.user, s) == 0)
				{
					break;
				}
				cur = cur->next;
				tem = tem->next;
			}
			if (strcmp(cur->data.user, s) == 0)
			{
				tem->next = cur->next;
				op = 0;
				printf("删除成功");
			}
			else
			{
				printf("输入错误，请重新输入：\n");
				system("pause");
			}
			break;
		}
		case '0':
		{
			op = 0;
			break;
		}
		default:
			printf("输入错误，请重新输入");
		}
	}
	SaveStaff(head);
}
void UpdateStaffInfo(PInfo*head)
{
	loadStaff(head);
	int op = 1;
	char tem;
	do
	{
		system("cls");
		printf("        操作        \n");
		printf("   1.修改用户信息   \n");
		printf("      0.返回        \n");
		tem = getch();
		switch (tem)
		{
		case '1':
		{
			int op = 0;
			PInfo* cur = head->next;
			do
			{
				system("cls");
				printf("请输入您要修改的用户的账号：\n");
				char account[20];
				scanf("%s", account);
				while (cur->next!=NULL)
				{
					if (strcmp(cur->data.account, account)==0)
					{
						op = 1;
						break;
					}
					cur = cur->next;
				}
				if (op)
				{
					break;
				}
				else
				{
					printf("查无此人，请重新输入\n");
					system("pause");
				}
			} while (1);
			int tem = 1;
			char c;
			do
			{
				system("cls");
				printf("请问您要修改的数据是\n");
				printf("1.用户名\n");
				printf("0.退出修改\n");
				c = getch();
				switch (c)
				{
				case '1':
				{
					printf("请输入修改后的用户名\n");
					char user[20];
					scanf("%s", user);
					strcpy(cur->data.user,user);
					printf("修改成功\n");
					system("pause");
					break;
				}
				case '0':
				{
					tem = 0;
					break;
				}
				default :
				{
					printf("输入错误，请重新输入：");
					system("pause");
					break;
				}
				}
			} while (tem);

			break;
		}
		case '0':
		{
			printf("返回");
			op = 0;
			break;
		}
		default:
		{
			printf("输入错误，请重新输入：");
			break;
		}
		}
	} while (op);
	SaveStaff(head);
}
void CheckIntime(PInfo* head,PInfo*current)
{
	loadStaff(head);
	PInfo* cur = current;
	PInfo* tem = head;

	cur->data.time.checkInTime  = time(NULL);
	struct tm checkInTime = *localtime(&cur->data.time.checkInTime);

	// 显示打卡时间
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &checkInTime);
	printf("%s的打卡时间是: %s\n", cur->data.user , timeStr);

	// 判断是否在8:00之前打卡
	if (checkInTime.tm_hour < 8)
	{
		printf("打卡成功！\n");
		cur->data.time.checkIn++;
	}
	else {
		printf("打卡失败，未在8:00前打卡。\n");
	}
	SaveStaff(head);
}
PInfo* StuffAccount(PInfo* head )
{
	char c;
	int op = 1;
	while (op)
	{
		system("cls");
		printf("请输入你的员工账号：\n");
		char Account[20];
		scanf("%s", Account);
		printf("请输入密码：\n");
		char Password[20];
		scanf("%s", Password);
		PInfo* current = head;
		while (current->next != NULL)
		{
			current = current->next;
			if (strcmp(current->data.account, Account) == 0)
				if (strcmp(current->data.password, Password) == 0)
					if(current->data.judge ==0)
						return current;

		}
		int a = 1;
		printf("账号或密码存在错误\n");
		while (a)
		{
			printf("----------------------------\n");
			printf("          请选择           :\n");
			printf("       1.重新输入           \n");
			printf("       0.退出程序           \n");
			c = getch();
			switch (c)
			{
			case '1':
			{
				a = 0;
				break;
			}
			case '0':
			{
				op = 0;
				a = 0;
				break;
			}
			default:
			{
				system("cls");
				printf("输入错误，请重新输入\n");
				break;
			}
			}
		}
		
	}
	return NULL;
}
void RequestLeave(PInfo* head,PInfo*current)
{
	loadStaff(head);
	PInfo* cur = current;
	PInfo* tem = head->next;
	if (cur->data.leave == 0)
	{
		printf("%s申请请假\n",cur->data.account);
		cur->data.leave = 1;
	}
	else if (cur->data.leave == 1)
	{
		printf("请假进行中，请耐心等待\n");
	}
	else if (cur->data.leave == 2)
	{
		printf("您的请假没有被批准，如需请假，请重新申请\n");
		cur->data.leave == 0;
	}
	else
		printf("申请成功，正在休假");
	SaveStaff(head);
}

void approveLeaveRequest(PInfo* head)
{
	loadStaff(head);
	PInfo* cur = head;
	while (cur != NULL)
	{
		if (cur->data.leave == 1)
		{
			printf("%s正在申请请假\n", cur->data.user);
		}
		cur = cur->next;
	}
	int op = 1;
	do
	{
		system("cls");
		printf("请选择：\n");
		printf("       1.批准请假        \n");
		printf("       2.驳回请假        \n");
		printf("       3.结束假期        \n");
		printf("       0.返回            \n");
		char n = getch();
		switch (n)
		{
		case '1':
		{
			
			int t = 1;
			while (t)
			{
				system("cls");
				printf("请输入批准请假的用户名\n");
				char user[100];
				scanf("%s", user);
				PInfo* tem = head;
				while (tem->next != NULL)
				{
					tem = tem->next;
					if (strcmp(user, tem->data.user) == 0&&tem->data.leave==1)
					{
						tem->data.leave = 3;
						printf("%s已批准请假\n", tem->data.user);
						system("pause");
						t = 0;
						break;
					}
					if (strcmp(user, tem->data.user) != 0 && tem->next == NULL)
					{
						printf("未查询到此人\n");
						char tis = '1';
						printf("按0退出，按其余键继续\n");
						tis = getch();
						if (tis == '0')
						{
							printf("退出\n");
							t = 0;
						}
						system("pause");
					}
				}
				
			}
			break;
		}
		case '2':
		{
			int e = 1;
			while (e)
			{
				printf("请输入驳回请假的用户名\n");
				char user[100];
				scanf("%s", user);
				PInfo* temp = head;
				while (temp->next != NULL)
				{
					temp = temp->next;
					if (strcmp(user, temp->data.user) == 0 && temp->data.leave == 1)
					{
						temp->data.leave = 2;
						printf("%s已驳回请假\n", temp->data.user);
						e = 0;
						system("pause");
						break;
					}
					if (strcmp(user, temp->data.user) != 0 && temp->next == NULL)
					{
						printf("未查询到此人\n");
						char tim = '1';
						printf("按0退出，按其余键继续\n");
						tim = getch();
						if (tim == '0')
						{
							printf("退出");
							e = 0;
						}
						system("pause");
					}
				}
				
			}
			break;
		}
		case '3':
		{
			PInfo* phead = head;
			while (phead != NULL)
			{
				if (phead->data.leave == 3)
				{
					printf("%s处于假期中\n", phead->data.user);
				}
				phead = phead->next;
			}
			int k = 1;
			while (k)
			{
				printf("请输入结束假期的用户名\n");
				char user[100];
				scanf("%s", user);
				PInfo* tempe = head;
				while (tempe->next != NULL)
				{
					tempe = tempe->next;
					if (strcmp(user, tempe->data.user) == 0 && tempe->data.leave == 3)
					{
						tempe->data.leave = 0;
						printf("%s已结束假期\n", tempe->data.user);
						system("pause");
						k = 0;
						break;
					}
					if (strcmp(user, tempe->data.user) != 0 && tempe->next == NULL)
					{
						printf("未查询到此人\n");
						char ti = '1';
						printf("按0退出，按其余键继续\n");
						ti = getch();
						if (ti == '0')
						{
							printf("退出");
							k = 0;
						}
						system("pause");
					}
					
				}
			
			}
			break;
		}
		case '0':
		{
			op = 0;
			printf("感谢使用");
			break;
		}
		default :
		{
			printf("输入错误，请重新输入：\n");
			system("pause");
		}
		}

	} while (op);
	SaveStaff(head);

}
void CheckOutTime(PInfo* head, PInfo* current)
{
	loadStaff(head);
	PInfo* cur = current;
	PInfo* tem = head;

	cur->data.time.checkOutTime = time(NULL);
	struct tm checkInTime = *localtime(&cur->data.time.checkOutTime);

	// 显示打卡时间
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &checkInTime);
	printf("%s的签退时间是: %s\n", cur->data.user, timeStr);

	// 判断是否在8:00之前打卡
	if (checkInTime.tm_hour > 8)
	{
		printf("签退成功！\n");
		cur->data.time.checkOut++;
	}
	else {
		printf("打卡签退，未在8:00前签退。\n");
	}
	SaveStaff(head);
}

void Option()
{
	printf("       考勤系统         \n");
	printf("------------------------\n");
	printf("        1.员工          \n");
	printf("        2.管理          \n");
	printf("------------------------\n");
	printf("        0.退出          \n");
	printf("------------------------\n");

}
void MenuAdmin()
{
	printf("登陆成功，请选择您要进行的操作：\n");
	printf("--------------------------------\n");
	printf("           1.增加员工           \n");
	printf("           2.查看员工信息       \n");
	printf("           3.删除员工           \n");
	printf("           4.修改员工信息       \n");
	printf("           5.请假批准           \n");
	printf("           0.退出登录           \n");

}
void MenuStuff()
{
	printf("登陆成功，请选择您要进行的操作：\n");
	printf("--------------------------------\n");
	printf("            1.打卡          \n");
	printf("            2.请假		    \n");
	printf("            3.签退          \n");
	printf("          4.考勤记录        \n");
	printf("          0.退出登录        \n");
}
