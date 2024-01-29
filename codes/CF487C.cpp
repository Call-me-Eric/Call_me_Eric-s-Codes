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
    n = read();
    if(n == 1){puts("YES\n1");return 0;}
    if(n == 4){puts("YES\n1\n3\n2\n4");return 0;}
    int flag = false;for(int i = 2;i < n;i++){if(i != 1 && n % i == 0)flag = true;}
    if(flag){puts("NO");return 0;}
    printf("YES\n1\n");for(int i = 2;i < n;i++)printf("%lld\n",(i - 1) * qpow(i,n - 2,n) % n);printf("%lld\n",n);

    return 0;
}