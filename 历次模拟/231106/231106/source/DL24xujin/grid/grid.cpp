//color
//被充能的是玩家吗... 
#include<bits/stdc++.h>
using namespace std;


inline int read()
{
	int x=0,f=1;
	char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x = (x*10)+(ch-'0');
		ch = getchar();
	}
	return x*f;
}

const int maxn = 509;
const int mod = 998244353;
int n,q;
int mapp[maxn][maxn];
int maxt = -1;//最大时间 
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int res;

inline bool judge(int x,int y)
{
	if(x>n||y>n||x<1||y<1) return false;
	return true;
}

inline void dfs(int x,int y,int Time)
{
	//int res = 1;//本身 
	if(res>=mod) res%=mod;
	if(mapp[x][y]==1e9+7||Time>=mapp[x][y])
	{
		return;
	}
	for(int i=0;i<4;++i)
	{
		int px = x+dx[i];
		int py = y+dy[i];
		if(judge(px,py))
		{
            res++;
            dfs(px,py,mapp[x][y]);
		}
	}
}

int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	n = read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			mapp[i][j] = read();
			
		}
	}
	q = read();
	for(int i=1;i<=q;++i)
	{
		int x = read(),y = read();
		res = n*n;
		int pos = mapp[x][y];
		mapp[x][y] = 1e9+7;
		for(int j=1;j<=n;++j)
		{
			for(int k=1;k<=n;++k)
			{
				dfs(j,k,0);
			}
		}
		printf("%d\n",res%mod);
		mapp[x][y] = pos;
	}
	return 0;
}
