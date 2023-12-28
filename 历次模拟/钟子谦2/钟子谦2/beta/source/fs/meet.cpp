#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
#define mp make_pair
#define pb push_back
int n;
ll d[505][505];
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(meet)
    scanf("%d",&n);
    memset(d,127/3,sizeof(d));
    for(int i=1,a,b,c;i<n;++i)
        scanf("%d%d%d",&a,&b,&c),
        d[a][b]=d[b][a]=c;
    for(int i=1;i<=n;++i) d[i][i]=0;
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    ll ans=8e18;
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j) {
            ll sd=0;
            for(int k=1;k<=n;++k)
                sd+=min(d[i][k],d[j][k]);
            ans=min(ans,sd);
        }
    printf("%lld\n",ans);
}