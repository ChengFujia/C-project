#include <iostream>
#include <vector>
using namespace std;
#define HAVEPEOPLE 0


//������������ʣ��seats,�������������ʣ��seats��
vector<int> handler(vector<int> seats,int request)
{
	vector<int> seats_5(5);	//һ��5����λ

	//��һ���������request����һ���н����������������λ
	for(int i=1;i<21;i++)
	{
		//��� һ��Ҫд��ѭ�����棬ÿһ�γ�ʼ��
		int seat_null = 5;		//�յ���λ
		int seat_null_pos=0;	//��һ���յ���λ��λ�ã������ĺ���5

		//�ֱ������3����������ֵ
		for(int j=0;j<5;j++)
		{
			seats_5[j] = seats[5*i-5+j];
			if(seats_5[j]==HAVEPEOPLE)
				{
					seat_null--;
					seat_null_pos++;
				}
		}
		//���ϵ�һ�����
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

	//�ڶ����������request��������һ���н������������С����λ
	//�������Լ����һ���������5��Ʊ�������������
	//ֻ�е�20�Ŷ����ˣ��ҵ�һ�ŵ�ʣ����Ϊ�������ṩ������Ϊ������²Ż����
	//һ������²�����ִ�У������ȼ��ͣ�
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