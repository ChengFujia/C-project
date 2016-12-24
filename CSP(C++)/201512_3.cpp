#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//注意一定要严格大于最大值（一般的测试用例都会有极端的测试）
char map[105][105];	
//四个方向（上下左右）
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int m,n;

//划线段时给定的可能是从右到左/从上到下，但是程序实现必须是从小到大
//因此我们判断大小关系，必要时进行调整
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

//对于填充指令，采用递归的想法（超级巧妙）
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
            //只有当前点是小写或大写字母或者是'.'才可以写  
            if((map[x][y]>='a'&&map[x][y]<='z')||(map[x][y]>='A'&&map[x][y]<='Z')||map[x][y]=='.')  
                cover(x,y,ch);  
        } 
	}
}

int main()
{
	//ifstream input("demo1.txt");
	memset(map,'.',sizeof(map));		//因为char只有1位，可以直接这么初始化
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

	//输出时要注意，我们的（0，0）在左下角，因此输出时y轴是从大到小
	for(int yy=n-1;yy>=0;yy--)
	{
		for(int xx=0;xx<=m-1;xx++)
			cout << map[xx][yy];
		cout << endl;
	}
	return 0;
}