#include<stdio.h>
#include<string.h>

int searchLine(char* arr){
	int num=3;
	return num;
}
int searchPas(char* arr){
	int num=3;
	return num;
}
/*
int main() {
	fopen("DataStructure.txt", "r");
	if(fp!=NULL){
		while(!feof(fp)){
			printf("%c",getc(fp));
		}
		fclose(fp);
	}
	else
		printf("fail to open!");
	return 0;
}*/

typedef struct user{
	char name[10];//用户姓名 
	char id[20];//用户身份证号 
	char account[15];//账号 
	char password[20];//密码 
	char phoneNum[12];//手机号 
	int num;//用户人数 
	//int level;//权限值 
}user;

typedef struct flight{
	char flightNum[10];//航班号 
	char up_time[17];//起飞时间 
	char off_time[17];//降落时间 
	char up_pos[10];
	char off_pos[10];//起始地 
	double price;//票价 
	double discount;//折扣 
	int num;//航班上的人数 
}flight;

typedef struct passenger{
	char name[10]; 
	char id[20];
	char flightNum[10];
	char phoneNum[12];
	int num;//乘客人数 
}passenger;

int level=0;//权限值 
user userArr[500005];
flight flightArr[500005];
passenger passengerArr[500005];

void rewrite(int index){//修改用户
	double choice;
	int aim_index;
	char aim_id[20];
	char oldPasword[20];
	char newPaswordf[20];
	char newPaswords[20];
	char newPhoneNum[12];
	if(level==1){
		printf("请输入用户身份证号：\n");
		scanf("%s",aim_id);
		aim_index=search_user(aim_id);
		while(aim_index==-1){
			printf("未查询到该用户，是否继续查询：\n");
			printf("1.继续查询\n");
			printf("2.退出\n");
			scanf("%lf",&choice);
			if(choice==2){
				printf("请输入用户身份证号：\n");
				scanf("%s",aim_id);
			}
			else
				return;
		}
	}
	else
		aim_index=index;
	printf("请选择您要修改的信息：\n");
	printf("1.密码\n");
	printf("2.手机号\n");
	scanf("%lf",&choice);
	while(choice<1||choice>2||choice!=(int)choice){
		printf("请求失败，请重新输入！\n");
		scanf("%lf",&choice);
	}
	if(choice==1){
		printf("请输入原密码：\n");
		scanf("%s",oldPasword);
		while(strcmp(oldPasword,userArr[aim_index].password)!=0){
			printf("原密码错误！是否继续修改：\n");
			printf("1.继续修改		2.退出修改\n");
			scanf("%lf",&choice);
			while(choice<1||choice>2||choice!=(int)choice){
				printf("请求失败，请重新输入！\n");
				scanf("%lf",&choice);
			}
			if(choice==1){
				printf("请输入原密码：\n");
				scanf("%s",oldPasword);
			}
			else
				return;
		}
		printf("请输入新密码：\n");
		scanf("%s",newPaswordf);
		printf("请再次输入新密码：\n");
		scanf("%s",newPaswords);
		while(strcmp(newPaswordf,newPaswords)!=0){
			for(int i=0;i<strlen(newPaswords);i++)
				newPaswords[i]='\0';
			printf("两次输入不一致，请再次输入新密码：\n");
			scanf("%s",newPaswords);
		}
		strcpy(userArr[aim_index].password,newPaswords);
	}
	else{
		printf("请输入新的手机号：\n");
		scanf("%s",newPhoneNum);
		while(strlen(newPhoneNum)!=strlen(userArr[aim_index].phoneNum)){
			printf("手机号异常，请重新输入：\n");
			scanf("%s",newPhoneNum);
		}
		strcpy(userArr[aim_index].phoneNum,newPhoneNum);
	}
	printf("用户信息修改成功！\n");
	return;
}

