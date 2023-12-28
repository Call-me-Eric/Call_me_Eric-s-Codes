#include<bits/stdc++.h>
using namespace std;
const int N=44;
int n,m,q;
int nm;
int lim;
struct State
{
	int a[N];
	inline string hash()
	{
		string s;
		for(int i=1;i<=lim;++i)
		{
			s+='0'+a[i]%10;
			s+='0'+a[i]/10%10;
		}
		return s;
	}
	inline State moveR(int x)
	{
		State t=*this;
		t.a[x]--,t.a[x+1]++;
		return t;
	}
	inline State moveL(int x)
	{
		State t=*this;
		t.a[x]--,t.a[x-1]++;
		return t;
	}
	unordered_map<string,pair<State,int>>trans()
	{
		unordered_map<string,pair<State,int>>mp;
		auto t=moveR(0);
		auto s=t.hash();
		auto itr=mp.find(s);
		if(itr==mp.end())
			itr=mp.insert(itr,{s,{t,0}});
		++itr->second.second;
		for(int i=1;i<=lim;++i)
		{
			t=moveL(i);
			s=t.hash();
			itr=mp.find(s);
			if(itr==mp.end())
				itr=mp.insert(itr,{s,{t,0}});
			++itr->second.second;

			t=moveR(0);
			s=t.hash();
			itr=mp.find(s);
			if(itr==mp.end())
				itr=mp.insert(itr,{s,{t,0}});
			++itr->second.second;
		}
		return mp;
	}
}a,b;
inline void merge(unordered_map<string,pair<State,int>>&a,unordered_map<string,pair<State,int>>&b,int time)
{
	for(auto &i:b)
	{
		auto itr=a.find(i.first);
		if(itr==a.end())
			a.insert(itr,i);
		else
			itr->second.second+=i.second.second*time;
	}
}
inline unordered_map<string,pair<State,int>> walk(unordered_map<string,pair<State,int>> a)
{
	unordered_map<string,pair<State,int>> res;
	for(auto &i:a)
	{
		auto t=i.second.first.trans();
		merge(res,t,i.second.second);
	}
	return res;
}
int main()
{
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a.a+i);
	scanf("%d",&m);
	for(int i;i<=m;++i)
		scanf("%d",b.a+i);
	nm=max(n,m);
	a.a[0]=b.a[0]=max(a.a[1],b.a[1]);
	for(int i=nm+1;i;--i)
	{
		a.a[i]=a.a[i-1]-a.a[i];
		b.a[i]-b.a[i-1]-b.a[i];
	}
	int q,k;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&k);
		int l=k>>1,r=k-l;
		unordered_map<string,pair<State,int>> A,B;
		A.insert(A.end(),{a.hash(),{a,0}});
		B.insert(B.end(),{b.hash(),{b,0}});
		while(l--)
			A=walk(A);
		while(r--)
			B=walk(B);
		long long ans=0;
		for(auto &i:A)
		{
			auto itr=B.find(i.first);
			if(itr!=B.end())
				ans+=i.second.second*1ll*itr->second.second;
		}
		printf("%lld\n",ans);
	}
}
