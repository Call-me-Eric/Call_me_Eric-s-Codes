#include<iostream>
#include<cstdio>
#define N 1000000
#define inf 1e9
using namespace std;
int read()
{
	char c=0;
	int sum=0;
	while (c<'0'||c>'9') c=getchar();
	while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
	return sum;
}
struct reads
{
	int p,r;
};
reads st[N+1];
int n,phin,k,rt,a[N+1],tong[N+1],leng,length,maxn=-inf;
bool used[N+1],vis[N+1];
void dfs(int x)
{
	if (x==leng+1)
	{
		int res=0;
		for (int i=0;i<n;++i) res+=used[i];
		if (res<=k&&res>maxn)
		{
			maxn=res;
			for (int i=0;i<n;++i) vis[i]=used[i];
		}
		return;
	}
	dfs(x+1);
	bool op=1;
	for (int i=st[x].r;i<n;i+=st[x].p)
		if (used[i])
			op=0;
	if (op)
	{
		for (int i=st[x].r;i<n;i+=st[x].p) used[i]=1;
		dfs(x+1);
		for (int i=st[x].r;i<n;i+=st[x].p) used[i]=0;
	}
	return;
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int x;
	x=phin=n=read(),k=read();
	if (n<=36)
	{
		for (int i=1;i<=n-1;++i)
			if (n%i==0)
			{
				for (int j=0;j<i;++j) st[++leng]=(reads){i,j};
			}
		dfs(1);
		for (int i=0;i<n;++i) printf("%d",vis[i]);
		puts("");
	}
	else
	{
		for (int i=2;i<=n;++i)
			if (x%i==0)
			{
				tong[++length]=i;
				while (x%i==0) x/=i;
			}
		for (int i=1;i<=length;++i)
			if (k/tong[i]*tong[i]>maxn)
				maxn=k/tong[i]*tong[i],rt=i;
		for (int i=0;i<k/tong[rt];++i)
			for (int j=i;j<n;j+=(n/tong[rt]))
				used[j]=1;
		for (int i=0;i<n;++i) printf("%d",used[i]);
		puts("");
	}
	return 0;
}
