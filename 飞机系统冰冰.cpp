#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <time.h>
using namespace std;
#define MAX 168
int lev;
//飞机荷载168人 
int limit;//权限 
/*	
	员工：
		录入
		修改航班信息 
		用户 ：
			查询
			订票
			退票 
*/
int choice;//选择服务 
//创建航线结构体，定义数组line储存航线信息 
typedef struct user{
	int amount;
	char name[10];//用户姓名 
	char id[20];//用户身份证号 
	char account[15];//账号 
	char password[20];//密码 
	char phoneNum[12];//手机号 
	int level;//权限值 
}user;

typedef struct flight{
	int amount;
	char flightNum[10];//航班号 
	char up_time[15];//起飞时间 
	char off_time[15];//降落时间 
	char up_pos[10];
	char off_pos[10];//起始地 
	double price;//票价 
	double dicount;//折扣 
	int num;//航班上的人数 
}flight;

typedef struct passenger{
	int amount;
	char name[10]; //姓名 
	char id[20];//身份证 
	char flightNum[10];//航班号 
	char phoneNum[12];//手机号 
}passenger;

user userArr[500005];
flight flightArr[500005];
passenger passengerArr[500005];


void print()
{
	/*
	printf("请输入您的账号：\n");
	char username[11];
	scanf("%s",username);
	printf("请输入您的密码:\n");
	char secret[20];
	*/

	printf("-----------------------------\n");
	printf("   计信学院航空公司欢迎您！\n");
	printf("1.查询航班\n");
	printf("2.订票服务\n");
	printf("3.退订服务\n"); 
	if(lev == 1){
		printf("4.录入航班信息\n");
		printf("5.修改航班信息\n"); 
	} 
	printf("-----------------------------\n");
	printf("请输入您选择的服务\n");
	
	bool judge = false;
	while(!judge){
		fflush(stdin);
		double data;
		scanf("%lf",&data);
		if(data>5 || data<1|| data!=(int)data) printf("输入错误，请重新输入：\n");
		else if(limit==0&&4<=data&&data<=5) printf("输入错误，请重新输入：\n");
		else {
			judge = true;
			choice = (int)data;
		}
	} 
	
}

void sign()//注册 
{	
int usersnum=userArr[0].amount;
	int a=0,index;
		printf("请输入身份证号\n"); 
		scanf("%s",userArr[usersnum].id);
			while(strlen(userArr[usersnum].id)!=18){
				printf("身份证格式错误请重新输入\n");
					scanf("%s",userArr[usersnum].id);
	} 
		//index=search用户(userArr[usersnum].id);
				//	if(index){
				//		printf("该身份证已有账户，可直接登录\n");
					//a=1;
				//	}
				if(a==0){
		printf("请输入姓名\n"); 
		scanf("%s",userArr[usersnum].name);
		while(strlen(userArr[usersnum].name)>6){
			printf("姓名格式错误请重新输入\n");
				scanf("%s",userArr[usersnum].name);
	} 
		
	
		printf("请输入手机号码\n"); 
		scanf("%s",userArr[usersnum].phoneNum);
			while(strlen(userArr[usersnum].phoneNum)!=11){
				printf("手机号格式错误请重新输入\n");
					scanf("%s",userArr[usersnum].phoneNum);
	} 
		printf("请输入密码\n"); 
		scanf("%s",userArr[usersnum].password);
			while(strlen(userArr[usersnum].password)>14||strlen(userArr[usersnum].password)<8){
				printf("密码格式错误请重新输入\n");
					scanf("%s",userArr[usersnum].password);
	}			
		string str;                 /*声明用来保存随机字符串的str*/
		    char c;                     /*声明字符c，用来保存随机生成的字符*/
		    int idx;                    /*用来循环的变量*/
		    srand((unsigned)time(NULL));
		    /*循环向字符串中添加随机生成的字符*/
		    for(idx = 0;idx <12;idx ++)
		    {
		        
		        c = '0' + rand()%10;
		        str.push_back(c);       /*push_back()是string类尾插函数。这里插入随机字符c*/
		    }
	 ;
	str.copy(userArr[usersnum].account, 12, 0);//这里5代表复制几个字符，0代表复制的位置，
	*(userArr[usersnum].account+12)='\0';//注意手动加结束符！！！
		system("cls");
		printf("这是您的账号与密码\n");
		printf("%s\n%s\n",userArr[usersnum].account,userArr[usersnum].password);
		printf("请牢记您的账号和密码，感谢您的配合再见！\n"); 
		
			user new_user;
			strcpy(new_user.account,userArr[usersnum].account);
			strcpy(new_user.id,userArr[usersnum].id);
			strcpy(new_user.name,userArr[usersnum].name);
			strcpy(new_user.password,userArr[usersnum].password);
			strcpy(new_user.phoneNum,userArr[usersnum].phoneNum);
				new_user.level=userArr[usersnum].level;
				userArr[usersnum].level=0;
			strcpy(userArr[usersnum].account,"0");
			strcpy(userArr[usersnum].id,"0");
			strcpy(userArr[usersnum].name,"0");
			strcpy(userArr[usersnum].password,"0");
			strcpy(userArr[usersnum].phoneNum,"0");
			int user_num=userArr[0].amount;
			int index;//用于记录新账号插入位置的下标
			if(user_num>0){//判断数组是否为空 
				for(int i=0;i<user_num;i++){
					if(strcmp(new_user.account,userArr[i].account)<0){
						index=i;
						break;
					}
					if(i+1==user_num){//判断账号信息插入位置是否在数组末尾 
						index=user_num;
						break;
					}
				}
				if(index<user_num){//若插入位置在数组末尾，则无需移动其他元素 
					for(int i=userArr[user_num].amount;i>index;i--){
						strcpy(userArr[i].account,userArr[i-1].account);
						strcpy(userArr[i].id,userArr[i-1].id);
						strcpy(userArr[i].name,userArr[i-1].name);
						strcpy(userArr[i].password,userArr[i-1].password);
						strcpy(userArr[i].phoneNum,userArr[i-1].phoneNum);
						userArr[i].level=userArr[i-1].level;
					}
				}
			}
			else
				index=0;
			//若数组为空，则直接在首结点插入 
			strcpy(userArr[index].account,new_user.account);
			strcpy(userArr[index].id,new_user.id);
			strcpy(userArr[index].name,new_user.name);
			strcpy(userArr[index].password,new_user.password);
			strcpy(userArr[index].phoneNum,new_user.phoneNum);
			userArr[index].level=new_user.level;
		usersnum++;
		userArr[0].amount=usersnum;
		
		}
	}
