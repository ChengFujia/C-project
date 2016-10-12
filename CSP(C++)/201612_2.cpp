#include <iostream>
#include <vector>
using namespace std;
#define HAVEPEOPLE 0


//处理函数（输入剩余seats,请求数量，输出剩余seats）
vector<int> handler(vector<int> seats,int request)
{
	vector<int> seats_5(5);	//一排5个座位

	//第一种情况，若request可在一排中解决，给予连续的座位
	for(int i=1;i<21;i++)
	{
		//这个 一定要写在循环里面，每一次初始化
		int seat_null = 5;		//空的座位
		int seat_null_pos=0;	//第一个空的座位的位置，他俩的和是5

		//分别给上述3个变量赋初值
		for(int j=0;j<5;j++)
		{
			seats_5[j] = seats[5*i-5+j];
			if(seats_5[j]==HAVEPEOPLE)
				{
					seat_null--;
					seat_null_pos++;
				}
		}
		//符合第一种情况
		if (request <= seat_null)
		{
			for(int k=1;k<=request;k++)
			{
				cout<<seats_5[seat_null_pos+k-1]<<' ';
				seats[i*5-5+seat_null_pos+k-1] = HAVEPEOPLE;
			}
			cout << endl;
			return seats;
		}
	}

	//第二种情况，若request不可能在一排中解决，给予编号最小的座位
	//鉴于题干约定的一个人最多买5张票，所以这种情况
	//只有当20排都有人，且第一排的剩余作为不足以提供连续作为的情况下才会出现
	//一般情况下并不会执行（故优先级低）
	for(int i=0;i<100;i++)
	{
		if (seats[i]!=HAVEPEOPLE)
		{
			cout << seats[i] << ' ';
			seats[i]=HAVEPEOPLE;
			request--;
			if (request==0)
			{
				cout << endl;
				return seats;
			}
		}
	}
}

int main()
{
	vector<int> seats(100);
	for(int i=1;i<=100;i++)
		seats[i-1]=i;
	int numRequest,request,count=0;
	cin >> numRequest;
	while(cin >> request)
	{
		seats = handler(seats,request);
		count = count + 1;
		if (count == numRequest)
			break;
	}
	return 0;
}