#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	#endif
}

#define fir first
#define sec second

const int mod=998244353;
inline int qmo(int x){return x+((x>>31)&mod);}
inline int add(int x,int y){return qmo(x+y-mod);}
inline int sub(int x,int y){return qmo(x-y);}
inline void inc(int &x,int y){x=add(x,y);}
inline void dec(int &x,int y){x=sub(x,y);}

map<vector<int>,int> mp[2][50];
void bfs(vector<int> S,int step,int tp)
{
	auto shrink=[&](vector<int> &v)
	{
		while (v.size()&&v.back()==0) v.pop_back();
	};
	mp[tp][0][S]=1;
	rep(s,1,step)
	{
		for (auto info:mp[tp][s-1])
		{
			auto u=info.fir;
			rep(i,0,(int)u.size()-1)
			{
				if (!i||u[i-1]>u[i])
				{
					auto v=u;
					v[i]++;
					shrink(v);
					inc(mp[tp][s][v],info.sec);
				}
				if (i==(int)u.size()-1||u[i+1]<u[i])
				{
					auto v=u;
					v[i]--;
					shrink(v);
					inc(mp[tp][s][v],info.sec);
				}
			}
			auto v=u;
			v.push_back(1);
			shrink(v);
			inc(mp[tp][s][v],info.sec);
		}
	}
	// printf("bfs : "); for (auto x:S) printf("%d ",x); printf("\n\n");
	// rep(s,1,step)
	// {
	// 	printf("qu %d :\n",s);
	// 	for (auto info:mp[tp][s])
	// 	{
	// 		for (auto x:info.fir) printf("%d ",x);
	// 		printf("val %d\n",info.sec);
	// 	}
	// 	printf("\n");
	// }
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	int n; cin>>n;
	vector<int> a(n);
	rep(i,0,n-1) cin>>a[i];
	int m; cin>>m;
	vector<int> b(m);
	rep(i,0,m-1) cin>>b[i];

	int q; cin>>q;
	auto solve=[&]()
	{
		int k; cin>>k;
		int mid=(k>>1);
		bfs(a,mid,0),bfs(b,k-mid,1);
		int ans=0;
		for (auto x:mp[0][mid]) inc(ans,1ll*x.sec*mp[1][k-mid][x.fir]%mod);
		printf("%d\n",ans);
	};
	while (q--) solve();

	return 0;
}