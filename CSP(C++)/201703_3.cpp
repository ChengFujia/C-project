#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MOST_LENGTH 10

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

// 处理列表
string handle_list(string line)
{
	int length = line.size();
	int i;
	for(i=1;i<length;i++)
	{
		if(line[i] != ' ')
			break;
	}
	line = "<li>" + line.substr(i,length-i) + "</li>";
	return line;
}

// 处理段落
string handle_para(string line)
{
	string result = "<p>" + line;
	return result;
}

// 处理强调
string handle_empha(string line)
{
	vector<int> loc;			//存储_的位置
	int i = 0;
	int length = line.size();

	while(i<=length-1 && line.substr(i,length-i).find('_')!=-1)
	{
		i += line.substr(i,length-i).find('_') +1;		//这里必须是+=，因为find到的index是从切割后的子串开始的
		loc.push_back(i-1);
		//cout<< i-1 << " " << line[i-1] <<endl;
	}

	for(int j=0;j<loc.size()/2;j++)
	{
		string string1 = line.substr(0,loc[2*j] + 7*j);	//这里的7j是偏移量，增加标签之后产生的偏移量
		string string2 = line.substr(loc[2*j]+1 + 7*j,loc[2*j+1]-1-loc[2*j]);
		string string3 = line.substr(loc[2*j+1]+1 + 7*j,length-1-loc[2*j+1]);
		line = " ";
		line = string1 + "<em>" + string2 + "</em>" + string3;
		//cout << line << endl;
	}

	return line;
}

// 处理超链接
string handle_link(string line)
{
	vector<int> loc;				//存储特殊字符的位置
	char cha[4] = {'[',']','(',')'};//存储特殊字符
	int j=0;
	int length = line.size();
	
	while(j<=length-1 && line.substr(j,length-j).find('[')!=-1)
	{
		for(int i=0;i<4;i++)
		{
			j += line.substr(j,length-j).find(cha[i]) + 1;
			loc.push_back(j -1);
			// cout << j-1 << " " << line[j-1] << endl; 
		}
	}

	for(int p=0;p<loc.size()/4;p++)
	{
		string string1 = line.substr(0,loc[4*p] + 9*p);
		string text = line.substr(loc[4*p]+1 + 9*p,loc[4*p+1]-1-loc[4*p]);
		string link = line.substr(loc[4*p+2]+1 + 9*p,loc[4*p+3]-1-loc[4*p+2]);
		string string2 = line.substr(loc[4*p+3]+1 + 9*p,length-1-loc[4*p+3]);
		line = "";
		line = string1 + "<a href=" + link + '>' + text + "</a>" + string2;
		//cout << line << endl;
	}

	return line;
}

int main()
{
	vector<string> result;
	string line = "";
	int num = 1;
	bool list_sign = false;
	bool para_sign = false;

	while(getline(cin,line) && num <= MOST_LENGTH)
	{
		if(line == "")
		{
			if(list_sign)
			{
				result.push_back("</ul>");
				list_sign = false;
			}
			if(para_sign)
			{
				result[result.size()-1] += "</p>";
				para_sign = false;
			}
			num++;
		}
		else
		{
			// 预处理 -- 行内的处理/块内部
			if(line.find('_'))
				line = handle_empha(line);
			if(line.find('['))
				line = handle_link(line);

			// 正式处理 -- 块处理
			// heading
			if(line[0] == '#')
			{
				line = handle_heading(line);
				result.push_back(line);
			}
			// list
			else if(line[0] == '*')
			{
				line = handle_list(line);
				if(!list_sign)
				{
					result.push_back("<ul>");
					list_sign = true;
				}
				result.push_back(line);
			}
			// paragraph
			else 
			{
				if(!para_sign)
				{
					line = handle_para(line);
					para_sign = true;
				}
				else
					line = line;
				result.push_back(line);
			}

			// 最后处理 -- 若最后一行是列表或者段落
			if(num == MOST_LENGTH)
			{
				if(list_sign)
					result.push_back("</ul>");
				if(para_sign)
					result[result.size()-1] += "</p>";
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
