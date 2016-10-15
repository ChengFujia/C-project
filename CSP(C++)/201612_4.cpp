#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Path
{
	int fromID;
	int toID;
	int distance;

	Path(int a ,int b ,int c)
	{
		fromID = a;
		toID = b;
		distance = c;
	}
};

int match(Path a,int b)	//指令中的路径是双向路径，不区分from和to
{
	if(b==a.fromID)
		return a.toID;
	else if( b==a.toID)
		return a.fromID;
	else
		return 0;
}

bool isInSet(vector<int> goStraightCity,int cityNumber)
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
			cout << "匹配的记录："<< match(map[j],1) << endl;
			handlerPathSet.push_back(map[j]);
			sDistanceSet.push_back(map[j]);
			goStraightCity.push_back(match(map[j],1));
		}
	}
	
	for(int i=2;i<=numCity;i++)		//第二遍处理非直达的,倒序处理
	{
		if(!isInSet(goStraightCity,i))
		{
			int tempdistance=1001;
			int tempID = 0;
			int tempCity = 0;
			for(int j=0;j<numPath;j++)
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