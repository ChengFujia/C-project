#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#define MAXN	1001		//节点最大数+1
#define MAXM	100001		//路径最大数+1
#define MAXNUM  50000		//设置一个足够大的值当作若两个无路径时的距离
int cost[MAXN][MAXN];				//存储任意两地点间的距离

int Dij(int N,int (&dist)[MAXN],bool (&s)[MAXN],int (&pnode)[MAXN])		//常规的Dijkstra算法计算最短路径
{																		//int (&dist)[MAXN]是引用数组，用来给数组返回值，从而传递多个返回值
	for(int i=1;i<=N;i++)
	{
		int temp = MAXNUM;
		int u = 1;
		for(int j=1;j<=N;j++)											//从{1}开始，找到直接和1相连的，且最短的路径（优先级最高）
		{
			if((!s[j])&&(dist[j]<temp))
			{
				u = j;
				temp = dist[j];
			}
		}
		s[u] = true;													//从{1，u}开始第二遍，计算在已知{1，u}最短路径的前提下，其他点的最短路径
		for(int j=1;j<=N;j++)
		{
			if((!s[j])&&(cost[u][j]<MAXNUM))
			{
				int sdistance = dist[u] + cost[u][j];
				if(sdistance < dist[j])
				{
					dist[j] = sdistance;
					pnode[j] = u;
				}
				else if(sdistance == dist[j])							//针对本题的要求，在相同最短路径前提下，保存最小扩展路径
				{
					if(cost[u][j] < dist[j]-dist[pnode[j]])
						pnode[j] = u;
				}
			}
		}
	}
	return 0;
}

int getAnswer(int N,int (&dist)[MAXN],int (&pnode)[MAXN])
{
	int result =0;
	vector<int>  list;
	list.push_back(1);
	int u =0;
	while(list.size()!=N)												//在计算出最小路径的前提下，根据pnode[]关系，摘取所有保留路径
	{
		for(int i=1;i<=N;i++)
		{
			if(pnode[i] == list[u])
			{
				result += dist[i]-dist[list[u]];
				pnode[i] = 0;
				list.push_back(i);
			}
		}
		u++;
	}
	return result;
}

int main()
{
	int N,M;					//N节点数，M路径数
	cin >> N >> M;
	
	for(int i=0;i<=N;i++)		//初始化cost[][]
		for(int j=0;j<=N;j++)
			cost[i][j] = MAXNUM;
		
	int count=0;
	string line;
	int arg1,arg2,arg3;
	while(getline(cin,line))
	{
		istringstream path(line);
		count++;
		path >> arg1 >> arg2 >> arg3;
		if(count>1)						//第一行是两个元素的，从第二行开始计算
		{
			cost[arg1][arg2] = arg3;	//给cost[i][j]赋值
			cost[arg2][arg1] = arg3;
		}
		if(count==M+1)
			break;
	}

	int dist[MAXN];						//存储源到任意地点的最短距离
	bool s[MAXN];						//存储源到任意地点的最短距离是否已经计算
	int pnode[MAXN];					//存储任意地点最短路径的前端点
	for(int i=1;i<=N;i++)				//给dist[],s[],pnode[]赋初值
	{
		dist[i] = cost[1][i];
		s[i] = false;
		if(dist[i]==MAXNUM)
			pnode[i] = 0;
		else
			pnode[i] = 1;
	}
	
	dist[1] = 0;
	s[1] = true;
	Dij(N,dist,s,pnode);				//从1开始，首先计算最短路径
	int answer = getAnswer(N,dist,pnode);//第二遍在遍历最短路径的前提下，计算最短保留路径
	cout << answer << endl;
	return 0;
}