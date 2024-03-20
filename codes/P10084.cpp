#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e7 + 10, mod = 998244353;
int qpow(int x,int a,int p = mod){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % p;
        x = x * x % p;a >>= 1;
    }
    return res;
}
bool book[maxn];
int prime[maxn], tot;
int phi[maxn];
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
int F(int m,int a,int b){
    if(!a || !b)return 0;
    return qpow(m,gcd(a,b),LONG_LONG_MAX);
}
void solve(){
    int m = read(), a = read(), b = read(), c = read(), d = read();
    int L = F(m,a,b) + 1,R = F(m,c,d);
    int n = R - L + 1;
    int u = m;while((u & 1) == 0)u >>= 1;
    int ans = 0;
    for(int i = 1, len = sqrt(u);i <= len;i++){
        if(u % i != 0)continue;
        ans = (ans + qpow(2,n / u * i) * phi[u / i] % mod) % mod;
        if(i * i != u){
            int j = u / i;
            ans = (ans + qpow(2,n / u * j) * phi[u / j] % mod) % mod;
        }
    }
    ans = ans * qpow(m,mod - 2) % mod;
    printf("%lld\n",ans);
}
void main(){
    phi[1] = 1;
    for(int i = 2;i < maxn;i++){
        if(!book[i]){prime[++tot] = i;phi[i] = i - 1;}
        for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    int T = read();while(T--)solve();
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}