#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, a[maxn];
vector<int> vec;
struct BIT{
    int c[maxn];void init(){memset(c,0,sizeof(c));}
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
}tr;
int L[maxn], id[maxn];
ll ans[maxn];
vector<int> del[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)vec.push_back(a[i] = read());
    sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(int i = 1;i <= n;i++)a[i] = lower_bound(vec.begin(),vec.end(),a[i]) - vec.begin() + 1;
    memset(ans,0x3f,sizeof(ans));
auto solve = [](){
    tr.init();for(int i = 1;i <= n;i++){L[i] = tr.qry(a[i] - 1);tr.upd(a[i],1);id[a[i]] = i;}
    tr.init();for(int i = 1;i <= n;i++)del[i].clear();
    for(int i = 1;i <= n;i++){
        int p = id[i], c = p;
        for(int j = 20;j + 1;j--){
            int x = c + (1 << j);
            if(x <= n && tr.qry(x) - L[p] <= L[p])c = x;
        }
        del[c + 1].push_back(i);tr.upd(p,1);
    }
    tr.init();ll res = 0;
    for(int i = 1;i <= n;i++){
        for(int j : del[i])tr.upd(j,-1);
        res += tr.qry(n) - tr.qry(a[i]);
        ans[i] = min(ans[i],res);tr.upd(a[i],1);
    }
    return;
};
    solve();for(int i = 1;i <= n;i++)a[i] = n - a[i] + 1;solve();
    for(int i = 1;i <= n;i++)printf("%lld\n",ans[i]);
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
9
11 4 5 14 1 9 19 8 10
*/