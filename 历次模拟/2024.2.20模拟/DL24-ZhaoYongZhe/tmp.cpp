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
namespace room{
    const int maxn = 1e6 + 10;
    int n = 5e3, range = 1e9,rng = 1e2;
    int b[maxn];
    void main(){
        freopen("room.in","w",stdout);
        srand(time(0));
        printf("%lld\n",n);mt19937 rnd(rand());
        int mid = n / 2;
        for(int i = 1;i <= n;i++)printf("%lld ",rnd() % rng + 1);puts("");
        b[0] = b[n + 2] = 0x3f3f3f3f;
        for(int i = 1;i <= n + 1;i++){
            b[i] = rnd() % range + 1;
            if(i <= mid && b[i] > b[i - 1])b[i] = max(0ll,b[i - 1] - 1);
        }
        for(int i = n + 1;i > mid;i--){
            if(b[i] > b[i + 1])b[i] = max(0ll,b[i + 1] - 1);
        }
        for(int i = 1;i <= n + 1;i++)printf("%lld ",(b[i] + rnd()) % range + 1);puts("");
        return;
    }
};
namespace graph{
    const int maxn = 1e4 + 10;
    int n = 1e2, q = 5e4, m = 1e2;
    void main(){
        freopen("graph.in","w",stdout);
        srand(time(0));mt19937 rnd(rand());
        printf("%lld %lld %lld\n",n,m,q);
        for(int i = 1;i <= q;i++){
            int l = rnd() % n + 1,r = rnd() % n + 1, u = rnd() % m + 1,d = rnd() % m + 1;
            if(l > r)swap(l,r);if(u > d)swap(u,d);
            printf("%lld %lld %lld %lld\n",l,u,r,d);
        }
    }
};
void main(){
    room::main();
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    // cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    // cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}