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
const int maxn = 100;
int n = 100, m = 100;

void main(){
    srand(time(0));mt19937 rnd(rand());
    printf("%d %d\n",n,m);
    for(int i = 1;i <= n;i++){
        int a = rnd() % 10 + 1, s = a + rnd() % 1000, p = 1;
        printf("%d %d %d\n",a,s,p);
    }
    for(int i = 1;i <= m;i++){
        int a = rnd() % 10 + 1, s = a + rnd() % 1000, p = 1;
        printf("%d %d %d\n",a,s,p);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("chef.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}