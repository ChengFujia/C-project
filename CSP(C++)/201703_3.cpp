#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

/*
// �������
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
