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
namespace puzzle{
    const int maxn = 1e3 + 10;
    int n = 150, m = 20;
    void main(){
        freopen("puzzle.in","w",stdout);
        srand(time(0));
        printf("%d %d\n",n,m);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                int c = 0;
                printf("%d ",c);
            }
            puts("");
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                int w = rand() % 100;
                printf("%d ",w);
            }
            puts("");
        }
        return;
    }
};
namespace witch{
    const int maxn = 5e3 + 10, range = 1e5;
    int n = 5e3, m = 5e3;
    void main(){
        freopen("witch.in","w",stdout);
        srand(time(0));mt19937 rnd(rand());
        printf("%d %d\n",n,m);
        for(int i = 1;i <= n;i++){
            printf("%d ",rnd() % range + 1);
        }
        puts("");
        for(int i = 1;i <= m;i++){
            int opt = rnd() % 4 + 1;
            if(opt == 4)opt = rnd() % 3 + 1;
            printf("%d ",opt);
            if(opt == 1){
                int l = rnd() % n + 1,r = rnd() % n + 1, w = rnd() % range + 1;
                if(l > r)swap(l, r);
                printf("%d %d %d\n",l,r,w);
            }
            if(opt == 2){
                int l = rnd() % n + 1, r = rnd() % n + 1;
                if(l > r)swap(l, r);
                printf("%d %d\n",l,r);
            }
            if(opt == 3){
                int l = rnd() % n + 1;
                printf("%d\n",l);
            }
            if(opt == 4){}
        }
    }
};
void main(){
    puzzle::main();
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