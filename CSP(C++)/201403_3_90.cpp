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
	//����ʶ���ѡ����洢���ͣ��в�/�޲Σ�
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
	cin.ignore();			//û������Ļ� ���ٶ���һ��
	vector<map<string,string> > Output;	//�洢���������һ��һ��

	//���ж�������ָ��
	for(int i=1;i<=n;i++)
	{
		string line;
		getline(cin,line);
		istringstream scin(line);
		string temp;
		int count = 0;		//���У���һ����Ҫ��
		map<string,string> lineOutput;	//�洢ÿһ�г�����ѡ�����
		int wait = 0;		//�����в�ѡ������õȴ���ʶ
		string index = "";	//�����в�ѡ��󣬼�¼����ѡ��
		while(scin)
		{
			scin >> temp;
			if(count==0)
			{
				count++;
				continue;
			}

			if(strIsLegal(temp))	//���temp�ǺϷ��ַ�����������Сд��ĸ/����/- ֮����ַ���
			{
				//�ж��Ƿ�Ϊ�Ϸ�����/ѡ��
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
				//�������������������������������Ρ���
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
	
	//ָ����ʽ���
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