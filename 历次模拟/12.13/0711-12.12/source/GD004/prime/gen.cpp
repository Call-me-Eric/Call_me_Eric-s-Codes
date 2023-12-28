#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	#endif
}

mt19937 rng(time(0)^rand()^(*(new int)));
inline int rnd(int l,int r)
{
	return l+((rng()%(r-l+1)));
}

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);

	int T=10;
	printf("%d\n",T);

	rep(tttt,1,T)
	{
		int len=100;
		vector<int> a,b;
		rep(i,1,len) a.push_back(rnd(i==1?1:0,9)),b.push_back(rnd(i==1?1:0,9));
		rep(i,0,len-1) 
		{
			if (a[i]>b[i])
			{
				swap(a,b);
				break;
			}
			if (a[i]<b[i]) break;
		}
		for (auto x:a) printf("%d",x); printf(" ");
		for (auto x:b) printf("%d",x); printf("\n");
	}


	return 0;
}