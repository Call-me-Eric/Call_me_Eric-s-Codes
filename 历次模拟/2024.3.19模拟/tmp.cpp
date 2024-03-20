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
int sid = 0, n = 2e5, m = 2e5;
mt19937 rnd(10086);
int range = 1e9;
int getint(int x = 1){return (rnd() % x + rnd()) % (2 * range) - range;}
void main(){
    freopen("recall.in","w",stdout);
    printf("%lld %lld %lld\n",sid,n,m);
    for(int i = 1;i <= n;i++)printf("%lld ",getint(i));puts("");
    int opt = 1, l = 1, r = 1, x = 1;
    for(int i = 1;i <= m;i++){
        opt = (rnd() & 1) + 1, l = rnd() % n + 1, r = rnd() % n + 1, x = getint(x) * getint(x);
        printf("%lld %lld %lld %lld\n",opt,l,r,opt == 1 ? (x % range) : x);
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