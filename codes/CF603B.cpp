#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int p, k;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
    p = read(); k = read();
    if(k == 0){printf("%lld\n",qpow(p,p - 1));return 0;}
    if(k == 1){printf("%lld\n",qpow(p,p));return 0;}
    int m = 1,tmp = k;while(tmp != 1){tmp = tmp * k % p;m++;}
    printf("%lld\n",qpow(p,(p - 1) / m));
    return 0;
}