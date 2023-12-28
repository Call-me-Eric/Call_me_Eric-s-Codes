#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int T, a, b, c, k;
const int mod = 200907;
int qpow(int a,int p){
    int res = 1;
    while(p){
        if(p & 1)res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}
signed main(){
    T = read();
    while(T--){
        a = read(); b = read(); c = read(); k = read();
        if(c - b == b - a) printf("%lld\n",((a + (c - b) * (k - 1)) % mod + mod) % mod);
        else printf("%lld\n",((a * qpow(c / b,k - 1)) % mod + mod) % mod);
    }
    return 0;
}
