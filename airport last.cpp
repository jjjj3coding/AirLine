#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#define MAX 168 //飞机荷载168人 
int lev;
int user_index;  //在用户信息里的下标 
int passenger_index; //在乘客信息里的下标 
int filght_index; 	//在航班信息里的下标 
char map[10][5] = { "","华北","西北","华南","西南","华东","东北","厦门","新疆" };
int year, month, day, hour, min, sum;
//创建航线结构体，定义数组line储存航线信息 
typedef struct user {
	int amount;
	char name[10];//用户姓名 
	char id[20];//用户身份证号 
	char account[15];//账号 
	char password[15];//密码 
	char phoneNum[12];//手机号 
	int level;//权限值 
}user;

typedef struct flight {
	int amount;
	char* flightNum;//航班号 
	char up_time[18];//起飞时间 
	char off_time[18];//降落时间 
	char up_pos[10];
	char off_pos[10];//起始地 
	double price;//票价 
	double discount;//折扣 
	int num;//航班上的人数 
}flight;

typedef struct passenger {
	int amount;
	char name[10]; //姓名 
	char id[20];//身份证 
	char flightNum[10];//航班号 
	char phoneNum[12];//手机号 
}passenger;

user userArr[500005];
flight flightArr[500005];
passenger passengerArr[500005];
/*功能：读入选择函数，用来判断格式是否正确*/
/*用法：当有1 ~ n个选择时， 把n传入，只有输入1<=x<=n 且为正整数时，才返回选择*/
int read(int r)
{
	int choice;
	while (1) {
		fflush(stdin);
		double data;
		scanf("%lf", &data);
		if (data > r || data < 1 || data != (int)data) printf("输入不合规范，请重新输入：\n");
		else {
			choice = (int)data;
			return choice;
		}
	}
}
/*功能：读入航班号函数，用来判读格式是否正确*/
char* read_flight()
{
	static char number[10];
	bool judge = false;
	while (1) {
		scanf("%s", number);
		if (strlen(number) != 8)  printf("您输入的航班号1格式有误，请重新输入：\n");
		else if (number[0] != 'C' || number[1] != 'N') printf("您输入的航班号2格式有误，请重新输入：\n");
		else if (number[2] < '1' || number[2]>'9' || number[3] < '1' || number[3]>'9') printf("您输入的航班号3格式有误，请重新输入：\n");
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
			else printf("您输入的航班号格式有误，请重新输入：\n");
		}
	}
}
//注册函数 
void sign()
{
	int usersnum = userArr[0].amount;

	printf("请输入您的账号(保证账号长度在8~14之间)：\n");
	while (1) {
		scanf("%s", userArr[usersnum].account);
		int len = strlen(userArr[usersnum].account);
		if (8 <= len && len <= 14) break;
		else printf("您输入的账号长度不符合要求，请重新输入：\n");
	}

	printf("请设置您的密码，使密码长度不低于8位，不超过14位：\n");
	scanf("%s", userArr[usersnum].password);
	while (strlen(userArr[usersnum].password) > 14 || strlen(userArr[usersnum].password) < 8) {
		printf("请使密码长度不低于8位，不超过14位,请重新输入：\n");
		scanf("%s", userArr[usersnum].password);
	}
	char temp_password[15];
	printf("请再次输入密码：\n");
	while (1) {
		scanf("%s", temp_password);
		if (strcmp(temp_password, userArr[usersnum].password) == 0) break;
		else printf("您前后两次设置密码不同，请重新输入您之前所设置密码：\n");
	}

	system("cls");
	printf("请完善您账号的个人信息\n");

	printf("请输入您的姓名\n");
	scanf("%s", userArr[usersnum].name);
	while (strlen(userArr[usersnum].name) > 6) {
		printf("请保持姓名长度在6位以下，请重新输入您的名字\n");
		scanf("%s", userArr[usersnum].name);
	}

	printf("请输入您的身份证号\n");
	scanf("%s", userArr[usersnum].id);
	while (strlen(userArr[usersnum].id) != 18) {
		printf("身份证格式错误，请重新输入\n");
		scanf("%s", userArr[usersnum].id);
	}

	printf("请输入您的手机号码\n");
	scanf("%s", userArr[usersnum].phoneNum);
	while (strlen(userArr[usersnum].phoneNum) != 11) {
		printf("手机号格式错误，请重新输入\n");
		scanf("%s", userArr[usersnum].phoneNum);
	}

	system("cls");
	printf("恭喜您注册成功\n");
	printf("这是您的账号与密码\n");
	printf("账号：%s\n 密码：%s\n", userArr[usersnum].account, userArr[usersnum].password);
	printf("请牢记您的账号和密码，感谢您的配合再见！\n");
	userArr[0].amount++;
	/*对新添加的信息 根据用户账号进行从小到大 插入排序*/
	user new_user = userArr[usersnum];
	int index = usersnum - 1;
	while (index >= 0 && strcmp(userArr[index].account, new_user.account) > 0) index--;
	index++;
	for (int i = index; i < usersnum; i++) userArr[i + 1] = userArr[i];
	userArr[index] = new_user;
}
//二分查找乘客信息中第一个符合的下标，若没有返回-1
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
//根据地点，遍历查询符合航班 
int search_area(int start, int end)
{
	printf("由%s飞往%s的航班：\n", map[start], map[end]);
	int num = 0;
	for (int i = 0; i < flightArr[0].amount; i++) {
		if (flightArr[i].flightNum[2] == start + '0'
			&& flightArr[i].flightNum[3] == end + '0')
			printf("%s\n", flightArr[i].flightNum), num++;
	}
	if (num == 0) {
		printf("抱歉，从%s飞往%s,暂无其他航班\n", map[start], map[end]);
		return 0;
	}
	return 1;
}
//二分查找乘客信息中第一个符合的下标，若没有返回-1 
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
//利用二分，根据账号，返回在文件中的下标 
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
//登录函数 
int logIn()
{
	/*输入账号*/
	printf("请输入您的账号：\n");
	char temp_account[15];
	char temp_password[20];
	int index;
	bool judge = false;
	while (!judge) {
		scanf("%s", temp_account);
		index = search_account(temp_account);
		if (index == -1) printf("您的账号不存在，请重新输入：\n");
		else judge = true;
	}

	/*输入密码*/
	printf("请输入您的密码:\n");
	judge = false;
	while (!judge) {
		scanf("%s", temp_password);
		if (strcmp(userArr[index].password, temp_password) != 0) printf("您的密码不正确，请重新输入(若您忘记密码请联系客服)：\n");
		else {
			printf("登录成功!欢迎您：%s\n", userArr[index].name);
			judge = true;
		}
	}
	return index;
}
//菜单函数 
int print()
{
	int choice1;
	/*进入菜单页面*/
	printf("-----------------------------\n");
	printf("   计信学院航空公司欢迎您！\n");
	printf("1.订票服务\n");
	printf("2.退票服务\n");
	printf("3.查询航班信息\n");
	printf("4.查询账号信息\n");
	printf("5.查询订票信息\n");
	printf("6.修改账号信息\n");
	printf("7.注销账号\n");
	printf("8.退出\n");
	if (lev) {
		printf("9.录入航班信息\n");
		printf("10.修改航班信息\n");
		printf("11.删除航班\n");
		printf("12.添加用户\n");
	}
	printf("-----------------------------\n");

	/*返回用户选择服务*/
	printf("请输入您选择的服务:\n");
	if (lev) choice1 = read(12);
	else choice1 = read(8);
	return choice1;
}
//单纯订票操作
void checkin()
{
	/*判断 购票方式*/
	printf("请您选择如下购票方式：\n");
	printf("1.根据航班号购票\n2.根据起始地购票\n");
	int choice = read(2);
	int search;
	/*输出相应航班*/
	if (choice == 2) {
		printf("我司支持以下8个地方飞行：\n");
		printf("1.华北\n2.西北\n3.华南\n4.西南\n5.华东\n6.东北\n7.厦门\n8.新疆\n");
		printf("请输入你的出发地、目的地的序号：\n");
		int start = read(8);
		int end;
		bool judge = false;
		while (!judge) {
			end = read(8);
			if (end == start) printf("您输入的目的地与出发地相同，请重新输入：\n");
			else judge = true;
		}
		search=search_area(start, end);
	}
	if(search==1||choice==1){
		char* temp_flightNum;
		/* 得到 订票航班号*/
		printf("请输入您选择的航班:");
temp_flightNum=read_flight() ;
	
		int index = search_flight(temp_flightNum);//承接下标 
		while (flightArr[index].num == MAX) {
			printf("抱歉本航班%s已满，向您推荐同样起始地航班\n", temp_flightNum);
			int flag = search_area(temp_flightNum[2] - '0', temp_flightNum[3] - '0');
			if (flag) {
				printf("若您重新选择订票航班号，请按1\n 若无需购票，请按2退出");
				int temp_choice = read(2);
				if (temp_choice == 2) exit(0);
				else {
					printf("请输入您选择的航班:\n");
					temp_flightNum=read_flight() ;
					index = search_flight(temp_flightNum);
				}
			}
		}
		int passnum = passengerArr[0].amount;
		/*订票，更新函数信息*/
		strcpy(passengerArr[passnum].flightNum, temp_flightNum);
		system("cls");
		printf("恭喜您，订票成功!\n");
		passengerArr[0].amount++;
		flightArr[index].num++;
		/*对新增订单根据身份证，进行插入排序*/
		passenger temp_passenger = passengerArr[passnum];
		index = passnum - 1;
		while (index >= 0 && strcmp(passengerArr[index].id, temp_passenger.id) > 0) index--;
		index++;
		for(int i = index; i < passnum; i++) passengerArr[i + 1] = passengerArr[i];
		passengerArr[index] = temp_passenger;
	}
	return;
}

