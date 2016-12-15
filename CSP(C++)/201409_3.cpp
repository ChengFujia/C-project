#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

string toLower(string temp)
{
	string result = "";
	for(int i=0;i<temp.size();i++)
	{
		if(temp[i]>='a' && temp[i]<='z')
			result += temp[i];
		else
			result += temp[i]+32;
	}
	return result;
}
int main()
{
	string S;
	cin >> S;
	int a;
	cin >> a;
	int num;
	cin >> num;
	vector<string> input;
	string temp;
	for(int i=0;i<num;i++)
	{
		cin >> temp;
		input.push_back(temp);
	}

	//handler
	if(a == 1)
	{
		for(int i=0;i<num;i++)
		{
			if(input[i].find(S) != -1)
				cout << input[i] << endl;
		}
	}
	else if(a==0)
	{
		string s = toLower(S);
		string ttemp;
		for(int i=0;i<num;i++)
		{
			ttemp = toLower(input[i]);
			if(ttemp.find(s) != -1)
				cout << input[i] << endl;
		}
	}
	else
		return 1;
	return 0;
}