#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e7 + 10, mod = 20101009;
int prime[maxn], tot;
bool book[maxn];
int f[maxn], sum[maxn];
int n, m;
void init(){
    f[1] = 1;
    for(int i = 2;i < maxn;i++){
        if(!book[i]){prime[++tot] = i;f[i] = (mod + 1 - i) % mod;}
        for(int j = 1;j <= tot && i * prime[j] < maxn;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0){f[i * prime[j]] = f[i];break;}
            f[i * prime[j]] = 1ll * f[i] * f[prime[j]] % mod;
        }
    }
    for(int i = 1;i < maxn;i++){f[i] = (f[i - 1] + 1ll * f[i] * i) % mod;}
    for(int i = 1;i < maxn;i++)sum[i] = (sum[i - 1] + i) % mod;
}
void main(){
    init();
    n = read(); m = read();
    if(n > m)swap(n, m);int ans = 0;
    for(int l = 1, r = 0;l <= n;l = r + 1){
        r = min(n / (n / l),m / (m / l));
        ans = 1ll * (ans + 1ll * (f[r] - f[l - 1] + mod) % mod * sum[n / l] % mod * sum[m / l] % mod) % mod;
    }
    printf("%d\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}