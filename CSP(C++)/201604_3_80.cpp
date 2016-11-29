#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int num = 0;
	string curDir = "";
	vector<string> list;

	cin >> num;
	cin >> curDir;
	cin.ignore();
	for(int i=0;i<num;i++)
	{
		string line;
		getline(cin,line);
		int pos;

		if(line[0] != '/')
			line = curDir + "/" +line;
		if(line.size()==0)
			line = curDir;

		//除去多个/,保留1个
		while( (pos = line.find("//")) != -1)
		{
			int count = 2;
			while(line[pos+count]='/')
				count++;
			line.erase(pos,count-1);
		}

		//处理/../,除去../
		while( (pos=line.find("/../")) != -1)
		{
			if(pos==0)
				line.erase(pos+1,3);
			else
			{
				int spos;
				//从"/../"的前一个位置开始 从后向前 找到第一个'/',eg:/abc/../,只保留一个'/'
				spos = line.rfind("/",pos-1);
				line.erase(spos,pos-spos+1+2);
			}
		}

		//处理/./
		while( (pos=line.find("/./")) != -1)
			line.erase(pos+1,2);

		if(line.size()>1 && line[line.size()-1]=='/')
			line.erase(line.size()-1);

		list.push_back(line);
	}

	for(int j=0;j<num;j++)
		cout << list[j] << endl;

	return 0;
}