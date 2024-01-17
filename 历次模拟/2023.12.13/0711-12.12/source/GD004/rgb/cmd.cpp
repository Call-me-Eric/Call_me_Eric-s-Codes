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

	rep(i,1,114514)
	{
		system("./gen.exe > data.in ");
		clock_t t1=clock();
		system("./rgb.exe < data.in > my.out");
		clock_t t2=clock();
		if (system("diff my.out hh.out -B -b"))
		{
			printf("gskfgjasjfasdf\n");
			return 0;
		}
		double tt=(t2-t1)/100.0;
		printf("%d ok %.5lfs\n",i,tt);
		assert(tt<=3);
	}

	return 0;
}