#include<iostream>
#include<cstdio>
#include<cassert>
#define erg(x,i) for(int i=head[x];i;i=e[i].next)
using namespace std;
const int MAXN=310,MAXM=MAXN*MAXN;
bool chs[MAXM];
int n,m,fa[MAXN],head[MAXN],col[MAXM],f[3],g[3],tot=1;
int st[MAXN],stpos;
struct Edge {int fr,to,next,dis;}e[MAXM<<1];
void Addedge(int u,int v,int w) {
	e[++tot].to=v,e[tot].fr=u,e[tot].next=head[u],e[tot].dis=w,head[u]=tot;
	e[++tot].to=u,e[tot].fr=v,e[tot].next=head[v],e[tot].dis=w,head[v]=tot;
}
int Getfa(int x) {
	if(!fa[x]) return x;
	return fa[x]=Getfa(fa[x]);
}
bool Dfs(int x,int fa,int goal) {
	if(x==goal) return 1;
	erg(x,i) {
		int v=e[i].to;
		if(v==fa||!chs[e[i].dis]) continue;
		st[++stpos]=e[i].dis;
		if(Dfs(v,x,goal)) return 1;
		stpos--;
	}
	return 0;
}
int main() {
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin>>g[0]>>g[1]>>g[2]>>m; n=g[0]+g[1]+g[2]+1;
	for(int i=1;i<=m;i++) {
		int u,v; char w; cin>>u>>v>>w;
		col[i]=(w=='r'?0:(w=='g'?1:2));
		Addedge(u,v,i);
	}
	for(int i=2;i<=tot;i+=2) {
		if(Getfa(e[i].fr)!=Getfa(e[i].to)) {
			fa[Getfa(e[i].fr)]=Getfa(e[i].to);
			chs[e[i].dis]=1,f[col[e[i].dis]]++;
		}
	}
	if(f[0]+f[1]+f[2]<n-1) {cout<<"NO"<<endl; return 0;}
	for(int i=1;i<=m;i++) {
		if(chs[i]||f[col[i]]>=g[col[i]]) continue;
		stpos=0; bool flag=0;
		assert(Dfs(e[i<<1].fr,0,e[i<<1].to));
		for(int j=1;j<=stpos;j++) {
			if(f[col[st[j]]]>g[col[st[j]]]) {
				flag=1,chs[st[j]]=0,chs[i]=1;
				f[col[st[j]]]--,f[col[i]]++;
			}
		}
	}
	if(f[0]!=g[0]||f[1]!=g[1]||f[2]!=g[2]) cout<<"NO"<<endl;
	else {
		cout<<"YES"<<endl;
		for(int i=1;i<=m;i++) cout<<chs[i]; cout<<endl;
	}
	return 0;
}