#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <time.h>
using namespace std;
#define MAX 168
int lev;
//�ɻ�����168�� 
int limit;//Ȩ�� 
/*	
	Ա����
		¼��
		�޸ĺ�����Ϣ 
		�û� ��
			��ѯ
			��Ʊ
			��Ʊ 
*/
int choice;//ѡ����� 
//�������߽ṹ�壬��������line���溽����Ϣ 
typedef struct user{
	int amount;
	char name[10];//�û����� 
	char id[20];//�û����֤�� 
	char account[15];//�˺� 
	char password[20];//���� 
	char phoneNum[12];//�ֻ��� 
	int level;//Ȩ��ֵ 
}user;

typedef struct flight{
	int amount;
	char flightNum[10];//����� 
	char up_time[15];//���ʱ�� 
	char off_time[15];//����ʱ�� 
	char up_pos[10];
	char off_pos[10];//��ʼ�� 
	double price;//Ʊ�� 
	double dicount;//�ۿ� 
	int num;//�����ϵ����� 
}flight;

typedef struct passenger{
	int amount;
	char name[10]; //���� 
	char id[20];//���֤ 
	char flightNum[10];//����� 
	char phoneNum[12];//�ֻ��� 
}passenger;

user userArr[500005];
flight flightArr[500005];
passenger passengerArr[500005];


void print()
{
	/*
	printf("�����������˺ţ�\n");
	char username[11];
	scanf("%s",username);
	printf("��������������:\n");
	char secret[20];
	*/

	printf("-----------------------------\n");
	printf("   ����ѧԺ���չ�˾��ӭ����\n");
	printf("1.��ѯ����\n");
	printf("2.��Ʊ����\n");
	printf("3.�˶�����\n"); 
	if(lev == 1){
		printf("4.¼�뺽����Ϣ\n");
		printf("5.�޸ĺ�����Ϣ\n"); 
	} 
	printf("-----------------------------\n");
	printf("��������ѡ��ķ���\n");
	
	bool judge = false;
	while(!judge){
		fflush(stdin);
		double data;
		scanf("%lf",&data);
		if(data>5 || data<1|| data!=(int)data) printf("����������������룺\n");
		else if(limit==0&&4<=data&&data<=5) printf("����������������룺\n");
		else {
			judge = true;
			choice = (int)data;
		}
	} 
	
}

