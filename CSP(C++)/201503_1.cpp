#include<iostream>
using namespace std;

int a[1005][1005];	//��ô�������һ��Ҫ����Ϊȫ�ֱ������������main���������Ī�������

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 0;i <= n-1;i++)
    {
        for(int j = 0;j <= m-1;j++)   cin >> a[i][j];
    }
    for(int j = m-1;j >= 0;j--)
    {
        for(int i = 0;i <= n-1;i++)   cout << a[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
