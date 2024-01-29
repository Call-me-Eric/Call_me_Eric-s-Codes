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
int ch[2][maxn],cnt = 1;
int n = 5e4 - 1, q = 5e4;
mt19937 rnd(0x0d000721);
void dfs(int u){
    if(cnt == n)return;
    if((rnd() % 4) >= 3)return;
    ch[0][u] = ++cnt;ch[1][u] = ++cnt;
    int fst = rnd() % 2;
    dfs(ch[fst][u]);dfs(ch[fst ^ 1][u]);
}
void main(){
    freopen("hypnotic.in","w",stdout);
    printf("%d\n",n);dfs(1);
    if(cnt != n){
        int u = 1;
        while(ch[0][u])u = ch[0][u];
        while(cnt != n){
            ch[0][u] = ++cnt;ch[1][u] = ++cnt;
            u = ch[rnd() % 2][u];
        }
    }
    for(int i = 1;i <= n;i++){
        printf("%d %d\n",ch[0][i],ch[1][i]);
    }
    for(int i = 1;i <= n;i++)printf("%d ",rnd() % 21);puts("");
    printf("%d\n",q);
    for(int i = 1;i <= q;i++){
        printf("%d %d\n",rnd() % n + 1,rnd() % 21);
    }
    return;
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