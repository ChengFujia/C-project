#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//vector<string> demo;
vector<string> seperate(string temp,vector<string> demo)
{
	vector<string> result;
	if(temp.size()==0 || temp.empty())
		return result;
	if (temp[0]!='/')
		temp = '/' + temp;
	if (temp[temp.size()-1]!='/')
		temp = temp + '/';
	string item = "";
	for(int i=1;i<temp.size();i++)
	{
		if(temp[i]=='/')
		{
			if(item!="." && item!= "")
			{
				if(item=="..")
				{
					if(result.size()>0)
					{
						result.pop_back();
						//cout << "******" << " ";
					}
					else
					{
						result = demo;
						result.pop_back();
						//cout << "______" << " ";
					}		
				}
				else
				{
					result.push_back(item);
					//cout << item << " ";
				}
			}
			
			item = "";
		}
		else
			item += temp[i];
	}
	//cout << endl;
	return result;
}

void output(vector<string> ttemp)
{
	if(ttemp.size() == 0)
		cout << '/';
	else
	{
		for(int m=0;m<ttemp.size();m++)
			cout << '/' << ttemp[m];
	}
	cout << endl;
}

int main()
{
	ifstream fcin("input.txt");
	int numOfDir = 0;
	int lineNum = 1;
	vector<vector<string>> dir;
	vector<string> demo;
	string line;
	while(getline(fcin,line))
	{
		if(lineNum == 1)
		{
			istringstream scin(line);
			scin >> numOfDir;
		}
		else if(lineNum >= 2 && lineNum <= 2+numOfDir)
		{
			vector<string> results = seperate(line,demo);
			if(lineNum == 2)
				demo = results;
			dir.push_back(results);
			if(lineNum == 2+numOfDir)
				break;
		}
		lineNum++;
	}

	for(int j=1;j<=numOfDir;j++)
	{
		if(dir[j].size()==0)
			output(dir[0]);
		else if(dir[j].size()==1)
			output(dir[j]);
		else
		{
			if (dir[j][dir[j].size()-1]==dir[j][dir[j].size()-2])
				dir[j].pop_back();
			if(dir[j].size()>=3) 
			{
				for(int k=dir[j].size()-2;k>=1;k--)
				{
					if(dir[j][k]==dir[j][k-1])
					{
						vector<string> midterm;
						for(int q=dir[j].size()-1;q>k;q--)
						{
							midterm.push_back(dir[j][q]);
							dir[j].pop_back();
						}
						dir[j].pop_back();
						for(int q=midterm.size()-1;q>=0;q--)
							dir[j].push_back(midterm[q]);
					}
				}
			}
			output(dir[j]);
		}
	}

	fcin.close();
	return 0;
}