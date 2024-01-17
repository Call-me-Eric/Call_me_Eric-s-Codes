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

const int mod=998244353;
inline int qmo(int x){return x+((x>>31)&mod);}
inline int add(int x,int y){return qmo(x+y-mod);}
inline int sub(int x,int y){return qmo(x-y);}
inline void inc(int &x,int y){x=add(x,y);}
inline void dec(int &x,int y){x=sub(x,y);}

vector<int> s={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
vector<int> sp[26];
void init()
{
	rep(i,0,25)
	{
		int aux=s[i];
		while (aux) sp[i].push_back(aux%10),aux/=10;
		reverse(sp[i].begin(),sp[i].end());
	}
}

const int S=150000;

int cnt,trans[S][12];
map<array<int,26>,int> mp;

int dfs(array<int,26> u)
{
	if (mp[u]) return mp[u];
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
		if (flg) trans[mp[u]][i]=dfs(v);
		else trans[mp[u]][i]=-1;
	}
	return mp[u];
}

int f[21][S][2],lst[21][S][2],val[62],T;

int dfs(int dep,int now,int tp)
{
	if (dep==-1) return 1;
	if (f[dep][now][tp]>=0) 
	{
		if (tp==0||lst[dep][now][tp]==T) return f[dep][now][tp];
	}
	int ans=0,ntp=(tp?val[dep]:9);
	rep(i,0,ntp) if (trans[now][i]>=0)
	{
		inc(ans,dfs(dep-1,trans[now][i],tp?(i==ntp):0));
	}
	lst[dep][now][tp]=T;
	return f[dep][now][tp]=ans;
}
int calc(ll x)
{
	T++;
	rep(i,0,19) val[i]=x%10,x/=10;
	memset(f,-1,sizeof(f));
	return dfs(19,1,1);
}

void solve()
{
	ll l,r; cin>>l>>r;
	printf("%d\n",sub(calc(r),calc(l-1)));
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);
	
	init();
	dfs(array<int,26>());
	// printf("cnt %d\n",cnt);

	int T; cin>>T;
	while (T--) solve();

	return 0;
}