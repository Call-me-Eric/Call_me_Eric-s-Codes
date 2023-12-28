#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
int read()
{
	char ch;
	int s=1;
	while((ch=getchar())<'0' || ch>'9')
	  if(ch=='-')
	    s=-1;
	int res=ch-'0';
	while((ch=getchar())>='0' && ch<='9')
	  res=res*10+ch-'0';
	return res*s;
}
int n=100,m=100,k;
int a[100001];
ll c[5001][5001];
ll f[5001][5001];
ll ans=0;
int main()
{
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
	n=read(),m=read();
	k=max(n,m);
	for(int i=1;i<=n;i++)
	  a[i]=read(); 
	for(int i=0;i<=k;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		  c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++)
	{
		f[i][0]=0;
		for(int j=1;j<=n;j++)
		  f[i][j]=(f[i-1][j-1]+f[i-1][j]*2LL*j)%mod;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j+i<=n;j++)
		{
			ans=(ans+f[m][n-j-1]*c[n-j-1][i-1])%mod;
			if(a[i+j+1]<a[i+j])
			  break;
		}
	}
	for(int i=0;i<=n;i++)
	  ans+=f[m][n]*c[n][i]%mod;
	printf("%lld",ans%mod);
}
