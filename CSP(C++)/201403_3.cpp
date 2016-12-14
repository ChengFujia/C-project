#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int a[128] = {0};
char ans[128][260];

int main()
{
    char str[260];
    gets(str);
    char *p = str;
    while(*p)
    {
        if(*(p+1) == ':')
        {
            a[*p] = 2;
            p += 2;
        }
        else
        {
            a[*p] = 1;
            p++;
        }
    }
    int n;
    scanf("%d",&n);
    getchar();
    for(int i = 1;i <= n;i++)
    {
        memset(str,0,sizeof(str));
        memset(ans,0,sizeof(ans));
        gets(str);
        p = str;
        while(*p != ' ' && *p != 0) p++;
        p++;
        while(1)
        {
            if(*p == '-' && *(p+2) == ' ')
            {
                p++;
                char temp = *p;
                if(!a[temp])  break;
                if(a[temp] == 1)
                {
                    ans[temp][0] = '.';
                    p += 2;
                }
                else
                {
                    p += 2;
                    int num = 0;
                    char *tp = p;
                    while(*p != ' ' && *p != 0)
                    {
                        num++;
                        p++;
                    } 
                    p++;
                    strncpy(ans[temp],tp,num);
                    ans[temp][num] = 0;
                }
            }
            else if(*p == '-' && *(p+2) == '0')
            {
                *p++;
                if(a[*p] == 1)  ans[*p][0] = '.';
                break;
            }
            else break;
        }
        printf("Case %d:",i);
        for(char j = 'a';j <= 'z';j++)
        {
            if(ans[j][0] == '.')    printf(" -%c",j);
            else if(ans[j][0] != 0) printf(" -%c %s",j,ans[j]);
        }
        putchar('\n');
    }
    return 0;
}