#include <iostream>
#include <cstring>
using namespace std;

int a[1001];
int main()
{
	memset(a,0,sizeof(a));
	int n,k;
	cin >> n >> k;
	for(int i=0;i<n;i++)
		cin >> a[i];

	int result = 0;
	int temp = 0;
	for(int i=0;i<n;i++)
	{
		temp += a[i];
		if(temp >= k)					//满足要求，人数加一
		{
			temp = 0;
			result ++;
		}
		else if(temp < k && i != n-1)	//非最后一个，继续
			continue;
		else							//最后一个，人数加一					
			result ++;
	}
	cout << result << endl;
	return 0;
}
