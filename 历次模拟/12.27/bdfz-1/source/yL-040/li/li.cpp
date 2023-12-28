#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n,m,deg[N];
int ufs[N],sze[N],edg[N];
int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]);}
inline void Merge(int x,int y)
{
	x = find(x);y = find(y);
	if(x == y) return;
	ufs[y] = x;sze[x] += sze[y];
}
int U[N],V[N];
int mxdeg[N];
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin >> n >> m;
	for(int i = 1;i <= n;i++) ufs[i] = i,sze[i] = 1;
	for(int i = 1;i <= m;i++)
	{
		int u,v;
		cin >> u >> v;
		U[i] = u,V[i] = v;
		++deg[u];++deg[v];
		Merge(u,v);
	}
	for(int i = 1;i <= n;i++)
		if(deg[i] >= 4) return puts("-1"),0;
	for(int i = 1;i <= m;i++) edg[find(U[i])]++;
	for(int i = 1;i <= n;i++) mxdeg[find(i)] = max(mxdeg[find(i)],deg[i]);
	int flg = 0;
	long long ans0 = 0,ans1 = 0;
	for(int i = 1;i <= n;i++)
	{
		if(find(i) != i) continue;	
		if(edg[i] > sze[i]) return puts("-1"),0;
		if(mxdeg[i] == 3)
		{
			if(sze[i] != 4 || edg[i] != 3) return puts("-1"),0;
			flg = 1;ans1 += 3;
		}
		else 
		{
			if(sze[i] > edg[i]) ans0 += 1ll * sze[i] * (sze[i] + 1) / 2;
			else flg = 1,ans1 += sze[i];
		}
	} 
	if(flg) printf("1 %lld\n",ans1);
	else printf("0 %lld\n",ans0);
	return 0;
}
