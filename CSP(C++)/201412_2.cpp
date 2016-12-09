#include <iostream>
#include <cstring>
using namespace std;

int a[505][505];
int main()
{
	int n;
	cin >> n;
	
	//特殊例子 直接输出
	if(n==1)
	{
		cin >> a[1][1];
		cout << a[1][1] << endl;
		return 0;
	}

	//读取输入
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin >> a[i][j];

	int direction = -1;

	//对角线输出，横纵坐标和的范围是（1+1 ---- n+n）
	for(int i=2;i<=2*n;i++)
	{
		//中线及前半部分
		if(i<= n+1)			
		{
			//每个对角线的横坐标 范围是（1 -- i-1）
			for(int j=1;j<=i-1;j++)
			{
				if(direction > 0)
					cout << a[j][i-j] << " ";
				else
					cout << a[i-j][j] << " ";
			}
		}
		//后半部分
		else
		{
			//每个对角线的横坐标 范围是（i-n -- n）
			for(int j=n;j>=i-n;j--)
			{
				if(direction > 0)
					cout << a[i-j][j] << " ";
				else
					cout << a[j][i-j] << " ";
			}
		}
		direction = direction * (-1);
	}
	cout << endl;
	return 0;
}