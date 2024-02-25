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
const int maxn = 5e3 + 10, mod = 998244353;
int n;
int a[maxn], b[maxn];
int f[maxn][maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++){a[i] = read();}
    for(int i = 1;i <= n + 1;i++)b[i] = read();
    sort(a + 1,a + 1 + n);sort(b + 1,b + 1 + n + 1);
    f[0][0] = 1;
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= i;j++){
            if(j){f[i + 1][j - 1] = (f[i + 1][j - 1] + f[i][j] * (j - 1) % mod) % mod;}
            if(a[i + 1] < b[i + j + 1]){
                f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] * (j + 1) % mod) % mod;
                f[i + 1][j] = (f[i + 1][j] + f[i][j] * j * 2 % mod) % mod;
            }
        }
    }
    printf("%lld\n",f[n][1]);
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