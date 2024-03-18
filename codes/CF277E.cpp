#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, maxm = maxn * maxn * 2, INF = 0x3f3f3f3f;
const double eps = 1e-9;
int n;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;double cost;
    edge(int to = 0,int ne = 0,int ca = 0,double co = 0.0,int fl = 0
    ):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxm];
void add(int u,int v,int cap,double cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,double cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn];
bool book[maxn];
double dis[maxn];
bool SPFA(int S,int T){
	// puts("IN");
	queue<int> que;
	// memset(dis,0x3f,sizeof(dis));
	for(int i = 1;i <= T;i++)dis[i] = INF;
	memset(book,0,sizeof(book));
	memset(pre,0,sizeof(pre));
	que.push(S);book[S] = true;dis[S] = 0;
	while(!que.empty()){
		// puts("111111111");
		int u = que.front();que.pop();book[u] = false;
		// printf("head:%d\n",u);
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
			// printf("%d ->%d,%d %d %d %d %d\n",i,e[i].to,e[i].cap,e[i].flow,dis[v],dis[u],e[i].cost);
			if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
				pre[v] = i;dis[v] = dis[u] + e[i].cost;
				if(!book[v]){que.push(v);book[v] = true;}
			}
		}
	}
	return pre[T] != 0;
}
pair<double,int> MCMF(int S,int T){
	double mincost = 0;int maxflow = 0;
	while(SPFA(S,T)){
		// puts("times");
		int fl = INF;
		for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
			fl = min(fl,e[i].cap - e[i].flow);
			// printf("%d %d\n",fl,e[i ^ 1].to);
		}
		mincost += fl * dis[T];maxflow += fl;
		for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
			e[i].flow += fl;
			e[i ^ 1].flow -= fl;
		}
	}
	return make_pair(mincost, maxflow);
}

int id[2][maxn], totpoint;
int x[maxn], y[maxn];

void main(){
    n = read();
    for(int i = 1;i <= n;i++){
        x[i] = read(), y[i] = read();
        id[0][i] = ++totpoint;id[1][i] = ++totpoint;
        // printf("i = %d, 0 = %d  1 = %d\n",i,id[0][i],id[1][i]);
    }
    int S = ++totpoint;int T = ++totpoint;
    for(int i = 1;i <= n;i++){
        addd(S,id[0][i],2,0);addd(id[1][i],T,1,0);
        for(int j = 1;j <= n;j++){
            if(i == j || y[i] <= y[j])continue;
            addd(id[0][i],id[1][j],1,sqrt((double)(y[i] - y[j]) * (y[i] - y[j])
                                        + (double)(x[i] - x[j]) * (x[i] - x[j])));
        }
    }
    auto tmp = MCMF(S,T);
    // for(int i = 2;i <= tot;i++){
    //     printf("%d -> %d,cap = %d, cost = %.6lf, flow = %d\n",e[i ^ 1].to,e[i].to,e[i].cap,e[i].cost,e[i].flow);
    // }
    // printf("flow = %d, cost = %.6lf\n",tmp.second,tmp.first);
    if(tmp.second != n - 1){puts("-1");}
    else printf("%.6lf\n",tmp.first);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}