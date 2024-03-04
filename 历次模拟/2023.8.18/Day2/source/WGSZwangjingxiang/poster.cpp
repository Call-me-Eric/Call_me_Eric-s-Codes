#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int T;
int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
		{
			res*=x;
			res%=mod;
		}
		x*=x;
		x%=mod;
		y>>=1;
	}
	return res;
}
signed main()
{
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		int ad=(n-1)*2;
		int tmp=ad;
		for(int i=2;i<=m;i++)
		{
			ad*=(n-2);
			tmp=ad+tmp*n;
		}
		cout<<tmp*ksm(ksm(n,m),mod-2)%mod<<endl;
	}
}
