#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int n,m;
int mp[N][N];
struct no{int x,y;}a[N],b[N],st[N];
int top;
void get(int x,int y,int lx,int ly)
{
	st[++top]={x,y};
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx==lx&&yy==ly)continue;
		if(mp[xx][yy]==mp[x][y])
		{
			get(xx,yy,x,y);
			break;
		}
	}
}
void pr()
{
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n;j++)cout<<mp[i][j]<<' ';
//		cout<<endl;
//	}
	for(int i=1;i<=m;i++)
	{
		top=0;
		get(a[i].x,a[i].y,0,0);
		printf("%lld\n",top);
		for(int j=1;j<=top;j++)printf("%lld %lld\n",st[j].x,st[j].y);
	}
}
void dfs(int x,int y,int num,int lx,int ly)
{
	if(num==m+1)
	{
		pr();
		exit(0);
	}
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if((mp[xx][yy]&&mp[xx][yy]!=num)||(xx==lx&&yy==ly)||xx<0||yy<0||xx>n||yy>n)continue;
		mp[xx][yy]=num;
		if(xx==b[num].x&&yy==b[num].y)dfs(a[num+1].x,a[num+1].y,num+1,0,0);
		dfs(xx,yy,num,x,y);
		mp[xx][yy]=0;
	}
}
signed main()
{
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		a[i].x=read(),a[i].y=read();
		b[i].x=read(),b[i].y=read();
		mp[b[i].x][b[i].y]=i;
		mp[a[i].x][a[i].y]=i;
	}
	dfs(a[1].x,a[1].y,1,0,0);
	return 0;
}
/*
4 4
1 1 4 3
3 2 4 4
1 2 2 3
1 3 2 4

*/
