#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=1e5+5,mod=1e9+7;
int n,a[N],ans[N],f[N],sum=0;
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
signed main()
{
    freopen("hard.in","r",stdin);
    freopen("hard.out","w",stdout);
    n=read(); int mx=1e5;
    for(int i=1;i<=n;i++) a[i]=read(),sum+=a[i];
    f[1]=(sum-1)*(sum-1)%mod*qpow(sum)%mod;
    for(int i=1;i<min(mx,sum);i++) 
        f[i+1]=(2*f[i]%mod-f[i-1]-(sum-1)*qpow(sum-i)%mod+2*mod)%mod;
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+f[a[i]])%mod;
    printf("%lld\n",ans);
    return 0;
}