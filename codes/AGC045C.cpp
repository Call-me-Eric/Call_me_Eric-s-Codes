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
const int maxn = 5e3 + 10, mod = 1e9 + 7;
int n, a, b;
int f[maxn][maxn][2], sum[maxn][maxn][2];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int pw[maxn], pre[maxn];
void main(){
    n = read(); a = read(); b = read();if(a < b)swap(a, b);
    pw[0] = 1;for(int i = 1;i < maxn;i++){pw[i] = pw[i - 1] * 2 % mod;}
    pre[0] = f[0][0][0] = f[0][0][1] = sum[0][0][0] = sum[0][0][1] = 1;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        sum[i][0][1] = f[i][0][1] = (pre[i - 1] - (i - b >= 0 ? pre[i - b] : 0) + mod) % mod;
        for(int j = 1;j <= i;j++){
            if(j >= b){
                int val = sum[i - b][j - b][0];
                if(j >= a)ans = (ans + val * pw[max(n - i - 1,0ll)] % mod) % mod;
                else f[i][j][1] = val;
            }
        }
        for(int j = 1;j <= i;j++){
            int val = sum[i - 1][j - 1][1];
            if(j >= a)ans = (ans + val * pw[max(n - i - 1,0ll)] % mod) % mod;
            else f[i][j][0] = val;
        }
        pre[i] = pre[i - 1];
        for(int j = 1;j <= i;j++){
            pre[i] = (pre[i] + f[i][j][0]) % mod;
            sum[i][j][0] = (sum[i - 1][j - 1][0] + f[i][j][0]) % mod;
            sum[i][j][1] = (sum[i - 1][j - 1][1] + f[i][j][1]) % mod;
        }
    }
    printf("%lld\n",ans);
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