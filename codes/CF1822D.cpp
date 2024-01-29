#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int X, T;
int n;
int qpow(int x,int a,int mod){
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
    n = read();
    if(((n & 1) != 0) && n != 1){puts("-1");}
    else{
        printf("%lld ",n);
        for(int i = 1;i < n;i++){printf("%lld ",(i & 1) ? (i) : (n - i));}
    }
}
    return 0;
}