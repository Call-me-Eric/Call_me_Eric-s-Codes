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
const int maxn = 2e5 + 10, range = 1e9;
int n, m;
map<int,int> mp;
void main(){
    n = 5e3;m = 5e3;srand(time(0));mt19937 rnd(rand());
    printf("%d %d\n",n,m);int x = 0;
    auto getval = [&](){
        x = (x + rnd()) % range + 1;
        while(mp[x])x = (x + rnd() + 1 + rand()) % range + 1;
        mp[x] = 1;return x;
    };
    for(int i = 1;i <= n;i++){printf("%d ",getval());}
    puts("");
    for(int i = 2;i <= n;i++){
        // int u = rnd() % (i - 1) + 1, v = i;
        int u = 1, v = i;
        printf("%d %d\n",u,v);
    }
    for(int i = 1;i <= m;i++){
        int opt = rnd() % 2 + 1;
        if(opt == 1){
            int u = rnd() % n + 1, v = getval();
            printf("%d %d %d\n",opt,u,v);
        }
        else{
            int u = rnd() % range + 1;
            printf("%d %d\n",opt,u);
        }
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("fall.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    // cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    // cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}