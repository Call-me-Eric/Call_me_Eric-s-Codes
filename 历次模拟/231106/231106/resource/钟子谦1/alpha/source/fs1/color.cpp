#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
#define fi first
#define se second
ll qp(ll a,ll b) {
    ll x=1; a%=MOD;
    while(b) {
        if(b&1) x=x*a%MOD;
        a=a*a%MOD, b>>=1;
    }
    return x;
}
#define SZ 666666
int n,c[SZ]; ll t;
vector<int> adj[SZ];
ll f[1005][1005];
void dfs(int x,int fa=0) {
    for(int i=1;i<=t;++i) f[x][i]=(c[x]==0)?1:(i==c[x]);
    for(auto b:adj[x]) if(b!=fa) {
        dfs(b,x);
        ll su=0;
        for(int j=1;j<=t;++j) (su+=f[b][j])%=MOD;
        for(int j=1;j<=t;++j)
            f[x][j]=f[x][j]*(su-f[b][j])%MOD;
    }
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
	FO(color)
    scanf("%d%lld",&n,&t);
    for(int i=1;i<=n;++i) scanf("%d",&c[i]),assert(0<=c[i]&&c[i]<=t);
    for(int i=1;i<n;++i) {
        int x,y; scanf("%d%d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1);
    ll ans=0;
    for(int i=1;i<=n;++i) {
        (ans+=f[1][i])%=MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<"\n";
}
