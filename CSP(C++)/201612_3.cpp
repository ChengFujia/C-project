#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Player
{
	int heroAttack;
	int heroHealthy;
	int numSummon;
	vector<int> attackSummons;
	vector<int> healthSummons;

	Player()
	{
		heroAttack = 0;
		heroHealthy = 30;
		numSummon = 0;
	}

	int deadSummon(int position)
	{
		if(position==numSummon)
		{
			attackSummons.pop_back();
			healthSummons.pop_back();
		}
		else
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>position;i--)
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.pop_back();
			healthSummons.pop_back();
			for(int i=temp1.size()-1;i>=0;i--)
			{
				attackSummons.push_back(temp1[i]);
				healthSummons.push_back(temp2[i]);
				temp1.pop_back();
				temp2.pop_back();
			}
		}
		numSummon -= 1;
		return 0;
	}

	int summon(int position,int attack,int health)
	{
		if(position>numSummon)
		{
			attackSummons.push_back(attack);
			healthSummons.push_back(health);
		}
		else
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>=position;i--)
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.push_back(attack);
			healthSummons.push_back(health);
			for(int i=temp1.size()-1;i>=0;i--)
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

	int attack(Player player1,Player player2,int attacker,int denfender)
	{
		if(denfender==0)
		{
			player2.heroHealthy -= player1.attackSummons[attacker-1];
		}
		else
		{
			player1.healthSummons[attacker-1] -= player2.attackSummons[denfender-1]; 
			player2.healthSummons[denfender-1]-= player1.attackSummons[attacker-1];
			if(player1.healthSummons[attacker-1]<=0)
				player1.deadSummon(attacker);
			if(player2.healthSummons[denfender-1]<=0)
				player2.deadSummon(denfender);
		}
		return 0;
	}

	//end²Ù×÷
	//void end()???
};

int main()
{
	Player playerFirst;
	Player playerSecond;
	int num;
	cin >> num;
	int count =0;
	bool direction = 0;
	int sign =0;
	string line,word;
	int arg1,arg2,arg3,arg4,arg5;
	while(getline(cin,line))
	{
		istringstream record(line);
		cout << count << endl;
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
				playerFirst.attack(playerFirst,playerSecond,arg4,arg5);
				if(playerSecond.heroHealthy<=0)
					{
						sign=1;
						break;
					}
			}	
			else
			{
				playerSecond.attack(playerSecond,playerFirst,arg4,arg5);
				if(playerFirst.heroHealthy<=0)
					{
						sign=-1;
						break;
					}
			}
		}
		if(word == "end")
			direction = !direction;
		if(count == num+1)
			break;
	}
	cout << sign << endl;
	cout << playerFirst.heroHealthy << endl;
	cout << playerFirst.numSummon << ' ' ;
	for(int i=0;i<playerFirst.numSummon-1;i++)
		cout << playerFirst.healthSummons[i]<< ' ';
	cout << playerFirst.healthSummons[playerFirst.numSummon-1]<<endl;
	cout << playerSecond.heroHealthy << endl;
	cout << playerSecond.numSummon << ' ' ;
	for(int i=0;i<playerSecond.numSummon-1;i++)
		cout << playerSecond.healthSummons[i]<< ' ';
	cout << playerSecond.healthSummons[playerSecond.numSummon-1]<<endl;
	return 0;
}