#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int num;
	cin >> num;
	int temp;
	vector<int> numbers;
	int i=0;
	while(cin)
	{
		if(i<num)
		{
			cin >> temp;
			numbers.push_back(temp);
			i++;
		}
		else
			break;
	}

	int result=0;
	for(int i=1;i<num;i++)
	{
		if(numbers[i]==numbers[i-1])
			continue;
		else
			result++;
	}
	result++;
	cout << result << endl;
	return 0;
}