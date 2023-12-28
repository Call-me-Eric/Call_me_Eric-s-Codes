#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4000005;
const ll mod=998244353;
inline int rd()
{
    int x=0; bool f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar())
        if(ch=='-') f=0;
    for(;isdigit(ch);ch=getchar())
        x=x*10+(ch^48);
    return f?x:-x;
}
int deg[N];
int f[N],siz[N],sized[N];
bool vis[N];
int fnd(int x)
{ return f[x]==x?x:f[x]=fnd(f[x]); }
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int n=rd(),m=rd();
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++)
	{
		int u=rd(),v=rd();
		deg[u]++; deg[v]++;
		int fu=fnd(u),fv=fnd(v);
		if(fu!=fv)
		{
			f[fu]=fv,siz[fv]+=siz[fu];
			sized[fv]+=sized[fu]; 
		}
		sized[fv]++;
	}
	int bb=0;
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		if(deg[i]>3||(deg[i]==3&&siz[fnd(i)]>4))
		{
			bb=1; break;
		}
		if(deg[i]==3)
			vis[fnd(i)]=1;
	}
	if(bb)
	{
		printf("-1\n");
		return 0;
	}
	ll fn=0;
	for(int i=1;i<=n;i++)
		if(fnd(i)==i)
		{
			if(sized[i]==siz[i])
				ans+=siz[i];
			else if(vis[i])
				ans+=3;
			else
				fn+=(1ll*siz[i]*(siz[i]+1)/2);
		}
	if(!ans)
		printf("0 %lld\n",fn);
	else
		printf("1 %lld\n",ans);
    return 0;
}
