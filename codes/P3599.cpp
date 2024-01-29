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
    X = read(); T = read();
if(X == 1){
while(T--){
    n = read();
    if(((n & 1) != 0) && n != 1){puts("0");}
    else{
        printf("2 %lld",n);
        for(int i = 1;i < n;i++){printf(" %lld",(i & 1) ? (i) : (n - i));}
        puts("");
    }
}
}
else{
while(T--){
    n = read();
    if(n == 1){puts("2 1");continue;}
    if(n == 4){puts("2 1 3 2 4");continue;}
    int flag = false;for(int i = 2;i < n;i++){if(i != 1 && n % i == 0)flag = true;}
    if(flag){puts("0");continue;}
    printf("2 1");for(int i = 2;i < n;i++)printf(" %lld",(i - 1) * qpow(i,n - 2,n) % n);printf(" %lld\n",n);
}
}
    return 0;
}