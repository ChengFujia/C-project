#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Path			//存储一条路径
{
	int fromID;		//地点a,不区分起点终点
	int toID;		//地点b,不区分起点终点
	int distance;	//两点间距离

	Path(int a ,int b ,int c)	//显示构造函数
	{
		fromID = a;
		toID = b;
		distance = c;
	}
};

int match(Path a,int b)	//指令中的路径是双向路径，不区分from和to
{
	//若匹配，返回另一个地点；否则，返回0
	if(b==a.fromID)
		return a.toID;
	else if( b==a.toID)
		return a.fromID;
	else
		return 0;
}

bool isInSet(vector<int> goStraightCity,int cityNumber)		//查看某城市的最短距离是否已经计算完成，1done，0not
{
	for(int i=0;i<goStraightCity.size();i++)
	{
		if(cityNumber==goStraightCity[i])
			return 1;
	}
	return 0;
}

int sDistance=1001;				//最短距离
vector<Path> handlerPathSet;	//最短距离路径集合
vector<Path> sDistanceSet;		//最短距离集合
vector<int> goStraightCity;		//从首都直达的城市列表

int handler(vector<Path> map,int numCity,int numPath)
{
	for(int j=0;j<numPath;j++)		//第一遍把1-n直达的都存下来
	{
		if(match(map[j],1))
		{
			handlerPathSet.push_back(map[j]);
			sDistanceSet.push_back(map[j]);
			goStraightCity.push_back(match(map[j],1));
		}
	}
	
	for(int i=2;i<=numCity;i++)		//第二遍处理非直达的,倒序处理
	{
		if(!isInSet(goStraightCity,i))		//从[2，numCity]中删选还没有计算的i
		{
			int tempdistance=1001;
			int tempID = 0;
			int tempCity = 0;
			for(int j=0;j<numPath;j++)		//从map中寻找带有i的路径
			{
				if(match(map[j],i) && isInSet(goStraightCity ,match(map[j],i)))
				{
					cout << "4匹配的指令：" << match(map[j],i) << endl;
					for(int k=0; k < sDistanceSet.size();k++)
					{
						if(match(sDistanceSet[k],match(map[j],i)))
						{
							if(sDistance >= map[j].distance +  sDistanceSet[k].distance)
							{
								sDistance = map[j].distance +  sDistanceSet[k].distance;
								if(tempdistance > map[j].distance)
								{
									tempdistance = map[j].distance ;
									tempID = j;
									tempCity = i ;
								}
								break;
							}
						}
					}
				}
			}
			handlerPathSet.push_back(map[tempID]);
			sDistanceSet.push_back(Path(1,tempCity,sDistance));	
			goStraightCity.push_back(i);
			sDistance = 1001;
		}
	}
	return 0;
}

int main()
{
	int numCity,numPath;
	cin >> numCity >> numPath;
	vector<Path> map;
	int count=0;
	string line;
	int arg1,arg2,arg3;
	while(getline(cin,line))
	{
		istringstream path(line);
		count++;
		path >> arg1 >> arg2 >> arg3;
		if(count>1)
			map.push_back(Path(arg1,arg2,arg3));
		if(count==numPath+1)
			break;
	}
	handler(map,numCity,numPath);
	int resultDistance = 0;

	//cout << "Result :"<<endl;
	for(int i=0;i<handlerPathSet.size();i++)
	{
		//cout<<handlerPathSet[i].fromID<<" "<<handlerPathSet[i].toID<<" "<<handlerPathSet[i].distance<<endl;
		resultDistance += handlerPathSet[i].distance;
	}

	cout << resultDistance << endl;

	//for(int m =0;m<goStraightCity.size();m++)
	//	cout << goStraightCity[m]<< " ";
	/*
	for(int i=0;i<sDistanceSet.size();i++)
	{
		cout<<sDistanceSet[i].fromID<<" "<<sDistanceSet[i].toID<<" "<<sDistanceSet[i].distance<<endl;
	}
	*/
	return 0;
}