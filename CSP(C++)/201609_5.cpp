#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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

bool compare(Points a,Points b)
{
	return a.list.size() < b.list.size();
}

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
	//ifstream input("demo.txt");
	//input >> num >> mode;
	cin >> num >> mode;

	int count=0;
	int x0,y0;
	int temp_same = 0;
	while(count<num)
	{
		vector<int> temp_lists_x;
		vector<int> temp_lists_y;
		//input >> x0 >> y0;
		cin >> x0 >> y0;
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

	int x_size = x.size();
	int y_size = y.size();
	for(int a=0;a<x_size-1;a++)
		sort(x[a].list.begin(),x[a].list.end());
	for(int b=0;b<y_size-1;b++)
		sort(y[b].list.begin(),y[b].list.end());
	sort(x.begin(),x.end(),compare);
	sort(y.begin(),y.end(),compare);

	int numOfNet =0;
	int numOfNetest = 0;
	vector<int> numOfPoint(100,0);

	for(int i=x_size-1;i>=0;i--)
	{
		Points x_temp = Points(x[i].same,x[i].list);
		int len_x_temp = x_temp.list.size();
		if (len_x_temp < 2*numOfNetest)
			break;
		for(int j=y_size-1;j>=0;j--)
		{
			Points y_temp = Points(y[j].same,y[j].list);
			int len_y_temp = y_temp.list.size();
			if (len_y_temp < 2*numOfNetest)
				break;
			if(x_temp.same <= y_temp.list[0] || x_temp.same >= y_temp.list[len_y_temp-1])
					continue;
			else
			{
				for(int k=0;k<len_y_temp-1;k++)
				{
					//不一定非要前少后多，反过来也可以
					if(x_temp.same>y_temp.list[k] && x_temp.same<y_temp.list[k+1])
					{
						numOfNet = len_y_temp-1-k>=k+1 ? k+1 :len_y_temp-1-k ;
						break;
					}
				}

				if(y_temp.same <= x_temp.list[0] || y_temp.same >= x_temp.list[len_x_temp-1] || numOfNet < numOfNetest)
					continue;
				else
				{
					for(int k=0;k<len_x_temp-1;k++)
					{
						if(y_temp.same>x_temp.list[k] && y_temp.same<x_temp.list[k+1])
						{
							int temp = len_y_temp-1-k>=k+1 ? k+1 :len_y_temp-1-k ;
							numOfNet = temp<numOfNet ? temp : numOfNet;
							numOfNetest = numOfNetest<numOfNet ? numOfNet : numOfNetest;
							numOfPoint[numOfNetest]++;
							break;
						}
					}
				}
			}
		}
	}
	if (mode==1)
		cout << numOfNetest << endl;
	if (mode==2)
		cout << numOfPoint[numOfNetest] << endl;
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