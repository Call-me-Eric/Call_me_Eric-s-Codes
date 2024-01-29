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
bool book[maxn];
int tot, prime[maxn];
int mu[maxn], sum[maxn];
void init(){
    mu[1] = 1;
    for(int i = 2;i < maxn;i++){
        if(!book[i]){mu[i] = -1;prime[++tot] = i;}
        for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for(int i = 1;i < maxn;i++)sum[i] = sum[i - 1] + mu[i];
}
void main(){
    int T = read();init();
    auto solve = [](int n,int m,int k)->int{
        if(n == 0 || m == 0)return 0;
        if(n > m)swap(n, m);
        n /= k;m /= k;int ans = 0;
        for(int l = 1, r = 0;l <= n;l = r + 1){
            r = min(n / (n / l), m / (m / l));
            ans += (n / l) * (m / l) * (sum[r] - sum[l - 1]);
        }
        return ans;
    };
    while(T--){
        int a = read(), b = read(), c = read(), d = read(), k = read();
        printf("%lld\n",solve(b, d, k) - solve(a - 1,d,k) - solve(b,c - 1,k) + solve(a - 1,c - 1,k));
    }
    return;
}
};
bool edmemory;
signed main(){
#ifndef ONLINE_JUDGE
    freopen("tmp.in","r",stdin);
    freopen("tmp.out","w",stdout);
#endif
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}