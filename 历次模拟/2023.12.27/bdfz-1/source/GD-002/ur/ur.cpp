/*
平衡的方案可以拆成一些组，每组的数量为 n 的质因子，且均匀分布在圆上。
*/
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> factor(int x)
{
	vector<pair<int,int>> ans(0);
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			ans.push_back(make_pair(i,0));
			while(x%i==0)
			{
				ans.back().second++;
				x/=i;
			}
		}
	}
	if(x>1)
		ans.push_back(make_pair(x,1));
	return ans;
}
int n,k;
vector<pair<int,int>> fac;
namespace solveNSmall
{
	string toBinary(int n,long long s)
	{
		return n==0?"":((char)('0'+s%2))+(toBinary(n-1,s/2));
	}
	int ansk;
	long long anss;
	unordered_set<long long> mem;
	void dfs(long long s)
	{
		if(mem.count(s))
			return;
		mem.insert(s);
		// cout<<"Dfs "<<toBinary(n,s)<<'\n';
		int c=__builtin_popcountll(s);
		if(c>k)
			return;
		if(c>ansk)
			ansk=c,anss=s;
		for(int i=0;i<fac.size()&&fac[i].first+c<=k;i++)
		{
			long long s1=0;
			int l=n/fac[i].first;
			for(int j=0;j<n;j+=l)
				s1|=(1LL<<j);
			for(int p=0;p<l;p++,s1<<=1)
			{
				if((s&s1)==0)
					dfs(s|s1);
			}
		}
	}
	void solve()
	{
		dfs(0);
		cout<<toBinary(n,anss)<<endl;
		// cout<<ansk<<endl;
	}
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin>>n>>k;
	fac=factor(n);
	int mxc=0;
	for(int i=0;i<fac.size();i++)
		mxc=max<int>(mxc,fac[i].second);
	if(n>36||fac.size()==1||mxc<=1)
	{
		int ansk=0,ansi=0;
		for(int i=0;i<fac.size();i++)
		{
			// cout<<"Prime factor "<<fac[i].first<<endl;
			int cnt=(k/fac[i].first)*fac[i].first;
			if(cnt>ansk)
				ansk=cnt,ansi=i;
		}
		int x=k/fac[ansi].first,l=n/fac[ansi].first;
		for(int i=0;i<n;i++)
			cout<<(bool)(i%l<x);
		cout<<endl;
		// cout<<ansk<<endl;
	}
	else
		solveNSmall::solve();
}
/*
30 27
20 15
36 33
*/