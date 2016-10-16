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
								
int ESZ,head[MAXN]; 			//ESZ是一个计数器，head[]对应每一个节点的next
void init()
{
	ESZ = 0;
	memset(head, -1, sizeof(head));
}

void add_edge(int u, int v, int w)
{
    edge[ESZ] = Edge(v, head[u], w);
    head[u] = ESZ ++;
}

struct Dij {
    struct QNode {
        int u, cost;
        QNode() {}
        QNode(int u, int cost) : u(u), cost(cost) {}
        bool operator > (const QNode& e) const {
            return cost > e.cost;
        }
    } cur;
    priority_queue<QNode, vector<QNode>, greater<QNode> > Q;//优先队列，数据越小，优先级越高
    int cost[MAXN];
    bool vis[MAXN];

    void init() {
        while(!Q.empty()) Q.pop();			
        memset(vis, false, sizeof(vis));	
        memset(cost, 0x3f, sizeof(cost));
    }

    void run() {
        int u, v, w;
        Q.push(QNode(1, cost[1] = 0));
        while(!Q.empty()) {
            cur = Q.top();
            Q.pop();
            u = cur.u;

            if(vis[u]) continue;
            vis[u] = true;
            for(int i = head[u]; ~i; i = edge[i].next)  {
                v = edge[i].v, w = edge[i].w;
                if(!vis[v] && cost[v] > cost[u] + w) {
                    Q.push(QNode(v, cost[v] = w + cost[u]));
                }
            }
        }
    }
} dij;

queue<int> Que;
int minx[MAXN];

int getAns() {
    int u, v, w;
    memset(minx, 0x3f, sizeof(minx));
    Que.push(1);
    minx[1] = 0;
    while(!Que.empty()) {
        u = Que.front();
        Que.pop();
        for(int i = head[u]; ~i; i = edge[i].next)  {
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
	while(~scanf("%d %d", &N, &M)) 
	{
        init();
        for(int i = 1; i <= M; i++) 
		{
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
		dij.init();
		dij.run();
		ans = getAns();
		cout << ans << endl;
	}
    return 0;
}