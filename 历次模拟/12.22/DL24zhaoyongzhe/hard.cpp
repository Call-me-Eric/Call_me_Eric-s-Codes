#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const ll mod = 1e9 + 7, maxn = 1e3 + 10;
ll qpow(ll x,int a){ll res = 1;for(;a;a >>= 1, x = x * x % mod)if(a & 1)res = res * x % mod;return res;}

int n, a[maxn];
signed main(){
    freopen("hard.in","r",stdin);
    freopen("hard.out","w",stdout);
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    if(n == 2){
        ll sum = a[1] + a[2];
        ll a0 = 0, b0 = 0, a1 = 1, b1 = 0;
        ll ax = 1, bx = 0;
        for(int i = 2;i <= sum;i++){
            a0 = (2 * a1 - a0 + mod) % mod;
            b0 = (2 * b1 - b0 - (sum - 1) * sum % mod * qpow((i - 1) * (sum - i + 1),mod - 2) % mod + mod) % mod;
            swap(a0,a1);swap(b0,b1);
            if(i == a[1]){ax = a1;bx = b1;}
        }
        ll k1 = (mod - b1) * qpow(a1,mod - 2) % mod;
        printf("%lld\n",(ax * k1 % mod + bx) % mod);
    }
    else{
        // puts("It's too hard for me");
        srand(time(0));mt19937 rnd(rand());
        printf("%d\n",rnd() % mod);
    }
    return 0;
}