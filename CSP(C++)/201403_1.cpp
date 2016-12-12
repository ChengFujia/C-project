#include <iostream>
using namespace std;

int a[1005];
int b[1005];
int main()
{
	int N;
	cin >> N;
	int temp = 0;
	for(int i=1;i<=N;i++)
	{
		cin >> temp;
		if(temp > 0)
			a[temp] = 1;
		else
		{
			temp = temp * (-1);
			b[temp] = 1;
		}
	}
	
	int count = 0;
	for(int i=1;i<=1000;i++)
	{
		if(a[i]==1 && b[i]==1)
			count++;
	}
	cout << count << endl;
	return 0;
}