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
int n, m, k;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
bool merge(int x,int y){
    int fx = getf(x), fy = getf(y);
    if(fx == fy)return false;
    fa[fx] = fy;return true;
}
void solve(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= (n + m) * 2;i++)fa[i] = i;
    for(int i = 1;i <= k;i++){
        int x = read(), y = read(), u = read(), v = read();
        if(y == v - 1){merge(x,(y + n) + (n + m));merge(x + (n + m),(y + n));}
        else{y--;merge(x,(y + n));merge(x + (n + m),(y + n) + (n + m));}
    }
    for(int i = 1;i <= n + m;i++){if(getf(i) == getf(i + (n + m))){puts("No");return;}}
    puts("Yes");
    return;
}
void main(){int T = read();while(T--)solve();return;}
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