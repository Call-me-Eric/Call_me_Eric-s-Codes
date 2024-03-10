//router
//n<=1e6,a<=1e9
//树形DP
//对于每个节点 我们仅考虑其被自己覆盖,儿子覆盖,父亲覆盖并累加答案即可
 
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1000009;
int n;
int a[maxn];
 
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}

int cnt,head[maxn*2];
int dp[maxn][4];//自己,儿子,父亲

struct node
{
    int v,nxt;	
}e[maxn*2];

inline void add(int u,int v)
{
	++cnt;
	e[cnt].v = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
} 

inline void dfs(int u,int fa)
{
	dp[u][0] = a[u];
	int sum = 0;
	int maxx = 0x7fffffff;
	for(int v,i=head[u];i;i=e[i].nxt)
	{
		v = e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
		dp[u][1]+=min(dp[v][0],dp[v][1]);
		if(dp[v][0]<dp[v][1]) sum++;
		else
		{
			maxx = min(dp[v][0]-dp[v][1],maxx);
		}
		dp[u][2]+=min(dp[v][0],dp[v][1]);
		
	}
	if(sum==0)
	{
		dp[u][1]+=maxx;
	}
}
signed main()
{
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	
	n = read();
	for(int i=1;i<=n;i++)
	{
		a[i] = read();
	}
    for(int i=1;i<=n-1;i++)
	{
		int u,v;
		u = read(),v = read();
		add(u,v);
		add(v,u);
	}	
	dfs(1,0);
	
    int ans = min(dp[1][0],dp[1][1]);
    printf("%lld",ans);
	return 0;
}
