#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
const int mod = 1e9+9;
typedef long long LL;
LL Inv[N];
int n;
LL m;
LL f[N];
LL a[N];
LL pre[N];
LL Pow(LL a,LL b)
{
	a%=mod;
	LL res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL inv(LL x)
{
	return Pow(x,mod-2);
}
int main()
{
	freopen("rain.in","r",stdin);
	freopen("rain.out","w",stdout);
	cin>>n;
	f[0]=0;
	LL r=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		m+=a[i];
		r=max(r,a[i]);
	}
	pre[0]=inv(m);
	for(int i=1;i<=r;i++)
	pre[i]=(pre[i-1]+inv(m-i))%mod;
	m%=mod;
	for(int i=1;i<=r;i++)
	f[i]=1ll*(m-1)*(m-i+mod)%mod*pre[i-1]%mod;
	LL ans=0;
	for(int i=1;i<=n;i++)
	ans=(ans+f[a[i]]+mod)%mod;
	cout<<ans;
	return 0;
}
