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
								
int ESZ,head[MAXN]; 			//ESZ��һ����������0 -- 2*M-1��
								//head[]��Ӧÿһ���ڵ��next,��ʵ��¼����һ����
								//����head[1]=2����u=1���һ�γ��ֵ�λ�ã���next������һ�γ��ֵ�λ��
								//һֱ��ĳһ�����next�ֶ�Ϊ-1
void init()
{
	ESZ = 0;
	memset(head, -1, sizeof(head));		//���������Ҫcstringͷ�ļ�֧��
}

void add_edge(int u, int v, int w)		//����������У�����2*M���ߣ�����¼����uΪ��������·��edge[]
{										//u��Χ��[1,N],����ÿһ��u����һ��������edge[]��ʾ��uΪ�������б�
    edge[ESZ] = Edge(v, head[u], w);
    head[u] = ESZ ++;
}

struct Dij {
    struct QNode {						//�ڶ���ṹ���ͬʱ�������cur�洢��ǰ��С�ڵ�
        int u, cost;
        QNode() {}
        QNode(int u, int cost) : u(u), cost(cost) {}
        bool operator > (const QNode& e) const {
            return cost > e.cost;
        }
    } cur;								
    priority_queue<QNode, vector<QNode>, greater<QNode> > Q;//���ȶ��У�Ĭ��������Խ�����ȼ�Խ��
															//����greater�ֶα�ʾ ����ԽС�����ȼ�Խ��
    int cost[MAXN];						//�洢ÿ���ڵ㵽Դ�ڵ����С����
    bool vis[MAXN];						//��ʾĿ��ڵ�״̬����true�����Ѽ�������false��֮��

    void init() {
        while(!Q.empty()) Q.pop();			
        memset(vis, false, sizeof(vis));	
        memset(cost, 0x3f, sizeof(cost));
    }

    void run() {						//�淶��Dijkstra�㷨�Ĺ��̣����㵥Դ���·����
        int u, v, w;
        Q.push(QNode(1, cost[1] = 0));	//�Ȱѽڵ�1���������У���{1}��ʼ
        while(!Q.empty()) {
            cur = Q.top();				
            Q.pop();
            u = cur.u;
            if(vis[u]) continue;		//���ڵ�1����Ϊ�Ѽ���״̬
            vis[u] = true;
            for(int i = head[u]; ~i; i = edge[i].next)  {	//����������1��ͷ�ıߣ��ֱ����1�����Ƕ�Ӧ�˵�v�����·��
                v = edge[i].v, w = edge[i].w;				//������ʶ��i=-1����ΪĬ���Ƕ����Ʋ��룬��-1��ʾΪȫ1
                if(!vis[v] && cost[v] > cost[u] + w) {		//���v�����·���Ѿ�����Ļ����Ͳ��ټ�����
                    Q.push(QNode(v, cost[v] = w + cost[u]));//��������ֽ׶����·����������
                }											//��ѭ�����ҳ����У��ֽ׶ε����·��
            }
        }													//while����һ��Ĭ�������ȼ���ߵ�pop��ȥ��Ҳ����cost��С��
    }
} dij;

queue<int> Que;
int minx[MAXN];

int getAns() {
    int u, v, w;
    memset(minx, 0x3f, sizeof(minx));
    Que.push(1);											//front�ǵ�һ��Ԫ�أ����ﲻ�漰���ȼ������⣬���μ���ͺ�
    minx[1] = 0;
    while(!Que.empty()) {
        u = Que.front();
        Que.pop();
        for(int i = head[u]; ~i; i = edge[i].next)  {		//�ظ��������·��ʱ��Ĺ��̣���=���·�������Ӿ������ʱ�����뵽minx[]��
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
	while(~scanf("%d %d", &N, &M))			//����д���Զ�����У�Ҳ����ȡ��whileѭ�������һ���Եĳ���
	{
        init();
        for(int i = 1; i <= M; i++) 
		{
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
		dij.init();
		dij.run();			//��һ��������·��
		ans = getAns();		//�ڶ��鱣�����·��ǰ���£�ѡ��������Ҫ��ģ����Ӿ������٣�
		cout << ans << endl;
	}
    return 0;
}