#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//fstream fcin("input.txt");
	int value[40][40];
	int result[40][40];
	int n=0;
	int m=0;
	cin >> n >> m;
	//���� ע��һ��Ҫ��ʼ��result,��Ϊ��ͬ�������ĳ�ʼֵ��ͬ������ɲ���Ҫ�Ĵ���
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> value[i][j];
			result[i][j] = value[i][j];
		}
	}
	//����ʱ��ı����ƽ�
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int k = j+1;			//��
			while(value[i][k] == value[i][j] && k<=m)
				k++;
			k--;
			if( k-j+1 >=3)
			{
				for(int l=j;l<=k;l++)
					result[i][l] = 0;
			}

			k = i+1;				//��
			while(value[i][j] == value[k][j] && k<=n)
				k++;
			k--;
			if(k-i+1 >=3)
			{
				for(int l=i;l<=k;l++)
					result[l][j] = 0;
			}
		}
	}
	//�������������ԭ������ ����ͬʱ���������������˲�����ֱ����ԭͼ���޸�
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(result[i][j] !=0)
				result[i][j] = value[i][j];
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}