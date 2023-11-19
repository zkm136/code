#include"Attendance.h"

void Staff(PInfo**head)
{
	loadStaff(*head);
	int temp = 1;
	char option;
	do
	{
		printf("请输入选项\n");
		printf("--------------------------\n");
		printf("         1.创建账号       \n");
		printf("         2.登录账号       \n");
		printf("       0.返回选择界面     \n");
		option = getch();
		switch (option)
		{
		case '1':
		{
			PushBack(*head);
			break;
		}
		case '2':
		{
			PInfo*current=StuffAccount(* head);
			if (current!=NULL)
			{
				int tem = 1;
				do
				{
					MenuStuff();
					char op = getch();
					switch (op)
					{
					case '1':
					{
						printf("打卡\n");
						CheckIntime(head, current);
						break;
					}
					case '2':
					{
						printf("请假\n");
						RequestLeave(head, current);

						break;
					}
					case '3':
					{
						printf("出差\n");
						break;
					}
					case '4':
					{
						printf("签退\n");
						break;
					}
					case '5':
					{
						printf("考勤记录");
						break;
					}
					case '0':
					{
						printf("退出登录");
						tem = 0;
						break;
					}
					default:
					{
						printf("输入错误请重新输入：\n");
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
			PushBack(*head);
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
					MenuAdmin();
					op = getch();
					switch (op)
					{
					case '1':
					{
						printf("增加员工\n");
						PushBack(*head);
						break;
					}
					case '2':
					{
						printf("查看员工信息\n");
						PrintData(*head);
						break;
					}case '3':
					{
						PrintData(*head);
						printf("删除员工\n");
						PopMid(* head);
						printf("删除完成\n");
						PrintData(*head);
						break;
					}case '4':
					{
						printf("修改员工信息\n");
						UpdateStaffInfo(*head);
						break;
					}case '5':
					{
						printf("请假批准\n");
						approveLeaveRequest(*head);
						break;
					}case '0':
					{
						printf("退出登录\n");
						tem = 0;
						break;
					}
					default:
					{
						printf("输入错误请重新输入：\n");
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
			break;
		}
	} while (temp);
	

	SaveStaff(*head);
}

int AdminAccount(PInfo* head)
{
	int op = 1;
	char c;
	while (op)
	{
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
			if (strcmp(current->data.account,Account)==0)
				if (strcmp(current->data.password,Password)==0)
					return 1;

		}
		printf("账号或密码存在错误\n");
		printf("----------------------------\n");
		printf("          请选择           :\n");
		printf("       1.重新输入           \n");
		printf("       0.推出程序           \n");
		c = getch();  
		switch (c)
		{
		case '1':
		{
			break;
		}
		case '0':
		{
			op = 0;
			break;
		}
		default:
		{
			printf("输入错误，请重新输入");
			break;
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


void PushBack(PInfo*head)
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
	scanf("%s",PersonData.account);
	printf("请输入密码：\n");
	scanf("%s", PersonData.password);
	printf("请输入用户名：\n");
	scanf("%s", PersonData.user);
	tem->next = NULL;
	tem->data.leave = 0;
	strcpy(tem->data.account, PersonData.account);
	strcpy(tem->data.password, PersonData.password);
	strcpy(tem->data.user, PersonData.user);
	PInfo* current = head;
	while (current->next!=NULL)
	{
		current = current->next;
	}
	current->next = tem;
	SaveStaff(head);
	
}
void PrintData(PInfo* head)
{
	loadStaff(head);

	if (!head)
	{
		return;
	}
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
		printf("\n");
	}
	SaveStaff(head);
	
}

void PopMid(PInfo*head)
{
	loadStaff(head);
	PInfo* cur = head->next;
	PInfo* tem = head;
	printf("请输入账号：\n");
	InfoDate data;
	scanf("%s", data.account);
	while (cur->next)
	{
		if (strcmp(cur->data.account,data.account)==0)
		{
			break;
		}
		cur = cur->next;
		tem =tem->next ;
	}
	tem->next = cur->next;
	free(cur);
	cur = NULL;
	SaveStaff(head);
}
void UpdateStaffInfo(PInfo*head)
{
	loadStaff(head);
	int op = 1;
	char tem;
	do
	{
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
				printf("请输入您要修改的用户的账号：\n");
				char account[20];
				scanf("%s", account);
				while (cur->next)
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
				}
			} while (1);
			int tem = 1;
			char c;
			do
			{
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
	while (tem->next != cur->next )
	{
		tem = tem->next;
	}
	tem->data.time  = time(NULL);
	struct tm checkInTime = *localtime(&tem->data.time);

	// 显示打卡时间
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &checkInTime);
	printf("%s的打卡时间是: %s\n", tem->data.user , timeStr);

	// 判断是否在8:00之前打卡
	if (checkInTime.tm_hour < 8)
	{
		printf("打卡成功！\n");
	}
	else {
		printf("打卡失败，未在8:00前打卡。\n");
	}
	SaveStaff(head);
}
PInfo* StuffAccount(PInfo* head)
{
	char c;
	int op = 1;
	while (op)
	{
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
					return current;

		}
		printf("账号或密码存在错误\n");
		printf("----------------------------\n");
		printf("          请选择           :\n");
		printf("       1.重新输入           \n");
		printf("       0.推出程序           \n");
		c = getch();
		switch (c)
		{
		case '1':
		{
			break;
		}
		case '0':
		{
			op = 0;
			break;
		}
		default:
		{
			printf("输入错误，请重新输入");
			break;
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
	while (strcmp(tem->data.account,cur->data.account)!=0)
	{
		tem = tem->next;
	}
	if (tem->data.leave == 0)
	{
		printf("%s申请请假\n",tem->data.account);
		tem->data.leave = 1;
	}
	if (tem->data.leave == 1)
	{
		printf("请假进行中，请耐心等待\n");
	}
	if(tem->data.leave!=1&&tem->data.leave!=0)
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
	printf("            3.出差          \n");
	printf("            4.签退          \n");
	printf("          5.考勤记录        \n");
	printf("          0.退出登录        \n");
}
