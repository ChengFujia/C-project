#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int a[1005];
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++)
		cin >> a[i];

	int signal = 0;		//��ʶ������ or ��������
	for(int i=0;i<n;i++)
	{
		int sthan = 0;	//����С���� ����
		int lthan = 0;	//��������� ����
		for(int j=0;j<n;j++)
		{
			if(a[i]>a[j])
				lthan++;
			else if(a[i]<a[j])
				sthan++;
			else
				continue;
		}
		//������������Ҳ����
		//���һ��ֻ��һ������
		//�������ֻ����ͬ����
		if(lthan == sthan)	
		{
			cout << a[i] << endl;
			signal = 1;
			break;
		}
	}

	if(signal == 0)
		cout << "-1" << endl;

	return 0;
}