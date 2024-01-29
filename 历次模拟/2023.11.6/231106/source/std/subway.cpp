#include <bits/stdc++.h>
using namespace std;
#define SZ 3333
int n,k,a[15][SZ],b[15][SZ];
typedef pair<int,int> pii;
typedef long long ll;
#define pb push_back
#define fi first
#define se second
vector<pii> e[15][SZ];
ll f[1<<8][508],d[508];
void work(int o) {
    priority_queue<pair<ll,int>> q;
    for(int u=1;u<=n;++u)
        q.push({-d[u],u});
    while(!q.empty()) {
        auto t=q.top(); q.pop();
        if(-t.fi!=d[t.se]) continue;
        for(auto ee:e[o][t.se]) {
            if(d[ee.fi]>d[t.se]+ee.se) {
                d[ee.fi]=d[t.se]+ee.se;
                q.push({-d[ee.fi],ee.fi});
            }
        }
    }
}
int ff[SZ];
int gf(int x) {
    return ff[x]?ff[x]=gf(ff[x]):x;
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
	FO(subway)
    scanf("%d%d",&n,&k);
    for(int i=0;i<k;++i) {
        for(int j=1;j<=n;++j) scanf("%d",&a[i][j]);
        for(int j=1;j<=n;++j) scanf("%d",&b[i][j]);
        int m,x,y,z; scanf("%d",&m);
        for(int j=1;j<=n;++j) ff[j]=0;
        for(int j=1;j<=m;++j) {
            scanf("%d%d%d",&x,&y,&z);
            e[i][x].push_back({y,z});
            e[i][y].push_back({x,z});
            x=gf(x); y=gf(y); if(x!=y) ff[x]=y;
        }
        for(int j=1;j<=n;++j) assert(gf(j)==gf(1));
    }
    memset(f,127/3,sizeof f);
    f[0][1]=0;
    ll ans=8e18;
    for(int x=1;x<(1<<k);++x) {
        for(int y=0;y<k;++y) if(x&(1<<y)) {
            for(int u=1;u<=n;++u)
                d[u]=f[x^(1<<y)][u]+a[y][u];
            work(y);
            for(int u=1;u<=n;++u)
                f[x][u]=min(f[x][u],d[u]+b[y][u]);
        }
        ans=min(ans,f[x][n]);
    }
    printf("%lld\n",ans);
}