void change(){//修改航班
	int index;
	char aim_flightNum[10];
	char reup_time[17];//起飞时间 
	char reoff_time[17];//降落时间 
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	double reprice;//票价 
	double rediscount;//折扣 
	double choice;
	printf("请输入航班号：\n");
	scanf("%s",aim_flightNum);
	index=search_flight(aim_flightNum);
	while(index==-1){
		printf("航班号不存在，请重新输入：\n");
		scanf("%s",aim_flightNum);
		index=search_flight(aim_flightNum);
	}
	printf("请选择需要修改的航班信息：\n"); 
	printf("1.航班起飞时间		2.航班降落时间\n");
	printf("3.航班票价			4.航班折扣\n");
	scanf("%lf",&choice);
	while(choice<1||choice>4||choice!=(int)choice){
		printf("请求失败，请重新输入！\n");
		scanf("%lf",&choice);
	}
	if(choice==1){
		printf("请输入新的起飞时间：\n");
		scanf("%s",reup_time);
		while(strlen(reup_time)!=16){
			printf("输入格式不正确，请重新输入：\n");
			scanf("%s",reup_time);
		}
		while(strcmp(reup_time,flightArr[index].off_time)>=0){
			printf("无效输入，请重新输入：\n");
			scanf("%s",reup_time);
		}
		for(int i=0;i<16;i++){
			if(reup_time[i]=='/'){
				if(i!=4||i!=7||i!=10){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reup_time);
					i=0;
					continue;
				}
			}
			else if(reup_time[i]==':'){
				if(i!=13){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reup_time);
					i=0;
					continue;
				}
			}
			else{
				if(reup_time[i]<'0'||reup_time[i]>'9'){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reup_time);
					i=0;
					continue;
				}
				for(int j=0;j<4;j++)
					year[j]=reup_time[j];
				month[0]=reup_time[5];month[1]=reup_time[6];
				day[0]=reup_time[8];day[1]=reup_time[9];
				hour[0]=reup_time[11];hour[1]=reup_time[12];
				minute[0]=reup_time[14];minute[1]=reup_time[15];
				if(strcmp(month,"01")<0||strcmp(month,"12")>0||strcmp(day,"01")<0||strcmp(day,"31")>0||
					strcmp(hour,"00")<0||strcmp(hour,"23")>0||strcmp(minute,"00")<0||strcmp(minute,"59")>0||
					strcmp(year,"2022")<0||strcmp(year,"2023")>0){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reup_time);
					i=0;
					continue;
				}
				else if(strcmp(month,"02")==0&&strcmp(day,"29")>0){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reup_time);
					i=0;
					continue;
				}
			}
		}
		strcpy(flightArr[index].up_time,reup_time);
		//2022/12/12/14:23
	}
	else if(choice==2){
		printf("请输入新的降落时间：\n");
		scanf("%s",reoff_time);
		while(strlen(reoff_time)!=16){
			printf("输入格式不正确，请重新输入：\n");
			scanf("%s",reoff_time);
		}
		while(strcmp(reoff_time,flightArr[index].up_time)<=0){
			printf("无效输入，请重新输入：\n");
			scanf("%s",reoff_time);
		}
		for(int i=0;i<16;i++){
			if(reoff_time[i]=='/'){
				if(i!=4||i!=7||i!=10){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reoff_time);
					i=0;
					continue;
				}
			}
			else if(reoff_time[i]==':'){
				if(i!=13){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reoff_time);
					i=0;
					continue;
				}
			}
			else{
				if(reoff_time[i]<'0'||reoff_time[i]>'9'){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reoff_time);
					i=0;
					continue;
				}
				for(int j=0;j<4;j++)
					year[j]=reoff_time[j];
				month[0]=reoff_time[5];month[1]=reoff_time[6];
				day[0]=reoff_time[8];day[1]=reoff_time[9];
				hour[0]=reoff_time[11];hour[1]=reoff_time[12];
				minute[0]=reoff_time[14];minute[1]=reoff_time[15];
				if(strcmp(month,"01")<0||strcmp(month,"12")>0||strcmp(day,"01")<0||strcmp(day,"31")>0||
					strcmp(hour,"00")<0||strcmp(hour,"23")>0||strcmp(minute,"00")<0||strcmp(minute,"59")>0||
					strcmp(year,"2022")<0||strcmp(year,"2023")>0){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reoff_time);
					i=0;
					continue;
				}
				else if(strcmp(month,"02")==0&&strcmp(day,"29")>0){
					printf("输入格式不正确，请重新输入：\n");
					scanf("%s",reoff_time);
					i=0;
					continue;
				}
			}
		}
		strcpy(flightArr[index].off_time,reoff_time);
	}
	else if(choice==3){
		printf("请输入新的票价：\n");
		scanf("%lf",&reprice);
		flightArr[index].price=reprice;
	}
	else{
		printf("请输入新的折扣：\n");
		scanf("%lf",&rediscount);
		while(rediscount<0||rediscount>100){
			printf("折扣值不正确，请重新输入：\n");
			scanf("%lf",&rediscount);
		}
		flightArr[index].discount=rediscount;
	}
	printf("航班信息修改成功！\n");
	return;
}

