#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10, maxm = 5e4 + 10, INF = 0x3f3f3f3f3f3f;
int S, T;
int head[maxn], tot = 1;
struct edge{
	int to, nexte, cap,flow, cost;
	edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(t),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn];bool book[maxn];int dis[maxn];
bool SPFA(){
	queue<int> que;
	for(int i = 1;i <= T;i++)dis[i] = INF;
	memset(book,0,sizeof(book));
	memset(pre,0,sizeof(pre));
	que.push(S);book[S] = true;dis[S] = 0;
	while(!que.empty()){
		int u = que.front();que.pop();book[u] = false;
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
			if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
				pre[v] = i;dis[v] = dis[u] + e[i].cost;
				if(!book[v]){que.push(v);book[v] = true;}
			}
		}
	}
	return pre[T] != 0;
}
vector<pair<int,int> > pr;
void MCMF(int S,int T){
	int mincost = 0, maxflow = 0;
	while(SPFA()){
		int fl = INF;//printf("maxflow = %d\n",maxflow);
		for(int i = pre[T];i;i = pre[e[i ^ 1].to])
			fl = min(fl,e[i].cap - e[i].flow);
		mincost += fl * dis[T];maxflow += fl;
		for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
			e[i].flow += fl;e[i ^ 1].flow -= fl;
		}
	    pr.push_back(make_pair(mincost, maxflow));
	}
}
int n, m, q;

void main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){u = read(); v = read(); w = read();addd(u, v, 1, w);}
    S = 1;T = n; MCMF(S,T); q = read();
    while(q--){
        int x = read(); double res = 1e10;
        for(auto d : pr){res = min(res,(double)(d.first + x) / d.second);}
        printf("%.10lf\n",res);
    }
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