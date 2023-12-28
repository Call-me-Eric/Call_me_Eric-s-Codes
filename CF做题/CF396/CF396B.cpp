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
int n;
int prime[maxn], tot;
bool book[maxn];

bool isprime(int x){
    for(int i = 1, len = sqrt(x);i <= tot && prime[i] <= len;i++)
        if(x % prime[i] == 0)return false;
    return true;
}
int U(int x){
    x++;while(!isprime(x))x++;
    return x;
}
int V(int x){
    while(!isprime(x))x--;
    return x;
}
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}

signed main(){
    for(int i = 2;i <= 1e5;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && prime[j] * i <= 1e5;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    int T = read();
    while(T--){
        n = read();
        int x = U(n), y = V(n);
        // printf("u = %lld, v = %lld\n", x, y);
        int u = x * y + (n - x - y + 1) * 2, v = 2 * x * y;
        int g = gcd(u, v);
        printf("%lld/%lld\n",u / g,v / g);
    }
    return 0;
}