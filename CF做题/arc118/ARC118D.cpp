#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int qpow(int x,int a,int mod){
    int res = 1;
    while(a){
        if(a & 1) res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int p, a, b, inva, invb;
bool book[maxn];
vector<int> arr;
signed main(){
    p = read(); a = read(); b = read();
    inva = qpow(a,p - 2,p);invb = qpow(b,p - 2,p);
    int n = 1, m = 1, x = a, y = b;
    while(n <= p){book[x] = 1;if(x == 1)break;x = (x * a % p);n++;}
    while(m <= p){if(book[y])break;y = y * b % p;m++;}
    if(n * m != p - 1 || !book[y]){puts("No");return 0;}
    puts("Yes");
    if(n == 1 || m == 1){
        if(n == 1){swap(a, b);}x = 1;
        for(int i = 1;i <= p;i++){printf("%lld ",x);x = x * a % p;}
        puts(""); return 0;
    }
    if((m & 1) == 0){
        x = 1;
        for(int i = 1;i <= m;i++){
            arr.push_back(x);
            x = x * b % p;
        }
        x = x * invb % p;x = x * a % p;
        for(int i = 1;i <= m;i += 2){
            for(int j = 2;j <= n;j++){
                arr.push_back(x);
                x = x * a % p;
            }
            x = x * inva % p;x = x * invb % p;
            for(int j = 2;j <= n;j++){
                arr.push_back(x);
                x = x * inva % p;
            }
            x = x * a % p;x = x * invb % p;
        }
        for(int i : arr)printf("%lld ",i);
        puts("1");
        return 0;
    }
    else{
        swap(a,b);swap(inva,invb);swap(n, m);
        x = 1, y = 1;
        for(int i = 1;i <= m;i += 2){
            for(int j = 1;j <= n;j++){
                arr.push_back(x * y % p);
                x = x * a % p;
            }
            y = y * b % p;x = x * inva % p;
            for(int j = 1;j <= n;j++){
                arr.push_back(x * y % p);
                x = x * inva % p;
            }
            x = x * a % p;y = y * b % p;
        }
        for(int i : arr)printf("%lld ",i);
        puts("1");
    }
    return 0;
}