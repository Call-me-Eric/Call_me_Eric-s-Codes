#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	#endif
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	int n,m; cin>>n>>m;
	vector<vector<int> > G(n+1);
	rep(i,1,m)
	{
		int x,y; cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}

	rep(i,1,n) if (G[i].size()>=4)
	{
		printf("-1\n");
		return 0;
	}

	vector<int> dep(n+1);
	ll ans0=0,ans1=0,ans=0;
	rep(i,1,n) if (!dep[i])
	{
		int p=0,e=0,cnt3=0,cir=0;
		function<void(int)> dfs=[&](int u)
		{
			p++,e+=G[u].size(),cnt3+=(G[u].size()==3);
			for (auto v:G[u])
			{
				if (!dep[v])
				{
					dep[v]=dep[u]+1;
					dfs(v);
				}
				else if (dep[v]<dep[u])
				{
					cir=max(cir,dep[u]-dep[v]+1);
				}
			}
		};
		dep[i]=1;
		dfs(i);
		assert(e%2==0);
		e>>=1;

		if (p==e+1)
		{
			if (cnt3>=2||(cnt3==1&&p!=4))
			{
				printf("-1\n");
				return 0;
			}
			if (cnt3==1)
			{
				ans=1;
				ans1+=3;
			}
			else ans0+=1ll*(p+1)*p/2;
		}
		else
		{
			ans=1;
			if (p==e&&cir==p) ans1+=p;
			else
			{
				printf("-1\n");
				return 0;
			}
		}
	}
	if (ans==0) printf("%d %lld\n",0,ans0);
	else printf("%d %lld\n",1,ans1);

	return 0;
}