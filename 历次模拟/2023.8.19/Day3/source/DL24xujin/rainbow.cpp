//rainbow
//n,m<=2000
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2009;
int n,m;
int a[maxn][maxn];
int r[maxn][maxn],c[maxn][maxn];
int ans[maxn][maxn],siz[maxn][maxn];

inline int read()
{
	int x = 0;
	int f = 1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		x = (x*10)+(c-'0');
		c = getchar();
	}
	return x*f;
}


int main()
{
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	n = read();
	m = read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
		    a[i][j] = read();
		} 
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!a[i-1][j-1]||a[i][j]==a[i-1][j-1])
			{
				r[i][j] = r[i][j-1]+1;
				c[i][j] = c[i-1][j]+1;
			}
			//
			else
			{
				r[i][j] = c[i][j] = 0;
			}
			//
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			siz[i][j] = min(siz[i-1][j-1],min(c[i][j],r[i][j]));
			if(siz[i][j]==siz[i-1][j-1] && a[i-siz[i][j]][j]!=a[i][j-siz[i][j]]) ++siz[i][j];
			//if(a[i-siz[i][j]][j]!=a[i][j-siz[i][j]]) ++siz[i][j];
			if(siz[i][j]==0) siz[i][j] = 1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
	    {
	    	ans[i][j] = ans[i][j-1] + ans[i-1][j] + siz[i][j] - ans[i-1][j-1];
		}
	}
	
	cout<<ans[n][m];
	return 0;
}
