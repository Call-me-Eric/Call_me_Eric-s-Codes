#include<iostream>
#include<cstdio>
#include<map>
#define N 40
#define mod 998244353
using namespace std;
int read()
{
    char c=0;
    int sum=0;
    while (c<'0'||c>'9') c=getchar();
    while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
    return sum;
}
void Adder(int &x,int d)
{
    x+=d;
    if (x>=mod) x-=mod;
    return;
}
struct reads
{
    int d[N+1];
    bool operator < (const reads &t)const
    {
	for (int i=1;i<=40;++i)
	    if (d[i]!=t.d[i])
		return d[i]<t.d[i];
	return 0;
    }
};
reads s,t,x,y;
map<reads,int>dp[N+1];
int n,m,k,q,a[N+1],b[N+1];
int main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    n=read();
    for (int i=1;i<=n;++i) s.d[i]=read();
    m=read();
    for (int i=1;i<=m;++i) t.d[i]=read();
    q=read();
    while (q--)
    {
	k=read();
	for (int i=0;i<=k;++i) dp[i].clear();
	dp[0][s]=1;
	for (int i=1;i<=k;++i)
	    for (auto it:dp[i-1])
	    {
		for (int j=1;j<=40;++j) x.d[j]=it.first.d[j];
		for (int j=1;j<=40;++j)
		{
		    if (j==1||x.d[j-1]!=x.d[j]) y=x,y.d[j]++,Adder(dp[i][y],it.second);
		    if (x.d[j]&&(j==40||x.d[j]!=x.d[j+1])) y=x,y.d[j]--,Adder(dp[i][y],it.second);
		}
	    }
	printf("%d\n",dp[k][t]);
    }
    return 0;
}
