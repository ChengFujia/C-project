#include <iostream>
using namespace std;

bool Judge(int year)
{
	return (year%400==0 || (year%4==0 && year%100!=0));
}

int main()
{
	int year,num;
	int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	cin >> year >> num;
	if (Judge(year))
		days[1] = 29;
	//cin.ignore();
	int temp = 0;
	int i = 0;
	for(i=0;i<12;i++)
	{
		if(num > temp && num <= temp+days[i])
			break;
		temp += days[i];
	}
	cout << i + 1 << endl;
	cout << num - temp << endl;
	return 0;
}