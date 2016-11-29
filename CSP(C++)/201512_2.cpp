#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//fstream fcin("input.txt");
	int value[40][40];
	int result[40][40];
	int n=0;
	int m=0;
	cin >> n >> m;
	//读入 注意一定要初始化result,因为不同编译器的初始值不同，会造成不必要的错误
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> value[i][j];
			result[i][j] = value[i][j];
		}
	}
	//不计时间的暴力破解
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int k = j+1;			//行
			while(value[i][k] == value[i][j] && k<=m)
				k++;
			k--;
			if( k-j+1 >=3)
			{
				for(int l=j;l<=k;l++)
					result[i][l] = 0;
			}

			k = i+1;				//列
			while(value[i][j] == value[k][j] && k<=n)
				k++;
			k--;
			if(k-i+1 >=3)
			{
				for(int l=i;l<=k;l++)
					result[l][j] = 0;
			}
		}
	}
	//设置两个矩阵的原因在于 存在同时行列消的情况，因此不方便直接在原图中修改
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(result[i][j] !=0)
				result[i][j] = value[i][j];
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}