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
	ok[0]=1;
	for (auto p:fac) rep(i,p,n) ok[i]|=ok[i-p];

	#define fir first
	#define sec second

	int cur;
	drep(i,k,0) if (ok[i]&&ok[n-i])
	{
		cur=i; break;
	}


	vector<pair<int,int> > nfac;	
	int tt=cur;
	for (auto p:fac)
	{
		int cnt=0;
		while (tt>=p)
		{
			int nx=tt-p;
			if (ok[nx]&&ok[n-nx]) tt=nx,cnt++;
			else break;
		}
		if (cnt) nfac.push_back(make_pair(p,cnt));
	}
	assert(tt==0);

	// printf("cur %d\n",cur);
	// for (auto p:nfac) printf("(%d,%d)\n",p.fir,p.sec);

	vector<int> rans(n);
	auto work=[&](int x)
	{
		do
		{
			auto match=[&](int cur)
			{
				vector<int> ans(n);
				for (auto it:nfac)
				{
					int p=it.fir,cnt=it.sec;
					if (cnt)
					{
						int c=n/p;
						vector<int> flg(c,1);
						rep(i,0,n-1) flg[i%c]&=(ans[i]==0);
						int emp=0;
						rep(i,0,c-1) if (flg[i]) emp++;
						if (emp<cnt) return 0;
						rep(i,0,c-1) if (flg[i]&&cnt)
						{
							cnt--;
							cur-=p;
							for (int j=i;j<n;j+=c) ans[j]=1;
						}
					}
				}
				assert(cur==0);
				rans=ans;
				return 1;
			};
			if (match(x)) return 1;
		}
		while (next_permutation(nfac.begin(),nfac.end()));
		return 0;
	};
	assert(work(cur)==1);

	#ifdef pbtxdy
	printf("greedy ok\n");
	#else
	rep(i,0,n-1) printf("%d ",rans[i]);
	printf("\n");
	#endif

	return 0;
}
/*
175 144

*/