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
int n = 2000;
int range = 1e9;
void main(){
    printf("%d %d %d\n",n,n,1);mt19937 rnd(114514);
    for(int i = 1;i <= n;i++){
        int l = rnd() % n + 1, r = rnd() % n + 1;
        if(l > r)swap(l, r);
        printf("%d %d\n",l,r);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("kuhu.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}