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
int a[10], p[10];
void solve(){
    int ans = 0,sum = 0;
    for(int i = 1;i <= 5;i++)(a[i] = read()),sum += (i - 3) * a[i];
    for(int i = 1;i <= 5;i++){p[i] = read();}
    if(sum >= 0){puts("0");return;}
    // cerr << "sum = " << sum << endl;
    sum = -sum;
    if(p[5] > 2 * p[4]){ans = sum * p[4];}
    else ans = sum / 2 * p[5] + (sum & 1) * min(p[5],p[4]);
    printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
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