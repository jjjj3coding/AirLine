#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#define MAX 168 //�ɻ�����168�� 
int lev;
int user_index;  //���û���Ϣ����±� 
int passenger_index; //�ڳ˿���Ϣ����±� 
int filght_index; 	//�ں�����Ϣ����±� 
char map[10][5] = { "","����","����","����","����","����","����","����","�½�" };
int year, month, day, hour, min, sum;
//�������߽ṹ�壬��������line���溽����Ϣ 
typedef struct user {
	int amount;
	char name[10];//�û����� 
	char id[20];//�û����֤�� 
	char account[15];//�˺� 
	char password[15];//���� 
	char phoneNum[12];//�ֻ��� 
	int level;//Ȩ��ֵ 
}user;

typedef struct flight {
	int amount;
	char* flightNum;//����� 
	char up_time[18];//���ʱ�� 
	char off_time[18];//����ʱ�� 
	char up_pos[10];
	char off_pos[10];//��ʼ�� 
	double price;//Ʊ�� 
	double discount;//�ۿ� 
	int num;//�����ϵ����� 
}flight;

typedef struct passenger {
	int amount;
	char name[10]; //���� 
	char id[20];//���֤ 
	char flightNum[10];//����� 
	char phoneNum[12];//�ֻ��� 
}passenger;

user userArr[500005];
flight flightArr[500005];
passenger passengerArr[500005];
/*���ܣ�����ѡ�����������жϸ�ʽ�Ƿ���ȷ*/
/*�÷�������1 ~ n��ѡ��ʱ�� ��n���룬ֻ������1<=x<=n ��Ϊ������ʱ���ŷ���ѡ��*/
int read(int r)
{
	int choice;
	while (1) {
		fflush(stdin);
		double data;
		scanf("%lf", &data);
		if (data > r || data < 1 || data != (int)data) printf("���벻�Ϲ淶�����������룺\n");
		else {
			choice = (int)data;
			return choice;
		}
	}
}
/*���ܣ����뺽��ź����������ж���ʽ�Ƿ���ȷ*/
char* read_flight()
{
	static char number[10];
	bool judge = false;
	while (1) {
		scanf("%s", number);
		if (strlen(number) != 8)  printf("������ĺ����1��ʽ�������������룺\n");
		else if (number[0] != 'C' || number[1] != 'N') printf("������ĺ����2��ʽ�������������룺\n");
		else if (number[2] < '1' || number[2]>'9' || number[3] < '1' || number[3]>'9') printf("������ĺ����3��ʽ�������������룺\n");
		else {
			bool judge = true;
			for (int i = 4; i < 8; i++) {
				if ('0' <= number[i] && number[i] <= '9') continue;
				else {
					judge = false;
					break;
				}
			}
			if (judge) return number;
			else printf("������ĺ���Ÿ�ʽ�������������룺\n");
		}
	}
}
//ע�ắ�� 
void sign()
{
	int usersnum = userArr[0].amount;

	printf("�����������˺�(��֤�˺ų�����8~14֮��)��\n");
	while (1) {
		scanf("%s", userArr[usersnum].account);
		int len = strlen(userArr[usersnum].account);
		if (8 <= len && len <= 14) break;
		else printf("��������˺ų��Ȳ�����Ҫ�����������룺\n");
	}

	printf("�������������룬ʹ���볤�Ȳ�����8λ��������14λ��\n");
	scanf("%s", userArr[usersnum].password);
	while (strlen(userArr[usersnum].password) > 14 || strlen(userArr[usersnum].password) < 8) {
		printf("��ʹ���볤�Ȳ�����8λ��������14λ,���������룺\n");
		scanf("%s", userArr[usersnum].password);
	}
	char temp_password[15];
	printf("���ٴ��������룺\n");
	while (1) {
		scanf("%s", temp_password);
		if (strcmp(temp_password, userArr[usersnum].password) == 0) break;
		else printf("��ǰ�������������벻ͬ��������������֮ǰ���������룺\n");
	}

	system("cls");
	printf("���������˺ŵĸ�����Ϣ\n");

	printf("��������������\n");
	scanf("%s", userArr[usersnum].name);
	while (strlen(userArr[usersnum].name) > 6) {
		printf("�뱣������������6λ���£�������������������\n");
		scanf("%s", userArr[usersnum].name);
	}

	printf("�������������֤��\n");
	scanf("%s", userArr[usersnum].id);
	while (strlen(userArr[usersnum].id) != 18) {
		printf("���֤��ʽ��������������\n");
		scanf("%s", userArr[usersnum].id);
	}

	printf("�����������ֻ�����\n");
	scanf("%s", userArr[usersnum].phoneNum);
	while (strlen(userArr[usersnum].phoneNum) != 11) {
		printf("�ֻ��Ÿ�ʽ��������������\n");
		scanf("%s", userArr[usersnum].phoneNum);
	}

	system("cls");
	printf("��ϲ��ע��ɹ�\n");
	printf("���������˺�������\n");
	printf("�˺ţ�%s\n ���룺%s\n", userArr[usersnum].account, userArr[usersnum].password);
	printf("���μ������˺ź����룬��л��������ټ���\n");
	userArr[0].amount++;
	/*������ӵ���Ϣ �����û��˺Ž��д�С���� ��������*/
	user new_user = userArr[usersnum];
	int index = usersnum - 1;
	while (index >= 0 && strcmp(userArr[index].account, new_user.account) > 0) index--;
	index++;
	for (int i = index; i < usersnum; i++) userArr[i + 1] = userArr[i];
	userArr[index] = new_user;
}
//���ֲ��ҳ˿���Ϣ�е�һ�����ϵ��±꣬��û�з���-1
int search_flight(char* flightNum)
{
	int l = 0, r = flightArr[0].amount - 1;
	int mid;
	while (l < r) {
		mid = (l + r) / 2;
		//if (strcmp(flightNum, flightArr[mid].flightNum) == 0) return mid;
		if (strcmp(flightNum, flightArr[mid].flightNum) <= 0) r = mid;
		else l = mid + 1;
	}
	if (strcmp(flightNum, flightArr[l].flightNum) == 0) return l;
	else return -1;
}
//���ݵص㣬������ѯ���Ϻ��� 
int search_area(int start, int end)
{
	printf("��%s����%s�ĺ��ࣺ\n", map[start], map[end]);
	int num = 0;
	for (int i = 0; i < flightArr[0].amount; i++) {
		if (flightArr[i].flightNum[2] == start + '0'
			&& flightArr[i].flightNum[3] == end + '0')
			printf("%s\n", flightArr[i].flightNum), num++;
	}
	if (num == 0) {
		printf("��Ǹ����%s����%s,������������\n", map[start], map[end]);
		return 0;
	}
	return 1;
}
//���ֲ��ҳ˿���Ϣ�е�һ�����ϵ��±꣬��û�з���-1 
int search_passenger(char* id, char* flightNum)
{
	int l = 0, r = passengerArr[0].amount-1;
	int mid;
	while (l<r) {
		mid = (l + r) >> 1;
		if (strcmp(id, passengerArr[mid].id) <= 0) r = mid;
		else l = mid+1;
	}
	if (flightNum != NULL) {
		while (strcmp(id, passengerArr[l].id) == 0 &&
			strcmp(flightNum, passengerArr[l].flightNum) != 0)
			l++;
	}
	if (strcmp(passengerArr[l].id, id) == 0) return l;
	return -1;
}
//���ö��֣������˺ţ��������ļ��е��±� 
int search_account(char* account)
{
	int l = 0, r = userArr[0].amount - 1;
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (strcmp(account, userArr[mid].account) == 0) return mid;
		else if (strcmp(account, userArr[mid].account) < 0) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}
