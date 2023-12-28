#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, m;
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x)if(a & 1)res = res * x;return res;}
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
signed main(){
    while((m = read()) , (n = read()), (n || m)){
        int ans = 0;
        for(int i = 1;i <= n;i++){ans += qpow(m,gcd(n,i));}
        if(n & 1){ans += n * qpow(m, n / 2 + 1);}
        else{ans += (n / 2) * (qpow(m,n / 2 + 1) + qpow(m,n / 2));}
        ans /= 2 * n;
        printf("%lld\n",ans);
    }
    return 0;
}