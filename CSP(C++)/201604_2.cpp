#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	//ifstream fcin("input.txt");
	int pic[15][10];		//整个图（15行10列）
	int oneHighest[10] = {15,15,15,15,15,15,15,15,15,15};	//存储每一列的最高点，默认为15（0-14），就是地图下面
	int oneInModel[4][2];	//模块中1位置（4个，分别存储(y1,x1)...(y3,x3)）
	int oneValue=0;			//读取模块中小方块的值
	int oneNum=0;			//读取模块中1的值（第几个1，对应oneModel的行数）
	int leftestModel = 3;	//默认的最左模块 x->从左到右 0->3
	int downestModel = 0;	//默认的最下模块 y->从上到下 0->3
	int leftLoc=0;			//用来读取模块放置的列数/位置
	int lineNum=1;			//用来读取输入的行数 1- 20
	string line;
	while(getline(cin,line)&&lineNum<21)
	{
		istringstream scin(line);
		//读取整个图 并存储
		if(lineNum>=1&&lineNum<=15)
		{
			for(int i=0;i<10;i++)
			{
				scin >> pic[lineNum-1][i];
				// 读取图中每一列的最高点 tips:读取是从上到下，因此只需做一次
				if(pic[lineNum-1][i]==1&&oneHighest[i]==15)
					oneHighest[i] = lineNum - 1;
			}
		}
		//读取模块 并存储1的位置
		else if(lineNum>=16&&lineNum<=19)
		{
			for(int i=0;i<4;i++)
			{
				scin >> oneValue;
				if (oneValue==1)
				{
					oneInModel[oneNum][0]= lineNum - 16;	
					oneInModel[oneNum][1]= i;
					//找到模块 中最左（x最小）最下（y最大）的一个小方块，用来求偏移量（相对位置）
					leftestModel = (oneInModel[oneNum][1] <=leftestModel) ? oneInModel[oneNum][1] : leftestModel;
					downestModel = (oneInModel[oneNum][0] >=downestModel) ? oneInModel[oneNum][0] : downestModel;
					oneNum++;
				}
			}
		}
		else if(lineNum == 20)
			scin >> leftLoc;
		lineNum++;
	}

	int x_piancha = leftLoc - 1;			//x偏移量
	for (int k=14;k>=0;k--)
	{
		int y_piancha = k - downestModel;	//y偏移量
		int m;
		for (m=0;m<4;m++)
		{
			int yy = oneInModel[m][0]+y_piancha;
			int xx = oneInModel[m][1]+x_piancha;
			//若对应位置值为1 或者 从中间插入 直接退出
			if (pic[yy][xx]==1||yy>oneHighest[xx])
				break;
		}
		//用m作为一个标识位 若正常结束，说明已经找到位置
		//赋值 并准备输出
		if (m==4)
		{
			pic[oneInModel[0][0]+y_piancha][oneInModel[0][1]+x_piancha]=1;
			pic[oneInModel[1][0]+y_piancha][oneInModel[1][1]+x_piancha]=1;
			pic[oneInModel[2][0]+y_piancha][oneInModel[2][1]+x_piancha]=1;
			pic[oneInModel[3][0]+y_piancha][oneInModel[3][1]+x_piancha]=1;
			break;
		}
	}

	//按照规定格式输出
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout << pic[i][j]<<" ";
		}
			cout << endl;
	}
	
	//fcin.close();
	return 0;
}