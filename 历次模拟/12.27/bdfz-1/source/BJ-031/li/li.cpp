#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline int read()
{
	int res=0,op=0;
	char ch=getchar();
	while(!isdigit(ch))
	{
		op|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	return op?-res:res;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10^48);
}
int n,m;
ll ans2;
vector<int>tr[200005],s;
bool vis[200005],ans1;
void dfs(int u)
{
	vis[u]=1;
	s.push_back(u);
	for(re int i=0;i<tr[u].size();++i)
	{
		int v=tr[u][i];
		if(vis[v]) continue;
		dfs(v);
	}
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout); 
	n=read();
	m=read();
	for(re int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	for(re int i=1;i<=n;++i)
	{
		if(tr[i].size()>3)
		{
			puts("-1");
			return 0;
		}
		if(tr[i].size()==3)
		{
			vis[i]=1;
			for(re int j=0;j<tr[i].size();++j)
			{
				int v=tr[i][j];
				if(tr[v].size()>1)
				{
					puts("-1");
					return 0;
				}
				vis[v]=1;
			}
			ans1=1;
			ans2+=3;
		}
		if(vis[i]) continue;
		s.clear();
		dfs(i);
		bool flag=1;
		for(re int j=0;j<s.size();++j)
		{
			if(tr[s[j]].size()<2)
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
			if(!ans1)
			{
				ans1=1;
				ans2=s.size();
			}
			else ans2+=s.size();
		}
		else if(!ans1) ans2+=1ll*s.size()*(s.size()+1)/2; 
	}
	write(ans1);
	putchar(' ');
	write(ans2);
	return 0;
}
