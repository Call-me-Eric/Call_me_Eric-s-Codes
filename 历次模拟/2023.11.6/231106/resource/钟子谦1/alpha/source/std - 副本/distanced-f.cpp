#include <bits/stdc++.h>
using namespace std;
int n,t;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
pii g[SZ];
int ff[SZ],mx[SZ],mi[SZ];
ll rl[SZ],su[SZ];
int gf(int x) {
    return ff[x]?ff[x]=gf(ff[x]):x;
}
void uni(int a,int b) {
    a=gf(a), b=gf(b);
    if(a!=b) ff[a]=b;
}
set<pair<ll,pii> > q;
int vs[SZ],vn;
ll tot=0,ans[SZ];
int L[SZ],R[SZ];
ll e[SZ];
set<int> ava;
ll f[505][505];
int main() {
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",&g[i].fi),mx[i]=-2e9,mi[i]=2e9;
    for(int i=1;i<=n;i++) scanf("%d",&g[i].se),tot+=max(0,g[i].se);
    sort(g+1,g+n+1);
    memset(f,-127/3,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;++i) {
        for(int j=0;j<i;++j)
            for(int k=0;k<=i;++k) {
                int nw=(j==0||abs(g[i].fi-g[j].fi)>t);
                f[i][k+nw]=max(f[i][k+nw],f[j][k]+g[i].se);
            }
    }
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            ans[i]=max(ans[i],f[j][i]);
    for(int i=1;i<=n;++i)
        ans[i]=max(ans[i],ans[i-1]);
    for(int i=1;i<=n;++i)
        printf("%lld ",ans[i]);puts("");
}