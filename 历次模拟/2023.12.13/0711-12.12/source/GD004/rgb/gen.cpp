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

	int R=rnd(180,200)/2,G=rnd(80,100)/2,B=rnd(180,200)/2,n=R+G+B+1,m=rnd(n-1,n+10);
	vector<int> hh;
	rep(i,1,R) hh.push_back(0);
	rep(i,1,G) hh.push_back(1);
	rep(i,1,B) hh.push_back(2);

	vector<vector<int> > e(n+1,vector<int>(n+1));
	int ecnt=0;
	auto link=[&](int u,int v)
	{
		ecnt++;
		e[u][v]=e[v][u]=1;
	};

	printf("%d %d %d %d\n",R,G,B,m);

	shuffle(hh.begin(),hh.end(),rng);
	char to[5]={'r','g','b'};
	rep(i,2,n)
	{
		int fa=rnd(1,i-1);
		printf("%d %d %c\n",fa,i,to[hh[i-2]]);
		link(fa,i);
	}
	while (ecnt<m)
	{
		int u,v;
		do
		{
			u=rnd(1,n),v=rnd(1,n);
		}
		while (e[u][v]||u==v);
		link(u,v);
		printf("%d %d %c\n",u,v,to[rnd(0,2)]);
	}

	return 0;
}