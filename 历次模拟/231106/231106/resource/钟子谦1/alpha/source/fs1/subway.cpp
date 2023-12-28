#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 3333
int n,t;
int a[15][SZ],b[15][SZ];
ll d[15][505][505];
ll ans=1e18;
#define FO(x) {freopen(#x".in","r",stdin); freopen(#x".out","w",stdout);}
void dfs(int v,vector<ll> dd) {
    ans=min(ans,dd[n]);
    for(int j=0;j<t;++j) if(!(v&(1<<j))) {
        vector<ll> nx=dd;
        for(int a=1;a<=n;++a)
            for(int b=1;b<=n;++b)
                nx[b]=min(nx[b],dd[a]+::a[j][a]+::b[j][b]+::d[j][a][b]);
        dfs(v|(1<<j),nx);
    }
}
int main() {
    FO(subway)
    scanf("%d%d",&n,&t);
    for(int i=0;i<t;++i) {
        for(int j=1;j<=n;++j) scanf("%d",&a[i][j]);
        for(int j=1;j<=n;++j) scanf("%d",&b[i][j]);
        memset(d[i],127/3,sizeof d[i]);
        for(int j=1;j<=n;++j) d[i][j][j]=0;
        int m; scanf("%d",&m);
        while(m--) {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            assert(d[i][x][y]>1e10);
            d[i][x][y]=d[i][y][x]=z;
        }
        for(int k=1;k<=n;++k)
            for(int j=1;j<=n;++j)
                for(int l=1;l<=n;++l)
                    d[i][j][l]=min(d[i][j][l],d[i][j][k]+d[i][k][l]);
    }
    vector<ll> c(n+1,1e18);
    c[1]=0;
    dfs(0,c);
    cout<<ans<<"\n";
}