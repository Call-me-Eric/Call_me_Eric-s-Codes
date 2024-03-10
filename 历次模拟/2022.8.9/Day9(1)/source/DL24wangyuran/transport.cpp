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
const int N=1e5+5;
int n,a[N];
int head[N],cnt;
struct qwq{
	int v,nxt,w;
}e[N<<1];
inline void add(int u,int v,int w){
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int dep[N],f[N][25],ww[N];
inline void dfs(int x,int fa){
	dep[x]=dep[fa]+1,f[x][0]=fa;
	ff(i,1,20) f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa) ww[v]=e[i].w,dfs(v,x);
	}
}
inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
inline bool qaq(int tp,int x,int &sum){
	if(x==tp){sum+=a[x];return 1;}
	if(!qaq(tp,f[x][0],sum)) return 0;
	sum-=ww[x];
	if(sum<0) return 0;
	sum+=a[x];
	return 1;
}
signed main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read();
	ff(i,1,n) a[i]=read();
	int u,v,w;
	ff(i,2,n){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	ll ans=0;
	ff(i,1,n) ff(j,1,n){
		int x=i,y=j;
		if(x==y) continue;
		int zz=lca(x,y),sum=0,flag=1;
		while(x!=zz){
			sum+=a[x]-ww[x],x=f[x][0];
			if(sum<0){flag=0;break;}
		}
		if(!flag) continue;
		if(qaq(zz,y,sum)) ++ans;
	}
	printf("%lld",ans);
	return 0;
}
