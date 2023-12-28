#include<bits/stdc++.h>
using namespace std;
const int M=705,mod=998244353;
int a[M][M],b[M][M],n;
int poww(int a,int b)
{
    long long ans=1,x=a;
    while(b)
    {
        if(b&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        b>>=1;
    }
    return ans;
}
void calc()
{
    int ma=0,x,t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++) a[i][j]=b[i][j];
    for(int i=1;i<=n;i++)
    {
        ma=0;
        for(int j=i;j<=n;j++)
            if(a[j][i]>ma) ma=a[j][i],x=j;
        if(x!=i) swap(a[x],a[i]);
        t=poww(a[i][i],mod-2);
        for(int j=i;j<=n+1;j++) a[i][j]=1ll*a[i][j]*t%mod;
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            t=a[j][i];
            for(int k=i;k<=n+1;k++) a[j][k]=(a[j][k]-1ll*a[i][k]*t%mod+mod)%mod;
        }
    }
    bool ff=0;
    for(int i=1;i<=n;i++)
    {
        int flag=0;
        for(int j=1;j<=n;j++)
            if(a[i][j]!=0) flag++;
        if(!flag)
        {
            if(a[i][n+1]) printf("No\n");
            else printf("Many\n");
            ff=1;break;
        }
    }
    if(!ff)
    {
        for(int i=1;i<=n;i++) printf("%d ",a[i][n+1]);
        printf("\n");
    }
}
int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    int q,id;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++) scanf("%d",&b[i][j]);
    calc();
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&id);
        for(int j=1;j<=n+1;j++) scanf("%d",&b[id][j]);
        calc();
    }
    return 0; 
}
