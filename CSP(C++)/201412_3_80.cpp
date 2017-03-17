#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Data
{
	float p;
	int s;
	Data()
	{
		p = 0.00;
		s = 0;
	}
	Data(float a,int b)
	{
		p = a;
		s = b;
	}
};


int main()
{
	//ifstream input("demo.txt");	
	Data sell[5005],buy[5005];
	float startPrices[5005];
	bool cancel[5005];
	for(int i=0;i<5005;i++)
	{
		sell[i] = Data();
		buy[i] = Data();
		startPrices[i] = 0.00;
		cancel[i] = false;
	}
	
	int line = 1;
	string l;
	
	//while(getline(input,l))
	while(getline(cin,l))
	{
		istringstream scin(l);	
		string c;		//command 指令
		scin >> c;
		if(c == "cancel")
		{
			int num;
			scin >> num;
			sell[num] = Data();
			buy[num] = Data();
			startPrices[num] = 0.00;
			cancel[num] = true;
			line++;
		}
		else
		{
			float p;
			int s;
			scin >> p >> s;
			if(c == "buy" && cancel[line] == false)
				buy[line] = Data(p,s);
			else if(c == "sell" && cancel[line] == false)
				sell[line] = Data(p,s);
			startPrices[line] = p; 
			line++;
		}
	}

	Data deal = Data();			//用来存储结果
	for(int i=1;i<=line;i++)		//针对每一个准备测试的开盘价
	{
		int buy_sum =0;
		int sell_sum = 0;
		int min = 0;
		for(int j=1;j<=line;j++)
		{ 
			if(buy[j].p>=startPrices[i])
				buy_sum += buy[j].s;
			if(sell[j].p<=startPrices[i])
				sell_sum += sell[j].s;
		}
		
		if(buy_sum < sell_sum)
			min = buy_sum;
		else
			min = sell_sum;
		
		if(min > deal.s)
			deal = Data(startPrices[i],min);
		else if(min == deal.s)				//成交量相同时，选开盘价高的（50到80分）
			deal = (startPrices[i] > deal.p) ? Data(startPrices[i],min) : Data(deal.p,min) ;
	}

	//fixed用来设置为定点小数字（小数点不动，使精度代表后面的小数位数），否则的话精度是整+小的位数
	cout << fixed << setprecision(2) << deal.p << " " ;
	//cout.unsetf(ios::fixed); //可以去掉fixed
	//cout.precision(6);	//也可以设置
	cout << deal.s << endl;
	
	return 0;
}