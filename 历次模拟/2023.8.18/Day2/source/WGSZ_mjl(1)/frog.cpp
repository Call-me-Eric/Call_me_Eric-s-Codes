#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,M=6e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
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
int n,num[N],b[N];
int du[N];
bool mp[N][N];
struct no
{
	int a[10],id;
	inline bool operator < (const no &aa)const
	{
		for(int i=1;i<=5;i++)if(a[i]!=aa.a[i])return a[i]<aa.a[i];
		return 1;
	}
}a[N];
inline bool chk(const int &x,const int &y)
{
	if(a[x].id>a[y].id)return 0;
	for(int i=1;i<=5;i++)if(a[x].a[i]>a[y].a[i])return 0;
	return 1;
}
void build(int x)
{
	for(int i=x+1;i<=n;i++)
	{
		if(chk(x,i))
		{
			if(!mp[a[x].id][a[i].id])
			{
				mp[a[x].id][a[i].id]=1;
				add(a[x].id,a[i].id);
//				cout<<a[x].id<<' '<<a[i].id<<endl;
				du[a[i].id]++;
			}
			build(i);
		}
	}
}
void topu()
{
	queue<int>q;
//	for(int i=0;i<=n;i++)if(!du[i])q.push(i);
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=h[x];i;i=e[i].nt)
		{
			int v=e[i].to;
//			cout<<x<<' '<<v<<endl;
			du[v]--;
			num[v]=max(num[v],num[x]+b[x]);
			if(!du[v])q.push(v);
		}
	}
}
signed main()
{
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=6;j++)a[i].a[j]=read();
		a[i].id=i;
		b[i]=a[i].a[6];
	}
	sort(a+1,a+1+n);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=6;j++)cout<<a[i].a[j]<<' ';
//		cout<<a[i].id<<endl;
//	}
	build(0);
	topu();
	for(int i=1;i<=n;i++)printf("%lld\n",num[i]+b[i]);
	return 0;
}
/*
10
2 8 6 6 8 9001
8 10 1 4 2 916
6 6 10 4 5 6989
7 9 10 8 2 571
2 7 3 1 8 9351
1 9 3 1 10 8962
5 9 4 2 3 2631
7 6 3 4 1 6298
8 9 2 8 4 9215
6 2 3 1 1 2207

*/
