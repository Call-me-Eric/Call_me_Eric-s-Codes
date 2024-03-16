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

mt19937 rnd(114514);
int range = 1 << 30;
int getint(int x = 0){return (1ll * x * rnd() % range + rnd()) % range;}
void main(){
    int T = 1;
    srand(time(0));
    printf("%d\n",T);
    while(T--){
        int n = 2e5, X = getint(T), m = 2e5;
        printf("%d %d\n",n,10);
        for(int i = 1;i <= n;i++)printf("%d ",getint(i));puts("");
        for(int i = 1;i <= n;i++)printf("%d ",getint(i));puts("");
        printf("%d\n",m);int opt = 0, u = 0, v = 0;
        for(int i = 1;i <= m;i++){
            opt = getint(opt) & 1, u = getint(u) % n + 1;
            if(!opt){v = getint(v);}
            else {v = getint(v) % n + 1;if(v < u)swap(u,v);}
            printf("%d %d %d\n",opt + 1,u,v);
        }
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