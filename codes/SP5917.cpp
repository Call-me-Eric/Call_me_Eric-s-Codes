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
const int maxn = 1e6 + 10;
int prime[maxn], tot;
int g[maxn];bool book[maxn];
void init(){
    g[1] = 1;
    for(int i = 2;i < maxn;i++){
        if(!book[i]){g[i] = (i - 1) * i + 1;prime[++tot] = i;}
        for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0){
                g[i * prime[j]] = g[i] + (g[i] - g[i / prime[j]]) * prime[j] * prime[j];
                break;
            }
            g[i * prime[j]] = g[i] * g[prime[j]];
        }
    }
}
void main(){
    init();int T = read();
    while(T--){
        int n = read();
        printf("%lld\n",n * (g[n] + 1) / 2);
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