void rulersign()//管理员添加用户//新管理员 
{	
int a=0,index;
int usersnum=userArr[0].amount;
	printf("请输入身份证号\n"); 
	scanf("%s",userArr[usersnum].id);
		while(strlen(userArr[usersnum].id)!=18){
			printf("身份证格式错误请重新输入\n");
				scanf("%s",userArr[usersnum].id);
} 
		//index=search_user(userArr[usersnum].id);
						//	if(index==1){
						//		printf("该身份证已有账户，可直接登录\n");
							//a=1;
						//	}
			if(a==0){
	printf("请输入姓名\n"); 
	scanf("%s",userArr[usersnum].name);
	while(strlen(userArr[usersnum].name)>6){
		printf("姓名格式错误请重新输入\n");
			scanf("%s",userArr[usersnum].name);
} 
	

	printf("请输入手机号码\n"); 
	scanf("%s",userArr[usersnum].phoneNum);
		while(strlen(userArr[usersnum].phoneNum)!=11){
			printf("手机号格式错误请重新输入\n");
				scanf("%s",userArr[usersnum].phoneNum);
} 
	printf("请输入密码\n"); 
	scanf("%s",userArr[usersnum].password);
		while(strlen(userArr[usersnum].password)>14||strlen(userArr[usersnum].password)<8){
			printf("密码格式错误请重新输入\n");
				scanf("%s",userArr[usersnum].password);
}			
	string str;                 /*声明用来保存随机字符串的str*/
	    char c;                     /*声明字符c，用来保存随机生成的字符*/
	    int idx;                    /*用来循环的变量*/
	    srand((unsigned)time(NULL));
	    /*循环向字符串中添加随机生成的字符*/
	    for(idx = 0;idx <12;idx ++)
	    {
	        
	        c = '0' + rand()%10;
	        str.push_back(c);       /*push_back()是string类尾插函数。这里插入随机字符c*/
	    }
 ;
str.copy(userArr[usersnum].account, 12, 0);//这里5代表复制几个字符，0代表复制的位置，
*(userArr[usersnum].account+12)='\0';//注意手动加结束符！！！
	system("cls");
	printf("是否赋予管理员权力？\n");
	scanf("%d",&userArr[usersnum].level);
	printf("这是您的账号与密码\n");
	printf("%s\n%s\n",userArr[usersnum].account,userArr[usersnum].password);
	printf("请牢记您的账号和密码，感谢您的配合再见！\n"); 
	
				user new_user;
					strcpy(new_user.account,userArr[usersnum].account);
					strcpy(new_user.id,userArr[usersnum].id);
					strcpy(new_user.name,userArr[usersnum].name);
					strcpy(new_user.password,userArr[usersnum].password);
					strcpy(new_user.phoneNum,userArr[usersnum].phoneNum);
					new_user.level=userArr[usersnum].level;
					userArr[usersnum].level=0;
					strcpy(userArr[usersnum].account,"0");
					strcpy(userArr[usersnum].id,"0");
					strcpy(userArr[usersnum].name,"0");
					strcpy(userArr[usersnum].password,"0");
					strcpy(userArr[usersnum].phoneNum,"0");
				int user_num=userArr[0].amount;
				int index;//用于记录新账号插入位置的下标
				if(user_num>0){//判断数组是否为空 
					for(int i=0;i<user_num;i++){
						if(strcmp(new_user.account,userArr[i].account)<0){
							index=i;
							break;
						}
						if(i+1==user_num){//判断账号信息插入位置是否在数组末尾 
							index=user_num;
							break;
						}
					}
					if(index<user_num){//若插入位置在数组末尾，则无需移动其他元素 
						for(int i=userArr[user_num].amount;i>index;i--){
							strcpy(userArr[i].account,userArr[i-1].account);
							strcpy(userArr[i].id,userArr[i-1].id);
							strcpy(userArr[i].name,userArr[i-1].name);
							strcpy(userArr[i].password,userArr[i-1].password);
							strcpy(userArr[i].phoneNum,userArr[i-1].phoneNum);
							userArr[i].level=userArr[i-1].level;
						}
					}
				}
				else
					index=0;
				//若数组为空，则直接在首结点插入 
				strcpy(userArr[index].account,new_user.account);
				strcpy(userArr[index].id,new_user.id);
				strcpy(userArr[index].name,new_user.name);
				strcpy(userArr[index].password,new_user.password);
				strcpy(userArr[index].phoneNum,new_user.phoneNum);
				userArr[index].level=new_user.level;
		usersnum++;
		userArr[0].amount=usersnum;
			}
} 

