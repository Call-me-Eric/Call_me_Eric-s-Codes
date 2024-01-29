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
const int maxn = 2e6 + 10, maxm = 1e2 + 10, mod = 998244353;
int fac[maxn], invfac[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int C(int n,int m){return fac[n] * invfac[m] % mod * invfac[n - m] % mod;}
int n, m;
int a[maxm], b[maxm];
int arr[maxm][maxm];
int det(int n,int mod,int a[][maxm]){
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
void main(){
    fac[0] = invfac[0] = 1;
    for(int i = 1;i < maxn;i++){fac[i] = fac[i - 1] * i % mod;}
    invfac[maxn - 1] = qpow(fac[maxn - 1],mod - 2);
    for(int i = maxn - 2;i;i--){invfac[i] = invfac[i + 1] * (i + 1) % mod;}
    auto solve = []()->int{
        n = read(); m = read();
        for(int i = 1;i <= m;i++){a[i] = read();b[i] = read();}
        for(int i = 1;i <= m;i++)
            for(int j = 1;j <= m;j++)
                arr[i][j] = ((b[j] >= a[i]) ? C(b[j] - a[i] + n - 1,n - 1) : 0);
        return det(m,mod,arr);
    };
    int T = read();
    while(T--){printf("%lld\n",solve());}
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