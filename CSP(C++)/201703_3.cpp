#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MOST_LENGTH 10

// �������
string handle_heading(string line)
{
	int num = 48;							//0��ascii�룬����������֣�������棨����+����=���֣��������ַ�+����=�ַ���
	int length = line.size();
	string result = "<h";
	for(int i=0;i<length;i++)
	{
		if(line[i]=='#')			//��ͷ��#
			num++;
		else if(line[i]==' ')		//��ͷ�Ŀո�
			continue;
		else if(line[i]!=' ')		//��ͷ֮�������
		{
			// �ַ��� ֧�ֺ���չ������ǰ��չЧ������
			result =  result + char(num) + '>' + line.substr(i,length-i) + "</h" + char(num) + '>';
			// printf("<h %c > %s </h %c >",char(num),line.substr(i,length-i),char(num));
			break;
		}
	}
	return result;
}

// �����б�
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

// �������
string handle_para(string line)
{
	string result = "<p>" + line;
	return result;
}

// ����ǿ��
string handle_empha(string line)
{
	vector<int> loc;			//�洢_��λ��
	int i = 0;
	int length = line.size();

	while(i<=length-1 && line.substr(i,length-i).find('_')!=-1)
	{
		i += line.substr(i,length-i).find('_') +1;		//���������+=����Ϊfind����index�Ǵ��и����Ӵ���ʼ��
		loc.push_back(i-1);
		//cout<< i-1 << " " << line[i-1] <<endl;
	}

	for(int j=0;j<loc.size()/2;j++)
	{
		string string1 = line.substr(0,loc[2*j] + 7*j);	//�����7j��ƫ���������ӱ�ǩ֮�������ƫ����
		string string2 = line.substr(loc[2*j]+1 + 7*j,loc[2*j+1]-1-loc[2*j]);
		string string3 = line.substr(loc[2*j+1]+1 + 7*j,length-1-loc[2*j+1]);
		line = " ";
		line = string1 + "<em>" + string2 + "</em>" + string3;
		//cout << line << endl;
	}

	return line;
}

// ��������
string handle_link(string line)
{
	vector<int> loc;				//�洢�����ַ���λ��
	char cha[4] = {'[',']','(',')'};//�洢�����ַ�
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
			// Ԥ���� -- ���ڵĴ���/���ڲ�
			if(line.find('_'))
				line = handle_empha(line);
			if(line.find('['))
				line = handle_link(line);

			// ��ʽ���� -- �鴦��
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

			// ����� -- �����һ�����б���߶���
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
