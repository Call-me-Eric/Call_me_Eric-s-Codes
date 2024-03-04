#include<bits/stdc++.h>
using namespace std;

const int N=1e5+7;
vector<int> G[N];
int a[N],b[N],c[N],d[N],e[N],f[N];
int dis[N];
int n,m;

void dfs(int u,int father){
	dis[u]=f[u];
	int maxx=0;
	for(int k:G[u]){
		if(k!=father) dfs(k,u),maxx=max(dis[k],maxx);
	}
	dis[u]+=maxx;
}

int main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d%d%d%d",&a[i],&b[i],&c[i],&d[i],&e[i],&f[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i<j&&a[i]<=a[j]&&b[i]<=b[j]&&c[i]<=c[j]&&d[i]<=d[j]&&e[i]<=e[j]) G[j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		memset(dis,0,sizeof dis);
		dfs(i,0);
		printf("%d\n",dis[i]);
	}
	return 0;
}
