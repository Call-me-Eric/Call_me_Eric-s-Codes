#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int qpow(int x,int a,int mod){
    int res = 1;
    while(a){
        if(a & 1) res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
    printf("%d %d\n",qpow(4,11,13),qpow(5,11,13));
    return 0;
}