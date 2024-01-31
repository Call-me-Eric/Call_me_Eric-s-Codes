#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int a[maxn], b[maxn];
int n, m;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = (res * x) % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int sum[maxn];
int frac(int x,int y){return x * qpow(y,mod - 2) % mod;}
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)b[i] = read();
    int times = 1, ans = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] && b[i] && a[i] != b[i]){printf("%lld",(ans + (a[i] > b[i]) * times % mod) % mod);return 0;}
        if(a[i] && !b[i]){ans = (ans + frac(a[i] - 1,m) * times % mod) % mod;times = times * frac(1, m) % mod;}
        if(!a[i] && b[i]){ans = (ans + frac(m - b[i],m) * times % mod) % mod;times = times * frac(1, m) % mod;}
        if(!a[i] && !b[i]){ans = (ans + frac(m - 1,2 * m) * times % mod) % mod;times = times * frac(1, m) % mod;}
    }
    printf("%lld\n",ans);
    return 0;
}