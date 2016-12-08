#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n=0;
	int m=0;
	cin >> n;
	cin	>> m;

	vector<int> nm;
	int temp = 0;
	for(int ci=0;ci < n*m ;ci++)
	{
		cin >> temp;
		nm.push_back(temp);
	}

	for(int max=m-1;max>=0;max--)
	{
		for(int num = 0; num<nm.size(); num++)
		{
			if(num%m == max)
				cout << nm[num] << " ";
		}
		cout << endl;
	}
	

	return 0;
}