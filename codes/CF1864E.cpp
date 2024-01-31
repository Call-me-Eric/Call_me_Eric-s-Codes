#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
const ll mod = 998244353;
int n;
ll ans;
struct Trie{
    int tr[maxn * 31][2], cnt[maxn * 31], tot;
    void clear(){for(int i = 1;i <= tot;i++)tr[i][0] = tr[i][1] = cnt[i] = 0;tot = 1;}
    void insert(int x){
        int u = 1;
        for(int i = 30;i + 1;i--){
            bool v = (x >> i) & 1LL;
            if(!tr[u][v])tr[u][v] = ++tot;
            u = tr[u][v];cnt[u]++;
        }
    }
}trie;
#define ls(u) trie.tr[(u)][0]
#define rs(u) trie.tr[(u)][1]
#define cnts(u) trie.cnt[(u)]

ll qpow(ll x,int a){
    ll res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void dfs(int u,int dep,int cnt){
    if(!u)return;
    if(dep == -1){
        ans = (ans + (ll)cnts(u) * cnts(u) % mod * (cnt + 1) % mod) % mod;
        return;
    }
    ans = (ans + (ll) cnts(ls(u)) * cnts(rs(u)) % mod * (cnt * 2 + 3) % mod) % mod;
    dfs(ls(u),dep - 1,cnt    );
    dfs(rs(u),dep - 1,cnt + 1);
}

signed main(){
int T = read();
while(T--){
    trie.clear(); n = read();
    for(int i = 1;i <= n;i++){trie.insert(read());}
    ans = 0;dfs(1,30,0);
    printf("%lld\n",ans * qpow(qpow(n,2),mod - 2) % mod);
}
    return 0;
}