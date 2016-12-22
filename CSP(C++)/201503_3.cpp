#include <iostream>
using namespace std;

int ping_year[12] = {31,28,31,30,31,30,31,31,30,31,30,31};		
int run_year[12]  = {31,29,31,30,31,30,31,31,30,31,30,31};
int a,b,c;
int y_1,y_2;

bool isRun(int year)			
{
	return (year%400==0 || (year%4==0 && year%100!=0));
}

void output(int z)
{
	if(z<10)
		cout << "0" << z;
	else
		cout << z;
}

void handleEachyear(int year)
{
	int day_1_1;
	int temp = 0;
	if(year == 1850)		//year年1月1日是 周day_1_1
		day_1_1 = 2;
	else
	{
		for(int i=1850;i<year;i++)
		{
			if(isRun(i))
				temp += 366;
			else
				temp += 365;
		}
		day_1_1 = (temp%7 + 2) % 7;
		if (day_1_1==0)
			day_1_1 = 7;
		temp = 0;
	}

	int day_a_1;
	if(a == 1)			//year年a月1日是 周day_a_1
		day_a_1 = day_1_1;
	else
	{
		for(int i=1;i<a;i++)
		{
			if(isRun(year))
				temp += run_year[i-1];
			else
				temp += ping_year[i-1];
		}
		day_a_1 = (day_1_1 + temp%7) % 7;
		if(day_a_1 == 0)
			day_a_1 = 7;
		temp = 0;
	}

	if(b == 1)
	{
		cout << year << "/" ;
		output(a);
		cout << "/" ;
		if(c==day_a_1)
			output(1);
		else if(c > day_a_1)
			output(c- day_a_1 + 1);
		else
			output(c+ 8 -day_a_1);
		cout << endl;
	}
	else
	{
		if ((c == day_a_1 && 1+(b-1)*7 <= ping_year[a-1] && !isRun(year)) || (c == day_a_1 && 1+(b-1)*7 <= run_year[a-1] && isRun(year)))
		{
			cout << year << "/" ;
			output(a);
			cout << "/" ;
			output(1+(b-1)*7);
			cout << endl;
		}
		else if ((c > day_a_1 && c- day_a_1 + 1+(b-1)*7 <= ping_year[a-1] && !isRun(year)) || (c > day_a_1 && c- day_a_1 + 1+(b-1)*7 <= run_year[a-1] && isRun(year)))
		{
			cout << year << "/" ;
			output(a);
			cout << "/" ;
			output( c- day_a_1 + 1+(b-1)*7);
			cout << endl;
		}
		else if ((c < day_a_1 &&c+ 8 -day_a_1+(b-1)*7 <= ping_year[a-1] && !isRun(year)) || (c < day_a_1 && c+ 8 -day_a_1+(b-1)*7 <= run_year[a-1] && isRun(year)))
		{
			cout << year << "/" ;
			output(a);
			cout << "/" ;
			output( c+ 8 -day_a_1+(b-1)*7);
			cout << endl;
		}
		else
			cout << "none" << endl;
	}
}

int main()
{
	cin >> a >> b >> c;
	cin >> y_1 >> y_2;
	
	for(int j=y_1;j<=y_2;j++)
		handleEachyear(j);

	return 0;
}