#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 10000 + 5;		//节点最大数
const int MAXM = 100000 + 5;	//路径最大数
int N, M;						//输入节点数，输入路径数

struct Edge
{								//在定义结构体的同时初始化一个对象，存储边的关系
    int v, next, w;				//大小 <<1 左移1位，相当于*2，
    Edge() {}					//因为本题中的路径不区分起点终点，所以两个都要加进去
    Edge(int v, int next, int w) : v(v), next(next), w(w) {}
} edge[MAXM << 1];				
								
int ESZ,head[MAXN]; 			//ESZ是一个计数器（0 -- 2*M-1）
								//head[]对应每一个节点的next,其实记录的是一条链
								//例如head[1]=2，是u=1最后一次出现的位置，而next是它上一次出现的位置
								//一直到某一项，它的next字段为-1
void init()
{
	ESZ = 0;
	memset(head, -1, sizeof(head));		//这个玩意需要cstring头文件支持
}

void add_edge(int u, int v, int w)		//在这个过程中，加入2*M条边，并记录下以u为起点的所有路径edge[]
{										//u范围是[1,N],对于每一个u，有一组相连的edge[]表示以u为起点的所有边
    edge[ESZ] = Edge(v, head[u], w);
    head[u] = ESZ ++;
}

struct Dij {
    struct QNode {						//在定义结构体的同时定义对象，cur存储当前最小节点
        int u, cost;
        QNode() {}
        QNode(int u, int cost) : u(u), cost(cost) {}
        bool operator > (const QNode& e) const {
            return cost > e.cost;
        }
    } cur;								
    priority_queue<QNode, vector<QNode>, greater<QNode> > Q;//优先队列，默认是数据越大，优先级越高
															//带有greater字段表示 数据越小，优先级越高
    int cost[MAXN];						//存储每个节点到源节点的最小代价
    bool vis[MAXN];						//表示目标节点状态。若true表明已计算结果，false反之。

    void init() {
        while(!Q.empty()) Q.pop();			
        memset(vis, false, sizeof(vis));	
        memset(cost, 0x3f, sizeof(cost));
    }

    void run() {						//规范的Dijkstra算法的过程（计算单源最短路径）
        int u, v, w;
        Q.push(QNode(1, cost[1] = 0));	//先把节点1放入序列中，从{1}开始
        while(!Q.empty()) {
            cur = Q.top();				
            Q.pop();
            u = cur.u;
            if(vis[u]) continue;		//将节点1设置为已计算状态
            vis[u] = true;
            for(int i = head[u]; ~i; i = edge[i].next)  {	//遍历所有以1开头的边，分别计算1到他们对应端点v的最短路径
                v = edge[i].v, w = edge[i].w;				//结束标识是i=-1，因为默认是二进制补码，则-1表示为全1
                if(!vis[v] && cost[v] > cost[u] + w) {		//如果v的最短路径已经计算的话，就不再计算啦
                    Q.push(QNode(v, cost[v] = w + cost[u]));//将计算的现阶段最短路径加入序列
                }											//再循环，找出所有，现阶段的最短路径
            }
        }													//while的下一次默认是优先级最高的pop出去，也就是cost最小的
    }
} dij;

queue<int> Que;
int minx[MAXN];

int getAns() {
    int u, v, w;
    memset(minx, 0x3f, sizeof(minx));
    Que.push(1);											//front是第一个元素，这里不涉及优先级的问题，依次检验就好
    minx[1] = 0;
    while(!Que.empty()) {
        u = Que.front();
        Que.pop();
        for(int i = head[u]; ~i; i = edge[i].next)  {		//重复计算最短路径时候的过程，当=最短路径且增加距离最短时，加入到minx[]中
            v = edge[i].v, w = edge[i].w;
            if(dij.cost[v] == dij.cost[u] + w) {
                minx[v] = min(minx[v], w);
                Que.push(v);
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        ans += minx[i];
    }
    return ans;
}

int main() 
{
    int u, v, w, ans;
	while(~scanf("%d %d", &N, &M))			//这样写可以多次运行，也可以取消while循环，变成一次性的程序
	{
        init();
        for(int i = 1; i <= M; i++) 
		{
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
		dij.init();
		dij.run();			//第一遍计算最短路径
		ans = getAns();		//第二遍保留最短路径前提下，选择符合题干要求的（增加距离最少）
		cout << ans << endl;
	}
    return 0;
}