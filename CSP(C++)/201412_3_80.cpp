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
		string c;		//command ָ��
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

	Data deal = Data();			//�����洢���
	for(int i=1;i<=line;i++)		//���ÿһ��׼�����ԵĿ��̼�
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
		else if(min == deal.s)				//�ɽ�����ͬʱ��ѡ���̼۸ߵģ�50��80�֣�
			deal = (startPrices[i] > deal.p) ? Data(startPrices[i],min) : Data(deal.p,min) ;
	}

	//fixed��������Ϊ����С���֣�С���㲻����ʹ���ȴ�������С��λ����������Ļ���������+С��λ��
	cout << fixed << setprecision(2) << deal.p << " " ;
	//cout.unsetf(ios::fixed); //����ȥ��fixed
	//cout.precision(6);	//Ҳ��������
	cout << deal.s << endl;
	
	return 0;
}