#include <iostream>
using namespace std;

int a[105][105];

int main()
{
	int n;
	cin >> n;
	int x1,y1,x2,y2;
	int count = 0;
	for(int i=1;i<=n;i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		//��һ�����ε� ���϶������һ�����Σ�1��1��--> ��100��100��
		for(int x=x1+1;x<=x2;x++)
		{
			for(int y=y1+1;y<=y2;y++)
			{
				//����һ�� ���ı�־λ������
				if(a[x][y] != 1)
				{
					count++;
					a[x][y] = 1;
				}
			}
		}
	}
	cout << count << endl;
	return 0;
}