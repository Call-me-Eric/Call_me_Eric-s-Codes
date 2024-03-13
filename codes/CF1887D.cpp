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
int n, q;int a[maxn];
stack<int> stk;
int pre[maxn], suf[maxn], suf1[maxn];
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    void upd(int x,int upd){for(;x <= n;x += lowbit(x))c[x] += upd;}
}tr;
vector<pair<pair<int,int>,int> > vec[maxn];
vector<pair<int,int> > qry[maxn];
int ans[maxn];
pair<int,int> st[21][maxn];
void main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read(),st[0][i] = make_pair(a[i],a[i]);
    for(int i = 1;i <= 20;i++)
        for(int j = 0;j <= n + 1;j++)
            st[i][j] = make_pair(0x3f3f3f3f,-0x3f3f3f3f);
    for(int j = 1;j <= 20;j++)
        for(int i = 1;i + (1 << j) - 1 <= n;i++)
            st[j][i] = make_pair(max(st[j - 1][i].first,st[j - 1][i + (1 << j - 1)].first)
                                ,min(st[j - 1][i].second,st[j - 1][i + (1 << j - 1)].second));
    q = read();
    for(int i = 1;i <= q;i++){
        int l = read(), r = read();
        qry[l].push_back(make_pair(r,i));
    }

    for(int i = 1;i <= n;i++){
        int t = i;
        for(int k = 20;k + 1;k--)
            if(t - (1 << k) + 1 >= 1 && st[k][t - (1 << k) + 1].first <= a[i])
                t -= (1 << k);
        pre[i] = t;
        t = i;
        for(int k = 20;k + 1;k--)
            if(t + (1 << k) - 1 <= n && st[k][t].first <= a[i])
                t += (1 << k);
        suf1[i] = t;
        for(int k = 20;k + 1;k--)
            if(t + (1 << k) - 1 <= n && st[k][t].second >= a[i])
                t += (1 << k);
        suf[i] = t;
    }

    for(int i = 1;i <= n;i++){
        // printf("i = %d pre = %d suf1 = %d suf = %d\n",i,pre[i],suf1[i],suf[i]);
        if(suf1[i] > n)continue;
        auto tmp = make_pair(suf1[i],suf[i] - 1);
        vec[pre[i] + 1].push_back(make_pair(tmp,1));
        vec[i + 1].push_back(make_pair(tmp,-1));
    }
    for(int i = 1;i <= n;i++){
        for(auto j : vec[i]){tr.upd(j.first.first,j.second);tr.upd(j.first.second + 1,-j.second);}
        for(auto j : qry[i]){ans[j.second] = tr.qry(j.first) > 0;}
        // for(int j = 1;j <= n;j++)printf("%d ",tr.qry(j));puts("");
    }
    for(int i = 1;i <= q;i++)puts(ans[i] ? "Yes" : "No");
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