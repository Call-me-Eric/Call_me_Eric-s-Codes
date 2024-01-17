#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define ll long long
#define int ll
const int N=2e3+5;
const int M=2e3+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=998244353;
inl int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inl void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inl void writei(int x){write(x);putchar(' ');}
inl void writel(int x){write(x);putchar('\n');}
int n,k,u,v,c,col[N],g[N],f[N][N];
int head[N],to[N],nxt[N],cnt;
inl void add(int u,int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
inl void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==fa)continue;
		dfs(y,x);
		for(int kk=1;kk<=k;kk++)
			f[x][kk]=(g[y]-f[y][kk]+mod)%mod*f[x][kk]%mod;
	}
	for(int kk=1;kk<=k;kk++)g[x]=(g[x]+f[x][kk])%mod;
}
signed main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=n;i++)col[i]=read();
	for(int i=1;i<=n;i++){
		if(col[i]){f[i][col[i]]=1;continue;}
		for(int kk=1;kk<=k;kk++)f[i][kk]=1;
	}
	for(int i=1;i<=n-1;i++){
		u=read();v=read();
		add(u,v);add(v,u);
	}dfs(1,0);
	writel(g[1]);
	return 0;
}


