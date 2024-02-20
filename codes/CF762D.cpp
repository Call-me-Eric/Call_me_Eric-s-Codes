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
const int maxn = 1e5 + 10;
int n, a[3][maxn], f[3][maxn];
int sum[maxn];
void main(){
    n = read();
    for(int i = 0;i < 3;i++)
        for(int j = 1;j <= n;j++){
            a[i][j] = read();
            sum[j] += a[i][j];
        }
    int max0 = sum[1], max2 = -0x3f3f3f3f3f3f3f3f;
    f[0][1] = a[0][1];f[1][1] = a[0][1] + a[1][1];f[2][1] = sum[1];
    for(int i = 2;i <= n;i++){
        f[0][i] = max(max(f[0][i - 1],f[1][i - 1] + a[1][i]),f[2][i - 1] + a[1][i] + a[2][i]) + a[0][i];
        f[1][i] = max(max(f[0][i - 1] + a[0][i],f[1][i - 1]),f[2][i - 1] + a[2][i]) + a[1][i];
        f[2][i] = max(max(f[0][i - 1] + a[1][i] + a[0][i],f[1][i - 1] + a[1][i]),f[2][i - 1]) + a[2][i];
        max2 = max(max2,f[2][i - 1]) + sum[i];
        max0 = max(max0,f[0][i - 1]) + sum[i];
        f[0][i] = max(f[0][i],max2);f[2][i] = max(max0,f[2][i]);
    }
    printf("%lld\n",f[2][n]);
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
/*
5
10 10 10 -1 -1
-1 10 10 10 10
-1 10 10 10 10
*/