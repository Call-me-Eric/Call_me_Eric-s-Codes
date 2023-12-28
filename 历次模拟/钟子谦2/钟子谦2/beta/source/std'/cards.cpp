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
pii p[SZ];
pair<ll,int> f[5005][5005];
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(cards)
    memset(f,-127/3,sizeof f);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&p[i].fi,&p[i].se);
    reverse(p+1,p+n+1);
    f[0][0]=mp(0,0);
    for(int i=1;i<=n;++i) {
        for(int j=0;j<i;++j) {
            ll w=f[i-1][j].fi;
            f[i][j+1]=max(f[i][j+1],mp(w+p[i].se,1));
            f[i][j]=max(f[i][j],mp(w+p[i].fi*(ll)j,0));
        }
    }
    int A=n,B=0;
    for(int i=0;i<=n;++i)
        if(f[n][i].fi>f[n][B].fi) B=i;
    printf("%lld\n",f[n][B].fi);
    while(A) {
        printf("%d ",f[A][B].se+1);
        B-=f[A][B].se; --A;
    }
    puts("");
}