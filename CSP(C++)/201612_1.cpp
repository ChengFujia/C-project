#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int a[1005];
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++)
		cin >> a[i];

	int signal = 0;		//标识是跳出 or 正常结束
	for(int i=0;i<n;i++)
	{
		int sthan = 0;	//比他小的数 个数
		int lthan = 0;	//比他大的数 个数
		for(int j=0;j<n;j++)
		{
			if(a[i]>a[j])
				lthan++;
			else if(a[i]<a[j])
				sthan++;
			else
				continue;
		}
		//两个都等于零也可以
		//情况一：只有一个数字
		//情况而：只有相同数字
		if(lthan == sthan)	
		{
			cout << a[i] << endl;
			signal = 1;
			break;
		}
	}

	if(signal == 0)
		cout << "-1" << endl;

	return 0;
}