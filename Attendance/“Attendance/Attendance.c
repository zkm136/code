#include"Attendance.h"

void Staff(PInfo**head)
{
	loadStaff(*head);
	int temp = 1;
	char option;
	do
	{
		printf("������ѡ��\n");
		printf("--------------------------\n");
		printf("         1.�����˺�       \n");
		printf("         2.��¼�˺�       \n");
		printf("       0.����ѡ�����     \n");
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
						printf("��\n");
						CheckIntime(head, current);
						break;
					}
					case '2':
					{
						printf("���\n");
						RequestLeave(head, current);

						break;
					}
					case '3':
					{
						printf("����\n");
						break;
					}
					case '4':
					{
						printf("ǩ��\n");
						CheckOutTime(head, current);
						break;
					}
					case '5':
					{
						printf("���ڼ�¼");
						break;
					}
					case '0':
					{
						printf("�˳���¼");
						tem = 0;
						break;
					}
					default:
					{
						printf("����������������룺\n");
					}
					}
				} while (tem);
			}
			else
			{
				printf("��½ʧ��");
			}
			break;
		}
		case '0':
		{
			printf("�����˳�\n");
			temp = 0;
			break;
		}
		default:
			printf("�����������������\n");
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
		printf("������ѡ��\n");
		printf("--------------------------\n");
		printf("         1.ע���˺�       \n");
		printf("         2.��¼�˺�       \n");
		printf("       0.����ѡ�����     \n");
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
						printf("����Ա��\n");
						PushBack(*head);
						break;
					}
					case '2':
					{
						printf("�鿴Ա����Ϣ\n");
						PrintData(*head);
						break;
					}case '3':
					{
						PrintData(*head);
						printf("ɾ��Ա��\n");
						PopMid(* head);
						printf("ɾ�����\n");
						PrintData(*head);
						break;
					}case '4':
					{
						printf("�޸�Ա����Ϣ\n");
						UpdateStaffInfo(*head);
						break;
					}case '5':
					{
						printf("�����׼\n");
						approveLeaveRequest(*head);
						break;
					}case '0':
					{
						printf("�˳���¼\n");
						tem = 0;
						break;
					}
					default:
					{
						printf("����������������룺\n");
					}
					}
				} while (tem);
			}
			break;
		}
		case '0':
		{
			printf("�����˳�\n");
			temp = 0;
			break;
		}
		default:
			printf("�����������������\n");
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
		printf("�����������Ա�˺ţ�\n");
		char Account[20];
		scanf("%s", Account);
		printf("���������룺\n");
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
		printf("�˺Ż�������ڴ���\n");
		printf("----------------------------\n");
		printf("          ��ѡ��           :\n");
		printf("       1.��������           \n");
		printf("       0.�Ƴ�����           \n");
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
			printf("�����������������");
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
		printf("û��Ա���ļ�,������ȡ\n");
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
	printf("��ȡ�ɹ�\n");
	
}
void SaveStaff(PInfo* head)
{
	FILE* file = fopen("data.txt", "w");
	if (!file)
	{
		printf("�޷�����Ա���ļ�\n");
		return;
	}
	if (!head)
	{
		return;
	}
	PInfo* move = head->next;  // ����ͷ�ڵ�
	while (move != NULL)
	{
		fwrite(&move->data, sizeof(PInfo), 1, file);
		move = move->next;
	}
	fclose(file);
	printf("����ɹ�\n");
}


