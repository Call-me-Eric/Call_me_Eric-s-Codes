#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10, mod = 1e8 + 7;
int f[maxn], S[maxn], Si[maxn];
int n, k;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
int T = read();
while(T--){
    n = read(); k = read();
    int ans = 0;Si[0] = 0;
    f[0] = S[0] = 1;
    for(int i = 1;i <= n;i++){
        if(i - 2 >= k)f[i] = (S[i - 1] - S[i - k - 2] + mod) % mod;
        else f[i] = S[i - 1];
        S[i] = (S[i - 1] + f[i]) % mod;
        Si[i] = (Si[i - 1] + f[i] * i) % mod;
    }
    for(int i = 1;i <= n;i++){
        int g =__gcd(i, n);
        if(g - 2 >= k){ans = (ans + g * (S[g - 1] - S[g - k - 2] + mod) % mod - (Si[g - 1] - Si[g - k - 2] + mod) % mod + mod) % mod;}
        else ans = (ans + g * (S[g - 1]) % mod - (Si[g - 1]) % mod + mod) % mod;
        if(k >= n)ans++;ans %= mod;
    }
    ans = ans * qpow(n,mod - 2) % mod;
    printf("%lld\n",ans);
}
    return 0;
}