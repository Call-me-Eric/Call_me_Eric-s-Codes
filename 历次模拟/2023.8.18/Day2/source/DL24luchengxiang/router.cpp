#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define ri register int 
const int N=2e6+5;
const int inf=INT_MAX;
int n,u,v,a[N];
ll f[N][2][2];
int head[N],nxt[N<<1],to[N<<1],cnt;
inl void add(int u,int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
inl int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
void dfs(int x,int faz){
	f[x][1][1]=a[x];
	if(!nxt[head[x]]){f[x][0][1]=inf;return;}
	ll ad=inf,de=inf;
	for(ri i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==faz)continue;
		dfs(y,x);
		f[x][0][0]+=f[y][0][1];
		f[x][1][1]+=min(f[y][1][1],min(f[y][0][1],f[y][0][0]));
		if(f[y][1][1]<ad){ad=f[y][1][1];de=min(f[y][0][1],f[y][1][1]);}
		f[x][0][1]+=min(f[y][0][1],f[y][1][1]);
	}
	f[x][0][1]=f[x][0][1]+ad-de;
}
signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n=read();
	for(ri i=1;i<=n;i++)a[i]=read();
	for(ri i=1;i<=n-1;i++){
		u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	printf("%lld\n",min(f[1][0][1],f[1][1][1]));
	return 0;
}

