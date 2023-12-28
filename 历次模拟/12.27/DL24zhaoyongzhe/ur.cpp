#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, k;
signed main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    n = read(); k = read();
    int x = n, minn = k, mod = n;
    for(int i = 2;i <= x;i++){
        if(x % i == 0){
            if(k % i < minn){minn = k % i;mod = i;}
            while(x % i == 0)x /= i;
        }
    }
    if(x > 1 && k % x <= minn){minn = k % x;mod = x;}
    for(int i = 1;i <= n;i += n / mod){
        for(int j = 0;j < k / mod;j++){putchar('1');}
        for(int j = k / mod;j < n / mod;j++){putchar('0');}
    }
    puts("");
    return 0;
}