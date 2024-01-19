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
const int maxn = 5e4 + 10;
int prime[maxn], tot;
bool book[maxn];
int mu[maxn];
int summu[maxn], sumd[maxn];
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
    for(int i = 1;i < maxn;i++){summu[i] = summu[i - 1] + mu[i];}
    for(int n = 1;n < maxn;n++){
        for(int l = 1,r = 0;l <= n;l = r + 1){
            r = n / (n / l);
            sumd[n] += (r - l + 1) * (n / l);
        }
    }
}
void main(){
    init();int T = read();
    while(T--){
        int n = read(), m = read();
        if(n > m)swap(n, m);int ans = 0;
        for(int l = 1, r = 0;l <= n;l = r + 1){
            r = min(n / (n / l),m / (m / l));
            ans += (summu[r] - summu[l - 1]) * sumd[n / l] * sumd[m / l];
        }
        printf("%lld\n",ans);
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