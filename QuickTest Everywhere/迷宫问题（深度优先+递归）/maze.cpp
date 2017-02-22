#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int C[51][51];
int count = 0; //�����������·�߷���������count++
int k;

//�ж��Ƿ�ӵ��һ�� ���������У��ҳ���>=k�� �м�����
bool judge(vector<int> route)
{
	int length = route.size();
	//���ѭ�� ���������е����
	for(int i=0;i<=length-k;i++)
	{
		int latter = route[i];		//the latter/the former ���ڱȽϵ�ǰ����
		int temp = 1;				//����ֵ����¼����������Ŀǰ�ĳ���
		//�ڲ�ѭ�� ����Ӿ���Ϊ1 ��length-1-i/Ҳ�������һ��
		for(int j=1;j<=length-1-i;j++)
		{
			if(latter < route[i+j])
			{
				temp++;
				if(temp >=k)
					return true;
				latter = route[i+j];
			}
		}
	}
	return false;					//��δ���� ˵�����еĶ�������
}

//������ȣ�x���� + �ݹ� -- �����о�ÿһ�ֿ��ܵ�·��������ÿ��·��judge�Ƿ��������
void f(vector<int> &route,int x,int y,int m,int n,int direction)
{
	//���ڵ�ͼ�ڲ� -- δ���߽��ϣ��ֲ棬��������ȱ������󷵻���������չ��ȣ�
	if (x != m-1 && y != n-1)
	{
		if(direction == 1)	//���� = 1
		{
			//���Ԫ�غ󣬼����ֲ�
			route.push_back(C[y][x+1]);		//����ע�� ��ȡ����ʱΪC[n][m] == C[y][x]
			f(route,x+1,y,m,n,1);
			//�� ���Է��֣�
			//�����˱߽磬��ֻʣ��һ��·�ˣ�������÷ֲ棬���ظ�
			//��δ���߽磬�����ֲ�
			if(x+1!=m-1)
				f(route,x+1,y,m,n,0);
			route.pop_back();				//ע����Щpop����Ҫ��Ϊ�˷�����һ��ʱ�ָ�ԭ��
		}
		else				//���� = 0
		{
			route.push_back(C[y+1][x]);
			f(route,x,y+1,m,n,1);
			if(y+1!=n-1)
				f(route,x,y+1,m,n,0);
			route.pop_back();
		}
	}
	//�����˵�ͼ�߽紦
	else 
	{
		//�����˵�ͼx����߽紦
		if(x == m-1 && y!=n-1)
		{
			//�ֶ��������Ԫ�أ�����y����˳����Ӽ��ɣ�
			for(int i=y+1;i<=n-1;i++)
				route.push_back(C[i][m-1]);
			/*
			for(int i=0;i<route.size();i++)
				cout << route[i] << " ";
			cout << endl;
			*/
			bool result = judge(route);
			if(result)
				count++;
			//cout << count << endl;

			for(int i=y+1;i<=n-1;i++)
				route.pop_back();
			/*
			for(int i=0;i<route.size();i++)
				cout << route[i] << " ";
			cout << endl << endl;
			*/
			return;
		}
		//�����˵�ͼy����߽紦
		if(y == n-1 && x!=m-1)
		{
			for(int j=x+1;j<=m-1;j++)
				route.push_back(C[n-1][j]);
			/*
			for(int i=0;i<route.size();i++)
				cout << route[i] << " ";
			cout << endl;
			*/
			bool result = judge(route);
			if(result)
				count++;
			//cout << count << endl;

			for(int j=x+1;j<=m-1;j++)
				route.pop_back();
			/*
			for(int i=0;i<route.size();i++)
				cout << route[i] << " ";
			cout << endl<< endl;
			*/
			return ;
		}
	}	
}

int main()
{
	memset(C,0,sizeof(C));
	int n,m;
	cin >> n >> m >> k;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>> C[i][j];

	vector<int> route;
	route.push_back(C[0][0]);
	f(route,0,0,m,n,1);
	f(route,0,0,m,n,0);
	cout << count % 1000000007 <<endl;
	return 0;
}