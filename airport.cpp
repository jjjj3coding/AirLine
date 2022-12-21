#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 168
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
void print()
{
	/*
	printf("请输入您的账号：\n");
	char username[11];
	scanf("%s",username);
	printf("请输入您的密码:\n");
	char secret[20];
	*/
	printf("请输入您的权限:\n"); 
	scanf("%d",&limit);
	printf("-----------------------------\n");
	printf("   计信学院航空公司欢迎您！\n");
	printf("1.查询航班\n");
	printf("2.订票服务\n");
	printf("3.退订服务\n"); 
	if(limit == 1){
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
void first(){
	//需要在同一个文件夹内，新建两个文件，分别为
	//航班信息文件：航班号、起飞降落 时间地点、票价、折扣、每趟航班已有人数 
	//乘客信息文件：姓名、身份证号、订票数 、航班 
}
void checkin()
{
	// 打开乘客信息文件 
	// 录入信息 
		//输入乘客姓名、身份证号、 订票数 、航班 
		//若满员 ，推荐相关航班
			/*推荐中转*/
			/*选择相关航班，可以不再重复输入信息*/
		//若没满员，写入乘客信息文件 
	//关闭乘客信息文件 
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
void search()
{
	// 打开航班信息 
	// 录入信息 
	//1.
		//输入查询航班号
		//二分查找
		//输出信息 
	//2.
		//输入起飞降落城市
		//输出以A为起点，B为终点的航班
		/*输出中转信息*/ 
	//关闭航班信息文件 
}
void input()
{
	// 打开航班信息 
		// 录入信息 
		//按航班号进行排序 
	//关闭航班信息文件 
	
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
	print();
	switch(choice)
	{
		case 1: search(); break;
		case 2: checkin(); break;
		case 3: checkout(); break;
		case 4: input(); break;
		default: change();
	}
	return 0;
} 
