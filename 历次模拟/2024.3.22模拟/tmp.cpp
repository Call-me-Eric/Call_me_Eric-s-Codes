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
const int maxn = 3e5 + 10, range = 1e9;
int n, q;
int a[maxn];
int l[maxn], r[maxn];
int s[maxn], t[maxn];
int getint(int x = 1){return (rand() % (x + 1) + (rand() * x) % (x / 2 + 1)) % range;}
void main(){
    srand(time(0));
    mt19937 rnd(rand());
    n = 5e3, q = 3e5;
    for(int i = 1;i <= n;i++){a[i] = getint(rnd() % range) % n + 1;l[i] = getint(rnd() % range),r[i] = getint(l[i]);}
    for(int i = 1;i <= q;i++){s[i] = getint(rnd() % range) % n + 1;t[i] = getint(s[i]) % n + 1;}
    puts("1");
    printf("%lld %lld\n",n,q);
    for(int i = 1;i <= n;i++)printf("%lld ",a[i]);puts("");
    for(int i = 1;i <= n;i++)printf("%lld %lld\n",l[i],r[i]);
    for(int i = 1;i <= q;i++)printf("%lld %lld\n",s[i],t[i]);
    return;
}
};
bool edmemory;
signed main(){
    freopen("railway.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}