#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
const ll mod=998244353;
ll fpow(ll x, ll y){
    ll ret=1;
    while(y){
        if(y&1) ret=ret*x%mod;
        x=x*x%mod; y>>=1;
    }
    return ret;
}
int n;
int lin[N], nxt[N<<1], to[N<<1], tot;
void in(int x, int y){
    nxt[++tot]=lin[x]; lin[x]=tot; to[tot]=y;
}
ll inv2;
ll ans[N];
void dp(int x, int fa){
    ans[x]=1;
    for(int i=lin[x]; i; i=nxt[i]){
        int y=to[i]; if(y==fa) continue;
        dp(y, x); ans[x]=(ans[x]+ans[y]*inv2%mod)%mod;
    }
}
void dp2(int x, int fa){
    if(x!=1) ans[x]=(ans[x]+(ans[fa]-ans[x]*inv2%mod+mod)%mod*inv2%mod)%mod;
    for(int i=lin[x]; i; i=nxt[i]){
        int y=to[i]; if(y==fa) continue;
        dp2(y, x);
    }
}
int main(){
    freopen("dorud.in", "r", stdin);
    freopen("dorud.out", "w", stdout);
    scanf("%d", &n);
    for(int i=1; i<n; i++){
        int x, y; scanf("%d%d", &x, &y); in(x, y); in(y, x);
    }
    inv2=fpow(2, mod-2);
    dp(1, 0); dp2(1, 0);
    for(int i=1; i<=n; i++) printf("%lld\n", ans[i]);
    return 0;
}
