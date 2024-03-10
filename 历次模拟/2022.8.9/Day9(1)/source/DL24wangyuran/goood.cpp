#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e6+5;
int n,m;
int head[N],cnt;
int h[N],cntt;
int h2[N],cnt1;
struct qwq{
	int u,v,nxt;
}e[N],e1[N],e2[N];
inline void add(int u,int v){
	e[++cnt].v=v;
	e[cnt].u=u;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
inline void addd(int u,int v){
	e1[++cntt].v=v;
	e1[cntt].u=u;
	e1[cntt].nxt=h[u];
	h[u]=cntt;
}
inline void addf(int u,int v){
	e2[++cnt1].v=v;
	e2[cnt1].u=u;
	e2[cnt1].nxt=h2[u];
	h2[u]=cnt1;
}
int dfn[N],low[N],tot,sccnum,jl[N],siz[N];
bool vis[N];
stack<int> s;
vector<int> y[N];
inline void tarjan(int x){
	dfn[x]=low[x]=++tot,vis[x]=1;
	s.push(x);
	for(int i(head[x]);i;i=e[i].nxt){
		int v=e[i].v;
		if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
		else if(vis[v]) low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x]){
		++sccnum;
		while(1){
			int u=s.top();s.pop();
			vis[u]=0,jl[u]=sccnum,++siz[sccnum];
			y[sccnum].push_back(u);
			if(u==x) break;
		}
	}
}
int in[N],out[N],num[N],num2[N];
int ans;
vector<int> res;
bool vis1[N],vis2[N];
inline void dfs(int x){
	vis1[x]=1;
	for(int i(h[x]);i;i=e1[i].nxt){
		int v=e1[i].v;
		if(vis1[v]) continue;
		dfs(v);
	}
}
inline void dfss(int x){
	vis2[x]=1;
	for(int i(h2[x]);i;i=e2[i].nxt){
		int v=e2[i].v;
		if(vis2[v]) continue;
		dfss(v);
	}
}
inline bool solve(int x){
	ff(i,1,sccnum) vis1[i]=vis2[i]=0;
	dfs(x);
	dfss(x);
	ff(i,1,sccnum) if(!vis1[i]&&!vis2[i]) return 0;
	return 1;
}
inline void T1(){
	queue<int> q;
	ff(i,1,sccnum) if(!in[i]) q.push(i);
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i(h[x]);i;i=e1[i].nxt){
			int v=e1[i].v;
			--in[v],num[v]+=num[x];
			if(!vis[v]) ++num[v];
			vis[v]=1;
			if(!in[v]) q.push(v);
		}
	}
	ff(i,1,sccnum) if(!out[i]) q.push(i);
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i(h2[x]);i;i=e2[i].nxt){
			int v=e2[i].v;
			--out[v],num2[v]+=num2[x];
			if(!vis[v]) ++num2[v];
			vis[v]=1;
			if(!out[v]) q.push(v);
		}
	}	
	ff(i,1,sccnum) if(num[i]+num2[i]>=sccnum-1){
		for(int j(0);j<y[i].size();++j) res.push_back(y[i][j]);
		ans+=siz[i];		
	}
}
signed main(){
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	n=read(),m=read();
	int u,v;
	ff(i,1,m){
		u=read(),v=read();
		add(u,v);
	}
	ff(i,1,n) if(!dfn[i]) tarjan(i);
//	ff(i,1,n) cout<<jl[i]<<' ';cout<<endl;
	ff(i,1,cnt){
		u=e[i].u,v=e[i].v;
		if(jl[u]!=jl[v]) addd(jl[u],jl[v]),++out[jl[u]],++in[jl[v]],addf(jl[v],jl[u]);
	}
	if(sccnum!=1){ff(i,1,sccnum) if(!in[i]&&!out[i]) return printf("0"),0;}
	else{
		printf("%d\n",n);
		ff(i,1,n) printf("%d ",i);
		return 0;
	}
	if(sccnum<=5000){
	ff(i,1,sccnum) if(solve(i)){
		ans+=siz[i];
		for(int j(0);j<y[i].size();++j) res.push_back(y[i][j]);
	}}
	else T1();
	printf("%d\n",ans);
	sort(res.begin(),res.end());
	for(int i(0);i<res.size();++i) printf("%d ",res[i]);
	return 0;
}
/*
6 7
1 2
1 3
2 4
3 4
4 5
5 6
6 5
*/
