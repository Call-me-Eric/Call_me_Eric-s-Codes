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

void main(){
    freopen("base.in","w",stdout);
    int n, k = 0;
    srand(time(0));mt19937 rnd(rand());
    n = rnd() % 114514 + 1;if(n & 1)n++;k = min((int)(1e8) / n,(int)(rnd() % n + 1));
    printf("%d %d\n",n,k);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    return 0;
}