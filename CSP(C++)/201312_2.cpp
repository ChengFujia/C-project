#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	int result = 0;
	string temp;
	getline(cin,temp);
	int sum = 0;
	int count = 1;
	for(int i=0;i<11;i++)
	{
		if(temp[i] == '-')
			continue;
		else
		{
			sum += ( temp[i] - 48 ) * count;
			count++;
		}
	}
	result = sum % 11;
	
	//Judge
	if(result == temp[12]-48)
		cout << "Right" << endl;
	else if(result == 10 && temp[12] == 'X')
		cout << "Right" << endl;
	else
	{
		if(result == 10)
			temp[12] = 'X';
		else
			temp[12] = result + '0';
		cout << temp << endl;
	}
	return 0;
}