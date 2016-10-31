#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<string>  
#include<vector>  
#include<set>  
#include<map>  
using namespace std;  
#define maxn 2000007  
struct Point {  
    int x,y;  
    Point(){  
  
    }  
};  
struct Node{  
    int num,v,c;  
    Node(){  
  
    }  
};  
  
#define maxv 500007  
Point point[maxv];  
vector<int> headx[maxv];  
vector<int> heady[maxv];  
Node node[maxn];  
//初始化线段树  
void build(int root,int l,int r){  
    node[root].num = 0;  
    node[root].v = 0;  
    node[root].c = 0;  
    if(l == r){  
        node[root].num = 1;  
        return ;  
    }  
    int mid = (l+r)/2;  
    build(root*2+1,l,mid);  
    build(root*2+2,mid+1,r);  
}  
//获取区间内得到层数最大值以及情况数  
Node get(int root,int l,int r,int L,int R,int lim){  
    if(r < l){  
        Node a;  
        a.v = 0;  
        a.num = 0;  
        return a;  
    }  
    if(l == L && R == r){  
        Node a = node[root];  
        if(a.v > lim) a.v = lim;  
        return a;  
    }  
    int mid = (L+R)/2;  
    if(mid >= r)  {  
        Node a = get(root*2+1,l,r,L,mid,lim);  
        a.v = min(a.v,lim);  
        return a;  
    }  
    else if(mid < l) {  
        Node a = get(root*2+2,l,r,mid+1,R,lim);  
        a.v = min(a.v,lim);  
        return a;  
    }  
    else {  
        Node a = get(root*2+1,l,mid,L,mid,lim);  
        Node b = get(root*2+2,mid+1,r,mid+1,R,lim);  
        if(a.v == b.v){  
            a.num += b.num;  
        }  
        else if(a.v < b.v){  
            a = b;  
        }  
        return a;  
    }  
}  
//更新线段树，加入新点  
int maxAns = 10000000; //取一个最大值第一次执行算法的时候是不会有影响的  
void add(int root,int p,int L,int R){  
    if(L == R){  
        node[root].c ++;  
        node[root].num = 1;  
        node[root].v = min(node[root].c,(int)headx[L].size()-node[root].c);  
        /* 
        node[root].v = min(node[root].v,maxAns);//此处为求第二问新加的 
        */  
        return ;  
    }  
    int mid = (L+R)/2;  
    if(p <= mid) add(root*2+1,p,L,mid);  
    else add(root*2+2,p,mid+1,R);  
    Node a = node[root*2+1];  
    Node b = node[root*2+2];  
    if(a.v == b.v) a.num += b.num;  
    else if(a.v < b.v) a = b;  
    node[root] = a;  
}  
  
int main(){  
    int n,q;  
    scanf("%d%d",&n,&q);  
    map<int,int>mapx;  
    map<int,int>mapy;  
    for(int i = 0;i < n; i++){  
        scanf("%d%d",&point[i].x,&point[i].y);  
        mapx[point[i].x] = 0;  
        mapy[point[i].y] = 0;  
    }  
    int cntx  = 0,cnty = 0;  
    map<int,int>::iterator it;  
    for(it = mapx.begin(); it != mapx.end(); it++){  
        it->second = cntx++;  
    }  
    for(it = mapy.begin(); it != mapy.end(); it++){  
        it->second = cnty++;  
    }  
    int x,y;  
    for(int i = 0;i < n; i++){  
        x = point[i].x = mapx[point[i].x];  
        y = point[i].y = mapy[point[i].y];  
        headx[x].push_back(y);  
        heady[y].push_back(x);  
    }  
    map<int,int> ans;  
    build(0,0,cntx-1);  
  
  
    for(int i = 0;i < cnty; i++){  
        sort(heady[i].begin(),heady[i].end());  
        for(int j = 1;j < heady[i].size(); j++){  
            Node p = get(0,heady[i][j-1]+1,heady[i][j]-1,0,cntx-1,min(j,(int)heady[i].size()-j));  
            ans[p.v] += p.num;  
        }  
        for(int j = 0;j < heady[i].size(); j++){  
            add(0,heady[i][j],0,cntx-1);  
        }  
    }  
  
  
    it = ans.end();  
    it--;  
    if(q == 1){  
        cout<<it->first<<endl;  
    }  
    else{  
        /* 这段代码新加的用来求第二问的 
        maxAns = it->first; 
        ans.clear(); 
        build(0,0,cntx-1); 
 
 
        for(int i = 0;i < cnty; i++){ 
            sort(heady[i].begin(),heady[i].end()); 
            for(int j = 1;j < heady[i].size(); j++){ 
                Node p = get(0,heady[i][j-1]+1,heady[i][j]-1,0,cntx-1,min(j,(int)heady[i].size()-j)); 
                ans[p.v] += p.num; 
            } 
            for(int j = 0;j < heady[i].size(); j++){ 
                add(0,heady[i][j],0,cntx-1); 
            } 
        } 
        it = ans.end(); 
        it--; 
        */  
        cout<<it->second<<endl;  
    }  
    return 0;  
}  