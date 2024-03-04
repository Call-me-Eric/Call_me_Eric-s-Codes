#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define il inline
#define rg register
#define lch(x) ((x)<<1)
#define rch(x) ((x)<<1^1)
#define rep(i,st,ed) for(rg int i=(st);i<=(ed);++i)
#define per(i,ed,st) for(rg int i=(ed);i>=(st);--i)
#define rep0(i,n) for(rg int i=0;i<(n);++i)
#define per0(i,n) for(rg int i=(n)-1;i>=0;--i)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double dbl;
typedef long double ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
template<typename T> il T qmin(const T &x,const T &y){return x<y?x:y;}
template<typename T> il T qmax(const T &x,const T &y){return x>y?x:y;}
template<typename T> il void getmin(T &x,const T &y){if(y<x) x=y;}
template<typename T> il void getmax(T &x,const T &y){if(y>x) x=y;}
il void fileio(const string &s){
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

const int inf=(int)1e9+7;
const ll linf=(ll)1e18+7;
const int N=1e6+7,M=1e6+7;

il void read(int &x){
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	x=ch-'0';
	while((ch=getchar())>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0';
}

char s[105];
il void print(int x){
	int cnt=0;
	do{
		s[++cnt]=x%10+48;
		x/=10;
	}while(x);
	per(i,cnt,1) putchar(s[i]);
}

int x[M],y[M];
vector<int> g[N];
int scc[N],dfn[N],low[N];
int stk[N],top;
int dfsclock,cnt;
bool kicked[N],inuse[N];
vector<int> g1[N],g2[N];
int n,m;

il void dfs(int u){
	dfn[u]=low[u]=++dfsclock;
	stk[++top]=u;
	rep0(i,g[u].size()){
		int v=g[u][i];
		if(!dfn[v]){
			dfs(v);
			getmin(low[u],low[v]);
		}else if(!scc[v]){
			getmin(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(stk[top]!=u) scc[stk[top--]]=cnt;
		scc[u]=cnt;
		--top;
	}
}

namespace task1{
	const int N=5005;
	bool vis1[N],vis2[N];
	vector<int> g2[N];
	
	il void dfs1(int u){
		if(vis1[u]) return;
		vis1[u]=true;
		rep0(i,g[u].size()) dfs1(g[u][i]);
	}
	
	il void dfs2(int u){
		if(vis2[u]) return;
		vis2[u]=true;
		rep0(i,g2[u].size()) dfs2(g2[u][i]);
	}

	il void solve(){
		rep(i,1,m){
			read(x[i]),read(y[i]);
			g[x[i]].pb(y[i]);
			g2[y[i]].pb(x[i]);
		}
		vector<int> ans(0);
		rep(u,1,n){
			memset(vis1+1,0,sizeof(bool)*n);
			memset(vis2+1,0,sizeof(bool)*n);
			dfs1(u);
			dfs2(u);
			bool flag=true;
			rep(i,1,n) if(!vis1[i]&&!vis2[i]){
				flag=false;
				break;
			}
			if(flag) ans.pb(u);
		}
		printf("%d\n",ans.size());
		rep0(i,ans.size()) printf("%d ",ans[i]);
		puts("");
	}
}

int main(){
//	fileio("test");
	fileio("goood");
	read(n),read(m);
	if(n<=5000&&m<=5000) return task1::solve(),0;
	rep(i,1,m){
		read(x[i]),read(y[i]);
		g[x[i]].pb(y[i]);
	}
	dfsclock=cnt=0;
	rep(i,1,n){
		if(!dfn[i]) dfs(i);
	}
	rep(i,1,m){
		if(scc[x[i]]==scc[y[i]]) continue;
		g1[scc[x[i]]].pb(scc[y[i]]);
		g2[scc[y[i]]].pb(scc[x[i]]);
	}
	int cur=0;
	rep(u,1,cnt){
		rep0(i,g1[u].size()){
			int v=g1[u][i];
			if(!inuse[v]) continue;
			--cur;
			inuse[v]=false;
		}
		if(cur) kicked[u]=true;
	//	cerr<<u<<" "<<cur<<endl;
		++cur;
		inuse[u]=true;
	}
	cur=0;
	per(u,cnt,1){
		rep0(i,g2[u].size()){
			int v=g2[u][i];
			if(!inuse[v]) continue;
			--cur;
			inuse[v]=false;
		}
		if(cur) kicked[u]=true;
	//	cerr<<" "<<u<<" "<<cur<<endl;
		++cur;
		inuse[u]=true;
	}
	int ans=0;
	rep(i,1,n) ans+=(!kicked[scc[i]]);
//	printf("%d\n",ans);
	print(ans),putchar('\n');
	rep(i,1,n) if(!kicked[scc[i]]) print(i),putchar(' ');
	putchar('\n');
	return 0;
}

