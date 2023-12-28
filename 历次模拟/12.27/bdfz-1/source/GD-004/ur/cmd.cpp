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

	system("g++ gen.cpp -o gen.exe && g++ ur.cpp -o ur.exe -Dpbtxdy -O2");
	rep(i,1,114514)
	{
		system("./gen.exe > data.in && ./ur.exe < data.in > my.out");
		if (system("diff my.out std.out"))
		{
			printf("GGGGGGGGGGGGGGGGGGG\n");
			return 0;
		}
		printf("%d ok\n",i);
	}

	return 0;
}