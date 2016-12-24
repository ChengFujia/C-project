#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//ע��һ��Ҫ�ϸ�������ֵ��һ��Ĳ������������м��˵Ĳ��ԣ�
char map[105][105];	
//�ĸ������������ң�
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int m,n;

//���߶�ʱ�����Ŀ����Ǵ��ҵ���/���ϵ��£����ǳ���ʵ�ֱ����Ǵ�С����
//��������жϴ�С��ϵ����Ҫʱ���е���
void small(int &a,int &b)
{
	int temp;
	if(a<b)
		return;
	else
	{
		temp = a;
		a = b;
		b = temp;
	}
}

//�������ָ����õݹ���뷨���������
void cover(int a,int b,char ch)
{
	int x,y;
	map[a][b] = ch;
	for(int i=0;i<4;i++)
	{
		x = a + dir[i][0];
		y = b + dir[i][1];
		if(x<0||x>=m||y<0||y>=n)
			continue;
		if(map[x][y]!=ch)
		{  
            //ֻ�е�ǰ����Сд���д��ĸ������'.'�ſ���д  
            if((map[x][y]>='a'&&map[x][y]<='z')||(map[x][y]>='A'&&map[x][y]<='Z')||map[x][y]=='.')  
                cover(x,y,ch);  
        } 
	}
}

int main()
{
	//ifstream input("demo1.txt");
	memset(map,'.',sizeof(map));		//��Ϊcharֻ��1λ������ֱ����ô��ʼ��
	int p;
	cin >> m >> n >> p;
	//input >> m >> n >> p;
	
	for(int count=1;count<=p;count++)
	{
		int cmd;
		cin >> cmd;
		//input >> cmd;
		if(cmd==0)
		{
			int x1,x2,y1,y2;
			cin >> x1 >> y1 >> x2 >> y2;
			//input >> x1 >> y1 >> x2 >> y2;
			if(x1==x2)
			{
				small(y1,y2);
				for(int y=y1;y<=y2;y++)
				{
					if(map[x1][y] == '-')
						map[x1][y] = '+';
					else if((map[x1][y]>='a'&&map[x1][y]<='z')||(map[x1][y]>='A'&&map[x1][y]<='Z')||map[x1][y]=='.')
						map[x1][y] = '|';
					else if(map[x1][y]=='|')
						continue;
				}
			}
			else if(y1==y2)
			{
				small(x1,x2);
				for(int x=x1;x<=x2;x++)
				{
					if(map[x][y1] == '|')
						map[x][y1] = '+';
					else if((map[x][y1]>='a'&&map[x][y1]<='z')||(map[x][y1]>='A'&&map[x][y1]<='Z')||map[x][y1]=='.')
						map[x][y1] = '-';
					else if(map[x][y1]=='-')
						continue;
				}
			}
			else
				break;
		}
		else if(cmd == 1)
		{
			int a,b;
			char c;
			cin >> a>> b >> c;
			//input >> a>> b >> c;
			cover(a,b,c);
		}
		else
			break;
	}

	//���ʱҪע�⣬���ǵģ�0��0�������½ǣ�������ʱy���ǴӴ�С
	for(int yy=n-1;yy>=0;yy--)
	{
		for(int xx=0;xx<=m-1;xx++)
			cout << map[xx][yy];
		cout << endl;
	}
	return 0;
}