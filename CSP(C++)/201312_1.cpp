#include <iostream>
#include <cstring>
using namespace std;

int a[10005];
int main()
{
	memset(a,0,sizeof(a));
	int n;
	cin >> n;
	int temp = 0;
	for(int i=1;i<=n;i++)
	{
		cin >> temp;
		a[temp]++;
	}

	int maxValue = 0;
	int maxIndex = 10004;
	for(int i=1;i<=10000;i++)
	{
		if(a[i]>maxValue)
		{
			maxValue = a[i];
			maxIndex = i;
		}
		else if(a[i] == maxValue)
			maxIndex = (i<maxIndex) ? i : maxIndex;
	}
	cout << maxIndex << endl;
	return 0;
}