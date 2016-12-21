#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#define MAXN	1001		//�ڵ������+1
#define MAXM	100001		//·�������+1
#define MAXNUM  50000		//����һ���㹻���ֵ������������·��ʱ�ľ���
int cost[MAXN][MAXN];				//�洢�������ص��ľ���

int Dij(int N,int (&dist)[MAXN],bool (&s)[MAXN],int (&pnode)[MAXN])		//�����Dijkstra�㷨�������·��
{																		//int (&dist)[MAXN]���������飬���������鷵��ֵ���Ӷ����ݶ������ֵ
	for(int i=1;i<=N;i++)
	{
		int temp = MAXNUM;
		int u = 1;
		for(int j=1;j<=N;j++)											//��{1}��ʼ���ҵ�ֱ�Ӻ�1�����ģ�����̵�·�������ȼ���ߣ�
		{
			if((!s[j])&&(dist[j]<temp))
			{
				u = j;
				temp = dist[j];
			}
		}
		s[u] = true;													//��{1��u}��ʼ�ڶ��飬��������֪{1��u}���·����ǰ���£�����������·��
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
				else if(sdistance == dist[j])							//��Ա����Ҫ������ͬ���·��ǰ���£�������С��չ·��
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
	while(list.size()!=N)												//�ڼ������С·����ǰ���£�����pnode[]��ϵ��ժȡ���б���·��
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
	int N,M;					//N�ڵ�����M·����
	cin >> N >> M;
	
	for(int i=0;i<=N;i++)		//��ʼ��cost[][]
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
		if(count>1)						//��һ��������Ԫ�صģ��ӵڶ��п�ʼ����
		{
			cost[arg1][arg2] = arg3;	//��cost[i][j]��ֵ
			cost[arg2][arg1] = arg3;
		}
		if(count==M+1)
			break;
	}

	int dist[MAXN];						//�洢Դ������ص����̾���
	bool s[MAXN];						//�洢Դ������ص����̾����Ƿ��Ѿ�����
	int pnode[MAXN];					//�洢����ص����·����ǰ�˵�
	for(int i=1;i<=N;i++)				//��dist[],s[],pnode[]����ֵ
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
	Dij(N,dist,s,pnode);				//��1��ʼ�����ȼ������·��
	int answer = getAnswer(N,dist,pnode);//�ڶ����ڱ������·����ǰ���£�������̱���·��
	cout << answer << endl;
	return 0;
}