#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+10,mod=998244353;
inline void Add(int &x,int y){x=(x+y)%mod;}
vector<int>e[MAXN];
int n,K,c[MAXN],tot;
namespace subtask1
{
	const int maxn=3e3+10;
	int f[maxn][maxn],sum[maxn];
	inline void dfs(int x,int fa)
	{
		for(auto y:e[x]) if(y!=fa) dfs(y,x);
		if(c[x])
		{
			f[x][c[x]]=1;
			for(auto y:e[x]) if(y!=fa)
				f[x][c[x]]=f[x][c[x]]*(sum[y]-f[y][c[x]])%mod;
		}
		else
		{
			for(int i=1;i<=tot+1;i++) f[x][i]=1;
			for(auto y:e[x]) if(y!=fa)
			{
				for(int i=1;i<=tot;i++)
					f[x][i]=(f[x][i]*(sum[y]-f[y][i])%mod+mod)%mod; 
				f[x][tot+1]=f[x][tot+1]*(sum[y]-f[y][tot+1])%mod; 
			}
		}
		for(int i=1;i<=tot;i++) Add(sum[x],f[x][i]); 
		Add(sum[x],f[x][tot+1]*(K-tot)%mod); 
			
	}
	inline void solve()
	{
		dfs(1,0);
		cout<<sum[1]<<endl;
	}
	
}
vector<int>lsh;
inline void solve()
{
	cin>>n>>K;
	for(int i=1;i<=n;i++) cin>>c[i],lsh.push_back(c[i]);
	sort(lsh.begin(),lsh.end());
	lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
	tot=(int)lsh.size()-1;
	for(int i=1;i<=n;i++) c[i]=lower_bound(lsh.begin(),lsh.end(),c[i])-lsh.begin();
	for(int i=1,x,y;i<n;i++) cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	subtask1::solve();
}
signed main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
