#include <iostream>
#include <cstring>
using namespace std;

int a[1001];
int main()
{
	memset(a,0,sizeof(a));
	int n,k;
	cin >> n >> k;
	for(int i=0;i<n;i++)
		cin >> a[i];

	int result = 0;
	int temp = 0;
	for(int i=0;i<n;i++)
	{
		temp += a[i];
		if(temp >= k)					//����Ҫ��������һ
		{
			temp = 0;
			result ++;
		}
		else if(temp < k && i != n-1)	//�����һ��������
			continue;
		else							//���һ����������һ					
			result ++;
	}
	cout << result << endl;
	return 0;
}
