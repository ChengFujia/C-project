#include <iostream>
#include <cstring>
using namespace std;

int a[1001];
int find_loc(int value,int n)
{
	// a[0]����ֵ
	for(int i=1;i<=n;i++)
		if(value == a[i])
			return i;
}

int main()
{
	memset(a,0,sizeof(a));
	int n,k;
	cin >> n >> k;

	for(int i=1;i<=n;i++)
		a[i] = i;

	// �߶��ߴ���
	int p,q;
	for(int j=1;j<=k;j++)
	{
		cin >> p >> q;
		int loc = find_loc(p,n);
		int temp = a[loc];
		if(q>0)
		{
			// >0,�������ǰ�ƶ�
			for(int s=0;s<q;s++)
				a[loc+s] = a[loc+s+1];
		}
		else
		{
			// <0,ǰ�������ƶ�
			for(int s=0;s>q;s--)
				a[loc+s] = a[loc+s-1];
		}
		a[loc+q] = temp;
	}

	for(int i=1;i<=n;i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
