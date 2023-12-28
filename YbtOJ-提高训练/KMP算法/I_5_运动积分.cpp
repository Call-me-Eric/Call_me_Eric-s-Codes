#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, mod = 1e9 + 7;
int trie[maxn * 100][2], tot, cnt[maxn * 100];
int n, M;
int a[maxn];
int f[40], ans, sum[40];
void insert(int x){
    int u = 0;
    for(int i = M;i + 1;i--){
        bool v = x >> i & 1;
        if(!trie[u][v])trie[u][v] = ++tot;
        u = trie[u][v];
        cnt[u]++;
    }
}
void query(int x){
    int u = 0;
    for(int i = M;i;i--){
        bool v = x >> i & 1;
        f[i - 1] = cnt[trie[u][!v]];
        u = trie[u][v];
    }
}
signed main(){
    n = read(); M = read();
    for(int i = 1;i <= n;i++){a[i] = read();insert(a[i]);}
    for(int i = 1;i <= n;i++){
        int res = 0, k = (1 << M - 1) % mod;
        memset(f,0,sizeof(f)); query(a[i]);
        sum[M - 1] = f[M - 1];
        for(int i = M - 2;i + 1;i--)sum[i] = (sum[i + 1] + f[i]) % mod;
        for(int i = 0;i < M;i++){res = (res + 1ll * f[i] * sum[i] % mod * k % mod) % mod;}
        ans = ans ^ res;
    }
    printf("%lld\n",ans);
    return 0;
}