//自己订票 
void checkIn_my()
{
	/*初始化*/
	int passnum = passengerArr[0].amount;
	char temp_flightNum[10];
	strcpy(passengerArr[passnum].name, userArr[user_index].name);
	strcpy(passengerArr[passnum].id, userArr[user_index].id);
	strcpy(passengerArr[passnum].phoneNum, userArr[user_index].phoneNum);
	checkin();
}
// 他人订票 
void checkIn_other()
{
	int usersnum = userArr[0].amount;
	printf("请输入您的购票数(一次性购票数不得超过10张)：\n");
	int num = read(10);
	while (num--) {
		printf("请输入乘客的姓名\n");
		scanf("%s", userArr[usersnum].name);
		while (strlen(userArr[usersnum].name) > 6) {
			printf("请保持姓名长度在6位以下，请重新输入您的名字\n");
			scanf("%s", userArr[usersnum].name);
		}

		printf("请输入乘客的身份证号\n");
		scanf("%s", userArr[usersnum].id);
		while (strlen(userArr[usersnum].id) != 18) {
			printf("身份证格式错误，请重新输入\n");
			scanf("%s", userArr[usersnum].id);
		}

		printf("请输入乘客的手机号码\n");
		scanf("%s", userArr[usersnum].phoneNum);
		while (strlen(userArr[usersnum].phoneNum) != 11) {
			printf("手机号格式错误，请重新输入\n");
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
	printf("欢迎使用本公司购票系统！\n");
	if (userArr[user_index].level == 0) {
		printf("请选择您的购票对象：");
		printf("1.为自己购票\n2.为他人购票\n");
		int choice = read(2);
		if (choice == 1)	checkIn_my();
		else checkIn_other();
	}
	else	checkIn_other();
}

//输出航班信息 
void search()
{
	/*选择查询方式*/
	system("cls");
	printf("-----------------------------\n");
	printf("您已选择查询航班服务：\n");
	printf("请输入查询方式 (请输入 1 或 2)：\n");
	printf("1.根据航班号查询\n");
	printf("2.根据起飞，降落城市查询\n");
	int way = read(2);

	if (way == 1) {
	
		/*查找输入的航班号*/
		system("cls");
		printf("   请输入查询航班号：\n");
		char* number;
		number = read_flight();
		int index = search_flight(number);

		/*输出航班号信息*/
		if (index != -1) {
			printf("航班%s的航班信息：\n", flightArr[index].flightNum);
			printf("起飞时间：%s\n", flightArr[index].up_time);
			printf("降落时间：%s\n", flightArr[index].off_time);
			printf("起飞地点：%s\n", flightArr[index].up_pos);
			printf("降落地点：%s\n", flightArr[index].off_pos);
			printf("航班票价：￥%.2lf\n", flightArr[index].price);
			printf("票价折扣：%.lf%%\n", flightArr[index].discount);
			printf("航班上人数：%d\n", flightArr[index].num);
			if (flightArr[index].num == MAX)	printf("注：已满仓\n");
			else {
				printf("您是否需要订本次航班的票：\n");
				printf("1.需要\n");
				printf("2,返回主界面\n");
				int choice = read(2);
				if (choice == 1)  checkin();
				else {
					system("cls");
					return; 
				}
			}
		}
		else printf("您所查询的航班号不存在。\n");
	}
	else {
		system("cls");
		printf("我司支持以下8个地方飞行：\n");
		printf("1.华北\n2.西北\n3.华南\n4.西南\n5.华东\n6.东北\n7.厦门\n8.新疆\n");
		printf("请输入你的出发地、目的地的序号：\n");

		/*输入起始地，目的地*/
		int start = read(8);
		int end;
		bool judge = false;
		while (!judge) {
			end = read(8);
			if (end == start) printf("您输入的目的地与出发地相同，请重新输入：\n");
			else judge = true;
		}
		search_area(start, end);
	}
}
//输出用户信息 
void search_user()
{
	//若是用户，则无需输入账号 
	//若是管理员，输入查询账号 
	system("cls");
	if (lev == 1) {
		printf("请输入您所要查询用户账号：\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			user_index = search_account(temp_account);
			if (user_index == -1) {
				printf("账户错误，是否继续查询？\n");
				printf("1.继续查询\n2.退出查询\n");
				int choice = read(2);
				if (choice == 2) exit(0);
			}
			else judge = true;
		}
	}
	printf("用户个人信息如下：\n");
	printf("用户姓名：%s\n", userArr[user_index].name);
	printf("用户身份证：%s\n", userArr[user_index].id);
	printf("用户账号：%s\n", userArr[user_index].id);
	printf("用户密码：%s\n", userArr[user_index].password);
	printf("用户手机号码：%s\n", userArr[user_index].phoneNum);
		printf("输入1返回主界面\n");
					int a = read(2);
					while (a != 1) {
						printf("输入错误请重新输入\n");
						a = read(2);
				}
				system("cls");
}
				
//输出订票信息 
void search_tickets()
{
	int index;
	//若是用户，则无需输入账号 
	//若是管理员，输入查询账号 
	system("cls");
	if (lev != 0) {
		printf("请输入您所要查询用户账号：\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			user_index = search_account(temp_account);
			if (user_index == -1) printf("您的账号不存在，请重新输入：\n");
			else judge = true;
		}
	}
	passenger_index = search_passenger(userArr[user_index].id, NULL);
	if (passenger_index == -1) printf("用户没有订票\n");
	else {
		int i = passenger_index;
		printf("用户订票信息如下：\n");
		while (strcmp(passengerArr[passenger_index].id, passengerArr[i].id) == 0) {
			printf("%s\n", passengerArr[i].flightNum);
			i++;
		}
	}
}
//将字符数字转为int型整数 
int time_change(char* time, int l, int r)
{
	int ans = 0;
	for (int i = l; i <= r; i++) {
		ans = ans * 10 + (time[i] - '0');
	}
	return ans;
}
//计算时间合理性 
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
//添加航班 
void flight_input()
{
	system("cls");
	int flinum = flightArr[0].amount;

	/*输入航班号*/
	printf("请输入航班号\n");
	flightArr[flinum].flightNum = read_flight();

	/*输入起飞时间*/
	printf("请输入起飞时间 \n");
	double time1;
	while (1) {
		scanf("%s", flightArr[flinum].up_time);
		if (strlen(flightArr[flinum].up_time) != 16) printf("您输入的时间格式有误，请重新输入：\n");
		else if (flightArr[flinum].up_time[4] != '/' || flightArr[flinum].up_time[7] != '/' ||
			flightArr[flinum].up_time[10] != '/' || flightArr[flinum].up_time[13] != ':')
			printf("您输入的时间格式有误，请重新输入：\n");
		else {
			time1 = computing_time(flightArr[flinum].up_time);
			int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
			if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
			if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
			else printf("您输入的时间格式有误，请重新输入：\n");
		}
	}
	//输入降落时间 
	printf("请输入降落时间\n");
	double time2;
	while (1)
	{
		scanf("%s", flightArr[flinum].off_time);
		if (strlen(flightArr[flinum].off_time) != 16) printf("您输入的时间格式有误，请重新输入：\n");
		else if (flightArr[flinum].off_time[4] != '/' || flightArr[flinum].off_time[7] != '/' ||
			flightArr[flinum].off_time[10] != '/' || flightArr[flinum].off_time[13] != ':')
			printf("您输入的时间格式有误，请重新输入：\n");
		else {
		time2 = computing_time(flightArr[flinum].off_time);
		int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
		if (day <= days[month] && 0 <= sum && sum <= 24 * 60 && time2 > time1) break;
		else printf("您输入的时间格式有误，请重新输入：\n");
		}
	}

	/*补充起始地*/
	strcpy(flightArr[flinum].up_pos, map[flightArr[flinum].flightNum[2] - '0']);
	strcpy(flightArr[flinum].off_pos, map[flightArr[flinum].flightNum[3] - '0']);
	
	flightArr[flinum].price = -1;
	printf("请输入票价\n");
	while (1) {
		fflush(stdin);
		scanf("%lf", &flightArr[flinum].price);
		if (flightArr[flinum].price > 10000 || flightArr[flinum].price < 0) printf("输入不合规范，请重新输入：\n");
		else  break;
	}

	flightArr[flinum].discount = -1;
	printf("请输入折扣\n");
	while (1) {
		fflush(stdin);
		scanf("%lf", &flightArr[flinum].discount);
		if (flightArr[flinum].discount > 100 || flightArr[flinum].discount < 0) printf("输入不合规范，请重新输入：\n");
		else  break;
	}

	flightArr[flinum].num = 0;
	flightArr[0].amount++;
	/*排序*/
	flight temp_flight = flightArr[flinum];
	int index = flinum - 1;
	while (index >= 0 && strcmp(flightArr[index].flightNum, temp_flight.flightNum) > 0) index--;
	index++;
	for (int i = index; i < flinum; i++) flightArr[i + 1] = flightArr[i];
	flightArr[index] = temp_flight;
	system("cls");
	printf("添加成功！\n");
}
//修改用户
void rewrite()
{
	system("cls");
	int choice;
	int temp_index;
	char oldPasword[20];
	char newPaswordf[20];
	char newPaswords[20];
	char newPhoneNum[12];
	//判断权限值，若为管理员则需输入用户账号 
	if (userArr[user_index].level == 1) {
		printf("请输入您所要查询用户账号：\n");
		char temp_account[15];
		bool judge = false;
		while (!judge) {
			scanf("%s", temp_account);
			temp_index = search_account(temp_account);
			if (temp_index == -1) {
				printf("账户错误，是否继续查询？\n");
				printf("1.继续查询\n2.退出查询\n");
				int choice = read(2);
				if (choice == 2) exit(0);
			}
			else judge = true;
		}
	}

	//选择需要修改的信息（因为账号和身份证、姓名是绑定的，所以身份证和姓名不可修改） 
	printf("请选择您要修改的信息：\n");
	printf("1.密码\n");
	printf("2.手机号\n");
	if (userArr[user_index].level == 2) {
		printf("3.设置管理员\n");
		choice = read(3);
	}
	else choice = read(2);

	//若选择修改密码，则需要先输入旧密码，再将新密码输入两次 
	if (choice == 1) {
		printf("请输入原密码：\n");
		scanf("%s", oldPasword);
		while (strcmp(oldPasword, userArr[temp_index].password) != 0) {
			printf("原密码错误！是否继续修改：\n");//原密码错误可选择继续修改或退出 
			printf("1.继续修改\n2.退出修改\n");
			choice = read(2);
			if (choice == 1) {
				printf("请输入原密码：\n");
				scanf("%s", oldPasword);
			}
			else	exit(0);
		}

		//两次输入的新密码必须相同才能修改成功 
		printf("请输入新密码：\n");
		scanf("%s", newPaswordf);
		printf("请再次输入新密码：\n");
		scanf("%s", newPaswords);
		while (strcmp(newPaswordf, newPaswords) != 0) {
			printf("两次输入不一致，请再次输入新密码：\n");
			scanf("%s", newPaswords);
		}
		strcpy(userArr[temp_index].password, newPaswords);
	}
	//若选择修改手机号，则检查手机号长度是否合规，若合规则修改成功，否则继续输入 
	else if (choice == 2) {
		printf("请输入新的手机号：\n");
		scanf("%s", newPhoneNum);
		while (strlen(newPhoneNum) != 11) {
			printf("您输入的新手机号错误，是否继续修改：\n");//手机号不合规，用户可选择继续输入或退出 
			printf("1.继续修改\n2.退出修改\n");
			choice = read(2);
			if (choice == 1) {
				printf("请输入新手机号：\n");
				scanf("%s", newPhoneNum);
			}
			else	exit(0);
		}
		strcpy(userArr[temp_index].phoneNum, newPhoneNum);//手机号修改成功 
	}

	else {
		printf("请选择您的操作：\n");
		printf("1.设置为管理员\n2.取消管理员\n");
		choice = read(2);
		if (choice == 1)  userArr[temp_index].level = 1;
		else  userArr[temp_index].level = 0;
	}
	system("cls");
	printf("用户信息修改成功！\n");
	return;
}
//删除航班函数 
void del_flight()
{
	system("cls");
	int index;
	char* aim_flightNum ;
	printf("请输入待删除航班号：\n");
	aim_flightNum = read_flight();
	index = search_flight(aim_flightNum);
	while (index == -1) {
		printf("未查询得此航班，请重新输入航班号：\n");
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
	printf("删除航班成功！\n");
	return;
}
//修改航班
void flight_change()
{
	system("cls");
	int index;
	int choice;

	char reup_time[18];//起飞时间 
	char reoff_time[18];//降落时间 
	double reprice;//票价 
	double rediscount;//折扣 

	/*读入航班号*/
	char* aim_flightNum;
	printf("请输入航班号：\n");
	aim_flightNum = read_flight();
	index = search_flight(aim_flightNum);
	while (index == -1) {
		printf("航班号不存在，请重新输入：\n");
		aim_flightNum = read_flight();
		index = search_flight(aim_flightNum);
	}
	double time1, time2, time3;

	/*选择服务*/
	while (1)
	{
		system("cls");
		printf("请在以下操作进行选择：\n");
		printf("1.航班起飞时间\n2.航班降落时间\n");
		printf("3.航班票价\n4.航班折扣\n");
		printf("5.退出\n");
		choice = read(5);

		/*计算老的起飞时间*/
		time1 = computing_time(flightArr[index].up_time);
		/*计算老的降落时间*/
		time2 = computing_time(flightArr[index].off_time);

		if (choice == 1)
		{
			printf("请按如下格式输入新的起飞时间：\n");
			printf("例如：2022/12/31/20:00");
			while (1) {
				scanf("%s", flightArr[index].up_time);
				if (strlen(flightArr[index].up_time) != 16) printf("您输入的时间格式有误，请重新输入：\n");
				if (flightArr[index].up_time[4] != '/' || flightArr[index].up_time[7] != '/' ||
					flightArr[index].up_time[10] != '/' || flightArr[index].up_time[13] != ':')
					printf("您输入的时间格式有误，请重新输入：\n");
				else {
					time3 = computing_time(flightArr[index].up_time);
					int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
					if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
					if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
					printf("您输入的时间格式有误，请重新输入：\n");
				}
			}
			if (time3 < time2) printf("您的起飞时间落后于降落时间，请继续修改降落时间\n");
			printf("航班信息修改成功！\n");
		}
		else if (choice == 2)
		{
			printf("请按如下格式输入新的降落时间：\n");
			printf("例如：2022/12/31/20:00");
			while (1) {
				scanf("%s", flightArr[index].off_time);
				if (strlen(flightArr[index].off_time) != 16) printf("您输入的时间格式有误，请重新输入：\n");
				if (flightArr[index].off_time[4] != '/' || flightArr[index].off_time[7] != '/' ||
					flightArr[index].off_time[10] != '/' || flightArr[index].off_time[13] != ':')
					printf("您输入的时间格式有误，请重新输入：\n");
				else {
					time3 = computing_time(flightArr[index].off_time);
					int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
					if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) days[2] = 29;
					if (day <= days[month] && 0 <= sum && sum <= 24 * 60) break;
					printf("您输入的时间格式有误，请重新输入：\n");
				}
			}
			if (time3 < time2) printf("您的起飞时间落后于降落时间，请继续修改起飞时间\n");
			printf("航班信息修改成功！\n");
		}
		else if (choice == 3)
		{
			printf("请输入新的票价：\n");
			scanf("%lf", &flightArr[index].price);
			while (flightArr[index].price < 0 || flightArr[index].price>10000) {
				printf("票价输入有误，请重新输入\n");
				scanf("%lf", &flightArr[index].price);
			}
			printf("航班信息修改成功！\n");
		}
		else if (choice == 4)
		{
			printf("请输入新的折扣：\n");
			scanf("%lf", &rediscount);//输入新的折扣 
			while (rediscount < 0 || rediscount>100) {//若新折扣不合理，则给出提示要求重新输入 
				printf("折扣值不正确，请重新输入：\n");
				scanf("%lf", &rediscount);
			}
			flightArr[index].discount = rediscount;
			printf("航班信息修改成功！\n");
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
//退票
void checkOut() {
	system("cls");
	char ticket[10];
	char aim_flight[10];
	int idx_passenger;
	int idx_flight;
	int choice;
	//首先进行权限值判断，若为管理员，需输入退票人身份证号和购票航班号 
	if (userArr[user_index].level >= 1) {
		while (1)
		{
			system("cls");
			//输入身份证 
			char aim_id[20];
			printf("请输入退票人身份证：\n");
			scanf("%s", aim_id);
			while (strlen(aim_id) != 18) {
					printf("身份证格式错误，请重新输入\n");
					scanf("%s", aim_id);
				}
			//输入航班号 
			printf("请输入退票航班号：\n");
			scanf("%s", aim_flight);
			idx_passenger = search_passenger(aim_id, aim_flight);//查询乘客信息 
			//若不存在，重新输入 
			if (idx_passenger != -1) break;
			else {
				printf("查询失败，是否继续查询：\n");
				printf("1.继续查询\n2.退出查询\n");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}
	}
	else {//若为乘客，只需输入购票航班号 
		while (1)
		{
			system("cls");
			printf("请输入退票航班号：\n");
			scanf("%s", aim_flight);
			idx_passenger = search_passenger(userArr[user_index].id, aim_flight);
			if (idx_passenger != -1) break;
			else {//查询失败，给出提示并退出 
				printf("退票失败，您未购买此航班！是否重新输入航班号：\n");
				printf("1.重新输入\n2.退出");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}

	}

	//查询成功，删除乘客购票信息，退票并给出提示 
	for (int i = idx_passenger; i < passengerArr[0].amount; i++) {
		passengerArr[i] = passengerArr[i + 1];
	}
	passengerArr[0].amount--;
	system("cls");
	printf("退票成功！\n");
	return;
}
//管理员删除用户 、用户注销账户 
void delAcount()
{
	system("cls");
	int aim_index;
	int choice;
	char aim_account[15];
	char aim_password[20];
	/*确定账号下标*/
	if (userArr[user_index].level == 1) {
		while (1)
		{
			printf("请输入被注销账号：\n");
			scanf("%s", aim_account);
			aim_index = search_account(aim_account);
			if (aim_index != -1) break;
			else {//判断权限值，若为管理员操作，则需输入被注销账号 
				printf("账号不存在，是否重新输入账号：\n");
				printf("1.重新输入账号\n2.退出注销\n");
				choice = read(2);
				if (choice == 2) exit(0);
			}
		}
	}
	else	aim_index = user_index;

	printf("是否确认注销此账户？\n");
	printf("1.确认注销\n2.退出注销\n");
	choice = read(2);

	if (choice == 1) {//为安全性考虑，还需输入密码确认身份 

		while (1)
		{
			printf("请输入账户密码确认身份：\n");
			scanf("%s", aim_password);
			if (strcmp(aim_password, userArr[aim_index].password) == 0) break;
			else {
				printf("密码错误，是否重新输入：\n");
				printf("1.重新输入\n2.退出注销\n");
				choice = read(2);
				if (choice == 2)	exit(0);
			}
		}

		for (int i = aim_index; i < userArr[0].amount; i++) {//注销成功，系统删除该用户信息并给出提示 
			userArr[i] = userArr[i + 1];
		}
		userArr[0].amount--;
		system("cls");
		printf("注销账户成功！\n");
	}
	return;
}
void user_input()
{
	int num;
	printf("输入您要添加的用户数：\n");
	num = read(1000000);
	while (num--)
	{
	int usersnum = userArr[0].amount;
	
		printf("请输入您的账号(保证账号长度在8~14之间)：\n");
		while (1) {
			scanf("%s", userArr[usersnum].account);
			int len = strlen(userArr[usersnum].account);
			if (8 <= len && len <= 14) break;
			else printf("您输入的账号长度不符合要求，请重新输入：\n");
		}
	
		printf("请设置您的密码，使密码长度不低于8位，不超过14位：\n");
		scanf("%s", userArr[usersnum].password);
		while (strlen(userArr[usersnum].password) > 14 || strlen(userArr[usersnum].password) < 8) {
			printf("请使密码长度不低于8位，不超过14位,请重新输入：\n");
			scanf("%s", userArr[usersnum].password);
		}
		char temp_password[15];
		printf("请再次输入密码：\n");
		while (1) {
			scanf("%s", temp_password);
			if (strcmp(temp_password, userArr[usersnum].password) == 0) break;
			else printf("您前后两次设置密码不同，请重新输入您之前所设置密码：\n");
		}
	
		system("cls");
		printf("请完善您账号的个人信息\n");
	
		printf("请输入您的姓名\n");
		scanf("%s", userArr[usersnum].name);
		while (strlen(userArr[usersnum].name) > 6) {
			printf("请保持姓名长度在6位以下，请重新输入您的名字\n");
			scanf("%s", userArr[usersnum].name);
		}
	
		printf("请输入您的身份证号\n");
		scanf("%s", userArr[usersnum].id);
		while (strlen(userArr[usersnum].id) != 18) {
			printf("身份证格式错误，请重新输入\n");
			scanf("%s", userArr[usersnum].id);
		}
	
		printf("请输入您的手机号码\n");
		scanf("%s", userArr[usersnum].phoneNum);
		while (strlen(userArr[usersnum].phoneNum) != 11) {
			printf("手机号格式错误，请重新输入\n");
			scanf("%s", userArr[usersnum].phoneNum);
		}
		printf("是否赋予管理员权利？是请输入1，不是请输入0\n");
		scanf("%d", &userArr[usersnum].level);
	 	while (userArr[usersnum].level != 0&&userArr[usersnum].level != 1) {
	 		printf("权限值格式错误，请重新输入\n");
	 		scanf("%s", userArr[usersnum].phoneNum);
	 		}
		system("cls");
		if(num!=0) printf("恭喜您添加成功,请继续添加下一个\n");
		else printf("恭喜您添加成功\n");
		userArr[0].amount++;
	}
}
void inti()
{
	strcpy(userArr[0].account, "12345678");
	strcpy(userArr[0].id, "111111111111111111");
	userArr[0].level = 1;
	strcpy(userArr[0].name, "张三");
	strcpy(userArr[0].password, "12345678");
	strcpy(userArr[0].phoneNum, "12345678");
	userArr[0].amount = 1;
	strcpy(userArr[1].account, "123456789");
	strcpy(userArr[1].id, "123456789");
	userArr[1].level = 0;
	strcpy(userArr[1].name, "张四");
	strcpy(userArr[1].password, "12345678");
	strcpy(userArr[1].phoneNum, "123456789");
	userArr[0].amount = 2;
    flightArr[0].flightNum= "CN121212";
    strcpy(flightArr[0].up_time, "2022/12/12/14:12");
    strcpy(flightArr[0].off_time, "2022/12/14/12:12");
    strcpy(flightArr[0].up_pos, "华北");
    strcpy(flightArr[0].off_pos, "西北");
	flightArr[0].price=300;
	flightArr[0].discount=80;
	flightArr[0].num=1;
	flightArr[0].amount=2;
	flightArr[1].flightNum= "CN231212";
	strcpy(flightArr[1].up_time, "2022/12/14/14:12");
	strcpy(flightArr[1].off_time, "2022/12/15/12:12");
	strcpy(flightArr[1].up_pos, "西北");
	strcpy(flightArr[1].off_pos, "华南");
	flightArr[1].price=300;
	flightArr[1].discount=80;
	flightArr[1].num=0;
	
	strcpy(passengerArr[0].name, "张三");
	strcpy(passengerArr[0].id, "111111111111111111");
	strcpy(passengerArr[0].flightNum, "CN121212");
	strcpy(passengerArr[0].phoneNum, "12345678");
	passengerArr[0].amount=1;
	strcpy(passengerArr[1].name, "张21");
	strcpy(passengerArr[1].id, "211111111111111111");
	strcpy(passengerArr[1].flightNum, "CN231212");
	strcpy(passengerArr[1].phoneNum, "12345678");
	passengerArr[0].amount=2;
}
int main()
{
	inti();
	int choice;
	/*开局选择 登录or注册  */
	printf("欢迎使用飞机航班系统！");
	printf("请选择您的操作：\n");
	printf("1.注册\n");
	printf("2.登录\n");
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
		printf("欢迎您的下次使用，再见！"); 
	}
	}
	//endi();
	return 0;
}
