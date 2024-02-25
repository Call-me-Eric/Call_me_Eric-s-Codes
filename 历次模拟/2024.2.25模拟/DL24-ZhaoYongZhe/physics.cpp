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
const int maxn = 2e6 + 10, mod = 998244353;
char ch[maxn];
int n;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int inv[maxn], pw[maxn];
int sum0[maxn], sum1[maxn];
int C(int x,int y){return pw[x] * inv[x - y] % mod * inv[y] % mod;}
void main(){
    scanf("%s",ch + 1);n = strlen(ch + 1);
    pw[0] = inv[0] = 1;
    for(int i = 1;i < maxn;i++)pw[i] = pw[i - 1] * i % mod;
    inv[maxn - 1] = qpow(pw[maxn - 1],mod - 2);
    for(int i = maxn - 2;i;i--)inv[i] = inv[i + 1] * (i + 1) % mod;
    for(int i = 1;i <= n;i++){
        sum0[i] = sum0[i - 1] + (ch[i] == '-');
        sum1[i] = sum1[i - 1] + (ch[i] == '?');
    }
    int ans = 0;
    for(int k = 0;k <= sum1[n];k++){
        int tot = n - k - sum0[n];
        ans = (ans + sum1[tot] * C(sum1[n] - 1,k - 1) % mod + sum0[tot] * C(sum1[n],k) % mod) % mod;
    }
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("physics.in","r",stdin);
    freopen("physics.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}