#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int main()
{
	int num;
	int absGap =0;	//最大波动（相邻两个数据的差的绝对值）
	cin >> num;
	int stockData;
	vector<int> stockDatas;	//预先不知道长度时可以使用vector代替数组
	while(cin>>stockData)
	{
		stockDatas.push_back(stockData);
		//到了指定数目后要跳出去,后面的输入是无效的，可以继续输入但并未加入到vector中
		if (stockDatas.size() == num)	
			break;
	}
	//从后向前
	for(int i=num-2;i>=0;i--)
	{
		if (absGap < abs(stockData-stockDatas[i]))
			absGap = abs(stockData-stockDatas[i]);
		stockData = stockDatas[i];
	}
	cout << absGap << endl;
	return 0;
}