//��¼���� 
int logIn()
{
	/*�����˺�*/
	printf("�����������˺ţ�\n");
	char temp_account[15];
	char temp_password[20];
	int index;
	bool judge = false;
	while (!judge) {
		scanf("%s", temp_account);
		index = search_account(temp_account);
		if (index == -1) printf("�����˺Ų����ڣ����������룺\n");
		else judge = true;
	}

	/*��������*/
	printf("��������������:\n");
	judge = false;
	while (!judge) {
		scanf("%s", temp_password);
		if (strcmp(userArr[index].password, temp_password) != 0) printf("�������벻��ȷ������������(����������������ϵ�ͷ�)��\n");
		else {
			printf("��¼�ɹ�!��ӭ����%s\n", userArr[index].name);
			judge = true;
		}
	}
	return index;
}
//�˵����� 
int print()
{
	int choice1;
	/*����˵�ҳ��*/
	printf("-----------------------------\n");
	printf("   ����ѧԺ���չ�˾��ӭ����\n");
	printf("1.��Ʊ����\n");
	printf("2.��Ʊ����\n");
	printf("3.��ѯ������Ϣ\n");
	printf("4.��ѯ�˺���Ϣ\n");
	printf("5.��ѯ��Ʊ��Ϣ\n");
	printf("6.�޸��˺���Ϣ\n");
	printf("7.ע���˺�\n");
	printf("8.�˳�\n");
	if (lev) {
		printf("9.¼�뺽����Ϣ\n");
		printf("10.�޸ĺ�����Ϣ\n");
		printf("11.ɾ������\n");
		printf("12.����û�\n");
	}
	printf("-----------------------------\n");

	/*�����û�ѡ�����*/
	printf("��������ѡ��ķ���:\n");
	if (lev) choice1 = read(12);
	else choice1 = read(8);
	return choice1;
}
//������Ʊ����
void checkin()
{
	/*�ж� ��Ʊ��ʽ*/
	printf("����ѡ�����¹�Ʊ��ʽ��\n");
	printf("1.���ݺ���Ź�Ʊ\n2.������ʼ�ع�Ʊ\n");
	int choice = read(2);
	int search;
	/*�����Ӧ����*/
	if (choice == 2) {
		printf("��˾֧������8���ط����У�\n");
		printf("1.����\n2.����\n3.����\n4.����\n5.����\n6.����\n7.����\n8.�½�\n");
		printf("��������ĳ����ء�Ŀ�ĵص���ţ�\n");
		int start = read(8);
		int end;
		bool judge = false;
		while (!judge) {
			end = read(8);
			if (end == start) printf("�������Ŀ�ĵ����������ͬ�����������룺\n");
			else judge = true;
		}
		search=search_area(start, end);
	}
	if(search==1||choice==1){
		char* temp_flightNum;
		/* �õ� ��Ʊ�����*/
		printf("��������ѡ��ĺ���:");
temp_flightNum=read_flight() ;
	
		int index = search_flight(temp_flightNum);//�н��±� 
		while (flightArr[index].num == MAX) {
			printf("��Ǹ������%s�����������Ƽ�ͬ����ʼ�غ���\n", temp_flightNum);
			int flag = search_area(temp_flightNum[2] - '0', temp_flightNum[3] - '0');
			if (flag) {
				printf("��������ѡ��Ʊ����ţ��밴1\n �����蹺Ʊ���밴2�˳�");
				int temp_choice = read(2);
				if (temp_choice == 2) exit(0);
				else {
					printf("��������ѡ��ĺ���:\n");
					temp_flightNum=read_flight() ;
					index = search_flight(temp_flightNum);
				}
			}
		}
		int passnum = passengerArr[0].amount;
		/*��Ʊ�����º�����Ϣ*/
		strcpy(passengerArr[passnum].flightNum, temp_flightNum);
		system("cls");
		printf("��ϲ������Ʊ�ɹ�!\n");
		passengerArr[0].amount++;
		flightArr[index].num++;
		/*�����������������֤�����в�������*/
		passenger temp_passenger = passengerArr[passnum];
		index = passnum - 1;
		while (index >= 0 && strcmp(passengerArr[index].id, temp_passenger.id) > 0) index--;
		index++;
		for(int i = index; i < passnum; i++) passengerArr[i + 1] = passengerArr[i];
		passengerArr[index] = temp_passenger;
	}
	return;
}

