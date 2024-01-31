#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10,mod = 1e9 + 7;
int n, k, cf[maxn];
int l[maxn], r[maxn], x[maxn], tot;
int pw[maxn], pwinv[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
    n = read();k = read();pw[0] = 1;
    for(int i = 1;i <= n;i++){
        x[++tot] = l[i] = read();
        x[++tot] = r[i] = read() + 1;
        pw[i] = pw[i - 1] * i % mod;
    }
    pwinv[n] = qpow(pw[n],mod - 2);
    for(int i = n - 1;i;i--)pwinv[i] = pwinv[i + 1] * (i + 1ll) % mod;
    pwinv[0] = 1;

    // for(int i = 1;i <= n;i++){printf("i = %lld,tim = %lld\n",i,pwinv[i] * pw[i] % mod);}

    sort(x + 1,x + 1 + tot);tot = unique(x + 1,x + 1 + tot) - x - 1;
    for(int i = 1;i <= n;i++){
        l[i] = lower_bound(x + 1,x + 1 + tot,l[i]) - x;
        r[i] = lower_bound(x + 1,x + 1 + tot,r[i]) - x;
        cf[l[i]]++;cf[r[i]]--;
    }
    int ans = 0;
    for(int i = 1;i < tot;i++){
        cf[i] += cf[i - 1];if(cf[i] < k)continue;
        int len = x[i + 1] - x[i];
        ans = (ans + pw[cf[i]] * pwinv[cf[i] - k] % mod * pwinv[k] % mod * len % mod) % mod;
    }
    printf("%lld\n",ans);
    return 0;
}