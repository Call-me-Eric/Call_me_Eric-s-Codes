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
const int N = 1e6 + 5;
int n,m;
vector<int>g1[N],g2[N],g3[N];
#define pb push_back
int in[N],in1[N],in2[N],out2[N],out1[N],dfn[N],low[N],sccnum[N],scccnt,dfncnt,sta[N],top,tag[N];
vector<int>ans;
long long f[N],g[N],outs;
void dfs1(int u){
	dfn[u] = low[u] = ++dfncnt;
	sta[++top] = u;
	for(int v : g1[u]){
		if(!dfn[v]){
			dfs1(v);
			low[u] = min(low[u],low[v]);	
		}
		else if(!sccnum[v])low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		++scccnt;
		while(1){
			int x = sta[top--];
			sccnum[x] = scccnt;
			if(x == u)break;
		}
	}
}
int flag = 0;
inline void topo(vector<int> g[],long long f[],int in[],int out[]){
	queue<int>q;
	
	rep(i,1,scccnt)if(!in[i])q.push(i),f[i]=1;
	while(!q.empty()){
		int u = q.front();
		if(!flag && !out[u]){
			outs += f[u];	
		}
		q.pop();
		for(int v : g[u]){
			f[v] += f[u];
			if(!--in[v])q.push(v);
		}
	}
	flag = 1;
}
inline void solve(){
	rep(i,1,n)if(!dfn[i])dfs1(i);
	rep(i,1,n){
		for(int j : g1[i]){
			if(sccnum[i] != sccnum[j]){
				++in1[sccnum[j]];++out1[sccnum[i]];	
				++in2[sccnum[i]];++out2[sccnum[j]];
				++in[sccnum[j]];
				g2[sccnum[i]].pb(sccnum[j]);
				g3[sccnum[j]].pb(sccnum[i]);
			}
		}
	}
	topo(g2,f,in1,out1);topo(g3,g,in2,out2);
	queue<int>q;
	rep(i,1,scccnt)if(!in[i])q.push(i);
	while(!q.empty()){
		int u = q.front();q.pop();
		if(g[u] * f[u] == outs)tag[u] = 1;
		for(int v : g2[u]){
			if(!--in[v])q.push(v);
		}
	}
	rep(i,1,n)if(tag[sccnum[i]])ans.push_back(i);
}

signed main(){
//	double be = clock();
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	read(n,m);
	rep(i,1,m){
		int u,v;
		read(u,v);
		g1[u].pb(v);
	}
	solve();
	printf("%d\n",ans.size());
	sort(ans.begin(),ans.end());
	for(int x : ans)printf("%d ",x);
//	double ed = clock();
//	printf("\n%lf",(ed-be)/CLOCKS_PER_SEC);
}

