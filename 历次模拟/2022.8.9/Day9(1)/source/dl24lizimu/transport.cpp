#include<bits/stdc++.h>
using namespace std;
const int N=7001;
int n;
long long ans=0;
int a[N],b[N];
int e[N][N],dis[N][N],vis[N];
void dfs1(int x){
	for(int i=1;i<=n;i++){
		if(e[x][i]<=b[x]&&(!vis[i])){
			ans++;
			b[i]=b[x]-e[x][i]+a[i];
			vis[i]=1;
			dfs1(i);
		}
	}
}
void dfs(int x){
	vis[x]=1;
	for(int i=1;i<=n;i++){
		if(e[x][i]<=a[x]&&(!vis[i])){
			ans++;
			vis[i]=1;
			b[i]=a[x]-e[x][i]+a[i];
			dfs1(i);
		}
	}
	return;
}
int main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	memset(e,0x3f3f3f3f,sizeof(e));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n-1;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]=w;e[v][u]=w;
	}
	for(int i=1;i<=n;i++){
		memset(b,0,sizeof(b));
		memset(vis,0,sizeof(vis));
		dfs(i);
	}
	printf("%lld\n",ans);
	return 0;
}
