#include <iostream>
using namespace std;

int a[11][4];   //store N
int sx[11];	//store squence
int b[10][2];	//store M

int main()
{
	
	int N,M;
	cin >> N >> M;
	for(int i=1;i<=N;i++)
	{
		cin >> a[i][0] >> a[i][1] >> a[i][2] >>	a[i][3];
		sx[i] = i;
	}
	
	for(int j=0;j<M;j++)
		cin >> b[j][0] >> b[j][1];

	// Handlering Process
	for(int j=0;j<M;j++)
	{
		int signal = 0;
		for(int begin=N;begin>=1;begin--)	// search in sx
		{
			if(b[j][0]>=a[sx[begin]][0] && b[j][0]<=a[sx[begin]][2] && b[j][1]>=a[sx[begin]][1] && b[j][1]<=a[sx[begin]][3])
			{
				cout << sx[begin] << endl;
				int temp = sx[begin];
				for(int i=begin;i<N;i++)
					sx[i] = sx[i+1];
				sx[N] = temp;
				signal = 1;
				break;
			}
		}
		if(signal == 0)
			cout << "IGNORED" << endl;
	}
	return 0;
}
