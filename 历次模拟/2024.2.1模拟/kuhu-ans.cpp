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
const int maxn = 3e5 + 10;
int n, m, num;
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int upd){for(;x <= n;x += lowbit(x))c[x] += upd;}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    int qry(int l,int r){return qry(r) - qry(l - 1);}
}tr;
vector<int> edg[maxn];
int f[maxn][2], fa[maxn];
int cur, sum;
void upd(int u,int upd){
    tr.upd(u,upd);
    cur += u * upd;
    if(fa[u]){
        tr.upd(fa[u],-upd);
        cur -= fa[u] * upd;
    }
}
void dfs(int u){
    if(!u)return;
    upd(u,-f[u][1]); int f0 = 0, f1 = 1;
    for(int v : edg[u]){
        f0 += f[v][1];
        f1 += f[v][0];
    }
    f[u][0] = f0; f[u][1] = max(f1,f0);
    upd(u,f[u][1]);dfs(fa[u]);
}
vector<pair<int,int> > qry[maxn];int ans[maxn];
void main(){
    n = read(); m = read();num = read();
    for(int i = 1;i <= n;i++)
        for(int j = 0;(1 << j) - i <= n;j++){
            int v = (1 << j) - i;
            if(v < i && v > 0){edg[v].push_back(i);fa[i] = v;}
        }
    // for(int i = 1;i <= n;i++){
    //     for(int v : edg[i]){
    //         printf("%lld -> %lld\n",i,v);
    //     }
    // }
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        qry[v].push_back(make_pair(u, i));
    }
    for(int r = 1;r <= n;r++){
        dfs(r); for(auto i : qry[r]){ans[i.second] = tr.qry(i.first,r);}
        sum += cur;
    }
    for(int i = 1;i <= m;i++)printf("%lld\n",ans[i]);printf("%lld\n",num * sum);
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
/*
20 3 1
1 20
10 20
1 10
*/