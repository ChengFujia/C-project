#include <iostream>
#include <cstring>
using namespace std;

int h[1005];
int main()
{
	memset(h,0,sizeof(h));
	int n;
	cin >> n;
	int high = 0;	//记录最高值
	for(int i=1;i<=n;i++)
	{
		cin >> h[i];
		high = ( h[i] >= high ) ? h[i] : high;
	}

	int max = 0;	//记录最大矩形面积
	for(int j=1;j<=high;j++)
	{
		int temp = 0;	//记录临时值，因为每轮循环中不会跳出，继续计算
		//y方向上 从小到大，依次扫描
		for(int k=1;k<=n;k++)
		{
			if(h[k] >= j)
				temp += j;
			//若中断，重新计算，记录当前临时最大面积
			else		
			{
				max = ( max >= temp ) ? max : temp;
				temp = 0;
			}
			//记录最后一个值，因为最后一个值没有经历else，从未保存
			if(k == n)
				max = ( max >= temp ) ? max : temp;
		}
	}
	cout << max << endl;
	return 0;
}