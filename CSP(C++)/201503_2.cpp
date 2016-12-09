#include<iostream>
#include <cstring>
using namespace std;

int a[1005];
int main()
{
	//memset(a,0,sizeof(int)*1005)
	memset(a,0,sizeof(a));	//memset是逐字节清空，因此初始数字数组时只能是-1 或者 0
    int n;
    cin >> n ;

	//数组下标代表 数字，值代表次数
	int temp = 0;
	for(int i=0;i<n;i++)
	{
		cin >> temp;
		a[temp]++;
	}

	//外圈循环是 从数值的最大到最小
	for(int j=1004;j>0;j--)
	{
		//内圈 循环是遍历数组元素
		for(int k=0;k<1005;k++)
		{
			//遇到满足的就输出 从小到大 恰好满足
			if(a[k] == j)
				cout << k << " " << j << endl;
		}
	}
  
    return 0;
}
