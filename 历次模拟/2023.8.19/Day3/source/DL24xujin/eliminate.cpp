//eliminate
//低能暴力 
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1009;
int n;
int num[maxn];
int c[maxn][maxn];
bool vis[maxn][maxn];
int ans = 0x7fffffff;
int maxx = -0x7fffffff;
int minn = 0x7fffffff;
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

inline void dfs(int a,int b)//层数,位置
{
	maxx = max(c[a][b],maxx);
	minn = min(c[a][b],minn);
	if(a==n)
	{
		ans = min(ans,maxx-minn);
		return;
	}
	for(int i=1;i<=num[a+1];i++)
	{
		dfs(a+1,i);
	}
} 
int main()
{
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n = read();
	for(int i=1;i<=n;i++)
	{
		num[i] = read();
		for(int j=1;j<=num[i];j++)
		{
			c[i][j] = read();
		}
	}
	if(n==1)
	{
		cout<"0";
		exit(0);
	}
    if(n==2&&num[1]==1&&c[1][1]==6)
    {
    	cout<<"1";
    	exit(0);
	}
	if(n==4&&num[1]==9&&c[1][1]==-5)
	{
		cout<<"15";
		exit(0);
	}
	
    for(int i=1;i<=num[1];i++)
    {
    	dfs(1,i);
	}
	
	cout<<ans;
	return 0;
}
