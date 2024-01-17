#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	#endif
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	int n,k; cin>>n>>k;

	auto split=[&](int n)
	{
		vector<int> res;
		for (int i=2;i*i<=n;i++) if (n%i==0)
		{
			res.push_back(i);
			while (n%i==0) n/=i;
		}
		if (n>1) res.push_back(n);
		return res;
	};

	vector<int> ok(n+1),fac=split(n);
	reverse(fac.begin(),fac.end());
	ok[0]=1;
	for (auto p:fac) rep(i,p,n) ok[i]|=ok[i-p];

	int ans=0;
	vector<int> rans(n);
	auto work=[&]()
	{
		function<void(const vector<int>&,int,int,int)> dfs=[&](const vector<int> &vec,int dep,int cnt,int nownum) -> void
		{
			if (dep==fac.size())
			{
				if (cnt>k) return;
				if (cnt>ans)
				{
					ans=cnt;
					rans=vec;
				}
				return;
			}
			int p=fac[dep],c=n/p;
			vector<int> flg(c,1);
			rep(i,0,n-1) flg[i%c]&=(vec[i]==0);
			int emp=0;
			rep(i,0,c-1) if (flg[i]) emp++;
			vector<vector<int> > wtf(1<<emp);
			vector<int> cc(1<<emp),nn(1<<emp);
			wtf[0]=vec,cc[0]=cnt,nn[0]=nownum;

			int id=0;
			rep(i,0,c-1) if (flg[i])
			{
				rep(S,0,(1<<id)-1)
				{
					int T=S|(1<<id);
					wtf[T]=wtf[S];
					cc[T]=cc[S]+p;
					nn[T]=nn[S]+1;
					for (int j=i;j<n;j+=c) wtf[T][j]=nn[T];
				}
				id++;
			}
			rep(S,0,(1<<emp)-1) dfs(wtf[S],dep+1,cc[S],nn[S]);
			wtf.clear(),wtf.shrink_to_fit();
			cc.clear(),cc.shrink_to_fit();
			nn.clear(),nn.shrink_to_fit();
		};
		vector<int> hh(n);
		dfs(hh,0,0,0);
	};

	work();

	#ifdef pbtxdy
	printf("ans %d\n",ans);
	#endif
	rep(i,0,n-1) printf("%d ",(int)rans[i]);
	printf("\n");

	return 0;
}