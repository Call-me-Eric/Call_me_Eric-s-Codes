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
const int maxn = 3e2 + 10, mod = 1e9 + 7;
int det(int n,int mod,int a[][maxn]){
    int res = 1, f = 1;
    for(int i = 1;i <= n;i++){
        int k = i;
        for(int j = i;j <= n;j++)if(a[j][i]){k = j;break;}
        if(!a[k][i])return 0;
        for(int j = k + 1;j <= n;j++)if(a[j][i] && a[j][i] < a[k][i])k = j;
        if(i != k){swap(a[i],a[k]);f = -f;}
        for(int j = i + 1;j <= n;j++){
            if(a[j][i] > a[i][i]){swap(a[j],a[i]);f = -f;}
            while(a[j][i]){
                int l = a[i][i] / a[j][i];
                for(int k = i;k <= n;k++)a[i][k] = (a[i][k] + (-l + mod) % mod * a[j][k] % mod) % mod;
                swap(a[j],a[i]);f = -f;
            }
        }
        res = res * a[i][i] % mod;
    }
    return (res * f + mod) % mod;
}
int n, m, opt;
int a[maxn][maxn];
void main(){
    n = read(); m = read(); opt = read();
    for(int i = 1;i <= m;i++){
        int u = read() - 1, v = read() - 1, w = read();
        a[v][v] = (a[v][v] + w) % mod;
        a[u][v] = (a[u][v] - w + mod) % mod;
        if(opt == 0){
            a[u][u] = (a[u][u] + w) % mod;
            a[v][u] = (a[v][u] - w + mod) % mod;
        }
    }
    printf("%lld\n",det(n - 1,mod,a));
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