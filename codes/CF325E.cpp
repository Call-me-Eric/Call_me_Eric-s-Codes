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
int n;
int fa[maxn], to[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void main(){
    n = read();if(n & 1){puts("-1");return;}
    for(int i = 0;i < n;i++)fa[i] = i;
    for(int i = 0;i < (n >> 1);i++){
        fa[getf(i)] = getf(to[i] = (i << 1));
        fa[getf(i + (n >> 1))] = getf(to[i + (n >> 1)] = (i << 1 | 1));
    }
    for(int i = 0;i < (n >> 1);i++){
        if(getf(i) != getf(i + (n >> 1))){
            swap(to[i],to[i + (n >> 1)]);
            fa[getf(i)] = getf(i + (n >> 1));
        }
    }
    // for(int i = 0;i < n;i++)printf("to[%d] = %d\n",i,to[i]);
    int x = 0, flg = true;
    while(x != 0 || flg){printf("%d ",x);x = to[x];flg = false;}
    puts("0");
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