int  enter()
{  
	int a,i,lmi;
	printf("是否有账号？有请输入1，没有请输入0\n");
	 scanf("%d",&a); 
	 if(a==0){
	 	printf("请注册\n"); 
	 	sign();
	 }
	char aa[20],bb[20],dd[12]; 
	printf("账号或身份证：");
	scanf("%s",aa);
	for(i=0;i<500005;i++)
	{
		if(!strcmp(aa,(userArr[i].account))||!strcmp(aa,(userArr[i].id))){
			
			printf("密码：");
			scanf("%s",bb);
			if(!strcmp(bb,(userArr[i].password))){
						
					printf("登录成功！\n");
					lev=userArr[i].level;
					 break;
					}
					if(strcmp(bb,(userArr[i].password))){
								
							printf("密码错误，是否找回密码？需要找回请输入1，不需要输入0\n");
							int cc;
							 scanf("%d",&cc);
							 if(cc==1){
							 	printf("请输入电话号码"); 
							 	scanf("%s",dd);
							 	while(!strcmp(dd,(userArr[i].phoneNum))){
								 	printf("输入错误请重新输入\n"); 
								 	scanf("%s",dd);
								 }
								 printf("请修改您的密码\n"); 
								 scanf("%s",userArr[i].password);
								 printf("感谢您的配合，您已成功登录"); 
							 } 
							lev=userArr[i].level;
							return i;
							 break;
							}
		}
		
	}
	
}/* 
typedef struct passenger{
	int amount;
	char name[10]; //姓名 
	char id[20];//身份证 
	char flightNum[10];//航班号 
	char phoneNum[12];//手机号 
}passenger;*/ 
void checkinmy(int a)//根据登录返回值确定哪一位用户订票 
{
	int i,am;
	int passnum=passengerArr[0].amount; 
	char up_pos[10];
	char off_pos[10];//起始地
	char flightNum[10]; 
strcpy(passengerArr[passnum].name,userArr[a].name);
strcpy(passengerArr[passnum].id,userArr[a].id);
strcpy(passengerArr[passnum].phoneNum,userArr[a].phoneNum);
char maps[10][7]={{" "},{"华北,"},{"西北"},{"华南"},{"西南"},{"华东"},{"东北"},{"厦门"},{"新疆"}};
printf("本公司可航行的地址有\n");
for(i=1;i<9;i++)
{
	printf("%s,",maps[i]); 
}
printf("请选择你的起点与终点"); 
scanf("%s",up_pos);
scanf("%s",off_pos);
searchArea(up_pos,off_pos);
printf("请输入您选择的航班");
/*bool jud = false;
		while(!jud){
			
			scanf("%s",flightNum);
			if([].flightNum[0]!='C'||flightNum[1]!='A') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightNum[2]<'1'||flightNum[2]>'8'||flightNum[3]<'1'||flightNum[3]>'8'||flightNum[2]==flightNum[3]) printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightNum[3]<'0'||flightNum[3]>'9'||flightNum[4]<'0'||flightNum[4]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightNum[5]<'0'||flightNum[5]>'9'||flightNum[6]<'0'||flightNum[6]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightNum[7]<'0'||flightNum[7]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(strlen(flightNum)!=8) printf("您输入的航班号格式有误，请重新输入：\n");
			else jud = true;
		}*/
	scanf("%s",flightNum);
am=seach_flight(flightNum);//承接下标 
while(flightArr[am].num>=168){
	printf("抱歉本航班%s已满，请选择其他航班\n",flightNum);
	searchArea(up_pos,off_pos);
	printf("\n");
	scanf("%s",flightNum);
	am=seach_flight(flightNum);//承接下标 
}
if(flightArr[am].num<168){
	strcpy(passengerArr[passnum].flightNum,flightNum);
		passenger new_passenger;	
					strcpy(new_passenger.id,passengerArr[passnum].id);
					strcpy(new_passenger.name,passengerArr[passnum].name);
					strcpy(new_passenger.flightNum,passengerArr[passnum].flightNum);
					strcpy(new_passenger.phoneNum,passengerArr[passnum].phoneNum);
					strcpy(passengerArr[passnum].id,"0");
					strcpy(passengerArr[passnum].name,"0");
					strcpy(passengerArr[passnum].flightNum,"0");
					strcpy(passengerArr[passnum].phoneNum,"0");
				int passenger_num=passengerArr[0].amount;
				int index;//用于记录新账号插入位置的下标
				if(passenger_num>0){//判断数组是否为空 
					for(int i=0;i<passenger_num;i++){
						if(strcmp(new_passenger.id,passengerArr[i].id)<0){
							index=i;
							break;
						}
						if(i+1==passenger_num){//判断账号信息插入位置是否在数组末尾 
							index=passenger_num;
							break;
						}
					}
					if(index<passenger_num){//若插入位置在数组末尾，则无需移动其他元素 
						for(int i=passengerArr[passenger_num].amount;i>index;i--){
							strcpy(passengerArr[i].id,passengerArr[i-1].id);
							strcpy(passengerArr[i].name,passengerArr[i-1].name);
							strcpy(passengerArr[i].flightNum,passengerArr[i-1].flightNum);
							strcpy(passengerArr[i].phoneNum,passengerArr[i-1].phoneNum);
						}
					}
				}
				else
					index=0;
				//若数组为空，则直接在首结点插入
				strcpy(passengerArr[index].id,new_passenger.id);
				strcpy(passengerArr[index].name,new_passenger.name);
				strcpy(passengerArr[index].flightNum,new_passenger.flightNum);
				strcpy(passengerArr[index].phoneNum,new_passenger.phoneNum);
	passnum++;
	passengerArr[0].amount=passnum;
	printf("购票成功！欢迎下次使用！\n"); 
} 

}
void checkinother()
{
		int i,am;
		int passnum=passengerArr[0].amount; 
		char up_pos[10];
		char off_pos[10];//起始地
		char flightNum[10]; 
		printf("请输入身份证号\n"); 
			scanf("%s",passengerArr[passnum].id);
				while(strlen(passengerArr[passnum].id)!=18){
					printf("身份证格式错误请重新输入\n");
						scanf("%s",passengerArr[passnum].id);
		} 
			printf("请输入姓名\n"); 
			scanf("%s",passengerArr[passnum].name);
			while(strlen(passengerArr[passnum].name)>6){
				printf("姓名格式错误请重新输入\n");
					scanf("%s",passengerArr[passnum].name);
		} 
		
			printf("请输入手机号码\n"); 
			scanf("%s",passengerArr[passnum].phoneNum);
				while(strlen(passengerArr[passnum].phoneNum)!=11){
					printf("手机号格式错误请重新输入\n");
						scanf("%s",passengerArr[passnum].phoneNum);
		} 
		
	char maps[10][7]={{" "},{"华北,"},{"西北"},{"华南"},{"西南"},{"华东"},{"东北"},{"厦门"},{"新疆"}};
	printf("本公司可航行的地址有\n");
	for(i=1;i<9;i++)
	{
		printf("%s,",maps[i]); 
	}
	printf("请选择你的起点与终点"); 
	scanf("%s",up_pos);
	scanf("%s",off_pos);
	searchArea(up_pos,off_pos);
	printf("请输入您选择的航班");
	/*bool jud = false;
			while(!jud){
				
				scanf("%s",flightNum);
				if([].flightNum[0]!='C'||flightNum[1]!='A') printf("您输入的航班号格式有误，请重新输入：\n");
				else if(flightNum[2]<'1'||flightNum[2]>'8'||flightNum[3]<'1'||flightNum[3]>'8'||flightNum[2]==flightNum[3]) printf("您输入的航班号格式有误，请重新输入：\n");
				else if(flightNum[3]<'0'||flightNum[3]>'9'||flightNum[4]<'0'||flightNum[4]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
				else if(flightNum[5]<'0'||flightNum[5]>'9'||flightNum[6]<'0'||flightNum[6]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
				else if(flightNum[7]<'0'||flightNum[7]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
				else if(strlen(flightNum)!=8) printf("您输入的航班号格式有误，请重新输入：\n");
				else jud = true;
			}*/
		scanf("%s",flightNum);
	am=seach_flight(flightNum);//承接下标 
	while(flightArr[am].num>=168){
		printf("抱歉本航班%s已满，请选择其他航班\n",flightNum);
		searchArea(up_pos,off_pos);
		printf("\n");
		scanf("%s",flightNum);
		am=seach_flight(flightNum);//承接下标 
	}
	if(flightArr[am].num<168){
		strcpy(passengerArr[passnum].flightNum,flightNum);
			passenger new_passenger;	
							strcpy(new_passenger.id,passengerArr[passnum].id);
							strcpy(new_passenger.name,passengerArr[passnum].name);
							strcpy(new_passenger.flightNum,passengerArr[passnum].flightNum);
							strcpy(new_passenger.phoneNum,passengerArr[passnum].phoneNum);
							strcpy(passengerArr[passnum].id,"0");
							strcpy(passengerArr[passnum].name,"0");
							strcpy(passengerArr[passnum].flightNum,"0");
							strcpy(passengerArr[passnum].phoneNum,"0");
						int passenger_num=passengerArr[0].amount;
						int index;//用于记录新账号插入位置的下标
						if(passenger_num>0){//判断数组是否为空 
							for(int i=0;i<passenger_num;i++){
								if(strcmp(new_passenger.id,passengerArr[i].id)<0){
									index=i;
									break;
								}
								if(i+1==passenger_num){//判断账号信息插入位置是否在数组末尾 
									index=passenger_num;
									break;
								}
							}
							if(index<passenger_num){//若插入位置在数组末尾，则无需移动其他元素 
								for(int i=passengerArr[passenger_num].amount;i>index;i--){
									strcpy(passengerArr[i].id,passengerArr[i-1].id);
									strcpy(passengerArr[i].name,passengerArr[i-1].name);
									strcpy(passengerArr[i].flightNum,passengerArr[i-1].flightNum);
									strcpy(passengerArr[i].phoneNum,passengerArr[i-1].phoneNum);
								}
							}
						}
						else
							index=0;
						//若数组为空，则直接在首结点插入
						strcpy(passengerArr[index].id,new_passenger.id);
						strcpy(passengerArr[index].name,new_passenger.name);
						strcpy(passengerArr[index].flightNum,new_passenger.flightNum);
						strcpy(passengerArr[index].phoneNum,new_passenger.phoneNum);	
		passnum++;
		passengerArr[0].amount=passnum;
		printf("购票成功！欢迎下次使用！\n"); 
	} 
}
void checkin(int a,int b)//需要权限值 与登录的返回值来确定是哪一位用户 
{
	int choise;
	printf("欢迎使用本公司购票系统！\n");
	if(a){
		printf("您是用户\n");
	printf("为自己购票请输入1，为他人购票请输入2\n");
	scanf("%d",&choise);
	if(choice==1)
	{
	checkinmy(b);
	}
	else 
	{
	checkinother();
	}
	
	}
	else{
		printf("您是管理员\n");
		checkinother();
	}
		//直接调用用户姓名、身份证号、 手机号  
		//若满员 ，推荐相关航班
			/*推荐中转*/
			/*选择相关航班，可以不再重复输入信息*/
		//若没满员，写入乘客信息文件 

}

