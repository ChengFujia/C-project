#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> values;
	int numOfValues = 0;
	cin >> numOfValues ;
	int count = 0;
	int temp;
	while(cin && count<numOfValues)
	{
		cin >> temp;
		values.push_back(temp);
		count++;
	}
	int numOfShift = 0;
	for(int i=1;i<values.size()-1;i++)
	{
		if(((values[i]>values[i-1])&&(values[i]>values[i+1]))||((values[i]<values[i-1])&&(values[i]<values[i+1])))
			numOfShift++;
	}
	cout << numOfShift << endl;
	return 0;
}