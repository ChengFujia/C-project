#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int record[1005];
	int output[1005];
	memset(record,0,sizeof(record));
	int temp;
	for(int i=0;i<=n-1;i++)
	{
		cin >> temp;
		record[temp]++;
		output[i] = record[temp];	
	}

	for(int i=0;i<n;i++)
		cout << output[i] << " ";
	cout << endl;
	return 0;
}