void checkout()
{
	//打开乘客信息文件
	// 录入信息 
		//输入乘客姓名、身份证
		//确认是否退票
		//修改文件内信息 
	//关闭乘客信息文件 
}
/*void search()
{
	// 打开航班信息 
	// 录入信息 
	printf("-----------------------------\n");
	FILE *file;
	file = fopen("airline.txt","r");
	if(file==NULL)//如果未打开就提示读取错误
	{
	printf("read error");
	return ;
	} 
	int NUM=0;
	int i=0;
	while(!feof(file)){
		fscanf(file,"%s",line[i].fight);
		fscanf(file,"%d/%d/%d/%d:%d",&line[i].up_year,&line[i].up_month,&line[i].up_day,
		&line[i].up_hour,&line[i].up_min);
		fscanf(file,"%d/%d/%d/%d:%d",&line[i].off_year,&line[i].off_month,&line[i].off_day,
		&line[i].off_hour,&line[i].off_min);
		fgets(line[i].up_pos,10,file);
		fgets(line[i].off_pos,10,file);
		//fscanf(file,"%s",line[i].up_pos);
		//fscanf(file,"%s",line[i].off_pos);
		fscanf(file,"￥%lf",&line[i].price);
		fscanf(file,"%lf%",&line[i].discount);
		fscanf(file,"%lf",&line[i].num);
		i++;
	} 
	NUM = i;
	printf("1)根据航班号查询\n");
	printf("2)根据起飞，降落城市查询\n");
	printf("请输入查询方式(1或2)：\n");
	int way;
	bool judge = false;
	while(!judge){
		scanf("%d",&way);
		if(way==1||way==2) judge = true;
		else printf("输入错误，请重新输入：\n"); 
	}
	if(way == 1){
		printf("   请输入查询航班号：\n");
		char number[10];
		judge = false;
		while(!judge){
			scanf("%s",number);
			if(number[0]!='C'||number[1]!='A') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(number[2]<'1'||number[2]>'9'||number[3]<'1'||number[3]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(number[4]!='0' || (number[5]!='1')&&number[5]!='2') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(strlen(number)!=6) printf("您输入的航班号格式有误，请重新输入：\n");
			else judge = true;
		}
		/*
		int l=0,r=NUM;
		int mid = (l+r)/2; 
		while(l<r){
			if(strcmp(line[mid].fight,number)<0) mid = l+1;
			else r = mid;
			mid = (l+r)/2;
		}
		for(int i=0;i<NUM;i++){
			if(strcmp(line[i].fight,number)==0)
			{
				int mid = i;
				printf("起飞时间：%d/%02d/%02d/%02d:%02d\n",line[mid].up_year,line[mid].up_month,line[mid].up_day,line[mid].up_hour,line[mid].up_min);
				printf("降落时间：%d/%02d/%02d/%02d:%02d\n",line[mid].off_year,line[mid].off_month,line[mid].off_day,line[mid].off_hour,line[mid].off_min);
				printf("起飞地点：%s\n",line[mid].up_pos);
				printf("降落地点：%s\n",line[mid].off_pos);
				printf("航班票价：￥%.2lf\n",line[mid].price);
				printf("票价折扣：%.lf%%\n",line[mid].discount);
				printf("是否满仓：");
				if(line[mid].num==MAX) printf("是\n");
				else printf("否\n");
				break;
			}
		}
	}  
	else{
		printf("请输入你的出发地、及目的地：\n");
		char map[10][5]={{" "},{"华北"},{"西北"},{"华南"},{"西南"},{"华东"},{"东北"},{"厦门"},{"新疆"}};
		char start_pos[10],end_pos[10];
		bool flag = false;
		int index1,index2;
		while(!flag){
			scanf("%s",start_pos);
			for(int i=1;i<10;i++){
				if(strcmp(map[i],start_pos)==0){
					index1 = i;
					flag=true;
					break;
				}	
			}
			if(!flag) printf("您输入的城市不在我司航线上，请重新输入：\n");
		}
		flag = false;
		while(!flag){
			scanf("%s",start_pos);
			for(int i=1;i<10;i++){
				if(strcmp(map[i],start_pos)==0 && strcmp(start_pos,end_pos)!=0){
					index2 = i;
					flag=true;
					break;
				}	
			}
			if(strcmp(start_pos,end_pos)==0) printf("您输入的目的地与出发地相同，请重新输入：\n");
			if(!flag) printf("您输入的城市不在我司航线上，请重新输入：\n");
		}
		printf("由%s飞往%s的航班有：\n",map[index1],map[index2]);
		for(int i=0;i<NUM;i++){
			if(line[i].fight[5]=='1'&&line[i].fight[2]==index1+'0' && line[i].fight[3]==index2+'0') printf("%s\n",line[i].fight);
			else if(line[i].fight[5]=='2'&&line[i].fight[3]==index1+'0' && line[i].fight[2]==index2+'0') printf("%s\n",line[i].fight);
		}
	}
	fclose(file); 
}
*/

