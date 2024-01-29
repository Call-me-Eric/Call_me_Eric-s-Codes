#include<bits/stdc++.h>
using namespace std;
bool stmemory;
inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e4 + 10,maxm = 1e6 + 10, INF = 0x3f3f3f3f ,maxN = 2e5 + 10;
int n, m;

int head[maxN], tot = 1;
struct edge{
	int to, nexte, cap, flow;
	edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}
int total, mx;

int dep[maxN], cur[maxN];
int dfs(int u,int flow,int T){
	// printf("%lld\n",u);
	if(u == T)return flow;
	int rest = 0, tmp = 0;
	for(int i = cur[u];i && flow;i = e[i].nexte){
		cur[u] = i; int v = e[i].to;
		if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
			tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
			if(tmp == 0)dep[v] = INF;
			e[i].flow += tmp; e[i ^ 1].flow -= tmp;
			flow -= tmp;rest += tmp;
			if(!flow)return rest;
		}
	}
	return rest;
}
bool bfs(int S,int T){
	queue<int> que;
	for(int i = 1;i <= total;i++){dep[i] = INF;cur[i] = 0;}
	que.push(S);dep[S] = 1; cur[S] = head[S];
	while(!que.empty()){
		int u = que.front(); que.pop();
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
			if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
				que.push(v);
				cur[v] = head[v];
				dep[v] = dep[u] + 1;
				if(v == T)return 1;
			}
		}
	}
	return 0;
}
int Dinic(int S,int T){
	int mxflow = 0;
	while(bfs(S,T)){mxflow += dfs(S,INF,T);}
	return mxflow;
}
int a[maxn], b[maxn], w[maxn], l[maxn], r[maxn], p[maxn];
int id[maxn][2];

struct Segment_Tree{
	int tot, rt;
	struct node{
		int id, ls, rs;
		node(int id = 0,int ls = 0,int rs = 0):id(id),ls(ls),rs(rs){}
	}d[maxn << 4];
	vector<int> vec[maxn << 4];
	void insert(int l,int r,int pos,int p1,int p2,int i){
		if(!d[p2].id)d[p2].id = ++total;
		if(l == r){
			vec[p2] = vec[p1];
			vec[p2].push_back(id[i][1]);
			for(int v : vec[p2]){addd(d[p2].id,v,INF);}
			return;
		}
		int mid = l + r >> 1;
		if(pos <= mid){
			d[p2].rs = d[p2].rs; d[p2].ls = ++tot;
			insert(l,mid,pos,d[p1].ls,d[p2].ls,i);
		}
		else{
			d[p2].ls = d[p2].ls; d[p2].rs = ++tot;
			insert(mid + 1,r,pos,d[p1].rs,d[p2].rs,i);
		}
		if(d[p2].ls){addd(d[p2].id,d[d[p2].ls].id,INF);}
		if(d[p2].rs){addd(d[p2].id,d[d[p2].rs].id,INF);}
	}
	void insert(int i){int p = ++tot;insert(1,mx,a[i],rt,p,i);rt = p;}
	void query(int l,int r,int s,int t,int p,int u){
		if(!p)return;
		if(s <= l && r <= t){if(d[p].id)addd(u,d[p].id,INF);return;}
		int mid = l + r >> 1;
		if(s <= mid)query(l,mid,s,t,d[p].ls,u);
		if(mid < t)query(mid + 1,r,s,t,d[p].rs,u);
	}
	void query(int i){
		int virt = ++total;addd(id[i][0],virt,p[i]);
		query(1,mx,l[i],r[i],rt,virt);
	}
}tree;
bool edmemory;
vector<int> tmp;
signed main(){
	cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost\n";
	n = read();int S = ++total;int T = ++total, sum = 0;mx = 1e9;
	for(int i = 1;i <= n;i++){id[i][0] = ++total;id[i][1] = ++total;}
	for(int i = 1;i <= n;i++){
		a[i] = read(); b[i] = read(); w[i] = read(); l[i] = read();r[i] = read();p[i] = read();
		tmp.push_back(a[i]);sum += b[i] + w[i];
	}
	sort(tmp.begin(),tmp.end());tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
	mx = tmp.size();
	for(int i = 1;i <= n;i++){
		a[i] = lower_bound(tmp.begin(),tmp.end(),a[i]) - tmp.begin();
		l[i] = upper_bound(tmp.begin(),tmp.end(),l[i]) - tmp.begin();
		r[i] = upper_bound(tmp.begin(),tmp.end(),r[i]) - tmp.begin();
		addd(S,id[i][0],b[i]);addd(id[i][0],id[i][1],INF);addd(id[i][1],T,w[i]);
		tree.query(i);tree.insert(i);
	}
	printf("%d\n",sum - Dinic(S,T));
//	for(int i = 2;i <= tot;i += 2){
//		printf("%lld -> %lld , cap = %lld, flow = %lld\n",e[i ^ 1].to,e[i].to,e[i].cap,e[i].flow);
//	}
//	printf("S = %lld, T = %lld\n",S,T);
//	for(int i = 1;i <= n;i++){
//		printf("i = %lld:0 = %lld, 1 = %lld\n",i,id[i][0],id[i][1]);
//	}	
	return 0;
}
