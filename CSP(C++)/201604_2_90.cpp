#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	//ifstream fcin("input.txt");
	int pic[15][10];
	int oneHighest[10] = {15,15,15,15,15,15,15,15,15,15};
	int oneInModel[4][2];
	int oneValue=0;
	int oneNum=0;
	int leftLoc=0;
	int lineNum=1;
	int leftestModel = 3;	//x
	int downestModel = 0;	//y
	string line;
	while(getline(cin,line)&&lineNum<21)
	{
		istringstream scin(line);
		if(lineNum>=1&&lineNum<=15)
		{
			for(int i=0;i<10;i++)
			{
				scin >> pic[lineNum-1][i];
				if(pic[lineNum-1][i]==1&&oneHighest[i]==15)
					oneHighest[i] = lineNum - 1;
			}
		}
		else if(lineNum>=16&&lineNum<=19)
		{
			for(int i=0;i<4;i++)
			{
				scin >> oneValue;
				if (oneValue==1)
				{
					oneInModel[oneNum][0]= lineNum - 16;	
					oneInModel[oneNum][1]= i;				
					oneNum++;
					leftestModel = oneInModel[oneNum][1] ? (oneInModel[oneNum][0] < leftestModel) : leftestModel;
					downestModel = oneInModel[oneNum][0] ? (oneInModel[oneNum][1] > downestModel) : downestModel;
				}
			}
		}
		else
			scin >> leftLoc;
		lineNum++;
	}

	int x_piancha = leftLoc - 1;
	for (int k=14;k>0;k--)
	{
		int y_piancha = k - leftestModel;
		int m;
		for (m=0;m<4;m++)
		{
			int yy = oneInModel[m][0]+y_piancha;
			int xx = oneInModel[m][1]+x_piancha;
			if (pic[yy][xx]==1||yy>oneHighest[xx])
				break;
		}
		if (m==4)
		{
			pic[oneInModel[0][0]+y_piancha][oneInModel[0][1]+x_piancha]=1;
			pic[oneInModel[1][0]+y_piancha][oneInModel[1][1]+x_piancha]=1;
			pic[oneInModel[2][0]+y_piancha][oneInModel[2][1]+x_piancha]=1;
			pic[oneInModel[3][0]+y_piancha][oneInModel[3][1]+x_piancha]=1;
			
			for(int i=0;i<15;i++)
			{
				for(int j=0;j<10;j++)
				{
					cout << pic[i][j] ;
					if(j!=9)
						cout << " ";
				}
				cout << endl;
			}
	
			//fcin.close();
			return 0;
		}
	}
}