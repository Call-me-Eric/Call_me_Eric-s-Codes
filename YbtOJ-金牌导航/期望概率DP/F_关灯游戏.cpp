#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 1e5 + 3;
int n, k;bool book[maxn];
int f[maxn];
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
signed main(){
    n = read();k = read();int cnt = 0, pw = 1;
    for(int i = 1;i <= n;i++){book[i] = read();}
    for(int i = n;i;i--){
        pw = pw * i % mod;
        if(book[i]){
            cnt++;
            for(int j = sqrt(i);j;j--){
                if(i % j)continue;
                book[i / j] ^= 1;
                if(j * j != i)book[j] ^= 1;
            }
        }
    }
    f[n + 1] = 0;int ans = 0;
    if(cnt > k){
        ans = k;
        for(int i = n;i;i--){f[i] = (n + (n - i) * f[i + 1] % mod) % mod * qpow(i,mod - 2) % mod;}
        for(int i = k + 1;i <= cnt;i++)ans = (ans + f[i]) % mod;
    }
    else ans = cnt;
    printf("%lld\n",ans * pw % mod);
    return 0;
}