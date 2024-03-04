#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define re register
#define int long long
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 4e5+10;
int a[M],vis[M],dis[M],head[M],siz[M],maxp[M];
int tmp[M],tot[M];
int n;
int edgecnt,ans,root,sum,tmpcnt;
struct edge{
	int to,nxt,w;
}e[M];
inline void add(int u,int v,int w){
	e[++edgecnt].to = v;
	e[edgecnt].w = w;
	e[edgecnt].nxt = head[u];
	head[u] = edgecnt;
}
inline void getroot(int u,int fa){
	siz[u] = 1,maxp[u] = 0;
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa || vis[v]) continue;
		getroot(v,u);
		siz[u] += siz[v];
		if(siz[v] > maxp[u]) maxp[u] = siz[v];
	}
	maxp[u] = max(maxp[u],sum-siz[u]);
	if(maxp[u] < maxp[root]) root = u;
}
inline void getdis(int u,int fa,int s){
	if(dis[u] >= 0) tmp[s]++;
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v] || v==fa) continue;
		dis[v] = dis[u] + a[v] - e[i].w;
		getdis(v,u,s);
	}
}
inline void solve(int u){
	tmpcnt = 0;
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		dis[v] = a[u];
		getdis(v,u,++tmpcnt);
		rep(j,1,tmpcnt-1) ans += tmp[tmpcnt]*tmp[j];
	}
//	if(tmpcnt == 1) ans += tmp[1];
	rep(i,1,tmpcnt) tmp[i] = 0;
}
inline void work(int u){
	vis[u] = 1;
	solve(u);
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		maxp[root = 0] = sum = siz[v];
		getroot(v,0);
		getroot(root,0);
		work(v);
	}
}
signed main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read();
	rep(i,1,n) a[i] = read();
	rep(i,1,n-1){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	maxp[0] = sum = n;
	getroot(1,0);
	getroot(root,0);
	work(root);
	printf("%lld\n",ans);
	return 0;
}

/*
2
3 1
1 2 2
*/
/*
5
3 1 2 4 5
1 2 3
3 2 2
4 2 6 
5 4 3
*/
