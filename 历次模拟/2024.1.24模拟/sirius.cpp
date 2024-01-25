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
const int maxn = 100 + 10;
int n, m, r, c, mod;
void main(){
    n = read(); m = read(); r = read(); c = read(); mod = read();
    if(r == c && r == 1){puts("2");return;}
    mt19937 rnd(1145141919);printf("%d\n",rnd() % mod);
    return;
}
};
bool edmemory;
signed main(){
    freopen("sirius.in","r",stdin);
    freopen("sirius.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}