#include"Attendance.h"



int main()
{

	PInfo *Info=(PInfo*)malloc(sizeof(PInfo));
	Info->next = NULL;
    char op = 0;
	int swi = 1;
	do
	{
		system("cls");
		Option();
		op = getch();
		switch (op)
		{
			case '1':
			{
				Staff(&Info);
				printf("Ա��\n");
				break;
			}
			case '2':
			{
				Admin(&Info);
				printf("����Ա\n");
				break;
			}
			case '0':
			{
				swi = 0;
				printf("��лʹ��\n");
				break;
			}
			default:
			{
				printf("����������������룺\n");
				break;
			}
		}
	} while (swi);
	free(Info);
	Info=NULL;
	return 0;
}