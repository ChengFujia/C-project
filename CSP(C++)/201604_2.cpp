#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	//ifstream fcin("input.txt");
	int pic[15][10];		//����ͼ��15��10�У�
	int oneHighest[10] = {15,15,15,15,15,15,15,15,15,15};	//�洢ÿһ�е���ߵ㣬Ĭ��Ϊ15��0-14�������ǵ�ͼ����
	int oneInModel[4][2];	//ģ����1λ�ã�4�����ֱ�洢(y1,x1)...(y3,x3)��
	int oneValue=0;			//��ȡģ����С�����ֵ
	int oneNum=0;			//��ȡģ����1��ֵ���ڼ���1����ӦoneModel��������
	int leftestModel = 3;	//Ĭ�ϵ�����ģ�� x->������ 0->3
	int downestModel = 0;	//Ĭ�ϵ�����ģ�� y->���ϵ��� 0->3
	int leftLoc=0;			//������ȡģ����õ�����/λ��
	int lineNum=1;			//������ȡ��������� 1- 20
	string line;
	while(getline(cin,line)&&lineNum<21)
	{
		istringstream scin(line);
		//��ȡ����ͼ ���洢
		if(lineNum>=1&&lineNum<=15)
		{
			for(int i=0;i<10;i++)
			{
				scin >> pic[lineNum-1][i];
				// ��ȡͼ��ÿһ�е���ߵ� tips:��ȡ�Ǵ��ϵ��£����ֻ����һ��
				if(pic[lineNum-1][i]==1&&oneHighest[i]==15)
					oneHighest[i] = lineNum - 1;
			}
		}
		//��ȡģ�� ���洢1��λ��
		else if(lineNum>=16&&lineNum<=19)
		{
			for(int i=0;i<4;i++)
			{
				scin >> oneValue;
				if (oneValue==1)
				{
					oneInModel[oneNum][0]= lineNum - 16;	
					oneInModel[oneNum][1]= i;
					//�ҵ�ģ�� ������x��С�����£�y��󣩵�һ��С���飬������ƫ���������λ�ã�
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

	int x_piancha = leftLoc - 1;			//xƫ����
	for (int k=14;k>=0;k--)
	{
		int y_piancha = k - downestModel;	//yƫ����
		int m;
		for (m=0;m<4;m++)
		{
			int yy = oneInModel[m][0]+y_piancha;
			int xx = oneInModel[m][1]+x_piancha;
			//����Ӧλ��ֵΪ1 ���� ���м���� ֱ���˳�
			if (pic[yy][xx]==1||yy>oneHighest[xx])
				break;
		}
		//��m��Ϊһ����ʶλ ������������˵���Ѿ��ҵ�λ��
		//��ֵ ��׼�����
		if (m==4)
		{
			pic[oneInModel[0][0]+y_piancha][oneInModel[0][1]+x_piancha]=1;
			pic[oneInModel[1][0]+y_piancha][oneInModel[1][1]+x_piancha]=1;
			pic[oneInModel[2][0]+y_piancha][oneInModel[2][1]+x_piancha]=1;
			pic[oneInModel[3][0]+y_piancha][oneInModel[3][1]+x_piancha]=1;
			break;
		}
	}

	//���չ涨��ʽ���
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