#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,M=2e6+5,MDEP=log2(N)+1,inf=1e10+5,mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
struct edge
{
	int nt,to;
}e[N<<1];
int h[N],id;
inline void add(const int x,const int y){e[++id].to=y;e[id].nt=h[x];h[x]=id;}
int n,m,a[N];
int f[N][3];
void dfs(int x,int fa)
{
	f[x][1]=a[x];
	f[x][2]=0;
	bool leaf=0;
	int mi1=inf,mx2=0,son=0;
	for(int i=h[x],v;i;i=e[i].nt)
	{
		if((v=e[i].to)==fa)continue;
		leaf=1;
		dfs(v,x);
		f[x][1]+=min(f[v][0],min(f[v][1],f[v][2]));
		f[x][2]+=f[x][0];
		if(f[v][1]<mi1||(f[v][1]==mi1&&f[v][0]>mx2))
		{
			mi1=f[v][1];mx2=f[v][0];
			son=v;
		}
	}
	if(!leaf)
	{
//		f[x][0]=0;
		f[x][1]=a[x];
		f[x][2]=0;
		return ;
	}
	f[x][0]=mi1;
	for(int i=h[x],v;i;i=e[i].nt)
	{
		if((v=e[i].to)==fa||v==son)continue;
		f[x][0]+=min(f[v][0],f[v][1]);
	}
}
signed main()
{
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++)f[i][0]=f[i][1]=f[i][2]=inf;
	dfs(1,0);
	cout<<min(f[1][0],f[1][1]);
	return 0;
}
/*
7
13 20 1 20 6 9 8
1 2
1 3
2 4
2 5
3 6
5 7

*/