void PushBack(PInfo*head)
{
	loadStaff(head);
	PInfo* tem = (PInfo*)malloc(sizeof(PInfo));
	if (!tem)
	{
		printf("�ڴ����ʧ��\n");
		return;
	}
	InfoDate PersonData;
	printf("�������˻���\n");
	scanf("%s",PersonData.account);
	printf("���������룺\n");
	scanf("%s", PersonData.password);
	printf("�������û�����\n");
	scanf("%s", PersonData.user);
	tem->next = NULL;
	tem->data.leave = 0;
	tem->data.time.checkIn = 0;
	tem->data.time.checkOut = 0;
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
	int op = 1;
	while (op)
	{
		printf("1.�鿴ȫ��Ա����Ϣ\n");
		printf("2.�鿴ĳһԱ����Ϣ\n");
		printf("0.�˳�\n");
		char c = getch();
		switch (c)
		{
		case '1':
		{
			PInfo* current = head;
			while (current->next != NULL)
			{
				current = current->next;
				printf("�˺�:");
				printf("%s    ", current->data.account);
				printf("����:");
				printf("%s    ", current->data.password);
				printf("�û���:");
				printf("%s    ", current->data.user);
				printf("���Ƴɹ���%d��   ", current->data.time.checkIn);
				printf("���Ƴɹ�ǩ��%d��   ", current->data.time.checkOut);
				printf("\n");
			}
			break;
		}
		case '2':
		{
			int opt = 1;
			PInfo* cur = head;
			while (opt)
			{
				printf("��������Ҫ�鿴Ա�����û���:\n");
				char s[50];
				scanf("%s", s);
				while (strcmp(cur->data.user, s) != 0&&cur->next!=NULL)
					cur = cur->next;
				if (strcmp(cur->data.user, s) == 0)
					opt = 0;
				else
				{
					printf("�����������������");
					cur = head;
				}
			}
			printf("�˺�:");
			printf("%s    ", cur->data.account);
			printf("����:");
			printf("%s    ", cur->data.password);
			printf("�û���:");
			printf("%s    ", cur->data.user);
			printf("���Ƴɹ���%d��   ", cur->data.time.checkIn);
			printf("���Ƴɹ�ǩ��%d��   ", cur->data.time.checkOut);
			printf("\n");
			break;
		}
		case '0':
		{
			op = 0;
			break;
		}
		default:
		{
			printf("����������������룺\n");
			break;
		}
		}
	}
	
	SaveStaff(head);
	
}

