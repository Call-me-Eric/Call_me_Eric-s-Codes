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
ll ans=0;
void dfs(int x,int y,int lt=-1) {
    if(x<1||x>n||y<1||y>n) return;
    ++ans;
    if(lt>=a[x][y]) return;
    for(int k=0;k<4;++k) {
        int xx=x+dx[k],yy=y+dy[k];
        dfs(xx,yy,a[x][y]);
    }
}
ll work() {
    ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) dfs(i,j,-1),cout<<i<<","<<j<<":"<<ans<<"\n";
    return ans;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a[i][j]);
    scanf("%d",&q);
    while(q--) {
        int x,y,z=-100;
        scanf("%d%d",&x,&y);
        swap(a[x][y],z);
        printf("%lld\n",work());
        swap(a[x][y],z);
    }
}