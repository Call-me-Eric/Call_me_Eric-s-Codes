#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10, mod = 1e9 + 7;
int f[maxn];
int n, k;
int ans, sum;

int inv[maxn], pw[maxn];

int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = (res * x) % mod;
        x = (x * x) % mod;a >>= 1;
    }
    return res;
}
int C(int x,int y){return pw[x] * inv[x - y] % mod * inv[y] % mod;}

signed main(){
    freopen("arisu.in","r",stdin);
    freopen("arisu.out","w",stdout);
    n = read(); k = read();
    pw[0] = f[0] = sum = 1;
    for(int i = 1;i <= n;i++){pw[i] = pw[i - 1] * i % mod;}
    inv[n] = qpow(pw[n],mod - 2);
    for(int i = n;i;i--){inv[i - 1] = inv[i] * i % mod;}
    
    for(int i = 1;i < n;i++){
        f[i] = pw[i - 1] * sum % mod;
        sum = (sum + inv[i] * f[i] % mod) % mod;
        ans = (ans + C(n - 1,i) * f[i] % mod * pw[n - i - 1] % mod) % mod;
        if(i >= k)sum = (sum - inv[i - k] * f[i - k] % mod + mod) % mod;
    }
    ans = (ans + pw[n - 1]) % mod;
    ans = (pw[n] - ans + mod) % mod;
    printf("%lld\n",ans % mod);
    return 0;
}