#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MOD=998244353;
const int N=1e3+7;

int n,K;
int col[N];
int f[N][N];
vector<int> G[N];
int sum[N];

void DFS(int u,int father){
	if(!col[u]){
		for(int i=1;i<=K;i++) f[u][i]=1;
	}
	else f[u][col[u]]=1;
	for(int k:G[u]) if(k!=father){
		DFS(k,u);
		for(int i=1;i<=K;i++) if(f[u][i]){
			f[u][i]=f[u][i]%MOD*((sum[k]-f[k][i]+MOD)%MOD)%MOD;f[u][i]%=MOD;
		}
	}
	for(int i=1;i<=K;i++) sum[u]+=f[u][i],sum[u]%=MOD;
}

signed main(){
//	freopen("data.txt","r",stdin);
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%lld%lld",&n,&K);
	for(int i=1;i<=n;i++) scanf("%lld",&col[i]);
	for(int i=1;i<n;i++){
		int u,v;scanf("%lld%lld",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	DFS(1,0);
//	for(int i=1;i<=n;i++) printf("%lld\n",sum[i]);
	printf("%lld\n",(sum[1]+MOD)%MOD);
	return 0;
}
