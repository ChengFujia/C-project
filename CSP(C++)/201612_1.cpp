#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int main()
{
	int num;
	int absGap =0;	//��󲨶��������������ݵĲ�ľ���ֵ��
	cin >> num;
	int stockData;
	vector<int> stockDatas;	//Ԥ�Ȳ�֪������ʱ����ʹ��vector��������
	while(cin>>stockData)
	{
		stockDatas.push_back(stockData);
		//����ָ����Ŀ��Ҫ����ȥ,�������������Ч�ģ����Լ������뵫��δ���뵽vector��
		if (stockDatas.size() == num)	
			break;
	}
	//�Ӻ���ǰ
	for(int i=num-2;i>=0;i--)
	{
		if (absGap < abs(stockData-stockDatas[i]))
			absGap = abs(stockData-stockDatas[i]);
		stockData = stockDatas[i];
	}
	cout << absGap << endl;
	return 0;
}