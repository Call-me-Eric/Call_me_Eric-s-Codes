#include<bits/stdc++.h>
#define il inline
using namespace std;
il int read()
{
    int xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9') 
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=105,M=(1<<8)+5,mod=22222223,Mod=998244353;
int n,m,a[N],b[N];
int f[N][M],g[N][M];
signed main()
{
    freopen("city.in","r",stdin);
    freopen("city.out","w",stdout);
    n=read(),m=read();
    for(int i=0;i<n;i++) a[i]=read();
    for(int i=1;i<=m;i++) b[i]=read();
    f[0][0]=g[0][0]=1;
    for(int k=1;k<=m;k++)
    {
        for(int j=0;j<(1<<n);j++)
        {
            int tot1=1,tot2=1;
            int gt1=1,gt2=1;
            for(int i=0;i<n;i++)
            {
                int lim1=min(b[k],a[i]-1),lim2=min(b[k]-1,a[i]-1);
                if(j>>i&1) 
                {
                    if(b[k]<a[i]) tot1=0,gt1=0;
                    if(b[k]-1<a[i]) tot2=0,gt2=0;
                    continue;
                }
                tot1=tot1*(lim1+1)%mod,tot2=tot2*(lim2+1)%mod;
                gt1=gt1*(lim1+1)%Mod,gt2=gt2*(lim2+1)%Mod;
            }
            // cout<<tot1<<" "<<tot2<<endl;
            int now=(tot1-tot2+mod)%mod,gnw=(gt1-gt2+Mod)%Mod;
            // cout<<k<<" "<<j<<" "<<now<<endl;
            for(int lst=0;lst<(1<<n);lst++) 
            {
                (f[k][j|lst]+=f[k-1][lst]*now%mod)%=mod;
                (g[k][j|lst]+=g[k-1][lst]*gnw%Mod)%=Mod;
            }
        }
    }
    if(f[m][(1<<n)-1]==0&&g[m][(1<<n)-1]==0) printf("No solution!\n");
    else printf("%lld\n",f[m][(1<<n)-1]);
    return 0;
}       
/*
2 2
1 1
1 1

4 3
2 3 4 3
1 3 4
*/