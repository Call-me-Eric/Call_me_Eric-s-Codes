#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e2+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<30),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
int n,k,a[N][N];
int dp[N][N];
int f[N][N][N*N*4],mx;
void sb1()
{
	int re=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)a[i][j]=read()+105;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			dp[i][j]=max(dp[i-1][j]+a[i][j],dp[i-1][j-1]+a[i][j]);
		}
	}
	for(int i=1;i<=n;i++)re=max(re,dp[n][i]);
	cout<<re-n*105;
	exit(0);
}
struct no
{
	int x;
	inline bool operator < (const no &aa)const{return x>aa.x;}
};
priority_queue<no>q;
int ans[N],tot;
signed main()
{
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	n=read();k=read();
	if(k==1)sb1();
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=1;j<=i;j++)
		{
			a[i][j]=read()+105;
			sum=max(sum,a[i][j]);
		}
		mx+=sum;
	}
	f[1][1][a[1][1]]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			for(int k=a[i][j];k<=mx;k++)
			{
				f[i][j][k]+=(f[i-1][j][k-a[i][j]]+f[i-1][j-1][k-a[i][j]]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=a[n][i];j<=mx;j++)
		{
			int x=j-n*105;
			if(f[n][i][j])
			{
				if(q.size()<=k)
				{
					while(q.size()<k&&f[n][i][j])
					{
						q.push({x});
						f[n][i][j]--;
					}
				}
				if(!f[n][i][j])continue;
				if(x>q.top().x)
				{
					while(x>q.top().x&&f[n][i][j])
					{
						q.push({x});
						q.pop();
						f[n][i][j]--;
					}
				}
			}
		}
	}
	while(!q.empty())
	{
		ans[++tot]=q.top().x;
		q.pop();
	}
	sort(ans+1,ans+1+tot);
	cout<<ans[tot-k+1];
	return 0;
}
/*
3 3
1
3 2
1 1 100

*/
