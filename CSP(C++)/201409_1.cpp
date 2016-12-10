#include <iostream>
using namespace std;

int a[1005];
int b[1005];

int main()
{
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	
	int count = 0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(b[j] == a[i] + 1)
			{
				count++;
				break;
			}
		}
	}
	cout << count << endl;
	return 0;
}