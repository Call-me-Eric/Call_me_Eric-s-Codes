#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 61;
int n, m, mod, ans, k, a[maxn];
int qpow(int x,int a){int res = 1;for(;a;a >>= 1, x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
int invv[maxn], pw[maxn], invpw[maxn];
void dfs(int sum,int rest,int inv,int lstnum, int cnt){
    if(rest == 0){
        // printf("%lld %lld\n",sum,inv);
        ans = (ans + qpow(m,sum) * inv) % mod;
        return;
    }
    for(int i = min(rest,lstnum);i;i--){
        int g = 0;for(int j = 1;j <= k;j++)g += __gcd(a[j],i);
        a[++k] = i;
        if(i == a[k - 1]){dfs(sum + i / 2 + g,rest - i,inv * invpw[cnt + 1] % mod * pw[cnt] % mod * invv[i] % mod,i,cnt + 1);}
        else dfs(sum + i / 2 + g,rest - i,inv * invv[i] % mod,i,1);
        k--;
    }
}
signed main(){
    n = read(); m = read();mod = read();pw[0] = invpw[0] = 1;
    for(int i = 1;i <= n;i++){
        invv[i] = qpow(i,mod - 2);
        pw[i] = pw[i - 1] * i % mod;
        invpw[i] = invpw[i - 1] * invv[i] % mod;
    }
    dfs(0,n,1,n,0);
    printf("%lld\n",ans);
    return 0;
}