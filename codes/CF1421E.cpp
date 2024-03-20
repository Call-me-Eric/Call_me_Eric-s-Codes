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
const int maxn = 2e5 + 10;
int n;
int a[maxn];
int f[maxn][3][2][2];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    if(n == 1){printf("%lld\n",a[1]);return;}
    memset(f,-0x3f,sizeof(f));
    f[1][1][1][0] = a[1];f[1][2][0][0] = -a[1];
    for(int i = 1;i < n;i++)for(int j = 0;j < 3;j++)
        for(int k = 0;k < 2;k++)for(int t = 0;t < 2;t++){
            f[i + 1][(j + 2) % 3][0][t |!k] = max(f[i + 1][(j + 2) % 3][0][t |!k],f[i][j][k][t] - a[i + 1]);
            f[i + 1][(j + 1) % 3][1][t | k] = max(f[i + 1][(j + 1) % 3][1][t | k],f[i][j][k][t] + a[i + 1]);
        }
    printf("%lld\n",max(f[n][1][1][1],f[n][1][0][1]));
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