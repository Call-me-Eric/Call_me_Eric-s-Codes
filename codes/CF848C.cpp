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
const int maxn = 1e5 + 10;
int n, m;
struct node{
    int x, y;int typ, tim, id;int val, ans, f;
    node(int x = 0,int y = 0,int typ = 0,int tim = 0,int id = 0,int val = 0,int ans = 0,int f = 0
    ):x(x),y(y),typ(typ),tim(tim),id(id),val(val),ans(ans),f(f){}
    friend bool operator < (node a,node b){
        return a.x == b.x ? (a.y == b.y ? (a.tim == b.tim ? a.typ < b.typ : a.tim < b.tim) : a.y < b.y) : a.x < b.x;
    }
};
vector<node> d;
int pre[maxn], suf[maxn];
set<int> st[maxn];int col[maxn];
int tim;
int ans[maxn];
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    void upd(int x,int add){for(;x <= tim;x += lowbit(x))c[x] += add;}
}tr;
bool cmp(node l,node r){return l.y == r.y ? (l.tim == r.tim ? l.typ < r.typ : l.tim < r.tim) : l.y < r.y;}
vector<node> tmp;
vector<pair<int,int> > trash;
void cdq(int l,int r){
    if(l == r)return;int mid = l + r >> 1;
    cdq(l,mid);cdq(mid + 1,r);
    int lp = l, rp = mid + 1;
    while(lp <= mid || rp <= r){
        if(rp > r || (lp <= mid && cmp(d[lp],d[rp]))){
            if(d[lp].typ == 1){
                tr.upd(d[lp].tim,d[lp].val);
                trash.push_back(make_pair(d[lp].tim,d[lp].val));
            }
            tmp.push_back(d[lp++]);
        }
        else{
            if(d[rp].typ == 2)d[rp].ans += tr.qry(d[rp].tim);
            tmp.push_back(d[rp++]);
        }
    }
    for(int i = 0;i < tmp.size();i++)d[i + l] = tmp[i];
    for(auto i : trash){tr.upd(i.first,-i.second);}
    tmp.clear();trash.clear();
}
void main(){
    n = read();m = read();tim = 1;
    for(int i = 1;i <= n;i++){st[i].insert(0);st[i].insert(n + 1);}
    for(int i = 1;i <= n;i++){col[i] = read();st[col[i]].insert(i);}
    for(int i = 1;i <= n;i++){
        auto it = st[i].begin(); int lst = *it;
        for(it++;it != st[i].end();it++){pre[*it] = lst;suf[lst] = *it;lst = *it;}
    }
    for(int i = 1;i <= n;i++)d.push_back(node(pre[i],i,1,tim,0,i - pre[i],0,0));
    for(int i = 1;i <= m;i++){
        int opt = read(), x = read(), y = read();
        if(opt == 1){
            tim++;
            int u = pre[x], v = suf[x];
            d.push_back(node(u,x,1,tim,0,u - x));
            d.push_back(node(x,v,1,tim,0,x - v));
            d.push_back(node(u,v,1,tim,0,v - u));

            st[col[x]].erase(x);
            suf[u] = v;pre[v] = u;
            col[x] = y;st[y].insert(x);
            auto it = st[y].find(x);
            it--;pre[x] = *it;it++;it++;suf[x] = *it;
            
            int a = pre[x], b = suf[x];
            suf[a] = x;pre[b] = x;
            d.push_back(node(x,b,1,tim,0,b - x));
            d.push_back(node(a,x,1,tim,0,x - a));
            d.push_back(node(a,b,1,tim,0,a - b));
            ans[i] = -0x3f3f3f3f;
        }
        else{
            d.push_back(node(y,y,2,tim,i,0,0,1));
            d.push_back(node(x - 1,y,2,tim,i,0,0,-1));
            d.push_back(node(y,x - 1,2,tim,i,0,0,-1));
            d.push_back(node(x - 1,x - 1,2,tim,i,0,0,1));
        }
    }
    sort(d.begin(),d.end());  cdq(0,d.size() - 1);
    for(node i : d){ans[i.id] += i.ans * i.f;}
    for(int i = 1;i <= m;i++)if(ans[i] >= 0)printf("%lld\n",ans[i]);
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