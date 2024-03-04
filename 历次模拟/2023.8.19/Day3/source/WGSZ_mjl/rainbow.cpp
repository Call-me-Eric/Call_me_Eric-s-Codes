#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
int n,m,a[N][N],ans;
struct no{int x,y;}b[N][N];
bool f[N*N];
inline bool chk(int x,int y,int len)
{
	int aa=x-len+1,bb=y-len+1;
	if(aa<0||bb<0)return 0;
	for(int i=aa;i<=x;i++)if(b[i][y].x>aa||b[i][y].y>aa-i+y)return 0;
	for(int i=bb;i<=y;i++)if(b[x][i].x>bb-i+x||b[x][i].y>bb)return 0;
	for(int i=aa;i<=x;i++)
	{
		if(f[a[i][y]])
		{
			for(int j=aa;j<=i;j++)f[a[j][y]]=1;
			return 0;
		}
		f[a[i][y]]=1;
	}
	for(int i=bb;i<y;i++)
	{
		if(f[a[x][i]])
		{
			for(int j=aa;j<=x;j++)f[a[j][y]]=0;
			for(int j=bb;j<=i;j++)f[a[x][j]]=0;
			return 0;
		}
		f[a[x][i]]=1;
	}
	for(int i=aa;i<=x;i++)f[a[i][y]]=0;
	for(int i=bb;i<=y;i++)f[a[x][i]]=0;
	return 1;
}
signed main()
{
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	n=read();m=read();
	int len=min(n,m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			if(a[i][j]==a[i-1][j-1])b[i][j]=b[i-1][j-1];
			else b[i][j]={i,j};
		}
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)cout<<i<<' '<<j<<' '<<b[i][j].x<<' '<<b[i][j].y<<endl;
//	}
//	cout<<chk(2,4,2);
	for(int i=n;i>=1;i--)
	{
		for(int j=m;j>=1;j--)
		{
			for(int k=2;k<=len;k++)
			{
				if(chk(i,j,k))ans++;
				else break;
			}
		}
	}
	cout<<ans+n*m;
	return 0;
}
/*
3 4
1 3 5 2
4 1 3 5
6 4 2 3

*/