void checkOut(int index){//退票
	char ticket[10];
	char aim_id[20];
	int idx_passenger;
	int	idx_user;
	double choice; 
	if(level==1){
		printf("请输入退票人身份证：\n");
		scanf("%s",aim_id);
		idx_passenger=search_passenger(aim_id);
		while(idx_passenger==-1){
			printf("查询失败，是否继续查询：\n");
			printf("1.继续查询		2.退出查询\n");
			scanf("%lf",&choice);
			while(choice<1||choice>2||choice!=(int)choice){
				printf("请求错误，请重新输入：\n");
				printf("1.继续查询		2.退出查询\n");
				scanf("%lf",&choice);
			}
			if(choice==1){
				scanf("%s",aim_id);
				idx_passenger=search_passenger(aim_id);
			}
			else
				return;
		}
	}
	else{
		idx_user=index;
		idx_passenger=search_passenger(userArr[user].account)
		if(idx_passenger==-1){
			printf("退票失败，您未购买此航班！\n");
			return;
		}
	}
	for(int i=idx_passenger;i<passengerArr[0].num;i++){
		strcpy(passengerArr[i].id,passengerArr[i+1].id);
		strcpy(passengerArr[i].name,passengerArr[i+1].name);
		strcpy(passengerArr[i].phoneNum,passengerArr[i+1].phoneNum);
		strcpy(passengerArr[i].flightNum,passengerArr[i+1].flightNum);
	}
	passengerArr[0].num--;
	printf("退票成功！\n");
	return; 
}

void delAcount(int index){//管理员删除用户 、用户注销账户 
	int aim_index;
	double choice;
	char aim_id[20];
	char aim_password[20];
	if(level==1){
		printf("请输入被注销人身份证：\n");
		scanf("%s",aim_id);
		aim_index=search_user(aim_id);
		while(aim_index==-1){
			printf("查询注销人失败，是否继续注销：\n");
			printf("1.继续注销		2.退出注销\n");
			scanf("%lf",&choice);
			while(choice<1||choice>2||choice!=(int)choice){
				printf("请求错误，请重新输入：\n");
				printf("1.继续注销		2.退出注销\n");
				scanf("%lf",&choice);
			}
			if(choice==1){
				scanf("%s",aim_id);
				aim_index=search_user(aim_id);
			}
			else
				return;
		}
	}
	else
		aim_index=index;
	printf("是否确认注销此账户？\n");
	printf("1.确认注销		2.退出注销\n");
	scanf("%lf",&choice);
	while(choice<1||choice>2||choice!=(int)choice){
		printf("请求错误，请重新输入：\n");
		printf("1.确认注销		2.退出注销\n");
		scanf("%lf",&choice);
	}
	if(choice==1){
		printf("请输入账户密码确认身份：\n");
		scanf("%s",aim_password);
		while(strcmp(aim_password,userArr[aim_index].password)!=0){
			printf("密码错误，是否重新输入：\n");
			printf("1.重新输入		2.退出注销\n");
			scanf("%lf",&choice);
			while(choice<1||choice>2||choice!=(int)choice){
				printf("请求错误，请重新输入：\n");
				printf("1.重新输入		2.退出注销\n");
				scanf("%lf",&choice);
			}
			if(choice==1){
				scanf("%s",aim_password);
			}
			else
				return;
		}
		for(int i=aim_index;i<userArr[0].num;i++){
			strcpy(userArr[i].name,userArr[i+1].name);
			strcpy(userArr[i].id,userArr[i+1].id);
			strcpy(userArr[i].account,userArr[i+1].account);
			strcpy(userArr[i].password,userArr[i+1].password);
			strcpy(userArr[i].phoneNum,userArr[i+1].phoneNum);
		}
		userArr[0].num--;
		printf("注销账户成功！\n");
	}
	else
		return;
}

void  link(){
	int len=0;
	char account[17];
	scanf("%s",account);
	for(int i=0;i<16;i++)
		printf("%c",account[i]);
	printf("\n");
	printf("%d",strlen(account));
}
int main(){
	link();
}

