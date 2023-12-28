#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define poly array<int,705>
using namespace std;
const int maxn=1405,mod=998244353;
int n,q,z,cnt,top;
int lst[maxn],now[maxn];
int inv[maxn],res[maxn],vis[maxn];
poly a[maxn],b[maxn];
vector<int> vec[1<<12];
struct node
{
    int *w,v;
}st[100005];
inline void read(poly &a)
{
    for(int i=1;i<=n+1;i++) scanf("%d",&a[i]);
}
inline int qpow(int a,int k)
{
    int res=1;
    for(;k;a=1ll*a*a%mod,k>>=1) if(k&1) res=1ll*res*a%mod;
    return res;
}
void push(int p,int l,int r,int L,int R,int x)
{
    if(L<=l&&r<=R) return vec[p].push_back(x);
    if(L>r||R<l) return ;
    int mid=(l+r)>>1;
    push(ls,l,mid,L,R,x);
    push(rs,mid+1,r,L,R,x);
}
inline void upd(int &x)
{
    st[++top]={&x,x};
}
inline void roll(int lim)
{
    while(top>lim) *st[top].w=st[top].v,top--;
}
inline void add(int x)
{
    upd(cnt),b[++cnt]=a[x];
    for(int i=cnt,p=1;p<=n;p++)
    {
        if(!b[i][p]) continue;
        if(!vis[p])
        {
            upd(vis[p]),vis[p]=i,inv[p]=qpow(b[i][p],mod-2);
            break;
        }
        int x=vis[p],t=1ll*inv[p]*b[i][p]%mod;
        for(int j=p;j<=n+1;j++) b[i][j]=(b[i][j]-1ll*b[x][j]*t)%mod;
    }
}
inline void ask()
{
    int flg1=0,flg2=0;
    for(int i=1;i<=n;i++) if(!vis[i]) flg1|=b[i][n+1],flg2|=!b[i][n+1];
    if(flg1) return printf("No\n"),void();
    if(flg2) return printf("Many\n"),void();
    for(int i=n;i>=1;i--)
    {
        int x=vis[i],cur=b[x][n+1];
        for(int j=i+1;j<=n;j++) cur=(cur-1ll*b[x][j]*res[j])%mod;
        res[i]=1ll*cur*inv[i]%mod;
    }
    for(int i=1;i<=n;i++) printf("%d ",(res[i]+mod)%mod);
    putchar('\n');
}
void solve(int p,int l,int r)
{
    int now=top;
    for(auto x:vec[p]) add(x);
    if(l==r) ask();
    else
    {
        int mid=(l+r)>>1;
        solve(ls,l,mid),solve(rs,mid+1,r);
    }
    roll(now);
}
int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) lst[i]=0,now[i]=i,read(a[i]);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&z),read(a[n+i]);
        push(1,0,q,lst[now[z]],i-1,now[z]),lst[now[z]=n+i]=i;
    }
    for(int i=1;i<=n;i++) push(1,0,q,lst[now[i]],n,now[i]);
    solve(1,0,q);
    return 0;
}