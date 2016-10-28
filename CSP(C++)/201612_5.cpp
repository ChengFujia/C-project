#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Points
{
	int same;
	vector<int> list;
	Points(int same1, vector<int> list1)
	{
		same = same1;
		list = list1;
	}
};

int findLoc(int a,vector<Points> b)
{
	for(int i=0;i < b.size();i++)
	{
		if(b[i].same == a)
			return i;
	}
	return -1;
}

//分别存储具有相同x y的水晶柱的集合
vector<Points> x,y;
int num,mode;

int readAndHandle()
{
	ifstream input("demo.txt");
	input >> num >> mode;

	//测试是否读入
	if(mode == 1)
		cout << "输出最大结界数"<<endl;
	else if(mode == 2)
		cout << "输出最佳方案数"<<endl;
	else
		cout << "错误模式，请重新输入："<<endl;

	int count=0;
	int x0,y0;
	int temp_same = 0;
	while(count<num)
	{
		vector<int> temp_lists_x;
		vector<int> temp_lists_y;
		input >> x0 >> y0;
		if(x.size()==0||findLoc(x0,x)==-1)
		{
			temp_lists_x.push_back(y0);
			x.push_back(Points(x0,temp_lists_x));
			
		}
		else
			x[findLoc(x0,x)].list.push_back(y0);

		if(y.size()==0||findLoc(y0,y)==-1)
		{
			temp_lists_y.push_back(x0);
			y.push_back(Points(y0,temp_lists_y));
		}
		else
			y[findLoc(y0,y)].list.push_back(x0);
		count++;
	}
	return 0;
}

int main()
{
	readAndHandle();
	
	/*
	cout << "x = " << endl;
	for(int i=0;i<x.size();i++)
	{
		cout << x[i].same << ": ";
		for(int k=0;k<x[i].list.size();k++)
			cout << x[i].list[k] << " ";
		cout << "\n";
	}
	cout << "*************************************\n";
	cout << "y = " << endl;
	for(int j=0;j<y.size();j++)
	{
		cout << y[j].same << ": " ;
		for(int s=0;s<y[j].list.size();s++)
			cout << y[j].list[s] << " ";
		cout << endl;
	}
	*/
	

	return 0;
}