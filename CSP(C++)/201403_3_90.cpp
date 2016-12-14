#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

bool strIsLegal(string temp)
{
	for(int i=0;i<temp.size();i++)
	{
		if(temp[i]>=65 && temp[i]<=90)
			return false;
	}
	return true;
}

int main()
{
	//读入识别的选项，并存储类型（有参/无参）
	string str ;
	cin >> str ;
	map<char,string> xx;
	for(int i=0;i<str.size();i++)
	{
		if(str[i]!=':')
			xx[str[i]] = "1";
		else
			xx[str[i-1]] = ":";
	}

	int n;
	cin >> n;
	cin.ignore();			//没有这个的话 会少读入一条
	vector<map<string,string> > Output;	//存储处理后结果，一行一项

	//逐行读入待检测指令
	for(int i=1;i<=n;i++)
	{
		string line;
		getline(cin,line);
		istringstream scin(line);
		string temp;
		int count = 0;		//计列（第一个不要）
		map<string,string> lineOutput;	//存储每一行出来后选项及参数
		int wait = 0;		//读入有参选项后，设置等待标识
		string index = "";	//读入有参选项后，记录参数选项
		while(scin)
		{
			scin >> temp;
			if(count==0)
			{
				count++;
				continue;
			}

			if(strIsLegal(temp))	//如果temp是合法字符串（不含有小写字母/数字/- 之外的字符）
			{
				//判断是否为合法参数/选项
				if(temp[0]=='-' && wait==0)
				{
					if(xx[temp[1]]=="1")
						lineOutput[temp] = "NONE";
					else if(xx[temp[1]]==":")
					{
						index = temp;
						wait = 1;
					}
					else
						break;
				}
				//测试用例描述不清晰，哎。。。尴尬。。
				else if(temp[0]=='-' && wait == 1)
				{
					lineOutput[index] = temp;
					index = "";
					wait = 0;
				}
				else
					break;
			}
			else
				break;
		}
		Output.push_back(lineOutput);
	}
	
	//指定格式输出
	for(int k=0;k<=n-1;k++)
	{
		cout <<"Case " << k+1 << ": ";
		map<string,string>::iterator iter;
		string temp = "-a-b-c-d-e-f-g-h-i-j-k-l-m-n-o-p-q-r-s-t-u-v-w-x-y-z";
		for(int i=1;i<=26;i++)
		{
			string str = temp.substr(2*i-2,2);
			iter = Output[k].find(str);
			if(iter == Output[k].end())
				continue;
			else
			{
				if( iter->second == "NONE")
					cout << iter->first << " ";
				else
					cout << iter->first << " " << iter->second << " ";
			}
		}
		cout << endl;
		/*
		for(map<string,string>::iterator iter = Output[k].begin();iter != Output[k].end();iter++)
		{
			if( iter->second == "NONE")
				cout << iter->first << " ";
			else
				cout << iter->first << " " << iter->second << " ";
		}
		*/
	}
	
	return 0;
}