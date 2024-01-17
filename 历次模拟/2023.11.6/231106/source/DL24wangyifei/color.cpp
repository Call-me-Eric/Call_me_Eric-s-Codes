#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
	long long xr=0,F=1; char cr;
	while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
	while(cr>='0'&&cr<='9') 
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
#define int long long
const int N=1005,mod=998244353;
int n,k,col[N];
vector<int> e[N];
int f[N][N],sum[N];
void dfs(int u,int fa)
{
	if(col[u]) f[u][col[u]]=1;
	else for(int i=1;i<=k;i++) f[u][i]=1;
	for(auto v:e[u]) if(v^fa)
	{
		dfs(v,u);
		for(int i=1;i<=k;i++) f[u][i]=f[u][i]*(sum[v]-f[v][i]+mod)%mod;
	}
	for(int i=1;i<=k;i++) sum[u]=(sum[u]+f[u][i])%mod;
}
signed main()
{
	freopen("color.in","r",stdin); 
	freopen("color.out","w",stdout); 
	n=read(),k=read();
	for(int i=1;i<=n;i++) col[i]=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	dfs(1,0);
	printf("%lld\n",sum[1]);
	return 0;
}
