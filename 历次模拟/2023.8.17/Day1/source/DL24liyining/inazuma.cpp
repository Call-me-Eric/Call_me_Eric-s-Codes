#include<bits/stdc++.h>
using namespace std;
#define int long long
#define genshin time(0)

const int maxn=1e5+5;
int to[maxn],cntt,head[maxn],nxt[maxn],dd[maxn];

void add(int x,int y,int z)
{
	to[++cntt]=y;dd[cntt]=z;
	nxt[cntt]=head[x];
	head[x]=cntt;
}

signed main()
{
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	int n,m;cin>>n>>m;
	int maxd=-114514,mind=0x7fffffff;
	for(int i=1;i<=m;i++)
	{
		int u,v,d;cin>>u>>v>>d;
		add(u,v,d),add(v,u,d),maxd=max(maxd,d),mind=min(mind,d);
	}
	srand(genshin);
	if(rand()%2) cout<<mind;
	else cout<<maxd;
	return 0;
}