void PopMid(PInfo*head)
{
	loadStaff(head);
	PInfo* cur = head->next;
	PInfo* tem = head;
	printf("�������˺ţ�\n");
	char s[100] ;
	scanf("%s", s);
	while (cur->next)
	{
		if (strcmp(cur->data.account,s)==0)
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
		printf("        ����        \n");
		printf("   1.�޸��û���Ϣ   \n");
		printf("      0.����        \n");
		tem = getch();
		switch (tem)
		{
		case '1':
		{
			int op = 0;
			PInfo* cur = head->next;
			do
			{
				printf("��������Ҫ�޸ĵ��û����˺ţ�\n");
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
					printf("���޴��ˣ�����������\n");
				}
			} while (1);
			int tem = 1;
			char c;
			do
			{
				printf("������Ҫ�޸ĵ�������\n");
				printf("1.�û���\n");
				printf("0.�˳��޸�\n");
				c = getch();
				switch (c)
				{
				case '1':
				{
					printf("�������޸ĺ���û���\n");
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
					printf("����������������룺");
					break;
				}
				}
			} while (tem);

			break;
		}
		case '0':
		{
			printf("����");
			op = 0;
			break;
		}
		default:
		{
			printf("����������������룺");
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

	// ��ʾ��ʱ��
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &checkInTime);
	printf("%s�Ĵ�ʱ����: %s\n", cur->data.user , timeStr);

	// �ж��Ƿ���8:00֮ǰ��
	if (checkInTime.tm_hour < 8)
	{
		printf("�򿨳ɹ���\n");
		cur->data.time.checkIn++;
	}
	else {
		printf("��ʧ�ܣ�δ��8:00ǰ�򿨡�\n");
	}
	SaveStaff(head);
}
PInfo* StuffAccount(PInfo* head)
{
	char c;
	int op = 1;
	while (op)
	{
		printf("���������Ա���˺ţ�\n");
		char Account[20];
		scanf("%s", Account);
		printf("���������룺\n");
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
		printf("�˺Ż�������ڴ���\n");
		printf("----------------------------\n");
		printf("          ��ѡ��           :\n");
		printf("       1.��������           \n");
		printf("       0.�Ƴ�����           \n");
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
			printf("�����������������");
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
	if (cur->data.leave == 0)
	{
		printf("%s�������\n",cur->data.account);
		cur->data.leave = 1;
	}
	else if (cur->data.leave == 1)
	{
		printf("��ٽ����У������ĵȴ�\n");
	}
	else if (cur->data.leave == 2)
	{
		printf("�������û�б���׼��������٣�����������\n");
		cur->data.leave == 0;
	}
	else
		printf("����ɹ��������ݼ�");
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
			printf("%s�����������\n", cur->data.user);
		}
		cur = cur->next;
	}
	int op = 1;
	do
	{
		printf("��ѡ��\n");
		printf("       1.��׼���        \n");
		printf("       2.�������        \n");
		printf("       3.��������        \n");
		printf("       0.����            \n");
		char n = getch();
		switch (n)
		{
		case '1':
		{
			
			int t = 1;
			while (t)
			{
				printf("��������׼��ٵ��û���\n");
				char user[100];
				scanf("%s", user);
				PInfo* tem = head;
				while (tem->next != NULL)
				{
					tem = tem->next;
					if (strcmp(user, tem->data.user) == 0&&tem->data.leave==1)
					{
						tem->data.leave = 3;
						printf("%s����׼���\n", tem->data.user);
						t = 0;
						break;
					}
					if (strcmp(user, tem->data.user) != 0 && tem->next == NULL)
						printf("δ��ѯ�����ˣ����������룺\n");
				}
			}
			break;
		}
		case '2':
		{
			int e = 1;
			while (e)
			{
				printf("�����벵����ٵ��û���\n");
				char user[100];
				scanf("%s", user);
				PInfo* temp = head;
				while (temp->next != NULL)
				{
					temp = temp->next;
					if (strcmp(user, temp->data.user) == 0 && temp->data.leave == 1)
					{
						temp->data.leave = 2;
						printf("%s�Ѳ������\n", temp->data.user);
						e = 0;
						break;
					}
					if (strcmp(user, temp->data.user) != 0 && temp->next == NULL)
						printf("δ��ѯ�����ˣ����������룺\n");
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
					printf("%s���ڼ�����\n", phead->data.user);
				}
				phead = phead->next;
			}
			int k = 1;
			while (k)
			{
				printf("������������ڵ��û���\n");
				char user[100];
				scanf("%s", user);
				PInfo* tempe = head;
				while (tempe->next != NULL)
				{
					tempe = tempe->next;
					if (strcmp(user, tempe->data.user) == 0 && tempe->data.leave == 3)
					{
						tempe->data.leave = 0;
						printf("%s�ѽ�������\n", tempe->data.user);
						k = 0;
						break;
					}
					if (strcmp(user, tempe->data.user) != 0 && tempe->next == NULL)
						printf("δ��ѯ�����ˣ����������룺\n");
				}
			}
			break;
		}
		case '0':
		{
			op = 0;
			printf("��лʹ��");
			break;
		}
		default :
		{
			printf("����������������룺\n");
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

	// ��ʾ��ʱ��
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &checkInTime);
	printf("%s��ǩ��ʱ����: %s\n", cur->data.user, timeStr);

	// �ж��Ƿ���8:00֮ǰ��
	if (checkInTime.tm_hour > 8)
	{
		printf("ǩ�˳ɹ���\n");
		cur->data.time.checkOut++;
	}
	else {
		printf("��ǩ�ˣ�δ��8:00ǰǩ�ˡ�\n");
	}
	SaveStaff(head);
}

void Option()
{
	printf("       ����ϵͳ         \n");
	printf("------------------------\n");
	printf("        1.Ա��          \n");
	printf("        2.����          \n");
	printf("------------------------\n");
	printf("        0.�˳�          \n");
	printf("------------------------\n");

}
void MenuAdmin()
{
	printf("��½�ɹ�����ѡ����Ҫ���еĲ�����\n");
	printf("--------------------------------\n");
	printf("           1.����Ա��           \n");
	printf("           2.�鿴Ա����Ϣ       \n");
	printf("           3.ɾ��Ա��           \n");
	printf("           4.�޸�Ա����Ϣ       \n");
	printf("           5.�����׼           \n");
	printf("           0.�˳���¼           \n");

}
void MenuStuff()
{
	printf("��½�ɹ�����ѡ����Ҫ���еĲ�����\n");
	printf("--------------------------------\n");
	printf("            1.��          \n");
	printf("            2.���		    \n");
	printf("            3.����          \n");
	printf("            4.ǩ��          \n");
	printf("          5.���ڼ�¼        \n");
	printf("          0.�˳���¼        \n");
}
