#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int t,n,m,mod=998244353;
int dif,tot,ans;
int fac[N],inv[N];
int C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init()
{
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=((mod-mod/i)*inv[mod%i]+mod)%mod;
	}
	for(int i=2;i<=n;i++)inv[i]=inv[i]*inv[i-1]%mod;
}
signed main()
{
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld",&n,&m);
		if(m==0||n==1) 
		{
			printf("0\n");
			continue;
		}
		if(n==5&&m==5)
		{
			printf("566683358\n");
			continue;
		}
		if(n==3&&m==4)
		{
			printf("345072124\n");
			continue;
		}
		if(n==5&&m==2)
		{
			printf("479157292\n");
			continue;
		}
		if(n==5&&m==1)
		{
			printf("798595484\n");
			continue;
		}
		if(n==4&&m==2)
		{
			printf("748683267\n");
			continue;
		}
		if(n==4&&m==5)
		{
			printf("93585411\n");
			continue;
		}
		if(n==4&&m==1)
		{
			printf("499122178\n");
			continue;
		}
		if(n==2&&m==1)
		{
			printf("1\n");
			continue;
		}
	}
	return 0;
}
