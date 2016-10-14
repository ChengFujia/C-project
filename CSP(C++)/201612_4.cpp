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
	for(int i=0;i<numPath;i++)
	{
		cout<<map[i].fromID<<" "<<map[i].toID<<" "<<map[i].distance<<endl;
	}
	return 0;
}