//�Լ���Ʊ 
void checkIn_my()
{
	/*��ʼ��*/
	int passnum = passengerArr[0].amount;
	char temp_flightNum[10];
	strcpy(passengerArr[passnum].name, userArr[user_index].name);
	strcpy(passengerArr[passnum].id, userArr[user_index].id);
	strcpy(passengerArr[passnum].phoneNum, userArr[user_index].phoneNum);
	checkin();
}
// ���˶�Ʊ 
void checkIn_other()
{
	int usersnum = userArr[0].amount;
	printf("���������Ĺ�Ʊ��(һ���Թ�Ʊ�����ó���10��)��\n");
	int num = read(10);
	while (num--) {
		printf("������˿͵�����\n");
		scanf("%s", userArr[usersnum].name);
		while (strlen(userArr[usersnum].name) > 6) {
			printf("�뱣������������6λ���£�������������������\n");
			scanf("%s", userArr[usersnum].name);
		}

		printf("������˿͵����֤��\n");
		scanf("%s", userArr[usersnum].id);
		while (strlen(userArr[usersnum].id) != 18) {
			printf("���֤��ʽ��������������\n");
			scanf("%s", userArr[usersnum].id);
		}

		printf("������˿͵��ֻ�����\n");
		scanf("%s", userArr[usersnum].phoneNum);
		while (strlen(userArr[usersnum].phoneNum) != 11) {
			printf("�ֻ��Ÿ�ʽ��������������\n");
			scanf("%s", userArr[usersnum].phoneNum);
		}

		int passnum = passengerArr[0].amount;
		strcpy(passengerArr[passnum].name, userArr[user_index].name);
		strcpy(passengerArr[passnum].id, userArr[user_index].id);
		strcpy(passengerArr[passnum].phoneNum, userArr[user_index].phoneNum);
		checkin();
	}
}
void checkIn()
{
	system("cls");
	printf("��ӭʹ�ñ���˾��Ʊϵͳ��\n");
	if (userArr[user_index].level == 0) {
		printf("��ѡ�����Ĺ�Ʊ����");
		printf("1.Ϊ�Լ���Ʊ\n2.Ϊ���˹�Ʊ\n");
		int choice = read(2);
		if (choice == 1)	checkIn_my();
		else checkIn_other();
	}
	else	checkIn_other();
}

