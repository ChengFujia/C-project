#include <iostream>
#include <cstring>
using namespace std;

int h[1005];
int main()
{
	memset(h,0,sizeof(h));
	int n;
	cin >> n;
	int high = 0;	//��¼���ֵ
	for(int i=1;i<=n;i++)
	{
		cin >> h[i];
		high = ( h[i] >= high ) ? h[i] : high;
	}

	int max = 0;	//��¼���������
	for(int j=1;j<=high;j++)
	{
		int temp = 0;	//��¼��ʱֵ����Ϊÿ��ѭ���в�����������������
		//y������ ��С��������ɨ��
		for(int k=1;k<=n;k++)
		{
			if(h[k] >= j)
				temp += j;
			//���жϣ����¼��㣬��¼��ǰ��ʱ������
			else		
			{
				max = ( max >= temp ) ? max : temp;
				temp = 0;
			}
			//��¼���һ��ֵ����Ϊ���һ��ֵû�о���else����δ����
			if(k == n)
				max = ( max >= temp ) ? max : temp;
		}
	}
	cout << max << endl;
	return 0;
}