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
const int maxn = 5e5 + 10;
mt19937 rnd(114514);
int range = 1 << 30;
int getint(int x = 0){return (1ll * x * rnd() % range + rnd()) % range;}
int p[maxn], a[maxn];
void main(){
    srand(time(0));
    int n = 5e5, m = 5e5;
    printf("%lld %lld\n",n,m);
    for(int i = 1;i <= n;i++)p[i] = n - i + 1;
    for(int i = 1;i <= n;i++){
        swap(p[i],p[getint(getint(i)) % n + 1]);
        if(p[i] == i){swap(p[i],p[(i + 1) % n + 1]);}
        a[i] = getint(i) % n + 1;
    }
    for(int i = 1;i <= n;i++)printf("%lld ",p[i]);puts("");
    for(int i = 1;i <= n;i++)printf("%lld ",a[i]);puts("");
    for(int i = 1;i <= m;i++){
        int opt = (getint(i) & 1) + 1, l = getint(i) % n + 1, r = getint(l) % n + 1;
        if(opt == 2){if(l > r)swap(l,r);}
        else r = getint(r) % n + 1;
        printf("%lld %lld %lld\n",opt,l,r);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("tmp.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}