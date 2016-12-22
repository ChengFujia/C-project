#include <iostream>
using namespace std;

bool isRun(int year)
{
	return (year%400==0 || (year%4==0 && year%100!=0));
}

void output(int a)
{
	if(a<10)
		cout << "0" << a;
	else
		cout << a;
}

void handleEachyear()
{

}

int main()
{
	int a,b,c;
	cin >> a >> b >> c;
	int y1,y2;
	cin >> y1 >> y2;
	int ping_year[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int run_year[12]  = {31,29,31,30,31,30,31,31,30,31,30,31};

	int day_1_1 = 0;
	int temp = 0;
	if(y1 == 1850)		//y1年1月1日是 周day_1_1
		day_1_1 = 2;
	else
	{
		for(int i=1850;i<y1;i++)
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

	int day_a_1 = 0;
	if(a == 1)			//y1年a月1日是 周day_a_1
		day_a_1 = day_1_1;
	else
	{
		for(int i=1;i<a;i++)
		{
			if(isRun(y1))
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
		cout << y1 << "/" ;
		output(a);
		cout << "/" ;
		if(c==day_a_1)
			output(1);
		else if(c > day_a_1)
			output(c- day_a_1 + 1);
		else
			output(day_a_1 + 8 - c);
		cout << endl;
	}
	else
	{
		if(b>5)
			cout << "none" << endl;
		else if ((c == day_a_1 && 1+(b-1)*7 <= ping_year[a-1] && !isRun(y1)) || (c == day_a_1 && 1+(b-1)*7 <= run_year[a-1] && isRun(y1)))
		{
			cout << y1 << "/" ;
			output(a);
			cout << "/" ;
			output(1+(b-1)*7);
			cout << endl;
		}
		else if ((c > day_a_1 && c- day_a_1 + 1+(b-1)*7 <= ping_year[a-1] && !isRun(y1)) || (c > day_a_1 && c- day_a_1 + 1+(b-1)*7 <= run_year[a-1] && isRun(y1)))
		{
			cout << y1 << "/" ;
			output(a);
			cout << "/" ;
			output( c- day_a_1 + 1+(b-1)*7);
			cout << endl;
		}
		else if ((c < day_a_1 &&day_a_1 + 8 - c+(b-1)*7 <= ping_year[a-1] && !isRun(y1)) || (c < day_a_1 && day_a_1 + 8 - c+(b-1)*7 <= run_year[a-1] && isRun(y1)))
		{
			cout << y1 << "/" ;
			output(a);
			cout << "/" ;
			output( day_a_1 + 8 - c+(b-1)*7);
			cout << endl;
		}
		else
			cout << "none" << endl;
	}

	

	return 0;
}