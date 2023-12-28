#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	#endif
}

const int N=2000010;

int prime[N];
bool ntprime[N];

bool test(int x)
{
	static int p[11]={2,3,5,7};
	
}

void init(int size)
{
	ntprime[1]=1;
	rep(i,2,size)
	{
		if (!ntprime[i]) prime[++prime[0]]=i;
		for (int j=1;j<=prime[0]&&i*prime[j]<=size;j++)
		{
			ntprime[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
	rep(i,1,prime[0])
	{
		if (!test(prime[i]))
		{
			printf("find %d!\n",i);
			return;
		}
	}
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	init(N-10);

	return 0;
}