void sign()//ע�� 
{	
int usersnum=userArr[0].amount;
	int a=0,index;
		printf("���������֤��\n"); 
		scanf("%s",userArr[usersnum].id);
			while(strlen(userArr[usersnum].id)!=18){
				printf("���֤��ʽ��������������\n");
					scanf("%s",userArr[usersnum].id);
	} 
		//index=search�û�(userArr[usersnum].id);
				//	if(index){
				//		printf("�����֤�����˻�����ֱ�ӵ�¼\n");
					//a=1;
				//	}
				if(a==0){
		printf("����������\n"); 
		scanf("%s",userArr[usersnum].name);
		while(strlen(userArr[usersnum].name)>6){
			printf("������ʽ��������������\n");
				scanf("%s",userArr[usersnum].name);
	} 
		
	
		printf("�������ֻ�����\n"); 
		scanf("%s",userArr[usersnum].phoneNum);
			while(strlen(userArr[usersnum].phoneNum)!=11){
				printf("�ֻ��Ÿ�ʽ��������������\n");
					scanf("%s",userArr[usersnum].phoneNum);
	} 
		printf("����������\n"); 
		scanf("%s",userArr[usersnum].password);
			while(strlen(userArr[usersnum].password)>14||strlen(userArr[usersnum].password)<8){
				printf("�����ʽ��������������\n");
					scanf("%s",userArr[usersnum].password);
	}			
		string str;                 /*����������������ַ�����str*/
		    char c;                     /*�����ַ�c����������������ɵ��ַ�*/
		    int idx;                    /*����ѭ���ı���*/
		    srand((unsigned)time(NULL));
		    /*ѭ�����ַ��������������ɵ��ַ�*/
		    for(idx = 0;idx <12;idx ++)
		    {
		        
		        c = '0' + rand()%10;
		        str.push_back(c);       /*push_back()��string��β�庯���������������ַ�c*/
		    }
	 ;
	str.copy(userArr[usersnum].account, 12, 0);//����5�����Ƽ����ַ���0�����Ƶ�λ�ã�
	*(userArr[usersnum].account+12)='\0';//ע���ֶ��ӽ�����������
		system("cls");
		printf("���������˺�������\n");
		printf("%s\n%s\n",userArr[usersnum].account,userArr[usersnum].password);
		printf("���μ������˺ź����룬��л��������ټ���\n"); 
		
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
			int index;//���ڼ�¼���˺Ų���λ�õ��±�
			if(user_num>0){//�ж������Ƿ�Ϊ�� 
				for(int i=0;i<user_num;i++){
					if(strcmp(new_user.account,userArr[i].account)<0){
						index=i;
						break;
					}
					if(i+1==user_num){//�ж��˺���Ϣ����λ���Ƿ�������ĩβ 
						index=user_num;
						break;
					}
				}
				if(index<user_num){//������λ��������ĩβ���������ƶ�����Ԫ�� 
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
			//������Ϊ�գ���ֱ�����׽����� 
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
void rulersign()//����Ա����û�//�¹���Ա 
{	
int a=0,index;
int usersnum=userArr[0].amount;
	printf("���������֤��\n"); 
	scanf("%s",userArr[usersnum].id);
		while(strlen(userArr[usersnum].id)!=18){
			printf("���֤��ʽ��������������\n");
				scanf("%s",userArr[usersnum].id);
} 
		//index=search_user(userArr[usersnum].id);
						//	if(index==1){
						//		printf("�����֤�����˻�����ֱ�ӵ�¼\n");
							//a=1;
						//	}
			if(a==0){
	printf("����������\n"); 
	scanf("%s",userArr[usersnum].name);
	while(strlen(userArr[usersnum].name)>6){
		printf("������ʽ��������������\n");
			scanf("%s",userArr[usersnum].name);
} 
	

	printf("�������ֻ�����\n"); 
	scanf("%s",userArr[usersnum].phoneNum);
		while(strlen(userArr[usersnum].phoneNum)!=11){
			printf("�ֻ��Ÿ�ʽ��������������\n");
				scanf("%s",userArr[usersnum].phoneNum);
} 
	printf("����������\n"); 
	scanf("%s",userArr[usersnum].password);
		while(strlen(userArr[usersnum].password)>14||strlen(userArr[usersnum].password)<8){
			printf("�����ʽ��������������\n");
				scanf("%s",userArr[usersnum].password);
}			
	string str;                 /*����������������ַ�����str*/
	    char c;                     /*�����ַ�c����������������ɵ��ַ�*/
	    int idx;                    /*����ѭ���ı���*/
	    srand((unsigned)time(NULL));
	    /*ѭ�����ַ��������������ɵ��ַ�*/
	    for(idx = 0;idx <12;idx ++)
	    {
	        
	        c = '0' + rand()%10;
	        str.push_back(c);       /*push_back()��string��β�庯���������������ַ�c*/
	    }
 ;
str.copy(userArr[usersnum].account, 12, 0);//����5�����Ƽ����ַ���0�����Ƶ�λ�ã�
*(userArr[usersnum].account+12)='\0';//ע���ֶ��ӽ�����������
	system("cls");
	printf("�Ƿ������ԱȨ����\n");
	scanf("%d",&userArr[usersnum].level);
	printf("���������˺�������\n");
	printf("%s\n%s\n",userArr[usersnum].account,userArr[usersnum].password);
	printf("���μ������˺ź����룬��л��������ټ���\n"); 
	
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
				int index;//���ڼ�¼���˺Ų���λ�õ��±�
				if(user_num>0){//�ж������Ƿ�Ϊ�� 
					for(int i=0;i<user_num;i++){
						if(strcmp(new_user.account,userArr[i].account)<0){
							index=i;
							break;
						}
						if(i+1==user_num){//�ж��˺���Ϣ����λ���Ƿ�������ĩβ 
							index=user_num;
							break;
						}
					}
					if(index<user_num){//������λ��������ĩβ���������ƶ�����Ԫ�� 
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
				//������Ϊ�գ���ֱ�����׽����� 
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
	printf("�Ƿ����˺ţ���������1��û��������0\n");
	 scanf("%d",&a); 
	 if(a==0){
	 	printf("��ע��\n"); 
	 	sign();
	 }
	char aa[20],bb[20],dd[12]; 
	printf("�˺Ż����֤��");
	scanf("%s",aa);
	for(i=0;i<500005;i++)
	{
		if(!strcmp(aa,(userArr[i].account))||!strcmp(aa,(userArr[i].id))){
			
			printf("���룺");
			scanf("%s",bb);
			if(!strcmp(bb,(userArr[i].password))){
						
					printf("��¼�ɹ���\n");
					lev=userArr[i].level;
					 break;
					}
					if(strcmp(bb,(userArr[i].password))){
								
							printf("��������Ƿ��һ����룿��Ҫ�һ�������1������Ҫ����0\n");
							int cc;
							 scanf("%d",&cc);
							 if(cc==1){
							 	printf("������绰����"); 
							 	scanf("%s",dd);
							 	while(!strcmp(dd,(userArr[i].phoneNum))){
								 	printf("�����������������\n"); 
								 	scanf("%s",dd);
								 }
								 printf("���޸���������\n"); 
								 scanf("%s",userArr[i].password);
								 printf("��л������ϣ����ѳɹ���¼"); 
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
	char name[10]; //���� 
	char id[20];//���֤ 
	char flightNum[10];//����� 
	char phoneNum[12];//�ֻ��� 
}passenger;*/ 
void checkinmy(int a)//���ݵ�¼����ֵȷ����һλ�û���Ʊ 
{
	int i,am;
	int passnum=passengerArr[0].amount; 
	char up_pos[10];
	char off_pos[10];//��ʼ��
	char flightNum[10]; 
strcpy(passengerArr[passnum].name,userArr[a].name);
strcpy(passengerArr[passnum].id,userArr[a].id);
strcpy(passengerArr[passnum].phoneNum,userArr[a].phoneNum);
char maps[10][7]={{" "},{"����,"},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"�½�"}};
printf("����˾�ɺ��еĵ�ַ��\n");
for(i=1;i<9;i++)
{
	printf("%s,",maps[i]); 
}
printf("��ѡ�����������յ�"); 
scanf("%s",up_pos);
scanf("%s",off_pos);
searchArea(up_pos,off_pos);
printf("��������ѡ��ĺ���");
/*bool jud = false;
		while(!jud){
			
			scanf("%s",flightNum);
			if([].flightNum[0]!='C'||flightNum[1]!='A') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightNum[2]<'1'||flightNum[2]>'8'||flightNum[3]<'1'||flightNum[3]>'8'||flightNum[2]==flightNum[3]) printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightNum[3]<'0'||flightNum[3]>'9'||flightNum[4]<'0'||flightNum[4]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightNum[5]<'0'||flightNum[5]>'9'||flightNum[6]<'0'||flightNum[6]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightNum[7]<'0'||flightNum[7]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(strlen(flightNum)!=8) printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else jud = true;
		}*/
	scanf("%s",flightNum);
am=seach_flight(flightNum);//�н��±� 
while(flightArr[am].num>=168){
	printf("��Ǹ������%s��������ѡ����������\n",flightNum);
	searchArea(up_pos,off_pos);
	printf("\n");
	scanf("%s",flightNum);
	am=seach_flight(flightNum);//�н��±� 
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
				int index;//���ڼ�¼���˺Ų���λ�õ��±�
				if(passenger_num>0){//�ж������Ƿ�Ϊ�� 
					for(int i=0;i<passenger_num;i++){
						if(strcmp(new_passenger.id,passengerArr[i].id)<0){
							index=i;
							break;
						}
						if(i+1==passenger_num){//�ж��˺���Ϣ����λ���Ƿ�������ĩβ 
							index=passenger_num;
							break;
						}
					}
					if(index<passenger_num){//������λ��������ĩβ���������ƶ�����Ԫ�� 
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
				//������Ϊ�գ���ֱ�����׽�����
				strcpy(passengerArr[index].id,new_passenger.id);
				strcpy(passengerArr[index].name,new_passenger.name);
				strcpy(passengerArr[index].flightNum,new_passenger.flightNum);
				strcpy(passengerArr[index].phoneNum,new_passenger.phoneNum);
	passnum++;
	passengerArr[0].amount=passnum;
	printf("��Ʊ�ɹ�����ӭ�´�ʹ�ã�\n"); 
} 

}
void checkinother()
{
		int i,am;
		int passnum=passengerArr[0].amount; 
		char up_pos[10];
		char off_pos[10];//��ʼ��
		char flightNum[10]; 
		printf("���������֤��\n"); 
			scanf("%s",passengerArr[passnum].id);
				while(strlen(passengerArr[passnum].id)!=18){
					printf("���֤��ʽ��������������\n");
						scanf("%s",passengerArr[passnum].id);
		} 
			printf("����������\n"); 
			scanf("%s",passengerArr[passnum].name);
			while(strlen(passengerArr[passnum].name)>6){
				printf("������ʽ��������������\n");
					scanf("%s",passengerArr[passnum].name);
		} 
		
			printf("�������ֻ�����\n"); 
			scanf("%s",passengerArr[passnum].phoneNum);
				while(strlen(passengerArr[passnum].phoneNum)!=11){
					printf("�ֻ��Ÿ�ʽ��������������\n");
						scanf("%s",passengerArr[passnum].phoneNum);
		} 
		
	char maps[10][7]={{" "},{"����,"},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"�½�"}};
	printf("����˾�ɺ��еĵ�ַ��\n");
	for(i=1;i<9;i++)
	{
		printf("%s,",maps[i]); 
	}
	printf("��ѡ�����������յ�"); 
	scanf("%s",up_pos);
	scanf("%s",off_pos);
	searchArea(up_pos,off_pos);
	printf("��������ѡ��ĺ���");
	/*bool jud = false;
			while(!jud){
				
				scanf("%s",flightNum);
				if([].flightNum[0]!='C'||flightNum[1]!='A') printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else if(flightNum[2]<'1'||flightNum[2]>'8'||flightNum[3]<'1'||flightNum[3]>'8'||flightNum[2]==flightNum[3]) printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else if(flightNum[3]<'0'||flightNum[3]>'9'||flightNum[4]<'0'||flightNum[4]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else if(flightNum[5]<'0'||flightNum[5]>'9'||flightNum[6]<'0'||flightNum[6]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else if(flightNum[7]<'0'||flightNum[7]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else if(strlen(flightNum)!=8) printf("������ĺ���Ÿ�ʽ�������������룺\n");
				else jud = true;
			}*/
		scanf("%s",flightNum);
	am=seach_flight(flightNum);//�н��±� 
	while(flightArr[am].num>=168){
		printf("��Ǹ������%s��������ѡ����������\n",flightNum);
		searchArea(up_pos,off_pos);
		printf("\n");
		scanf("%s",flightNum);
		am=seach_flight(flightNum);//�н��±� 
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
						int index;//���ڼ�¼���˺Ų���λ�õ��±�
						if(passenger_num>0){//�ж������Ƿ�Ϊ�� 
							for(int i=0;i<passenger_num;i++){
								if(strcmp(new_passenger.id,passengerArr[i].id)<0){
									index=i;
									break;
								}
								if(i+1==passenger_num){//�ж��˺���Ϣ����λ���Ƿ�������ĩβ 
									index=passenger_num;
									break;
								}
							}
							if(index<passenger_num){//������λ��������ĩβ���������ƶ�����Ԫ�� 
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
						//������Ϊ�գ���ֱ�����׽�����
						strcpy(passengerArr[index].id,new_passenger.id);
						strcpy(passengerArr[index].name,new_passenger.name);
						strcpy(passengerArr[index].flightNum,new_passenger.flightNum);
						strcpy(passengerArr[index].phoneNum,new_passenger.phoneNum);	
		passnum++;
		passengerArr[0].amount=passnum;
		printf("��Ʊ�ɹ�����ӭ�´�ʹ�ã�\n"); 
	} 
}
void checkin(int a,int b)//��ҪȨ��ֵ ���¼�ķ���ֵ��ȷ������һλ�û� 
{
	int choise;
	printf("��ӭʹ�ñ���˾��Ʊϵͳ��\n");
	if(a){
		printf("�����û�\n");
	printf("Ϊ�Լ���Ʊ������1��Ϊ���˹�Ʊ������2\n");
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
		printf("���ǹ���Ա\n");
		checkinother();
	}
		//ֱ�ӵ����û����������֤�š� �ֻ���  
		//����Ա ���Ƽ���غ���
			/*�Ƽ���ת*/
			/*ѡ����غ��࣬���Բ����ظ�������Ϣ*/
		//��û��Ա��д��˿���Ϣ�ļ� 

}

void checkout()
{
	//�򿪳˿���Ϣ�ļ�
	// ¼����Ϣ 
		//����˿����������֤
		//ȷ���Ƿ���Ʊ
		//�޸��ļ�����Ϣ 
	//�رճ˿���Ϣ�ļ� 
}
/*void search()
{
	// �򿪺�����Ϣ 
	// ¼����Ϣ 
	printf("-----------------------------\n");
	FILE *file;
	file = fopen("airline.txt","r");
	if(file==NULL)//���δ�򿪾���ʾ��ȡ����
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
		fscanf(file,"��%lf",&line[i].price);
		fscanf(file,"%lf%",&line[i].discount);
		fscanf(file,"%lf",&line[i].num);
		i++;
	} 
	NUM = i;
	printf("1)���ݺ���Ų�ѯ\n");
	printf("2)������ɣ�������в�ѯ\n");
	printf("�������ѯ��ʽ(1��2)��\n");
	int way;
	bool judge = false;
	while(!judge){
		scanf("%d",&way);
		if(way==1||way==2) judge = true;
		else printf("����������������룺\n"); 
	}
	if(way == 1){
		printf("   �������ѯ����ţ�\n");
		char number[10];
		judge = false;
		while(!judge){
			scanf("%s",number);
			if(number[0]!='C'||number[1]!='A') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(number[2]<'1'||number[2]>'9'||number[3]<'1'||number[3]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(number[4]!='0' || (number[5]!='1')&&number[5]!='2') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(strlen(number)!=6) printf("������ĺ���Ÿ�ʽ�������������룺\n");
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
				printf("���ʱ�䣺%d/%02d/%02d/%02d:%02d\n",line[mid].up_year,line[mid].up_month,line[mid].up_day,line[mid].up_hour,line[mid].up_min);
				printf("����ʱ�䣺%d/%02d/%02d/%02d:%02d\n",line[mid].off_year,line[mid].off_month,line[mid].off_day,line[mid].off_hour,line[mid].off_min);
				printf("��ɵص㣺%s\n",line[mid].up_pos);
				printf("����ص㣺%s\n",line[mid].off_pos);
				printf("����Ʊ�ۣ���%.2lf\n",line[mid].price);
				printf("Ʊ���ۿۣ�%.lf%%\n",line[mid].discount);
				printf("�Ƿ����֣�");
				if(line[mid].num==MAX) printf("��\n");
				else printf("��\n");
				break;
			}
		}
	}  
	else{
		printf("��������ĳ����ء���Ŀ�ĵأ�\n");
		char map[10][5]={{" "},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"�½�"}};
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
			if(!flag) printf("������ĳ��в�����˾�����ϣ����������룺\n");
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
			if(strcmp(start_pos,end_pos)==0) printf("�������Ŀ�ĵ����������ͬ�����������룺\n");
			if(!flag) printf("������ĳ��в�����˾�����ϣ����������룺\n");
		}
		printf("��%s����%s�ĺ����У�\n",map[index1],map[index2]);
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
printf("�����뺽���\n");
bool jud = false;
		while(!jud){
			
			scanf("%s",flightArr[flinum].flightNum);
			index=search_flight(flightArr[flinum].flightNum);
			if(index==-1)printf("������Ѵ��ڣ����������룺\n");
			else if(flightArr[flinum].flightNum[0]!='C'||flightArr[flinum].flightNum[1]!='A') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightArr[flinum].flightNum[2]<'1'||flightArr[flinum].flightNum[2]>'8'||flightArr[flinum].flightNum[3]<'1'||flightArr[flinum].flightNum[3]>'8'||flightArr[flinum].flightNum[2]==flightArr[flinum].flightNum[3]) printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightArr[flinum].flightNum[3]<'0'||flightArr[flinum].flightNum[3]>'9'||flightArr[flinum].flightNum[4]<'0'||flightArr[flinum].flightNum[4]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightArr[flinum].flightNum[5]<'0'||flightArr[flinum].flightNum[5]>'9'||flightArr[flinum].flightNum[6]<'0'||flightArr[flinum].flightNum[6]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(flightArr[flinum].flightNum[7]<'0'||flightArr[flinum].flightNum[7]>'9') printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else if(strlen(flightArr[flinum].flightNum)!=8) printf("������ĺ���Ÿ�ʽ�������������룺\n");
			else jud = true;
		}

			if(a==0){
printf("���������ʱ�� \n");
jud = false;
		while(!jud){
			scanf("%s",flightArr[flinum].up_time);
		
			if(strlen(flightArr[flinum].up_time)!=16) printf("�������ʱ���ʽ�������������룺\n");
			else if(flightArr[flinum].up_time[0]!='2'||flightArr[flinum].up_time[1]!='0') printf("�����������������������룺\n");
			else if(flightArr[flinum].up_time[2]!='2'||(flightArr[flinum].up_time[3]!='2'&&flightArr[flinum].up_time[3]!='3')||flightArr[flinum].up_time[4]!='/') printf("��������ݸ�ʽ�������������룺\n");
			//��� 
			else if(flightArr[flinum].up_time[5]!='0'&&flightArr[flinum].up_time[5]!='1') printf("�������·ݸ�ʽ�������������룺\n");
			else if(((flightArr[flinum].up_time[5]=='0')&&((flightArr[flinum].up_time[6]>'9')||flightArr[flinum].up_time[6]<'1'))||((flightArr[flinum].up_time[5]=='1')&&((flightArr[flinum].up_time[6]>'2')||flightArr[flinum].up_time[6]<'0'))) printf("��������·�2��ʽ�������������룺\n");
			else if(flightArr[flinum].up_time[7]!='/') printf("�������·�3��ʽ�������������룺\n");
			//�·� 
			else if((flightArr[flinum].up_time[5]=='0'&&flightArr[flinum].up_time[6]!='2')&&(flightArr[flinum].up_time[8]<'0'||flightArr[flinum].up_time[8]>'3')) printf("����������ڸ�ʽ�������������룺\n");
			//�жϲ���2��
			else if((flightArr[flinum].up_time[5]=='0'&&flightArr[flinum].up_time[6]=='2')&&(flightArr[flinum].up_time[8]<'0'||flightArr[flinum].up_time[8]>'2')) printf("����������ڸ�ʽ�������������룺\n"); 
			//�ж�2�� 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='1'||flightArr[flinum].up_time[6]=='3'||flightArr[flinum].up_time[6]=='5'||flightArr[flinum].up_time[6]=='7'||flightArr[flinum].up_time[6]=='8'))||(flightArr[flinum].up_time[5]=='1'&&(flightArr[flinum].up_time[6]=='0'||flightArr[flinum].up_time[6]=='2')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='3'&&(flightArr[flinum].up_time[9]>'1'||flightArr[flinum].up_time[6]<'0')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�31�� 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='4'||flightArr[flinum].up_time[6]=='6'||flightArr[flinum].up_time[6]=='9'))||(flightArr[flinum].up_time[5]=='1'&&(flightArr[flinum].up_time[6]=='1')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='3'&&(flightArr[flinum].up_time[9]!='0')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�30�� 
			else if((((flightArr[flinum].up_time[5]=='0')&&(flightArr[flinum].up_time[6]=='2')))&&(((flightArr[flinum].up_time[9]>'9'||flightArr[flinum].up_time[9]<'0'))||(flightArr[flinum].up_time[8]=='2'&&(flightArr[flinum].up_time[9]<'0'||flightArr[flinum].up_time[9]>'8')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�28��
			else if(flightArr[flinum].up_time[10]!='/') printf("����������ڸ�ʽ�������������룺\n");
			else if(flightArr[flinum].up_time[11]<'0'||flightArr[flinum].up_time[11]>'2'||flightArr[flinum].up_time[12]<'0'||flightArr[flinum].up_time[12]>'9'||(flightArr[flinum].up_time[11]=='2'&&(flightArr[flinum].up_time[12]>'4'||flightArr[flinum].up_time[12]<'0'))) printf("�������ʱ�̸�ʽ�������������룺\n");
			//�ж�24Сʱ 
			else if(flightArr[flinum].up_time[13]!=':') printf("�������ʱ�̸�ʽ�������������룺\n");
			else if(flightArr[flinum].up_time[14]<'0'||flightArr[flinum].up_time[14]>'5'||flightArr[flinum].up_time[15]<'0'||flightArr[flinum].up_time[15]>'9') printf("�������ʱ�̸�ʽ�������������룺\n");
			//�жϷ��� 
			
			else jud = true;
		}
printf("�����뽵��ʱ��\n");

jud = false;
		while(!jud){
			scanf("%s",flightArr[flinum].off_time);
		
			if(strlen(flightArr[flinum].off_time)!=16) printf("�������ʱ���ʽ�������������룺\n");
			else if(flightArr[flinum].off_time[0]!='2'||flightArr[flinum].off_time[1]!='0') printf("�����������������������룺\n");
			else if(flightArr[flinum].off_time[2]!='2'||(flightArr[flinum].off_time[3]!='2'&&flightArr[flinum].off_time[3]!='3')||flightArr[flinum].off_time[4]!='/') printf("��������ݸ�ʽ�������������룺\n");
			//��� 
			else if(flightArr[flinum].off_time[5]!='0'&&flightArr[flinum].off_time[5]!='1') printf("�������·ݸ�ʽ�������������룺\n");
			else if(((flightArr[flinum].off_time[5]=='0')&&((flightArr[flinum].off_time[6]>'9')||flightArr[flinum].off_time[6]<'1'))||((flightArr[flinum].off_time[5]=='1')&&((flightArr[flinum].off_time[6]>'2')||flightArr[flinum].off_time[6]<'0'))) printf("��������·ݸ�ʽ�������������룺\n");
			else if(flightArr[flinum].off_time[7]!='/') printf("�������·ݸ�ʽ�������������룺\n");
			//�·� 
			else if((flightArr[flinum].off_time[5]=='0'&&flightArr[flinum].off_time[6]!='2')&&(flightArr[flinum].off_time[8]<'0'||flightArr[flinum].off_time[8]>'3')) printf("����������ڸ�ʽ�������������룺\n");
			//�жϲ���2��
			else if((flightArr[flinum].off_time[5]=='0'&&flightArr[flinum].off_time[6]=='2')&&(flightArr[flinum].off_time[8]<'0'||flightArr[flinum].off_time[8]>'2')) printf("����������ڸ�ʽ�������������룺\n"); 
			//�ж�2�� 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='1'||flightArr[flinum].off_time[6]=='3'||flightArr[flinum].off_time[6]=='5'||flightArr[flinum].off_time[6]=='7'||flightArr[flinum].off_time[6]=='8'))||(flightArr[flinum].off_time[5]=='1'&&(flightArr[flinum].off_time[6]=='0'||flightArr[flinum].off_time[6]=='2')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='3'&&(flightArr[flinum].off_time[9]>'1'||flightArr[flinum].off_time[6]<'0')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�31�� 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='4'||flightArr[flinum].off_time[6]=='6'||flightArr[flinum].off_time[6]=='9'))||(flightArr[flinum].off_time[5]=='1'&&(flightArr[flinum].off_time[6]=='1')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='3'&&(flightArr[flinum].off_time[9]!='0')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�30�� 
			else if((((flightArr[flinum].off_time[5]=='0')&&(flightArr[flinum].off_time[6]=='2')))&&(((flightArr[flinum].off_time[9]>'9'||flightArr[flinum].off_time[9]<'0'))||(flightArr[flinum].off_time[8]=='2'&&(flightArr[flinum].off_time[9]<'0'||flightArr[flinum].off_time[9]>'8')))) printf("����������ڸ�ʽ�������������룺\n");
			//�ж�28��
			else if(flightArr[flinum].off_time[10]!='/') printf("����������ڸ�ʽ�������������룺\n");
			else if(flightArr[flinum].off_time[11]<'0'||flightArr[flinum].off_time[11]>'2'||flightArr[flinum].off_time[12]<'0'||flightArr[flinum].off_time[12]>'9'||(flightArr[flinum].off_time[11]=='2'&&(flightArr[flinum].off_time[12]>'4'||flightArr[flinum].off_time[12]<'0'))) printf("�������ʱ�̸�ʽ�������������룺\n");
			//�ж�24Сʱ 
			else if(flightArr[flinum].off_time[13]!=':') printf("�������ʱ�̸�ʽ�������������룺\n");
			else if(flightArr[flinum].off_time[14]<'0'||flightArr[flinum].off_time[14]>'5'||flightArr[flinum].off_time[15]<'0'||flightArr[flinum].off_time[15]>'9') printf("�������ʱ�̸�ʽ�������������룺\n");
			//�жϷ��� 
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
																								else printf("����1��������������");
																							}
																						else printf("����1��������������");
																					}
																				else printf("����1��������������");
																			}
																		else printf("����2��������������");
																	}
																else printf("����3��������������");
															}
														 else printf("����4��������������");
													}
												else printf("����5��������������");
											}
										else printf("����6��������������");
								}
							else printf("����7��������������");
		}
	
		}
												
char map[10][5]={{" "},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"����"},{"�½�"}};																					
																			
strcpy(flightArr[flinum].up_pos, map[(int)flightArr[flinum].flightNum[2]]);							
strcpy(flightArr[flinum].off_pos, map[(int)flightArr[flinum].flightNum[3]]);			
printf("������Ʊ��\n");
scanf("%lf",&flightArr[flinum].price);
while(flightArr[flinum].price<0||flightArr[flinum].price>10000){
	printf("Ʊ��������������������\n");
	scanf("%lf",&flightArr[flinum].price);
}
printf("�������ۿ�\n");
scanf("%lf",&flightArr[flinum].dicount);
while(flightArr[flinum].dicount<0||flightArr[flinum].dicount>100){
	printf("�ۿ�������������������\n");
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
				int index;//���ڼ�¼���˺Ų���λ�õ��±�
				if(flight_num>0){//�ж������Ƿ�Ϊ�� 
					for(int i=0;i<flight_num;i++){
						if(strcmp(new_flight.flightNum,passengerArr[i].id)<0){
							index=i;
							break;

						}
						if(i+1==flight_num){//�ж��˺���Ϣ����λ���Ƿ�������ĩβ 
							index=flight_num;
							break;
						}
					}
					if(index<flight_num){//������λ��������ĩβ���������ƶ�����Ԫ�� 
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
				//������Ϊ�գ���ֱ�����׽�����
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
printf("��ӳɹ���\n");
}

}
void change()
{
	// �򿪺�����Ϣ 
	// ¼����Ϣ 
		//�޸ķ����ࣺ���� or ɾ��
		//�����ģ��ѽṹ������Ϣ����
		//��ɾ�����Ѻ��渲��ǰ�� struct[i-1]=struct[i] 
	//�رպ�����Ϣ�ļ� 
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
