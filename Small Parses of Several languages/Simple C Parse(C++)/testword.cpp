#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

char tempstr[255] = {};	//handled string
bool temp = false;	//space symbol
char word[255] = {};	//temp array
string keyword[26]={"main","if","then","while","do","static","default","do","int","double","struct","break","else","long","switch",
"case","typedef","char","return","const","float","short","continue","for","void","sizeof"};
int keyword_num[26]={1,2,3,4,5,6,39,40,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
char symbol[9] = {'+','-','*','/','=',';','(',')','#'};
int symbol_num[9] = {27,28,29,30,38,41,42,43,0};

bool IsDigit(char ch)
{
	if(ch>='0'&&ch<='9')
		return true;
	return false;
}

bool IsLetter(char ch)
{
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		return true;
	return false;
}

int IsSymbol(char ch)
{
	for(int i=0;i<9;i++)
	{
		if(ch==symbol[i])
			return i;
	}
	return -1;
}

int IsKeyword(string str)
{
	for(int i=0;i<26;i++)
	{
		if(str==keyword[i])
			return i;
	}
	return 25;
}

void HandleSpace(char a[])
{
	int j=0;
	memset(word,0,255);//Make Blank
	temp = false;
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]!=' ' && a[i]!='\t')
		{
			word[j++] = a[i];
			temp = false;
		}
		else
		//combine series blanks into one
		{
			if(!temp&&a[i]!='\t')
			{
				word[j++] = a[i];
				temp = true;
			}
		}
	}
}

// handler //
void prePro()
{
	int j=0;
	memset(tempstr,0,255);
	for(int i=0;i<strlen(word);i++)
	{
		if(word[i]=='/'&&word[i+1]=='/')
		{
			while(i<strlen(word))
				i++;
		}
		else
			tempstr[j++]=word[i];
	}
}

int main()
{
	char instr[255] = {};	//in string
	bool flag=false;	//multi-line /* */
	string Token;		//string 
	char *str=NULL;		//every-line string
	char delims[] = " ";
	freopen("text.cpp","r",stdin);
	freopen("result.txt","w",stdout);
	while((gets(instr))!=NULL)
	{
		HandleSpace(instr);
		/*
		//function gets()---read line-by-line
		for(int j=0;j<strlen(word);j++)
			cout << word[j]<< '/';
		*/
		prePro();
		str = strtok(tempstr,delims);
		while(str!=NULL)
		{
			if(*(str)=='#')
			{
				printf("#\n");
				break;
			}
			for(int i=0;i<strlen(str);i++)
			{
				if(*(str+i)=='/')
				{
					if(*(str+i+1)=='*')
					{
						flag=true;
						break;
					}
				}
				if(*(str+i)=='*'&&flag)
				{
					if(*(str+i+1)=='/')
					{
						flag=false;	
						i++;
						break;
					}
				}
				if(IsLetter(*(str+i))&&(!flag))
				{
					//printf("ID JUDGE BEGIN\n");
					while(IsLetter(*(str+i))||IsDigit(*(str+i))||*(str+i)=='_')
					{
						Token+=*(str+i);
						i++;
					}
					if(IsKeyword(Token)!=25)
						printf("%s---->%d\n",Token.c_str(),keyword_num[IsKeyword(Token)]);
					else
						printf("%s---->25\n",Token.c_str());
					Token = "";
					//printf("ID JUDGE END\n");
				}
				if(IsDigit(*(str+i))&&(!flag))
				{	
					//printf("NUM JUDGE BEGIN\n");
					while(IsDigit(*(str+i)))
					{
						Token+=*(str+i);
						i++;
					}
					printf("%s------>26\n",Token.c_str());
					Token="";
				}
				if(*(str+i)=='<'&&(!flag))
				{
					if(*(str+i+1)=='=')
						{printf("<=------>35\n");i++;}
					if(*(str+i+1)=='>')
						{printf("<>------>34\n");i++;}
					else
						printf("<------>33\n");
				}
				else if(*(str+i)=='>'&&(!flag))
				{
					if(*(str+i+1)=='=')
						{printf(">=------>37\n");}
					else
						printf(">------->36\n");
				}
				else if(*(str+i)==':'&&(!flag))
				{
					if(*(str+i+1)=='=')
						{printf(":=------>32\n");}
					else
						printf(":------->31\n");
				}
				else if(IsSymbol(*(str+i))!=-1&&(!flag))
				{
					printf("%c------->%d\n",*(str+i),symbol_num[IsSymbol(*(str+i))]);
				}
			}
		str=strtok(NULL,delims);
		}
	}
	return 0;
}

