#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	#endif
}

const int N=200000010;

int prime[N/10];
bool ntprime[N];
vector<int> s,hh[N/10];

void split(int x)
{
	if (hh[x].size()) return;
	int aux=prime[x];
	while (aux) hh[x].push_back(aux%10),aux/=10;
}
bool test(int x,int y)
{
	int now=0; split(x),split(y);
	for (auto t:hh[x])
	{
		if (t==hh[y][now]) now++;
		if (now==hh[y].size()) return 1;
	}
	return 0;
}

bool test(int x)
{
	for (auto y:s)
	{
		if (test(x,y)) return 1;
	}
	return 0;
}

void init(int size)
{
	ntprime[1]=1;
	rep(i,2,size)
	{
		if (!ntprime[i]) prime[++prime[0]]=i;
		for (int j=1;j<=prime[0]&&i*prime[j]<=size;j++)
		{
			ntprime[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
	rep(i,1,prime[0])
	{
		if (!test(i))
		{
			s.push_back(i);
		}
	}
}

void solve()
{
	int l,r; cin>>l>>r;
	int ans=0;
	rep(i,l,r) if (!test(i)) ans++;
	printf("%d\n",ans);
}

vector<int> sp[26];
void init()
{
	rep(i,0,25)
	{
		int aux=prime[s[i]];
		while (aux) sp[i].push_back(aux%10),aux/=10;
		reverse(sp[i].begin(),sp[i].end());
	}
}

int cnt;
map<array<int,26>,int> mp;

void dfs(array<int,26> u)
{
	if (mp[u]) return;
	if (!mp[u]) mp[u]=++cnt;
	rep(i,0,9)
	{
		array<int,26> v=u;
		bool flg=1;
		rep(j,0,25) 
		{
			if (i==sp[j][u[j]])
			{
				v[j]++;
				if (v[j]==sp[j].size())
				{
					flg=0;
					break;
				}
			}
		}
		if (flg) dfs(v);
	}
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	init(N-10);
	printf("vector<int> s={");
	for (auto x:s) printf("%d%c",prime[x],x==s.back()?'}':',');
	printf(";");	
	printf("\n");

	return 0;
}