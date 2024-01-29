#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
bool st;
const int maxn = 1e6 + 10, mod = 998244353,INF = 0x3f3f3f3f;
int n, a[maxn], b[maxn];

struct edge{
	int to, nexte, cap,flow;
	edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn << 2];
int head[maxn << 1], tot = 1;
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap); add(v, u, 0);}


int dis[maxn << 1], cur[maxn << 1];
queue<int> que;
int dfs(int u,int flow,int T){
	if(u == T || !flow)return flow;
	int res = 0;
	for(int i = cur[u];i;i = e[i].nexte){
		int v = e[i].to;cur[u] = i;
		if(e[i].cap > e[i].flow && dis[v] == dis[u] + 1){
			int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
			if(!tmp)dis[v] = INF;
			e[i].flow += tmp;e[i ^ 1].flow -= tmp;
			res += tmp;flow -= tmp;
			if(!flow)break;
		}
	}
	return res;
}
bool bfs(int S,int T){
	for(int i = 1;i <= T;i++){dis[i] = INF;cur[i] = 0;}
	while(!que.empty())que.pop();
	que.push(S);dis[S] = 0;cur[S] = head[S];
	while(!que.empty()){
		int u = que.front();que.pop();
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
			if(e[i].cap > e[i].flow && dis[v] == INF){
				dis[v] = dis[u] + 1;cur[v] = head[v];
				que.push(v);
			}
		}
	}
	return cur[T] != 0;
}
void initflow(){for(int i = 1;i <= tot;i++)e[i].flow = 0;}
int Dinic(int S,int T){
	int mxflow = 0;
	while(bfs(S,T))mxflow += dfs(S,INF,T);
	return mxflow;
}

int fa[maxn << 1];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

vector<int> vec[maxn];int book[maxn];bool flags[maxn];
bool ed;
signed main(){
//	cerr << (&ed - &st) / 1024 / 1024 << endl;
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	n = read();long long ans = 1;int S = n * 2 + 1,T = n * 2 + 2;
	for(int i = 1;i <= n;i++){a[i] = read();ans = (ans * (long long)n) % (long long)mod;}
	for(int i = 1;i <= n;i++){b[i] = read();}
	for(int i = 1;i <= n;i++){
		addd(S,i,1);addd(i + n,T,1);
		addd(i,a[i] + n,1);addd(i,b[i] + n,1);
	}
	if(Dinic(S,T) < n){printf("%lld\n",ans);return 0;}
	
	long long times = 1;tot = 1;
	head[S] = head[T] = 0;
	for(int i = 1;i <= n;i++){
		fa[i] = fa[i + n] = i;head[i] = head[i + n] = 0;
		if(a[i] == b[i]){flags[a[i]] = 1;times = times * (long long)n % (long long)mod;}
	}
	for(int i = 1;i <= n;i++){
		addd(i + n,T,1);
		if(a[i] != b[i]){
			if(!flags[a[i]]){
				addd(i,a[i] + n,1);
				if(getf(a[i] + n) != getf(i))fa[getf(a[i] + n)] = getf(i);
			}
			if(!flags[b[i]]){
				addd(i,b[i] + n,1);
				if(getf(b[i] + n) != getf(i))fa[getf(b[i] + n)] = getf(i);
			}
		}
	}
	
	int totblock = 0;
	for(int i = 1;i <= n;i++){
		if(!book[getf(i)])book[getf(i)] = ++totblock;
		vec[book[getf(i)]].push_back(i);
	}
	
//	printf("totblock = %d\n",totblock);
	long long cnt = 1;
	for(int i = 1;i <= totblock;i++){
		for(int j : vec[i]){
			addd(S,j,1);
			for(int k = head[j];k;k = e[k].nexte)e[k].flow = 0;
		}
		int res = Dinic(S,T);long long flag = 1;
		vector<int> tmp;tmp.clear();
//		printf("res = %d\n",res);
		for(int j : vec[i]){
			for(int k = head[j];k;k = e[k].nexte)
				if(e[k].cap == e[k].flow && e[k].flow == 1){
					tmp.push_back(k);break;}
		}
		for(int k : tmp){
			for(int j : vec[i])for(int k = head[j];k;k = e[k].nexte)e[k].flow = 0;
//			initflow();
			e[k].cap = 0;if(Dinic(S,T) == res){flag = 2;break;}
		}
		cnt = cnt * flag % (long long)mod;
	}
	printf("%lld\n",(ans - cnt * times % mod + mod) % mod);
	
	return 0;
}
