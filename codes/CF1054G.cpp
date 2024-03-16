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
const int maxn = 2e3 + 10, maxm = maxn * maxn;
bitset<maxn> a[maxn];
int n, m;
char ch[maxn];

struct edge{
    int u, v, w;
    edge(int u = 0,int v = 0,int w = 0):u(u),v(v),w(w){}
    friend bool operator < (edge a,edge b){return a.w < b.w;}
}edg[maxm], ans[maxn];
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void solve(){
    n = read();m = read();
    for(int i = 1;i <= m;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= n;j++)a[j][i] = ch[j] - '0';
    }
    for(int i = 1;i <= n;i++)fa[i] = i;
    int cnt = 0, tot = 0;
    for(int i = 1;i <= n;i++)for(int j = i + 1;j <= n;j++)
        edg[++cnt] = edge(i,j,(a[i] & a[j]).count());
    sort(edg + 1,edg + 1 + cnt);
    for(int i = 1;i <= cnt;i++){
        int fu = getf(edg[i].u), fv = getf(edg[i].v);
        if(fu != fv){fa[fu] = fv;ans[++tot] = edg[i];}
    }
    for(int i = 1;i <= m;i++){
        tot = cnt = 0;
        for(int j = 1;j <= n;j++)cnt += a[j][i];
        for(int j = 1;j < n;j++)tot += (a[edg[j].u][i] && a[edg[j].v][i]);
        if(tot + 1 != cnt){puts("No");return;}
    }
    puts("Yes");
    for(int i = 1;i < n;i++)printf("%d %d\n",ans[i].u,ans[i].v);
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