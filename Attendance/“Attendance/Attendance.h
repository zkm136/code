#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>


typedef struct CheckinTime
{
	time_t checkInTime;
	struct CheckinTime* next;
}CITime;

typedef struct PersonData
{
	char account[50];
	char password[20];
	char user[20];
	time_t time;
	int leave;
}PData;
typedef PData InfoDate;

typedef struct PersonInfo
{
	InfoDate data;
	struct PersonInfo* next;
}PInfo;




void MenuAdmin();//Ա���˵�
void Option();//�ܲ˵�
void Staff(PInfo** head);//Ա��
void Admin(PInfo** head);//����Ա
void loadStaff(PInfo* head);//���ļ�
void SaveStaff(PInfo* head);//�����ļ�
void PushBack(PInfo*head);//β�壬���Ա��
void PrintData(PInfo* head);//��ӡԱ����Ϣ
void PopMid(PInfo* head);//ɾ��Ա��
int AdminAccount(PInfo* head);//����Ա��¼
void UpdateStaffInfo(PInfo*head);//����Ա����Ϣ
void MenuStuff();//Ա���˵�
void CheckIntime(PInfo* head, PInfo* cur);//Ա����
PInfo* StuffAccount(PInfo* head);//Ա����¼
void RequestLeave(PInfo* head, PInfo* cur);//Ա�����
void approveLeaveRequest(PInfo*head);//�����׼




