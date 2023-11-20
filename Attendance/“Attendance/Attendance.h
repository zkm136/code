#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>


typedef struct StuffTime
{
	time_t checkInTime;
	time_t checkOutTime;
	int checkIn;
	int checkOut;
}STime;
typedef struct PersonData
{
	char account[50];
	char password[20];
	char user[20];
	STime time;
	int leave;
	int judge;
}PData;
typedef PData InfoDate;

typedef struct PersonInfo
{
	InfoDate data;
	struct PersonInfo* next;
}PInfo;




void MenuAdmin();//员工菜单
void Option();//总菜单
void Staff(PInfo** head);//员工
void Admin(PInfo** head);//管理员
void loadStaff(PInfo* head);//打开文件
void SaveStaff(PInfo* head);//保存文件
void PushBack(PInfo*head,int judge);//尾插，添加员工
void PrintData(PInfo* head);//打印员工信息
void PopMid(PInfo* head);//删除员工
int AdminAccount(PInfo* head);//管理员登录
void UpdateStaffInfo(PInfo*head);//更新员工信息
void MenuStuff();//员工菜单
void CheckIntime(PInfo* head, PInfo* cur);//员工打卡
void CheckOutTime(PInfo* head, PInfo* cur);//员工签退
PInfo* StuffAccount(PInfo* head);//员工登录
void RequestLeave(PInfo* head, PInfo* cur);//员工请假
void approveLeaveRequest(PInfo*head);//请假批准




