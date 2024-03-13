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
const int maxn = 2e5 + 10, mod = 1e9 + 7, maxk = 10;
int n, q;
int arr[maxn];
int sum[maxk + 1][maxn];
int fac[maxk + 1][maxn];
int C[maxk + 1][maxk + 1];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int calc(int a,int d,int len,int k){
    int ans = 0;
    for(int j = 0;j <= k;j++){
        ans = (ans + (C[k][j] * qpow(a,k - j) % mod * qpow(d,j) % mod * fac[j][len - 1] % mod)) % mod;
    }
    return ans;
}
void main(){
    n = read(); q = read();
    C[0][0] = 1;
    for(int i = 1;i <= maxk;i++){C[i][0] = 1;for(int j = 1;j <= i;j++)C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;}
    fac[0][0] = 1;
    for(int i = 1;i <= n;i++){
        arr[i] = read(); sum[0][i] = 1; fac[0][i] = 1;
        for(int k = 1;k <= maxk;k++){sum[k][i] = sum[k - 1][i] * arr[i] % mod;fac[k][i] = fac[k - 1][i] * i % mod;}
        for(int k = 0;k <= maxk;k++){sum[k][i] = (sum[k][i] + sum[k][i - 1]) % mod;fac[k][i] = (fac[k][i] + fac[k][i - 1]) % mod;}
    }
    while(q--){
        int l = read(), r = read(), d = read();
        int sm = (sum[1][r] - sum[1][l - 1] + mod) % mod;
        int a = (sm - d * ((r - l) * (r - l + 1) / 2 % mod) % mod + mod) % mod * qpow(r - l + 1,mod - 2) % mod;
        bool flag = true;
        for(int k = 1;k <= maxk;k++)
            if((sum[k][r] - sum[k][l - 1] + mod) % mod != calc(a,d,r - l + 1,k)){
                // printf("k = %lld,a = %lld\n",k,a);
                flag = false;break;
            }
        puts(flag ? "Yes" : "No");
    }
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