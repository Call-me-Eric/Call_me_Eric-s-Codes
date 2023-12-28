#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int mod, n;
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
int phi(int n){
    int ans = n;
    for(int i = 2;i * i <= n;i++){
        if(n % i == 0){
            ans = ans / i * (i - 1);
            while(n % i == 0)n /= i;
        }
    }
    if(n > 1)ans = ans / n * (n - 1);
    return ans;
}
signed main(){
    for(int Test = read();Test;Test--){
        n = read();mod = read();
        int ans = 0;
        for(int i = 1;i * i <= n;i++){
            if(n % i != 0)continue;
            ans = (ans + phi(i) * qpow(n,n / i - 1) % mod) % mod;
            if(i * i != n)ans = (ans + phi(n / i) * qpow(n,i - 1) % mod) % mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}