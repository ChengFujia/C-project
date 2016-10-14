#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/*
	第一想法是通过类，实践证明，用类做很麻烦（虽然通用性高，但边界/语法复杂，小型程序反而不方便）；
	第二想法是直接模拟过程，设置两套完全一样的变量，作为先手方和后手方，逐条读入指令即可（通用性差，但语法/边界很清晰）
*/

struct Player
{
	int heroAttack;		//英雄攻击力
	int heroHealthy;	//英雄生命值
	int numSummon;		//随从个数
	vector<int> attackSummons;	//随从攻击力列表
	vector<int> healthSummons;	//随从生命值列表

	//默认构造函数，当初始化对象时自动调用
	Player()
	{
		heroAttack = 0;		
		heroHealthy = 30;
		numSummon = 0;
	}

	//如果有随从死亡，更新numSummon attackSummons healthSummons
	int deadSummon(int position)
	{
		if(position==numSummon)		//如果是最后一个
		{
			attackSummons.pop_back();
			healthSummons.pop_back();
		}
		else						//如果在中间位置
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>position;i--)		//该位置后面的存到缓存
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.pop_back();				//该位置的删除
			healthSummons.pop_back();
			for(int i=temp1.size()-1;i>=0;i--)		//原该位置后面的还原回来
			{
				attackSummons.push_back(temp1[i]);
				healthSummons.push_back(temp2[i]);
				temp1.pop_back();
				temp2.pop_back();
			}
		}
		//这个要最后加，如果在第一句执行，会造成vector的索引错乱，得到错误的结果
		numSummon -= 1;			
		return 0;
	}

	//召唤新随从
	int summon(int position,int attack,int health)
	{
		if(position>numSummon)		//如果是最后一个
		{
			attackSummons.push_back(attack);
			healthSummons.push_back(health);
		}
		else						//如果是中间位置
		{
			vector<int> temp1,temp2;
			for(int i=numSummon;i>=position;i--)		//该位置以及后面的存到缓存
			{
				temp1.push_back(attackSummons[i-1]);
				temp2.push_back(healthSummons[i-1]);
				attackSummons.pop_back();
				healthSummons.pop_back();
			}
			attackSummons.push_back(attack);			//该位置插入新元素
			healthSummons.push_back(health);
			for(int i=temp1.size()-1;i>=0;i--)			//原该位置以及后面的还原回来
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

	//攻击函数。。这里的被攻击对象一定得用&引用，因为计算结果要更新回去
	//这个原因造成之前出现错误
	int attack(Player &player2,int attacker,int denfender)
	{
		if(denfender==0)		//若被攻击对象是英雄
		{
			player2.heroHealthy -= attackSummons[attacker-1];
		}
		else					//若被攻击对象是随从
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

//输出函数（注意理解题干设置的输出格式，因为这个从50->80->100）
void coutFunction(int sign,Player playerFirst,Player playerSecond)
{
	cout << sign << endl;
	cout << playerFirst.heroHealthy << endl;
	cout << playerFirst.numSummon << ' ' ;
	if (playerFirst.numSummon!=0)	//如果随从个数非零，分别输出生命值（注意最后一个后面不能跟空格，而是直接换行）
	{
		for(int i=0;i<playerFirst.numSummon-1;i++)
			cout << playerFirst.healthSummons[i]<< ' ';
		cout << playerFirst.healthSummons[playerFirst.numSummon-1]<<endl;
	}
	else							//如果随从个数是零，不用输出生命值（注意直接输出换行符）
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
	int count =0;		//指令条数
	bool direction = 0;	//先手攻击（0），后手攻击（1）
	int sign =0;		//状态标识（0-游戏未结束 1-游戏结束，先手胜利 -1-游戏结束，后手胜利）
	string line,word;
	int arg1,arg2,arg3,arg4,arg5;
	while(getline(cin,line))
	{
		//将读到的一行赋值给输入字符串流，recode类似于cin，分别读入string中一个个的单词
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
		if(count == num+1)		//num指的是下面指令的行数，因此总共的行数为num+1(加上自己这一行)
			break;
	}
	coutFunction(sign,playerFirst,playerSecond);
	return 0;
}