void input()
{
	int a=0,i,index;
		int flinum=flightArr[0].amount;
printf("请输入航班号\n");
bool jud = false;
		while(!jud){
			
			scanf("%s",flightArr[flinum].flightNum);
			index=search_flight(flightArr[flinum].flightNum);
			if(index==-1)printf("航班号已存在，请重新输入：\n");
			else if(flightArr[flinum].flightNum[0]!='C'||flightArr[flinum].flightNum[1]!='A') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightArr[flinum].flightNum[2]<'1'||flightArr[flinum].flightNum[2]>'8'||flightArr[flinum].flightNum[3]<'1'||flightArr[flinum].flightNum[3]>'8'||flightArr[flinum].flightNum[2]==flightArr[flinum].flightNum[3]) printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightArr[flinum].flightNum[3]<'0'||flightArr[flinum].flightNum[3]>'9'||flightArr[flinum].flightNum[4]<'0'||flightArr[flinum].flightNum[4]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightArr[flinum].flightNum[5]<'0'||flightArr[flinum].flightNum[5]>'9'||flightArr[flinum].flightNum[6]<'0'||flightArr[flinum].flightNum[6]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(flightArr[flinum].flightNum[7]<'0'||flightArr[flinum].flightNum[7]>'9') printf("您输入的航班号格式有误，请重新输入：\n");
			else if(strlen(flightArr[flinum].flightNum)!=8) printf("您输入的航班号格式有误，请重新输入：\n");
			else jud = true;
		}

			if(a==0){
printf("请输入起飞时间 \n");
jud = false;
		while(!jud){
			scanf("%s",flightArr[flinum].up_time);
		
			if(strlen(flightArr[flinum].up_time)!=16) printf("您输入的时间格式有误，请重新输入：\n");
			else if(flightArr[flinum].up_time[0]!='2'||flightArr[flinum].up_time[1]!='0') printf("您输入的年份有误，请重新输入：\n");
			else if(flightArr[flinum].up_time[2]!='2'||(flightArr[flinum].up_time[3]!='2'&&flightArr[flinum].up_time[3]!='3')||flightArr[flinum].up_time[4]!='/') printf("您输入年份格式有误，请重新输入：\n");
			//年份 
			else if(flightArr[flinum].up_time[5]!='0'&&flightArr[flinum].up_time[5]!='1') printf("您输入月份格式有误，请重新输入：\n");
			else if(((flightArr[flinum].up_time[5]=='0')&&((flightArr[flinum].up_time[6]>'9')||flightArr[flinum].up_time[6]<'1'))||((flightArr[flinum].up_time[5]=='1')&&((flightArr[flinum].up_time[6]>'2')||flightArr[flinum].up_time[6]<'0'))) printf("您输入的月份2格式有误，请重新输入：\n");
			else if(flightArr[flinum].up_time[7]!='/') printf("您输入月份3格式有误，请重新输入：\n");
			//月份 
			else if((flightArr[flinum].up_time[5]=='0'&&flightArr[flinum].up_time[6]!='2')&&(flightArr[flinum].up_time[8]<'0'||flightArr[flinum].up_time[8]>'3')) printf("您输入的日期格式有误，请重新输入：\n");
			//判断不是2月
			else if((flightArr[flinum].up_time[5]=='0'&&flightArr[flinum].up_time[6]=='2')&&(flightArr[flinum].up_time[8]<'0'||flightArr[flinum].up_time[8]>'2')) printf("您输入的日期格式有误，请重新输入：\n"); 
			//判断2月 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='1'||flightArr[flinum].up_time[6]=='3'||flightArr[flinum].up_time[6]=='5'||flightArr[flinum].up_time[6]=='7'||flightArr[flinum].up_time[6]=='8'))||(flightArr[flinum].up_time[5]=='1'&&(flightArr[flinum].up_time[6]=='0'||flightArr[flinum].up_time[6]=='2')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='3'&&(flightArr[flinum].up_time[9]>'1'||flightArr[flinum].up_time[6]<'0')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断31天 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='4'||flightArr[flinum].up_time[6]=='6'||flightArr[flinum].up_time[6]=='9'))||(flightArr[flinum].up_time[5]=='1'&&(flightArr[flinum].up_time[6]=='1')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='3'&&(flightArr[flinum].up_time[9]!='0')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断30天 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='2')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='2'&&(flightArr[flinum].up_time[9]<'0'||flightArr[flinum].up_time[9]>'8')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断28天
			else if(flightArr[flinum].up_time[10]!='/') printf("您输入的日期格式有误，请重新输入：\n");
			else if(flightArr[flinum].up_time[11]<'0'||flightArr[flinum].up_time[11]>'2'||flightArr[flinum].up_time[12]<'0'||flightArr[flinum].up_time[12]>'9'||(flightArr[flinum].up_time[11]=='2'&&(flightArr[flinum].up_time[12]>'4'||flightArr[flinum].up_time[12]<'0'))) printf("您输入的时刻格式有误，请重新输入：\n");
			//判断24小时 
			else if(flightArr[flinum].up_time[13]!=':') printf("您输入的时刻格式有误，请重新输入：\n");
			else if(flightArr[flinum].up_time[14]<'0'||flightArr[flinum].up_time[14]>'5'||flightArr[flinum].up_time[15]<'0'||flightArr[flinum].up_time[15]>'9') printf("您输入的时刻格式有误，请重新输入：\n");
			//判断分钟 
			
			else jud = true;
		}
printf("请输入降落时间\n");

jud = false;
		while(!jud){
			scanf("%s",flightArr[flinum].off_time);
		
			if(strlen(flightArr[flinum].off_time)!=16) printf("您输入的时间格式有误，请重新输入：\n");
			else if(flightArr[flinum].off_time[0]!='2'||flightArr[flinum].off_time[1]!='0') printf("您输入的年份有误，请重新输入：\n");
			else if(flightArr[flinum].off_time[2]!='2'||(flightArr[flinum].off_time[3]!='2'&&flightArr[flinum].off_time[3]!='3')||flightArr[flinum].off_time[4]!='/') printf("您输入年份格式有误，请重新输入：\n");
			//年份 
			else if(flightArr[flinum].off_time[5]!='0'&&flightArr[flinum].off_time[5]!='1') printf("您输入月份格式有误，请重新输入：\n");
			else if(((flightArr[flinum].off_time[5]=='0')&&((flightArr[flinum].off_time[6]>'9')||flightArr[flinum].off_time[6]<'1'))||((flightArr[flinum].off_time[5]=='1')&&((flightArr[flinum].off_time[6]>'2')||flightArr[flinum].off_time[6]<'0'))) printf("您输入的月份格式有误，请重新输入：\n");
			else if(flightArr[flinum].off_time[7]!='/') printf("您输入月份格式有误，请重新输入：\n");
			//月份 
			else if((flightArr[flinum].off_time[5]=='0'&&flightArr[flinum].off_time[6]!='2')&&(flightArr[flinum].off_time[8]<'0'||flightArr[flinum].off_time[8]>'3')) printf("您输入的日期格式有误，请重新输入：\n");
			//判断不是2月
			else if((flightArr[flinum].off_time[5]=='0'&&flightArr[flinum].off_time[6]=='2')&&(flightArr[flinum].off_time[8]<'0'||flightArr[flinum].off_time[8]>'2')) printf("您输入的日期格式有误，请重新输入：\n"); 
			//判断2月 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='1'||flightArr[flinum].off_time[6]=='3'||flightArr[flinum].off_time[6]=='5'||flightArr[flinum].off_time[6]=='7'||flightArr[flinum].off_time[6]=='8'))||(flightArr[flinum].off_time[5]=='1'&&(flightArr[flinum].off_time[6]=='0'||flightArr[flinum].off_time[6]=='2')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='3'&&(flightArr[flinum].off_time[9]>'1'||flightArr[flinum].off_time[6]<'0')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断31天 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='4'||flightArr[flinum].off_time[6]=='6'||flightArr[flinum].off_time[6]=='9'))||(flightArr[flinum].off_time[5]=='1'&&(flightArr[flinum].off_time[6]=='1')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='3'&&(flightArr[flinum].off_time[9]!='0')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断30天 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='2')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='2'&&(flightArr[flinum].off_time[9]<'0'||flightArr[flinum].off_time[9]>'8')))) printf("您输入的日期格式有误，请重新输入：\n");
			//判断28天
			else if(flightArr[flinum].off_time[10]!='/') printf("您输入的日期格式有误，请重新输入：\n");
			else if(flightArr[flinum].off_time[11]<'0'||flightArr[flinum].off_time[11]>'2'||flightArr[flinum].off_time[12]<'0'||flightArr[flinum].off_time[12]>'9'||(flightArr[flinum].off_time[11]=='2'&&(flightArr[flinum].off_time[12]>'4'||flightArr[flinum].off_time[12]<'0'))) printf("您输入的时刻格式有误，请重新输入：\n");
			//判断24小时 
			else if(flightArr[flinum].off_time[13]!=':') printf("您输入的时刻格式有误，请重新输入：\n");
			else if(flightArr[flinum].off_time[14]<'0'||flightArr[flinum].off_time[14]>'5'||flightArr[flinum].off_time[15]<'0'||flightArr[flinum].off_time[15]>'9') printf("您输入的时刻格式有误，请重新输入：\n");
			//判断分钟 
			else {
		if(flightArr[flinum].up_time[3]<flightArr[flinum].off_time[3]){
							jud = true;
							}
						else if (flightArr[flinum].up_time[3]==flightArr[flinum].off_time[3]){
								if(flightArr[flinum].up_time[5]<flightArr[flinum].off_time[5]){
								jud = true;
								}
							 else if(flightArr[flinum].up_time[5]==flightArr[flinum].off_time[5]){
							 		if(flightArr[flinum].up_time[6]<flightArr[flinum].off_time[6]){
									 	jud = true;
										}
										else if(flightArr[flinum].up_time[6]==flightArr[flinum].off_time[6]){
											if(flightArr[flinum].up_time[8]<flightArr[flinum].off_time[8]){
												jud = true;
												}
												else if(flightArr[flinum].up_time[8]==flightArr[flinum].off_time[8]){
												if(flightArr[flinum].up_time[9]<flightArr[flinum].off_time[9]){
														jud = true;
														}
														else if(flightArr[flinum].up_time[9]==flightArr[flinum].off_time[9]){
														if(flightArr[flinum].up_time[11]<flightArr[flinum].off_time[11]){
																jud = true;
														     	}
																	else if(flightArr[flinum].up_time[11]==flightArr[flinum].off_time[11]){
																		if(flightArr[flinum].up_time[12]<flightArr[flinum].off_time[12]){
																				jud = true;
																					}
																					else if(flightArr[flinum].up_time[12]==flightArr[flinum].off_time[12]){
																					if(flightArr[flinum].up_time[14]<flightArr[flinum].off_time[14]){
																							jud = true;
																								}
																								else if(flightArr[flinum].up_time[14]==flightArr[flinum].off_time[14]){
																								if(flightArr[flinum].up_time[15]<flightArr[flinum].off_time[15]){
																										jud = true;
																										}
																								else printf("输入1错误，请重新输入");
																							}
																						else printf("输入1错误，请重新输入");
																					}
																				else printf("输入1错误，请重新输入");
																			}
																		else printf("输入2错误，请重新输入");
																	}
																else printf("输入3错误，请重新输入");
															}
														 else printf("输入4错误，请重新输入");
													}
												else printf("输入5错误，请重新输入");
											}
										else printf("输入6错误，请重新输入");
								}
							else printf("输入7错误，请重新输入");
		}
	
		}
												
char map[10][5]={{" "},{"华北"},{"西北"},{"华南"},{"西南"},{"华东"},{"东北"},{"厦门"},{"新疆"}};																					
																			
strcpy(flightArr[flinum].up_pos, map[(int)flightArr[flinum].flightNum[2]]);							
strcpy(flightArr[flinum].off_pos, map[(int)flightArr[flinum].flightNum[3]]);			
printf("请输入票价\n");
scanf("%lf",&flightArr[flinum].price);
while(flightArr[flinum].price<0||flightArr[flinum].price>10000){
	printf("票价输入有误，请重新输入\n");
	scanf("%lf",&flightArr[flinum].price);
}
printf("请输入折扣\n");
scanf("%lf",&flightArr[flinum].dicount);
while(flightArr[flinum].dicount<0||flightArr[flinum].dicount>100){
	printf("折扣输入有误，请重新输入\n");
	scanf("%lf",&flightArr[flinum].dicount);
}
flightArr[flinum].num=0;
	flight new_flight;	
					strcpy(new_flight.flightNum,flightArr[flinum].flightNum);
					strcpy(new_flight.up_time,flightArr[flinum].up_time);
					strcpy(new_flight.off_time,flightArr[flinum].off_time);
					strcpy(new_flight.up_pos,flightArr[flinum].up_pos);
					strcpy(new_flight.off_pos,flightArr[flinum].off_pos);
					new_flight.price=flightArr[flinum].price;
					new_flight.dicount=flightArr[flinum].dicount;
					new_flight.num=flightArr[flinum].num;
					strcpy(flightArr[flinum].up_time,"0");
					strcpy(flightArr[flinum].up_pos,"0");
					strcpy(flightArr[flinum].flightNum,"0");
					strcpy(flightArr[flinum].off_time,"0");
					strcpy(flightArr[flinum].off_pos,"0");
					flightArr[flinum].price=0;
					flightArr[flinum].dicount=0;
					flightArr[flinum].num=0;
				int flight_num=flightArr[0].amount;
				int index;//用于记录新账号插入位置的下标
				if(flight_num>0){//判断数组是否为空 
					for(int i=0;i<flight_num;i++){
						if(strcmp(new_flight.flightNum,passengerArr[i].id)<0){
							index=i;
							break;

						}
						if(i+1==flight_num){//判断账号信息插入位置是否在数组末尾 
							index=flight_num;
							break;
						}
					}
					if(index<flight_num){//若插入位置在数组末尾，则无需移动其他元素 
						for(int i=flightArr[flight_num].amount;i>index;i--){
							strcpy(flightArr[i].flightNum,flightArr[i-1].flightNum);
							strcpy(flightArr[i].up_time,flightArr[i-1].up_time);
							strcpy(flightArr[i].off_time,flightArr[i-1].off_time);
							strcpy(flightArr[i].up_pos,flightArr[i-1].up_pos);
							strcpy(flightArr[i].off_pos,flightArr[i-1].off_pos);
							flightArr[i].price=flightArr[i-1].price;
							flightArr[i].dicount=flightArr[i-1].dicount;
							flightArr[i].num=flightArr[i-1].num;
				
						}
					}
				}
				else
					index=0;
				//若数组为空，则直接在首结点插入
				strcpy(flightArr[index].up_time,new_flight.up_time);
				strcpy(flightArr[index].off_time,new_flight.off_time);
				strcpy(flightArr[index].flightNum,new_flight.flightNum);
				strcpy(flightArr[index].up_pos,new_flight.up_pos);
				strcpy(flightArr[index].off_pos,new_flight.off_pos);
				flightArr[index].price=new_flight.price;
				flightArr[index].dicount=new_flight.dicount;
				flightArr[index].num=new_flight.num;
 flinum++;
 flightArr[0].amount=flinum;
printf("添加成功！\n");
}

}
void change()
{
	// 打开航班信息 
	// 录入信息 
		//修改分两类：更改 or 删除
		//若更改，把结构体内信息更改
		//若删除，把后面覆盖前面 struct[i-1]=struct[i] 
	//关闭航班信息文件 
}
int main(){

//	enter();
input();

	print();
	int am=enter();
	switch(choice)
	{
		case 1: sign(); break;
		case 2: checkin(userArr[am].level,am); break;
		case 3: checkout(); break;
		case 4: input(); break;
		default: change();
	}
	return 0;
}
