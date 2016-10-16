#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 10000 + 5;		//�ڵ������
const int MAXM = 100000 + 5;	//·�������
int N, M;						//����ڵ���������·����

struct Edge
{								//�ڶ���ṹ���ͬʱ��ʼ��һ�����󣬴洢�ߵĹ�ϵ
    int v, next, w;				//��С <<1 ����1λ���൱��*2��
    Edge() {}					//��Ϊ�����е�·������������յ㣬����������Ҫ�ӽ�ȥ
    Edge(int v, int next, int w) : v(v), next(next), w(w) {}
} edge[MAXM << 1];				
								
int ESZ,head[MAXN]; 			//ESZ��һ����������head[]��Ӧÿһ���ڵ��next
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
    priority_queue<QNode, vector<QNode>, greater<QNode> > Q;//���ȶ��У�����ԽС�����ȼ�Խ��
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