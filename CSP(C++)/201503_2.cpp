#include<iostream>
#include <cstring>
using namespace std;

int a[1005];
int main()
{
	//memset(a,0,sizeof(int)*1005)
	memset(a,0,sizeof(a));	//memset�����ֽ���գ���˳�ʼ��������ʱֻ����-1 ���� 0
    int n;
    cin >> n ;

	//�����±���� ���֣�ֵ�������
	int temp = 0;
	for(int i=0;i<n;i++)
	{
		cin >> temp;
		a[temp]++;
	}

	//��Ȧѭ���� ����ֵ�������С
	for(int j=1004;j>0;j--)
	{
		//��Ȧ ѭ���Ǳ�������Ԫ��
		for(int k=0;k<1005;k++)
		{
			//��������ľ���� ��С���� ǡ������
			if(a[k] == j)
				cout << k << " " << j << endl;
		}
	}
  
    return 0;
}
