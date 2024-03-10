#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e6+7;
vector<int> G[N];
int f[N][4];
int fa[N];
int a[N];
int n;
int son[N];

char buf[1<<24] , *p1 , *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<24,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x = 0 , f = 1;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f ;
}

void dfs(int u,int father){
	fa[u]=father;
	for(int k:G[u]){
		if(k!=father) dfs(k,u),son[u]++;
	}
}

void DFS(int u,int father){
	f[u][1]=a[u];
	if(!son[u]) f[u][0]=0x3f3f3f3f;
	bool flag=1;
	int minn=0x3f3f3f3f;
	for(int k:G[u]){
		if(k!=father){
			DFS(k,u);
			f[u][0]+=min(f[k][1],f[k][0]);
			if(son[k]) f[u][1]+=min(f[k][1],f[k][0]);
			if(f[k][0]>=f[k][1]) flag=0;
			minn=min(minn,f[k][1]-f[k][0]); 
		}
	}
	if(flag&&son[u]){
		f[u][0]+=minn;
	}
}

signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n-1;i++){
		int u,v;u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs(1,0);
	DFS(1,0);
	printf("%lld\n",min(f[1][0],f[1][1]));
	return 0;
}
