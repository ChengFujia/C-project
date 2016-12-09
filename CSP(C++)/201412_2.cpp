#include <iostream>
#include <cstring>
using namespace std;

int a[505][505];
int main()
{
	int n;
	cin >> n;
	
	//�������� ֱ�����
	if(n==1)
	{
		cin >> a[1][1];
		cout << a[1][1] << endl;
		return 0;
	}

	//��ȡ����
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin >> a[i][j];

	int direction = -1;

	//�Խ����������������͵ķ�Χ�ǣ�1+1 ---- n+n��
	for(int i=2;i<=2*n;i++)
	{
		//���߼�ǰ�벿��
		if(i<= n+1)			
		{
			//ÿ���Խ��ߵĺ����� ��Χ�ǣ�1 -- i-1��
			for(int j=1;j<=i-1;j++)
			{
				if(direction > 0)
					cout << a[j][i-j] << " ";
				else
					cout << a[i-j][j] << " ";
			}
		}
		//��벿��
		else
		{
			//ÿ���Խ��ߵĺ����� ��Χ�ǣ�i-n -- n��
			for(int j=n;j>=i-n;j--)
			{
				if(direction > 0)
					cout << a[i-j][j] << " ";
				else
					cout << a[j][i-j] << " ";
			}
		}
		direction = direction * (-1);
	}
	cout << endl;
	return 0;
}