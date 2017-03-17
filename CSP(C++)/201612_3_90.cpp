#include <iostream>
#include <sstream>
using namespace std;

struct Author				//Ȩ����
{
	string name;
	string level;
	Author() {}
	Author(string name,string level) : name(name),level(level) {}
};

struct Role					//��ɫ��
{
	string name;
	int num;
	Author table[10];
	Role() {}
	Role(string name,int num) :name(name),num(num) {}
};

struct User					//�û���
{
	string name;
	int num;
	string table[10];
	User() {}
	User(string name,int num) :name(name),num(num) {}
};

int main()
{
	Author f_table[101];	//���ȼ���Ȩ��
	int f_length=0;
	Role r_table[101];		//��ɫ�б�
	int r_length=0;
	User u_table[101];		//�û��б�
	int u_length=0;
	int final[1000];		//���ս��
	int final_length=0;

	int line = 0;			//���������
	string temp = "";		//�����ÿһ��

	/*��ȡ���� ������洢*/
	int number1,number2,number3,number4 = 0;		//��¼ �������� ����
	while(getline(cin,temp))
	{
		istringstream scin(temp);
		if(line==0)
			scin >> number1;		//Ȩ������
		else if(line<=number1)
		{
			//�������벻ͬ�������еȼ� or �޵ȼ� ��Ȩ��
			int loc = temp.find(':');
			if(loc == -1)
				f_table[f_length]=Author(temp,"NONE");
			else
			{
				f_table[f_length]=Author(temp.substr(0,loc),temp.substr(loc+1,1));
			}
			f_length++;
		}
		
		else if(line==number1+1)
		{
			scin >> number2;		//��ɫ����
			number2 += line;
		}
		else if(line<=number2)
		{
			//�����ɫ����
			string name,item;
			int num;
			scin >>  name >> num;
			Role role = Role(name,num);
			for(int i=0;i<=num-1;i++)
			{
				scin >> item;
				int loction = item.find(':');
				if(loction==-1)
					role.table[i] = Author(item,"NONE");
				else
				{
					bool same = false;
					if(i>0)
					{
						//ȥ��
						for(int j=0;j<i;j++)
						{
							if(role.table[j].name==item.substr(0,loction))
							{
								same = true;
								role.table[j].level = role.table[j].level[0]>item.substr(loction+1,1)[0] ? role.table[j].level[0] :item.substr(loction+1,1)[0];
							}
						}
					}
					if(same == false)
						role.table[i]=Author(item.substr(0,loction),item.substr(loction+1,1));
				} 
			}
			r_table[r_length] = role;
			r_length ++;
		}
		else if(line==number2+1)
		{
			scin >> number3;		//�û�����
			number3 += line;	
		}
		else if(line<=number3)
		{
			//�����û�����
			string name,item;
			int num;
			scin >>  name >> num;
			User user = User(name,num);
			for(int i=0;i<=num-1;i++)
			{
				scin >> item;
				user.table[i] = item;
			}
			u_table[u_length] = user;
			u_length ++;
		}
		else if (line == number3+1)
		{
			scin >> number4;		//��������
			number4 += line;
		}
		else if(line<=number4)
		{
			//������������,�߶��ߴ���
			string name,question;
			int result = -2;				//-2����fasle,-1����true
			int result_temp = -2;
			scin >> name >> question;
			//���� ����
			bool find_user = false;
			//���� ���е� user
			for(int i=0;i<u_length;i++)
			{
				//���� һ�� user
				if(u_table[i].name==name)			
				{
					find_user = true;
					//���� һ�� user ������ role
					for(int j=0;j<u_table[i].num;j++)
					{
						string r_name=u_table[i].table[j];
						//���� ���е� role
						for(int k=0;k<r_length;k++)
						{
							//���� һ�� role
							if(r_name==r_table[k].name)
							{
								//���� һ�� role ������ Ȩ��
								for(int p=0;p<r_table[k].num;p++)
								{
									Author author = r_table[k].table[p];
									int loca=question.find(':');
									// ������У���
									if(loca!=-1)
									{
										string question_level = question.substr(loca+1,1);
										string question_name = question.substr(0,loca);
										// �ҵȼ��߹�
										if(author.name == question_name && author.level[0]>=question_level[0])
												result = -1;
									}
									else if(loca==-1)
									{
										if(author.name == question && author.level == "NONE")
											result = -1;
										else if(author.name == question && author.level != "NONE")
										{
											//�漰�����Ȩ��ȡ���
											result_temp = int(author.level[0]-48);
											result = result>result_temp ? result :result_temp;
										}
									}
								}
							}
						}

					}
				}
			}
			// ����δ�ҵ�user��
			if(!find_user)
				result = -2;
			final[final_length] = result;
			final_length ++;
		}
		else if(line==1+number4)
			break;
		line++;
	}
	/*
	cout << "\n-------------------\n" << endl;
	for(int i=0;i<f_length;i++)
		cout << f_table[i].name << " " << f_table[i].level << endl;
	cout << "\n-------------------\n" << endl;
	for(int i=0;i<r_length;i++)
	{
		cout << r_table[i].name << " " << r_table[i].num << " ";
		for(int j=0;j<r_table[i].num;j++)
			cout << r_table[i].table[j].name << " " << r_table[i].table[j].level << " "; 
		cout << endl;
	}
	cout << "\n-------------------\n" << endl;
	for(int i=0;i<u_length;i++)
	{
		cout << u_table[i].name << " " << u_table[i].num << " ";
		for(int j=0;j<u_table[i].num;j++)
			cout << u_table[i].table[j]<<" "; 
		cout << endl;
	}
	cout << "\n-------------------\n" << endl;
	*/
	for(int i=0;i<final_length;i++)
	{
		switch(final[i])
		{
		case -2:cout<<"false"<<endl;break;
		case -1:cout<<"true"<<endl;break;
		default:cout<<final[i]<< endl;break;
		}
	}
	return 0;
}
