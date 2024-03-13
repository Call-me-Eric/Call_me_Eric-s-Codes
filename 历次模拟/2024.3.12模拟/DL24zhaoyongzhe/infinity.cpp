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
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int n, m;
int a[maxn], c[maxn];
int f[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)c[i] = read();
    if(n == 1){
        if(c[1] == 0){
            printf("%lld\n",qpow(a[1],m));
            return;
        }
        else{
            printf("%lld\n",qpow(2,m - 1));
            return;
        }
    }
    if(n == 2){
        int ans = 0;
        for(int i = 0;i <= m;i++){
            if((m - i) & 1)continue;
            int x = (m - i) / 2;
            ans = (ans + qpow(i + 1,x) * qpow(a[1],i) % mod * qpow(a[2],x) % mod) % mod;
        }
        printf("%lld\n",ans);
    }
    for(int i = 1;i <= n;i++)f[i] = a[i];
    for(int i = n + 1;i <= m;i++)for(int j = 1;j <= n;j++)
        f[i] = (f[i] + c[j] * f[i - j] % mod) % mod;
    return;
}
};
bool edmemory;
signed main(){
    freopen("infinity.in","r",stdin);
    freopen("infinity.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}