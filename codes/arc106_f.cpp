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
const int maxn = 2e5 + 10, mod = 998244353;
int n;
void main(){
    n = read();int sum = 0, prod = 1;
    for(int i = 1;i <= n;i++){
        int t = read();
        sum += t;prod *= t; prod %= mod;
        sum = (sum >= mod) ? (sum - mod) : sum;
    }
    for(int i = 0;i <= n - 3;i++){prod = (prod * (sum - n - i)) % mod;}
    printf("%lld\n",prod);
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