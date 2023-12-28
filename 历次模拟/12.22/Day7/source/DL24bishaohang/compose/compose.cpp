#include <bits/stdc++.h>
using namespace std;

int n,q,k,a[15][100010],b[100100],cnt,head[100100],tmp;
vector<pair<int,int> > ve[100100];
bool fl=1;
struct edge
{
	int next,to;bool va;
}e[200100];
void ad(int u,int v,bool va)
{
	e[++tmp].next=head[u];
	e[tmp].to=v;
	e[tmp].va=va;
	head[u]=tmp;
}
int dfs(int x,int y)
{
	if(x<=k) return a[x][y];
	for(auto i:ve[x])
	{
		if(i.first==y) return i.second;
	}
	bool chk=e[head[x]].va;
	int manx=0,minx=0x3f3f3f3f;
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].to,d=dfs(v,y);
		if(chk) manx=max(manx,d);
		else minx=min(minx,d);
	}
	if(chk)
	{
		ve[x].push_back(make_pair(y,manx));return manx;
	}
	else
	{
		ve[x].push_back(make_pair(y,minx));return minx;
	}
}
int main()
{
	freopen("compose.in","r",stdin);
	freopen("compose.out","w",stdout);
	cin>>n>>k>>q;cnt=k;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++) cin>>a[i][j];
		b[i]=(1<<(i-1));
	}
	if(n<=100)
	{
		while(q--)
		{
			int m,l,r;cin>>m>>l>>r;
			if(m==1)
			{
				ad(++cnt,l,1);ad(cnt,r,1);
			}
			else if(m==2)
			{
				ad(++cnt,l,0);ad(cnt,r,0);
			}
			else
			{
				cout<<dfs(l,r)<<'\n';
			}
		}
		return 0;
	}
	while(q--)
	{
		int m,l,r;cin>>m>>l>>r;
		if(m==1) b[++cnt]=b[l]|b[r];
		else if(m==3&&fl)
		{
			int manx=0;
			for(int i=0;i<k;i++)
			{
				if(!(b[l]&(1<<i))) continue;
				manx=max(manx,a[i+1][r]);
			}
			cout<<manx<<'\n';
		}
	}
	return 0;
}