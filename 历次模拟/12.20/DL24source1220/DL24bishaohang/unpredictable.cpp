#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;

char a[2010][100010];
int f[2010][2010],w[2010][100010],n,cnt=1,ans;
int tree[100010][26],fail[100010],dep[100010];
vector<int> en[100010];
void build(int x)
{
	int p=1,len=strlen(a[x]+1);
	for(int i=1;i<=len;i++)
	{
		int c=a[x][i]-'a';
		if(!tree[p][c]) tree[p][c]=++cnt;
		dep[tree[p][c]]=dep[p]+1;
		p=tree[p][c];
		en[p].push_back(x);
//		cout<<p<<'\n';
//		for(auto i:en[p]) cout<<i<<' ';
//		cout<<'\n';
	}
}
void bfs()
{
	for(int i=0;i<26;i++) tree[0][i]=1;
	queue<int> q;q.push(1);
	while(q.size())
	{
		int p=q.front();q.pop();
		for(int c=0;c<26;c++)
		{
			int v=tree[p][c];
			if(!v) tree[p][c]=tree[fail[p]][c];
			else
			{
				fail[v]=tree[fail[p]][c];
				q.push(v);
			}
		}
	}
}
void find(int x)
{
	int p=1,len=strlen(a[x]+1);
	for(int i=1;i<=len;i++)
	{
		int c=a[x][i]-'a';
		int k=tree[p][c];
		p=tree[p][c];
	}
	while(p>1)
	{
		for(auto i:en[p]) f[x][i]=w[x][dep[p]]+w[i][dep[p]];
		p=fail[p];
	}
}
signed main()
{
	freopen("unpredictable.in","r",stdin);
	freopen("unpredictable.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]+1;
		int len=strlen(a[i]+1);
		for(int j=1;j<=len;j++) cin>>w[i][j];
		build(i);
	}
	if(n==1)
	{
		cout<<0;return 0;
	}
	bfs();
	for(int i=1;i<=n;i++) find(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
//			cout<<i<<' '<<j<<' '<<f[i][j]<<'\n';
			ans=(ans+f[i][j])%mod;
		}
	}
	for(int i=n-1;i;i--)
	{
		ans=ans*i%mod;
	}
	cout<<ans;
	return 0;
}
/*
1234
1243
1324
1342
1423
1432
2134
2143
2314
2341
2413
2431
3124
3142
3214
3241
3412
3421
4123
4132
4213
4231
4312
4321
*/