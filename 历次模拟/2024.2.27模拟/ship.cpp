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
const int maxn = 3e5 + 10;
int n, m, k;
vector<pair<int,int> > edg[maxn];
void main(){
    n = read(); m = read(); k = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        edg[u].push_back(make_pair(v, w));
    }
    if(k == 1){puts("0");return;}
    return;
}
};
bool edmemory;
signed main(){
    freopen("ship.in","r",stdin);
    freopen("ship.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}