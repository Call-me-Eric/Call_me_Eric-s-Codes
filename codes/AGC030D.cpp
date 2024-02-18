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
const int maxn = 3e3 + 10, mod = 1e9 + 7;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int f[maxn][maxn];
int n, q;
int a[maxn];
void main(){
    n = read(); q = read();int inv2 = qpow(2,mod - 2);
    for(int i  =1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)for(int j = 1;j <= n;j++)f[i][j] = a[i] < a[j];
    for(int i = 1;i <= q;i++){
        int x = read(), y = read();
        f[x][y] = f[y][x] = (f[x][y] + f[y][x]) * inv2 % mod;
        for(int j = 1;j <= n;j++){
            if(j == x || j == y)continue;
            f[j][x] = f[j][y] = (f[j][x] + f[j][y]) * inv2 % mod;
            f[x][j] = f[y][j] = (f[x][j] + f[y][j]) * inv2 % mod;
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)for(int j = 1;j < i;j++)ans = (ans + f[i][j]) % mod;
    printf("%lld\n",ans * qpow(2,q) % mod);
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