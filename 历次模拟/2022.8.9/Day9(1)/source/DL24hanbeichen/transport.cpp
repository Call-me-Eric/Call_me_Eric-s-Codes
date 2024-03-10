#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i<(b);++i)
#define rrep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=0;
	while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(f)x=-x;
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
const int N = 1e5 + 5;
int n,a[N];
vector<pair<int,int>>g[N];
#define pb push_back
int fa[N][25],dep[N];
int val[N];
int cnt,rx[N],son[N],x[N];
void dfs(int u,int f){
	x[++cnt] = u;rx[u] = cnt;
	for(auto tmp : g[u]){
		int v = tmp.first;
		if(v == f)continue;
		son[u] = v;
		dfs(v,u);
	}
}
inline int check(int u,int v){
	int sum = 0;
	if(rx[u] > rx[v])swap(u,v);
	while(u != v){
		sum += a[u];
		for(auto tmp : g[u]){
			int v = tmp.first;
			if(v == son[u]){
				sum -= tmp.second;
				if(sum < 0)return 0;
			}	
		}
		u = son[u];
	}
	return 1;
}
inline void solve(int root){
	dfs(root,0);
	long long ans = 0;
	rep(i,1,n){
		rep(j,1,n){
			if(i == j)continue;
			ans += check(i,j);
		}
	}
}
signed main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	read(n);
	rep(i,1,n)read(a[i]);
	Rep(i,1,n){
		int u,v,w;
		read(u,v,w);
		g[u].pb({v,w});g[v].pb({u,w});	
	}
	int cnt = 0,root = 0;
	rep(i,1,n){
		if(g[i].size() == 1)++cnt,root = i;	
	}
	solve(root);
//	if(cnt == 2)solve1();
//	else solve();
}

