#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int n,q,u,v,l,r,ans,x,y,cnt[N];
vector<int>e[N];
int main()
{
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
	scanf("%d %d",&n,&q);
	if(n<=100&&q<=100)
	{
		for(int i=1;i<n;i++)
		{
			scanf("%d %d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		while(q--)
		{
			ans=0;
			scanf("%d %d",&l,&r);
			for(int i=l;i<=r;i++)
			{
				for(int j=0;j<e[i].size();j++)
				{
					if(e[i][j]>=l&&e[i][j]<=r) ans++;
				}
			}
			printf("%d\n",r-l+1-ans/2);
		}
		return 0;
	}
	else{
		for(int i=1;i<n;i++)
		{
			scanf("%d %d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i=1;i<=n;i++)
		{
			x=0;
			for(int j=0;j<e[i].size();j++)
			{
				x=x|(1<<(e[i][j]-1));
			}
			cnt[i]=x;
		}
		while(q--)
		{
			ans=0;
			scanf("%d %d",&l,&r);
			for(int i=l;i<=r;i++)
			{
				y=cnt[i];
				for(int j=l;j<=r;j++)
				{
					if (((1<<(j-1))&y)>0) ans++;
				}
			}
			printf("%d\n",r-l+1-ans/2);
		}
	}
	return 0;
}
