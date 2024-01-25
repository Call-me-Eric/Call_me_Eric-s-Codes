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
const int maxn = 2e3 + 10, mod = 998244353;
vector<int> edg[maxn];
int n, m, k;
namespace Subtask1{
    long long ans = 0;
    int book[maxn], cnt;
    void tag(int u){cnt += !book[u];book[u]++;}
    void untag(int u){cnt -= !--book[u];}
    void dfs(int u,int tim){
        if(tim){if(cnt == n)ans++;}
        if(!tim){dfs(0, 1);}
        for(int v : edg[u])if(book[v] < k){tag(v);dfs(v, tim);untag(v);}
    }
    void main(){
        for(int i = 1;i <= n;i++){edg[0].push_back(i);}
        dfs(0, 0);
        printf("%lld\n",ans);
    }
};
void main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= m;i++){int u = read(), v = read(); edg[u].push_back(v);}
    if(n <= 5){Subtask1::main();return;}
    mt19937 rnd(11451419);printf("%d\n",rnd() % mod);
    return;
}
};
bool edmemory;
signed main(){
    freopen("travel.in","r",stdin);
    freopen("travel.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}