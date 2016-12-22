#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

char map[100][100];
int main()
{
	ifstream input("demo2.txt");
	memset(map,0,sizeof(map));
	int m,n;
	//cin >> m >> n;
	input >> m >> n;
	for(int x=0;x<m;x++)
		for(int y=0;y<n;y++)
			map[x][y] = '.';
	int p;
	//cin >> p;
	input >> p;
	for(int count=1;count<=p;count++)
	{
		int cmd;
		//cin >> cmd;
		input >> cmd;
		if(cmd==0)
		{
			int x1,x2,y1,y2;
			//cin >> x1 >> y1 >> x2 >> y2;
			input >> x1 >> y1 >> x2 >> y2;
			if(x1==x2)
			{
				for(int y=y1;y<=y2;y++)
				{
					if(map[x1][y] == '-')
						map[x1][y] = '+';
					else
						map[x1][y] = '-';
				}
			}
			else if(y1==y2)
			{
				for(int x=x1;x<=x2;x++)
				{
					if(map[x][y1] == '-')
						map[x][y1] = '+';
					else
						map[x][y1] = '-';
				}
			}
			else
				break;
		}
		else if(cmd == 1)
		{
			int a,b;
			//cin >> a>> b;
			input >> a>> b;
			char c;
			//cin >> c;
			input >> c;
			for(int x=a;x<m;x++)
			{
				for(int y=b;y<n;y++)
				{
					if(map[x][y]!='-' && map[x][y]!='+')
						map[x][y] = c;
					else
						break;
				}
			}
		}
		else
			break;
	}

	for(int yy=n-1;yy>=0;yy--)
	{
		for(int xx=0;xx<=m-1;xx++)
			cout << map[xx][yy];
		cout << endl;
	}

	return 0;
}