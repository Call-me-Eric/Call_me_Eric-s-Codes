#include<bits/stdc++.h>
using namespace std;
const int N = 720;
int a[N][N],c[N];
int n,m;
int b[N][N];
int pos[N],idx[N];
const int mod = 998244353;
int Pow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}
void upd(int i,int j,int v)
{
    for(int k=1;k<=n;k++)
    {
        a[i][k]=(a[i][k]-1ll*a[j][k]*v%mod+mod)%mod;
        b[i][k]=(b[i][k]-1ll*b[j][k]*v%mod+mod)%mod;
    }
    c[i]=(c[i]-1ll*c[j]*v%mod+mod)%mod;
}
int C=0;
void ins(int i)
{
    for(int j=1;j<=n;j++)
    if(a[i][j])
    {
        if(!idx[j])
        {
            idx[j]=i;
            pos[i]=j;
            return;
        }
        int u=idx[j];
        int v=1ll*a[i][j]*Pow(a[u][j],mod-2)%mod;
        upd(i,u,v);
    }
    pos[i]=1e9;
    if(c[i])C++;
}
int mt[N][N],val[N];
int del(int x)
{
    int mx=0,u=0;
    for(int i=1;i<=n;i++)if(b[i][x]&&pos[i]>mx){mx=pos[i];u=i;}
    for(int i=1;i<=n;i++)if(b[i][x]&&i!=u){int v=1ll*b[i][x]*Pow(b[u][x],mod-2)%mod;upd(i,u,v);}
    if(pos[u]<=n)idx[pos[u]]=0,pos[u]=0;
    else if(c[u])C--;
    for(int i=1;i<=n;i++)b[u][i]=a[u][i]=0;c[u]=0;
    return u;
}
void getans()
{
    if(C)
    {
        printf("No\n");
        return;
    }
    for(int i=1;i<=n;i++)
    {
        val[i]=c[idx[i]];
        for(int j=1;j<=n;j++)
        mt[i][j]=a[idx[i]][j];
    }
    for(int i=n;i>=1;i--)
    {
        if(mt[i][i]==0&&val[i]==0) continue;
        if(mt[i][i]==0&&val[i])
        {
            printf("No\n");
            return;
        }
        val[i]=1ll*val[i]*Pow(mt[i][i],mod-2)%mod;
        for(int j=1;j<i;j++)
        val[j]=(val[j]-1ll*val[i]*mt[j][i]%mod+mod)%mod;
    }
    for(int i=1;i<=n;i++)if(!val[i])
    {
        printf("Many\n");
        return;
    }
    for(int i=1;i<=n;i++)printf("%d ",val[i]);
    printf("\n");
}
int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        b[i][i]=1;
        for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
        scanf("%d",&c[i]);
        ins(i);
    }
    getans();
    while(m--)
    {
        int j,x;
        scanf("%d",&j);
        x=del(j);
        b[x][j]=1;
        for(int i=1;i<=n;i++)scanf("%d",&a[x][i]);scanf("%d",&c[x]);
        ins(x);
        getans();
    }
    return 0;
}