//���������Ϣ 
void search()
{
	/*ѡ���ѯ��ʽ*/
	system("cls");
	printf("-----------------------------\n");
	printf("����ѡ���ѯ�������\n");
	printf("�������ѯ��ʽ (������ 1 �� 2)��\n");
	printf("1.���ݺ���Ų�ѯ\n");
	printf("2.������ɣ�������в�ѯ\n");
	int way = read(2);

	if (way == 1) {
	
		/*��������ĺ����*/
		system("cls");
		printf("   �������ѯ����ţ�\n");
		char* number;
		number = read_flight();
		int index = search_flight(number);

		/*����������Ϣ*/
		if (index != -1) {
			printf("����%s�ĺ�����Ϣ��\n", flightArr[index].flightNum);
			printf("���ʱ�䣺%s\n", flightArr[index].up_time);
			printf("����ʱ�䣺%s\n", flightArr[index].off_time);
			printf("��ɵص㣺%s\n", flightArr[index].up_pos);
			printf("����ص㣺%s\n", flightArr[index].off_pos);
			printf("����Ʊ�ۣ���%.2lf\n", flightArr[index].price);
			printf("Ʊ���ۿۣ�%.lf%%\n", flightArr[index].discount);
			printf("������������%d\n", flightArr[index].num);
			if (flightArr[index].num == MAX)	printf("ע��������\n");
			else {
				printf("���Ƿ���Ҫ�����κ����Ʊ��\n");
				printf("1.��Ҫ\n");
				printf("2,����������\n");
				int choice = read(2);
				if (choice == 1)  checkin();
				else {
					system("cls");
					return; 
				}
			}
		}
		else printf("������ѯ�ĺ���Ų����ڡ�\n");
	}
	else {
		system("cls");
		printf("��˾֧������8���ط����У�\n");
		printf("1.����\n2.����\n3.����\n4.����\n5.����\n6.����\n7.����\n8.�½�\n");
		printf("��������ĳ����ء�Ŀ�ĵص���ţ�\n");

		/*������ʼ�أ�Ŀ�ĵ�*/
		int start = read(8);
		int end;
		bool judge = false;
		while (!judge) {
			end = read(8);
			if (end == start) printf("�������Ŀ�ĵ����������ͬ�����������룺\n");
			else judge = true;
		}
		search_area(start, end);
	}
}
//����û���Ϣ 
void search_user()
{
	//�����û��������������˺� 
	//���ǹ���Ա�������ѯ�˺� 
	system("cls");
	if (lev == 1) {
		printf("����������Ҫ��ѯ�û��˺ţ�\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			user_index = search_account(temp_account);
			if (user_index == -1) {
				printf("�˻������Ƿ������ѯ��\n");
				printf("1.������ѯ\n2.�˳���ѯ\n");
				int choice = read(2);
				if (choice == 2) exit(0);
			}
			else judge = true;
		}
	}
	printf("�û�������Ϣ���£�\n");
	printf("�û�������%s\n", userArr[user_index].name);
	printf("�û����֤��%s\n", userArr[user_index].id);
	printf("�û��˺ţ�%s\n", userArr[user_index].id);
	printf("�û����룺%s\n", userArr[user_index].password);
	printf("�û��ֻ����룺%s\n", userArr[user_index].phoneNum);
		printf("����1����������\n");
					int a = read(2);
					while (a != 1) {
						printf("�����������������\n");
						a = read(2);
				}
				system("cls");
}
				
