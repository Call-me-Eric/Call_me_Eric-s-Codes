#include<bits/stdc++.h>
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
int n;
void solve(){
    n = read();long long ans = 0;
    for(int i = 3;i <= 1 + n;i++)ans += 1ll * (n - i / 2) * (n - i / 2);
    printf("%lld\n",ans);
    printf("%d ",n / 2 + 1);for(int i = 1;i < n / 2;i++)printf("%d ",i);
    for(int i = n / 2 + 2;i <= n;i++)printf("%d ",i);printf("%d\n",n / 2);
    printf("%d\n",n - 1);
    for(int i = n / 2;i >= 2;i--)printf("%d %d\n",i,n);
    for(int i = n / 2 + 1;i <= n;i++)printf("%d %d\n",i,1);
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