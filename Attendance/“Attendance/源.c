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
				printf("员工\n");
				break;
			}
			case '2':
			{
				Admin(&Info);
				printf("管理员\n");
				break;
			}
			case '0':
			{
				swi = 0;
				printf("感谢使用\n");
				break;
			}
			default:
			{
				printf("输入错误，请重新输入：\n");
				break;
			}
		}
	} while (swi);
	free(Info);
	Info=NULL;
	return 0;
}