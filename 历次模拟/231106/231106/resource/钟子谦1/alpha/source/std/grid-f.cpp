#include <bits/stdc++.h>
using namespace std;
#define SZ 3333
int n,q,a[3333][3333];
const int MOD=998244353;
typedef pair<int,int> pii;
typedef long long ll;
#define fi first
#define se second
pii ix[2333333]; int in=0;
ll f[1005][1005];
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
ll work() {
    in=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) if(a[i][j]!=-1) ix[++in]=pii(i,j),f[i][j]=0;
    sort(ix+1,ix+1+in,[&](pii p,pii q) {
        return a[p.fi][p.se]>a[q.fi][q.se];
    });
    ll ans=1;
    for(int _=1;_<=in;++_) {
        int i=ix[_].fi,j=ix[_].se;
        f[i][j]=0; ++ans;
        for(int k=0;k<4;++k) {
            int ii=i+dx[k],jj=j+dy[k];
            if(ii>=1&&ii<=n&&jj>=1&&jj<=n) {
                f[i][j]++;
                if(a[ii][jj]>a[i][j])
                    f[i][j]=(f[i][j]+f[ii][jj])%MOD;
            }
        }
        ans+=f[i][j]; ans%=MOD;
    }
    ans=(ans+MOD)%MOD;
    return ans;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a[i][j]);
    scanf("%d",&q);
    while(q--) {
        int x,y,z=-1;
        scanf("%d%d",&x,&y);
        swap(a[x][y],z);
        printf("%lld\n",work());
        swap(a[x][y],z);
    }
}