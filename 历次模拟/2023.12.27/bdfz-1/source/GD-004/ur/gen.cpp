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

mt19937 rng(time(0)^rand()^(*(new int)));
inline int rnd(int l,int r){return l+((rng()%(r-l+1)));}

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);

	int lim=300,n=rnd(1,lim),k=rnd(0,n);
	printf("%d %d\n",n,k);

	return 0;
}