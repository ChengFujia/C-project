#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/*
	��һ�뷨��ͨ���࣬ʵ��֤�������������鷳����Ȼͨ���Ըߣ����߽�/�﷨���ӣ�С�ͳ��򷴶������㣩��
	�ڶ��뷨��ֱ��ģ����̣�����������ȫһ���ı�������Ϊ���ַ��ͺ��ַ�����������ָ��ɣ�ͨ���Բ���﷨/�߽��������
*/

struct Player
{
	int heroAttack;		//Ӣ�۹�����
	int heroHealthy;	//Ӣ������ֵ
	int numSummon;		//��Ӹ���
	vector<int> attackSummons;	//��ӹ������б�
	vector<int> healthSummons;	//�������ֵ�б�

	//Ĭ�Ϲ��캯��������ʼ������ʱ�Զ�����
	Player()
	{
		heroAttack = 0;		
		heroHealthy = 30;
		numSummon = 0;
	}

	//������������������numSummon attackSummons healthSummons
	int deadSummon(int position)
	{
		if(position==numSummon)		//��������һ��
		{
			attackSummons.pop_back();
			healthSummons.pop_back();
		}
		else						//������м�λ��
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>position;i--)		//��λ�ú���Ĵ浽����
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.pop_back();				//��λ�õ�ɾ��
			healthSummons.pop_back();
			for(int i=temp1.size()-1;i>=0;i--)		//ԭ��λ�ú���Ļ�ԭ����
			{
				attackSummons.push_back(temp1[i]);
				healthSummons.push_back(temp2[i]);
				temp1.pop_back();
				temp2.pop_back();
			}
		}
		//���Ҫ���ӣ�����ڵ�һ��ִ�У������vector���������ң��õ�����Ľ��
		numSummon -= 1;			
		return 0;
	}

	//�ٻ������
	int summon(int position,int attack,int health)
	{
		if(position>numSummon)		//��������һ��
		{
			attackSummons.push_back(attack);
			healthSummons.push_back(health);
		}
		else						//������м�λ��
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>=position;i--)		//��λ���Լ�����Ĵ浽����
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.push_back(attack);			//��λ�ò�����Ԫ��
			healthSummons.push_back(health);
			for(int i=temp1.size()-1;i>=0;i--)			//ԭ��λ���Լ�����Ļ�ԭ����
			{
				attackSummons.push_back(temp1[i]);
				healthSummons.push_back(temp2[i]);
				temp1.pop_back();
				temp2.pop_back();
			}
		}
		numSummon += 1;
		return 0;
	}

	//����������������ı���������һ������&���ã���Ϊ������Ҫ���»�ȥ
	//���ԭ�����֮ǰ���ִ���
	int attack(Player &player2,int attacker,int denfender)
	{
		if(denfender==0)		//��������������Ӣ��
		{
			player2.heroHealthy -= attackSummons[attacker-1];
		}
		else					//�����������������
		{
			healthSummons[attacker-1] -= player2.attackSummons[denfender-1]; 
			player2.healthSummons[denfender-1]-= attackSummons[attacker-1];
			if(healthSummons[attacker-1]<=0)
				deadSummon(attacker);
			if(player2.healthSummons[denfender-1]<=0)
				player2.deadSummon(denfender);
		}
		return 0;
	}
};

//���������ע�����������õ������ʽ����Ϊ�����50->80->100��
void coutFunction(int sign,Player playerFirst,Player playerSecond)
{
	cout << sign << endl;
	cout << playerFirst.heroHealthy << endl;
	cout << playerFirst.numSummon << ' ' ;
	if (playerFirst.numSummon!=0)	//�����Ӹ������㣬�ֱ��������ֵ��ע�����һ�����治�ܸ��ո񣬶���ֱ�ӻ��У�
	{
		for(int i=0;i<playerFirst.numSummon-1;i++)
			cout << playerFirst.healthSummons[i]<< ' ';
		cout << playerFirst.healthSummons[playerFirst.numSummon-1]<<endl;
	}
	else							//�����Ӹ������㣬�����������ֵ��ע��ֱ��������з���
		cout << endl;

	cout << playerSecond.heroHealthy << endl;
	cout << playerSecond.numSummon << ' ' ;
	if (playerSecond.numSummon!=0)
	{
		for(int i=0;i<playerSecond.numSummon-1;i++)
			cout << playerSecond.healthSummons[i]<< ' ';
		cout << playerSecond.healthSummons[playerSecond.numSummon-1]<<endl;
	}
	else
		cout << endl;
}


int main()
{
	Player playerFirst;
	Player playerSecond;
	int num;
	cin >> num;
	int count =0;		//ָ������
	bool direction = 0;	//���ֹ�����0�������ֹ�����1��
	int sign =0;		//״̬��ʶ��0-��Ϸδ���� 1-��Ϸ����������ʤ�� -1-��Ϸ����������ʤ����
	string line,word;
	int arg1,arg2,arg3,arg4,arg5;
	while(getline(cin,line))
	{
		//��������һ�и�ֵ�������ַ�������recode������cin���ֱ����string��һ�����ĵ���
		istringstream record(line);		
		count++;
		record >> word;
		if(word == "summon")
		{
			record >> arg1 >> arg2 >> arg3;
			if(!direction) 
				playerFirst.summon(arg1,arg2,arg3);
			else
				playerSecond.summon(arg1,arg2,arg3);
		}
		if(word == "attack")
		{
			record >> arg4 >> arg5;
			if(!direction)
			{
				playerFirst.attack(playerSecond,arg4,arg5);
				if(playerSecond.heroHealthy<=0)
					{
						sign=1;
						break;
					}
			}	
			else
			{
				playerSecond.attack(playerFirst,arg4,arg5);
				if(playerFirst.heroHealthy<=0)
					{
						sign=-1;
						break;
					}
			}
		}
		if(word == "end")
			direction = !direction;
		if(count == num+1)		//numָ��������ָ�������������ܹ�������Ϊnum+1(�����Լ���һ��)
			break;
	}
	coutFunction(sign,playerFirst,playerSecond);
	return 0;
}