#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int C[51][51];
int count = 0; //计数，如果本路线符合条件，count++
int k;

//判断是否拥有一个 递增子序列，且长度>=k， 有即满足
bool judge(vector<int> route)
{
	int length = route.size();
	//外层循环 定义子序列的起点
	for(int i=0;i<=length-k;i++)
	{
		int latter = route[i];		//the latter/the former 用于比较的前后项
		int temp = 1;				//计数值，记录递增子序列目前的长度
		//内层循环 定义从距离为1 到length-1-i/也就是最后一项
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
	return false;					//从未弹出 说明所有的都不符合
}

//深度优先（x方向） + 递归 -- 用来列举每一种可能的路径，对于每条路再judge是否符合条件
void f(vector<int> &route,int x,int y,int m,int n,int direction)
{
	//若在地图内部 -- 未到边界上（分叉，先向右深度遍历，后返回来向下拓展广度）
	if (x != m-1 && y != n-1)
	{
		if(direction == 1)	//向右 = 1
		{
			//添加元素后，继续分叉
			route.push_back(C[y][x+1]);		//这里注意 读取输入时为C[n][m] == C[y][x]
			f(route,x+1,y,m,n,1);
			//经 测试发现：
			//若到了边界，就只剩下一条路了，如果设置分叉，会重复
			//若未到边界，正常分叉
			if(x+1!=m-1)
				f(route,x+1,y,m,n,0);
			route.pop_back();				//注意这些pop很重要，为了返回上一层时恢复原样
		}
		else				//向下 = 0
		{
			route.push_back(C[y+1][x]);
			f(route,x,y+1,m,n,1);
			if(y+1!=n-1)
				f(route,x,y+1,m,n,0);
			route.pop_back();
		}
	}
	//若到了地图边界处
	else 
	{
		//若到了地图x方向边界处
		if(x == m-1 && y!=n-1)
		{
			//手动添加其余元素（沿着y方向顺序添加即可）
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
		//若到了地图y方向边界处
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