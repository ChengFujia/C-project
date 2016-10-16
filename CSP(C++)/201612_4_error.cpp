#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Path			//�洢һ��·��
{
	int fromID;		//�ص�a,����������յ�
	int toID;		//�ص�b,����������յ�
	int distance;	//��������

	Path(int a ,int b ,int c)	//��ʾ���캯��
	{
		fromID = a;
		toID = b;
		distance = c;
	}
};

int match(Path a,int b)	//ָ���е�·����˫��·����������from��to
{
	//��ƥ�䣬������һ���ص㣻���򣬷���0
	if(b==a.fromID)
		return a.toID;
	else if( b==a.toID)
		return a.fromID;
	else
		return 0;
}

bool isInSet(vector<int> goStraightCity,int cityNumber)		//�鿴ĳ���е���̾����Ƿ��Ѿ�������ɣ�1done��0not
{
	for(int i=0;i<goStraightCity.size();i++)
	{
		if(cityNumber==goStraightCity[i])
			return 1;
	}
	return 0;
}

int sDistance=1001;				//��̾���
vector<Path> handlerPathSet;	//��̾���·������
vector<Path> sDistanceSet;		//��̾��뼯��
vector<int> goStraightCity;		//���׶�ֱ��ĳ����б�

int handler(vector<Path> map,int numCity,int numPath)
{
	for(int j=0;j<numPath;j++)		//��һ���1-nֱ��Ķ�������
	{
		if(match(map[j],1))
		{
			handlerPathSet.push_back(map[j]);
			sDistanceSet.push_back(map[j]);
			goStraightCity.push_back(match(map[j],1));
		}
	}
	
	for(int i=2;i<=numCity;i++)		//�ڶ��鴦���ֱ���,������
	{
		if(!isInSet(goStraightCity,i))		//��[2��numCity]��ɾѡ��û�м����i
		{
			int tempdistance=1001;
			int tempID = 0;
			int tempCity = 0;
			for(int j=0;j<numPath;j++)		//��map��Ѱ�Ҵ���i��·��
			{
				if(match(map[j],i) && isInSet(goStraightCity ,match(map[j],i)))
				{
					cout << "4ƥ���ָ�" << match(map[j],i) << endl;
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