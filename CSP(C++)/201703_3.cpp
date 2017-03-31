#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 处理标题
string handle_heading(string line)
{
	int num = 48;							//0的ascii码，这里采用数字，方便后面（数字+数字=数字，而不是字符+数字=字符）
	int length = line.size();
	string result = "<h";
	for(int i=0;i<length;i++)
	{
		if(line[i]=='#')			//开头的#
			num++;
		else if(line[i]==' ')		//开头的空格
			continue;
		else if(line[i]!=' ')		//开头之后的正文
		{
			// 字符串 支持后扩展，对于前扩展效果不好
			result =  result + char(num) + '>' + line.substr(i,length-i) + "</h" + char(num) + '>';
			// printf("<h %c > %s </h %c >",char(num),line.substr(i,length-i),char(num));
			break;
		}
	}
	return result;
}

/*
// 处理段落
string handle_para(string line,bool add)
{
	string result = "<p>";
	if(!add)
		result += line + "</p>";
	else
		result += line;
	return result;
}
*/
int main()
{
	vector<string> result;
	string line = "";
	int num = 1;
	while(getline(cin,line) && num <= 3)
	{
		if(line == "")
		{
			num++;

		}
		else
		{
			// heading
			if(line[0] == '#')
			{
				line = handle_heading(line);
				result.push_back(line);
			}
			// paragraph
			else 
			{
				
			}
			num ++;
		}
	}

	for(int i=0;i < result.size();i++)
	{
		cout << result[i] << endl;
	}
	return 0;
}