//�����Ʊ��Ϣ 
void search_tickets()
{
	int index;
	//�����û��������������˺� 
	//���ǹ���Ա�������ѯ�˺� 
	system("cls");
	if (lev != 0) {
		printf("����������Ҫ��ѯ�û��˺ţ�\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			user_index = search_account(temp_account);
			if (user_index == -1) printf("�����˺Ų����ڣ����������룺\n");
			else judge = true;
		}
	}
	passenger_index = search_passenger(userArr[user_index].id, NULL);
	if (passenger_index == -1) printf("�û�û�ж�Ʊ\n");
	else {
		int i = passenger_index;
		printf("�û���Ʊ��Ϣ���£�\n");
		while (strcmp(passengerArr[passenger_index].id, passengerArr[i].id) == 0) {
			printf("%s\n", passengerArr[i].flightNum);
			i++;
		}
	}
}
//���ַ�����תΪint������ 
int time_change(char* time, int l, int r)
{
	int ans = 0;
	for (int i = l; i <= r; i++) {
		ans = ans * 10 + (time[i] - '0');
	}
	return ans;
}
//����ʱ������� 
double computing_time(char* time)
{
	double temp_time;
	 year = time_change(time, 0, 3);
	 month = time_change(time, 5, 6);
	 day = time_change(time, 8, 9);
	 hour = time_change(time, 11, 12);
	 min = time_change(time, 14, 15);
	 sum = hour * 60 + min;
	temp_time = year * 1e8 + month * 1e6 + day * 1e4 + sum;
	return temp_time;
}
//��Ӻ��� 
void flight_input()
{
	system("cls");
	int flinum = flightArr[0].amount;

	/*���뺽���*/
	printf("�����뺽���\n");
	flightArr[flinum].flightNum = read_flight();

	/*�������ʱ��*/
	printf("���������ʱ�� \n");
	double time1;
	while (1) {
		scanf("%s", flightArr[flinum].up_time);
		if (strlen(flightArr[flinum].up_time) != 16) printf("�������ʱ���ʽ�������������룺\n");
		else if (flightArr[flinum].up_time[4] != '/' || flightArr[flinum].up_time[7] != '/' ||
			flightArr[flinum].up_time[10] != '/' || flightArr[flinum].up_time[13] != ':')
			printf("�������ʱ���ʽ�������������룺\n");
		else {
			time1 = computing_time(flightArr[flinum].up_time);
			int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
			if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
			if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
			else printf("�������ʱ���ʽ�������������룺\n");
		}
	}
	//���뽵��ʱ�� 
	printf("�����뽵��ʱ��\n");
	double time2;
	while (1)
	{
		scanf("%s", flightArr[flinum].off_time);
		if (strlen(flightArr[flinum].off_time) != 16) printf("�������ʱ���ʽ�������������룺\n");
		else if (flightArr[flinum].off_time[4] != '/' || flightArr[flinum].off_time[7] != '/' ||
			flightArr[flinum].off_time[10] != '/' || flightArr[flinum].off_time[13] != ':')
			printf("�������ʱ���ʽ�������������룺\n");
		else {
		time2 = computing_time(flightArr[flinum].off_time);
		int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
		if (day <= days[month] && 0 <= sum && sum <= 24 * 60 && time2 > time1) break;
		else printf("�������ʱ���ʽ�������������룺\n");
		}
	}

	/*������ʼ��*/
	strcpy(flightArr[flinum].up_pos, map[flightArr[flinum].flightNum[2] - '0']);
	strcpy(flightArr[flinum].off_pos, map[flightArr[flinum].flightNum[3] - '0']);
	
	flightArr[flinum].price = -1;
	printf("������Ʊ��\n");
	while (1) {
		fflush(stdin);
		scanf("%lf", &flightArr[flinum].price);
		if (flightArr[flinum].price > 10000 || flightArr[flinum].price < 0) printf("���벻�Ϲ淶�����������룺\n");
		else  break;
	}

	flightArr[flinum].discount = -1;
	printf("�������ۿ�\n");
	while (1) {
		fflush(stdin);
		scanf("%lf", &flightArr[flinum].discount);
		if (flightArr[flinum].discount > 100 || flightArr[flinum].discount < 0) printf("���벻�Ϲ淶�����������룺\n");
		else  break;
	}

	flightArr[flinum].num = 0;
	flightArr[0].amount++;
	/*����*/
	flight temp_flight = flightArr[flinum];
	int index = flinum - 1;
	while (index >= 0 && strcmp(flightArr[index].flightNum, temp_flight.flightNum) > 0) index--;
	index++;
	for (int i = index; i < flinum; i++) flightArr[i + 1] = flightArr[i];
	flightArr[index] = temp_flight;
	system("cls");
	printf("��ӳɹ���\n");
}
//�޸��û�
void rewrite()
{
	system("cls");
	int choice;
	int temp_index;
	char oldPasword[20];
	char newPaswordf[20];
	char newPaswords[20];
	char newPhoneNum[12];
	//�ж�Ȩ��ֵ����Ϊ����Ա���������û��˺� 
	if (userArr[user_index].level == 1) {
		printf("����������Ҫ��ѯ�û��˺ţ�\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			temp_index = search_account(temp_account);
			if (temp_index == -1) {
				printf("�˻������Ƿ������ѯ��\n");
				printf("1.������ѯ\n2.�˳���ѯ\n");
				int choice = read(2);
				if (choice == 2) exit(0);
			}
			else judge = true;
		}
	}

	//ѡ����Ҫ�޸ĵ���Ϣ����Ϊ�˺ź����֤�������ǰ󶨵ģ��������֤�����������޸ģ� 
	printf("��ѡ����Ҫ�޸ĵ���Ϣ��\n");
	printf("1.����\n");
	printf("2.�ֻ���\n");
	if (userArr[user_index].level == 2) {
		printf("3.���ù���Ա\n");
		choice = read(3);
	}
	else choice = read(2);

	//��ѡ���޸����룬����Ҫ����������룬�ٽ��������������� 
	if (choice == 1) {
		printf("������ԭ���룺\n");
		scanf("%s", oldPasword);
		while (strcmp(oldPasword, userArr[temp_index].password) != 0) {
			printf("ԭ��������Ƿ�����޸ģ�\n");//ԭ��������ѡ������޸Ļ��˳� 
			printf("1.�����޸�\n2.�˳��޸�\n");
			choice = read(2);
			if (choice == 1) {
				printf("������ԭ���룺\n");
				scanf("%s", oldPasword);
			}
			else	exit(0);
		}

		//��������������������ͬ�����޸ĳɹ� 
		printf("�����������룺\n");
		scanf("%s", newPaswordf);
		printf("���ٴ����������룺\n");
		scanf("%s", newPaswords);
		while (strcmp(newPaswordf, newPaswords) != 0) {
			printf("�������벻һ�£����ٴ����������룺\n");
			scanf("%s", newPaswords);
		}
		strcpy(userArr[temp_index].password, newPaswords);
	}
	//��ѡ���޸��ֻ��ţ������ֻ��ų����Ƿ�Ϲ棬���Ϲ����޸ĳɹ�������������� 
	else if (choice == 2) {
		printf("�������µ��ֻ��ţ�\n");
		scanf("%s", newPhoneNum);
		while (strlen(newPhoneNum) != 11) {
			printf("����������ֻ��Ŵ����Ƿ�����޸ģ�\n");//�ֻ��Ų��Ϲ棬�û���ѡ�����������˳� 
			printf("1.�����޸�\n2.�˳��޸�\n");
			choice = read(2);
			if (choice == 1) {
				printf("���������ֻ��ţ�\n");
				scanf("%s", newPhoneNum);
			}
			else	exit(0);
		}
		strcpy(userArr[temp_index].phoneNum, newPhoneNum);//�ֻ����޸ĳɹ� 
	}

	else {
		printf("��ѡ�����Ĳ�����\n");
		printf("1.����Ϊ����Ա\n2.ȡ������Ա\n");
		choice = read(2);
		if (choice == 1)  userArr[temp_index].level = 1;
		else  userArr[temp_index].level = 0;
	}
	system("cls");
	printf("�û���Ϣ�޸ĳɹ���\n");
	return;
}
//ɾ�����ຯ�� 
void del_flight()
{
	system("cls");
	int index;
	char* aim_flightNum ;
	printf("�������ɾ������ţ�\n");
	aim_flightNum = read_flight();
	index = search_flight(aim_flightNum);
	while (index == -1) {
		printf("δ��ѯ�ô˺��࣬���������뺽��ţ�\n");
		scanf("%s", aim_flightNum);
		index = search_flight(aim_flightNum);
	}
	for (int i = index; i < flightArr[0].amount; i++) {
		flightArr[i].flightNum=flightArr[i+1].flightNum;
			strcpy(flightArr[i].up_time, flightArr[i+1].up_time);
			strcpy(flightArr[i].off_time,flightArr[i+1].off_time);
			strcpy(flightArr[i].up_pos, flightArr[i+1].up_pos);
			strcpy(flightArr[i].off_pos, flightArr[i+1].off_pos);
			flightArr[i].price=flightArr[i+1].price;
		flightArr[i].discount=flightArr[i+1].discount;
		flightArr[i].num=flightArr[i+1].num;
	}
	flightArr[0].amount--;
	printf("ɾ������ɹ���\n");
	return;
}
//�޸ĺ���
void flight_change()
{
	system("cls");
	int index;
	int choice;

	char reup_time[18];//���ʱ�� 
	char reoff_time[18];//����ʱ�� 
	double reprice;//Ʊ�� 
	double rediscount;//�ۿ� 

	/*���뺽���*/
	char* aim_flightNum;
	printf("�����뺽��ţ�\n");
	aim_flightNum = read_flight();
	index = search_flight(aim_flightNum);
	while (index == -1) {
		printf("����Ų����ڣ����������룺\n");
		aim_flightNum = read_flight();
		index = search_flight(aim_flightNum);
	}
	double time1, time2, time3;

	/*ѡ�����*/
	while (1)
	{
		system("cls");
		printf("�������²�������ѡ��\n");
		printf("1.�������ʱ��\n2.���ཱུ��ʱ��\n");
		printf("3.����Ʊ��\n4.�����ۿ�\n");
		printf("5.�˳�\n");
		choice = read(5);

		/*�����ϵ����ʱ��*/
		time1 = computing_time(flightArr[index].up_time);
		/*�����ϵĽ���ʱ��*/
		time2 = computing_time(flightArr[index].off_time);

		if (choice == 1)
		{
			printf("�밴���¸�ʽ�����µ����ʱ�䣺\n");
			printf("���磺2022/12/31/20:00");
			while (1) {
				scanf("%s", flightArr[index].up_time);
				if (strlen(flightArr[index].up_time) != 16) printf("�������ʱ���ʽ�������������룺\n");
				if (flightArr[index].up_time[4] != '/' || flightArr[index].up_time[7] != '/' ||
					flightArr[index].up_time[10] != '/' || flightArr[index].up_time[13] != ':')
					printf("�������ʱ���ʽ�������������룺\n");
				else {
					time3 = computing_time(flightArr[index].up_time);
					int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
					if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
					if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
					printf("�������ʱ���ʽ�������������룺\n");
				}
			}
			if (time3 < time2) printf("�������ʱ������ڽ���ʱ�䣬������޸Ľ���ʱ��\n");
			printf("������Ϣ�޸ĳɹ���\n");
		}
		else if (choice == 2)
		{
			printf("�밴���¸�ʽ�����µĽ���ʱ�䣺\n");
			printf("���磺2022/12/31/20:00");
			while (1) {
				scanf("%s", flightArr[index].off_time);
				if (strlen(flightArr[index].off_time) != 16) printf("�������ʱ���ʽ�������������룺\n");
				if (flightArr[index].off_time[4] != '/' || flightArr[index].off_time[7] != '/' ||
					flightArr[index].off_time[10] != '/' || flightArr[index].off_time[13] != ':')
					printf("�������ʱ���ʽ�������������룺\n");
				else {
					time3 = computing_time(flightArr[index].off_time);
					int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
					if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
					if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
					printf("�������ʱ���ʽ�������������룺\n");
				}
			}
			if (time3 < time2) printf("�������ʱ������ڽ���ʱ�䣬������޸����ʱ��\n");
			printf("������Ϣ�޸ĳɹ���\n");
		}
		else if (choice == 3)
		{
			printf("�������µ�Ʊ�ۣ�\n");
			scanf("%lf", &flightArr[index].price);
			while (flightArr[index].price < 0 || flightArr[index].price>10000) {
				printf("Ʊ��������������������\n");
				scanf("%lf", &flightArr[index].price);
			}
			printf("������Ϣ�޸ĳɹ���\n");
		}
		else if (choice == 4)
		{
			printf("�������µ��ۿۣ�\n");
			scanf("%lf", &rediscount);//�����µ��ۿ� 
			while (rediscount < 0 || rediscount>100) {//�����ۿ۲������������ʾҪ���������� 
				printf("�ۿ�ֵ����ȷ�����������룺\n");
				scanf("%lf", &rediscount);
			}
			flightArr[index].discount = rediscount;
			printf("������Ϣ�޸ĳɹ���\n");
		}
		else {
			system("cls");
		    return;
		}
		Sleep(1000);
		system("cls");
	}
	return;
}
//��Ʊ
void checkOut() {
	system("cls");
	char ticket[10];
	char aim_flight[10];
	int idx_passenger;
	int idx_flight;
	int choice;
	//���Ƚ���Ȩ��ֵ�жϣ���Ϊ����Ա����������Ʊ�����֤�ź͹�Ʊ����� 
	if (userArr[user_index].level >= 1) {
		while (1)
		{
			system("cls");
			//�������֤ 
			char aim_id[20];
			printf("��������Ʊ�����֤��\n");
			scanf("%s", aim_id);
			while (strlen(aim_id) != 18) {
					printf("���֤��ʽ��������������\n");
					scanf("%s", aim_id);
				}
			//���뺽��� 
			printf("��������Ʊ����ţ�\n");
			scanf("%s", aim_flight);
			idx_passenger = search_passenger(aim_id, aim_flight);//��ѯ�˿���Ϣ 
			//�������ڣ��������� 
			if (idx_passenger != -1) break;
			else {
				printf("��ѯʧ�ܣ��Ƿ������ѯ��\n");
				printf("1.������ѯ\n2.�˳���ѯ\n");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}
	}
	else {//��Ϊ�˿ͣ�ֻ�����빺Ʊ����� 
		while (1)
		{
			system("cls");
			printf("��������Ʊ����ţ�\n");
			scanf("%s", aim_flight);
			idx_passenger = search_passenger(userArr[user_index].id, aim_flight);
			if (idx_passenger != -1) break;
			else {//��ѯʧ�ܣ�������ʾ���˳� 
				printf("��Ʊʧ�ܣ���δ����˺��࣡�Ƿ��������뺽��ţ�\n");
				printf("1.��������\n2.�˳�");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}

	}

	//��ѯ�ɹ���ɾ���˿͹�Ʊ��Ϣ����Ʊ��������ʾ 
	for (int i = idx_passenger; i < passengerArr[0].amount; i++) {
		passengerArr[i] = passengerArr[i + 1];
	}
	passengerArr[0].amount--;
	system("cls");
	printf("��Ʊ�ɹ���\n");
	return;
}
//����Աɾ���û� ���û�ע���˻� 
void delAcount()
{
	system("cls");
	int aim_index;
	int choice;
	char aim_account[15];
	char aim_password[20];
	/*ȷ���˺��±�*/
	if (userArr[user_index].level == 1) {
		while (1)
		{
			printf("�����뱻ע���˺ţ�\n");
			scanf("%s", aim_account);
			aim_index = search_account(aim_account);
			if (aim_index != -1) break;
			else {//�ж�Ȩ��ֵ����Ϊ����Ա�������������뱻ע���˺� 
				printf("�˺Ų����ڣ��Ƿ����������˺ţ�\n");
				printf("1.���������˺�\n2.�˳�ע��\n");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}
	}
	else	aim_index = user_index;

	printf("�Ƿ�ȷ��ע�����˻���\n");
	printf("1.ȷ��ע��\n2.�˳�ע��\n");
	choice = read(2);

	if (choice == 1) {//Ϊ��ȫ�Կ��ǣ�������������ȷ����� 

		while (1)
		{
			printf("�������˻�����ȷ����ݣ�\n");
			scanf("%s", aim_password);
			if (strcmp(aim_password, userArr[aim_index].password) == 0) break;
			else {
				printf("��������Ƿ��������룺\n");
				printf("1.��������\n2.�˳�ע��\n");
				choice = read(2);
				if (choice == 2)	exit(0);
			}
		}

		for (int i = aim_index; i < userArr[0].amount; i++) {//ע���ɹ���ϵͳɾ�����û���Ϣ��������ʾ 
			userArr[i] = userArr[i + 1];
		}
		userArr[0].amount--;
		system("cls");
		printf("ע���˻��ɹ���\n");
	}
	return;
}
void user_input()
{
	int num;
	printf("������Ҫ��ӵ��û�����\n");
	num = read(1000000);
	while (num--)
	{
	int usersnum = userArr[0].amount;
	
		printf("�����������˺�(��֤�˺ų�����8~14֮��)��\n");
		while (1) {
			scanf("%s", userArr[usersnum].account);
			int len = strlen(userArr[usersnum].account);
			if (8 <= len && len <= 14) break;
			else printf("��������˺ų��Ȳ�����Ҫ�����������룺\n");
		}
	
		printf("�������������룬ʹ���볤�Ȳ�����8λ��������14λ��\n");
		scanf("%s", userArr[usersnum].password);
		while (strlen(userArr[usersnum].password) > 14 || strlen(userArr[usersnum].password) < 8) {
			printf("��ʹ���볤�Ȳ�����8λ��������14λ,���������룺\n");
			scanf("%s", userArr[usersnum].password);
		}
		char temp_password[15];
		printf("���ٴ��������룺\n");
		while (1) {
			scanf("%s", temp_password);
			if (strcmp(temp_password, userArr[usersnum].password) == 0) break;
			else printf("��ǰ�������������벻ͬ��������������֮ǰ���������룺\n");
		}
	
		system("cls");
		printf("���������˺ŵĸ�����Ϣ\n");
	
		printf("��������������\n");
		scanf("%s", userArr[usersnum].name);
		while (strlen(userArr[usersnum].name) > 6) {
			printf("�뱣������������6λ���£�������������������\n");
			scanf("%s", userArr[usersnum].name);
		}
	
		printf("�������������֤��\n");
		scanf("%s", userArr[usersnum].id);
		while (strlen(userArr[usersnum].id) != 18) {
			printf("���֤��ʽ��������������\n");
			scanf("%s", userArr[usersnum].id);
		}
	
		printf("�����������ֻ�����\n");
		scanf("%s", userArr[usersnum].phoneNum);
		while (strlen(userArr[usersnum].phoneNum) != 11) {
			printf("�ֻ��Ÿ�ʽ��������������\n");
			scanf("%s", userArr[usersnum].phoneNum);
		}
		printf("�Ƿ������ԱȨ������������1������������0\n");
		scanf("%d", &userArr[usersnum].level);
	 	while (userArr[usersnum].level != 0&&userArr[usersnum].level != 1) {
	 		printf("Ȩ��ֵ��ʽ��������������\n");
	 		scanf("%s", userArr[usersnum].phoneNum);
	 		}
		system("cls");
		if(num!=0) printf("��ϲ����ӳɹ�,����������һ��\n");
		else printf("��ϲ����ӳɹ�\n");
		userArr[0].amount++;
	}
}
void inti()
{
	strcpy(userArr[0].account, "12345678");
	strcpy(userArr[0].id, "111111111111111111");
	userArr[0].level = 1;
	strcpy(userArr[0].name, "����");
	strcpy(userArr[0].password, "12345678");
	strcpy(userArr[0].phoneNum, "12345678");
	userArr[0].amount = 1;
	strcpy(userArr[1].account, "123456789");
	strcpy(userArr[1].id, "123456789");
	userArr[1].level = 0;
	strcpy(userArr[1].name, "����");
	strcpy(userArr[1].password, "12345678");
	strcpy(userArr[1].phoneNum, "123456789");
	userArr[0].amount = 2;
    flightArr[0].flightNum= "CN121212";
    strcpy(flightArr[0].up_time, "2022/12/12/14:12");
    strcpy(flightArr[0].off_time, "2022/12/14/12:12");
    strcpy(flightArr[0].up_pos, "����");
    strcpy(flightArr[0].off_pos, "����");
	flightArr[0].price=300;
	flightArr[0].discount=80;
	flightArr[0].num=1;
	flightArr[0].amount=2;
	flightArr[1].flightNum= "CN231212";
	strcpy(flightArr[1].up_time, "2022/12/14/14:12");
	strcpy(flightArr[1].off_time, "2022/12/15/12:12");
	strcpy(flightArr[1].up_pos, "����");
	strcpy(flightArr[1].off_pos, "����");
	flightArr[1].price=300;
	flightArr[1].discount=80;
	flightArr[1].num=0;
	
	strcpy(passengerArr[0].name, "����");
	strcpy(passengerArr[0].id, "111111111111111111");
	strcpy(passengerArr[0].flightNum, "CN121212");
	strcpy(passengerArr[0].phoneNum, "12345678");
	passengerArr[0].amount=1;
	strcpy(passengerArr[1].name, "��21");
	strcpy(passengerArr[1].id, "211111111111111111");
	strcpy(passengerArr[1].flightNum, "CN231212");
	strcpy(passengerArr[1].phoneNum, "12345678");
	passengerArr[0].amount=2;
}
int main()
{
	inti();
	int choice;
	/*����ѡ�� ��¼orע��  */
	printf("��ӭʹ�÷ɻ�����ϵͳ��");
	printf("��ѡ�����Ĳ�����\n");
	printf("1.ע��\n");
	printf("2.��¼\n");
	choice = read(2);
	if (choice == 1) sign();
	else user_index = logIn();
	lev = userArr[user_index].level;
	system("cls");
	int a=1;
	while(a){
		int choice = print();
	switch (choice)
	{
	case 1: checkIn(); break;
	case 2: checkOut(); break;
	case 3: search(); break;
	case 4: search_user(); break;
	case 5: search_tickets(); break;
	case 6: rewrite(); break;
	case 7: delAcount(); break;
	case 8: a=0; break;
	case 9: flight_input(); break;
	case 10: flight_change(); break;
	case 11: del_flight(); break;
	case 12: user_input(); break;
	}
	if(a==0){
		printf("��ӭ�����´�ʹ�ã��ټ���"); 
	}
	}
	//endi();
	return 0;
}
