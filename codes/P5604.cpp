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
const int maxn = 5e5 + 10;
int n, m;
set<int> st[maxn];
int p[maxn], a[maxn], rp[maxn];
int res[maxn], lst[maxn];
struct Segment_Tree{
    struct node{
        int maxx;
        node(int maxx = 0):maxx(maxx){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(res[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd);res[pos] = upd;return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int pos,int upd){update(1,n,pos,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
int getans(int x){
    auto it = st[a[x]].lower_bound(x);
    int pre = 0, pos = 0;
    if(it != st[a[x]].begin())pre = *(--it);
    it = st[p[a[x]]].lower_bound(x);
    if(it != st[p[a[x]]].begin())pos = max(pos,*(--it));
    it = st[rp[a[x]]].lower_bound(x);
    if(it != st[rp[a[x]]].begin())pos = max(pos,*(--it));
    return (pos > pre) ? pos : 0;
}
void erase(int x){
    st[a[x]].erase(x);
    auto it = st[a[x]].lower_bound(x);
    if(it != st[a[x]].end())tree.update(*it,getans(*it));
    it = st[p[a[x]]].lower_bound(x);
    if(it != st[p[a[x]]].end())tree.update(*it,getans(*it));
    it = st[rp[a[x]]].lower_bound(x);
    if(it != st[rp[a[x]]].end())tree.update(*it,getans(*it));
}
void add(int x,int upd){
    a[x] = upd;st[a[x]].insert(x);tree.update(x,getans(x));
    auto it = st[a[x]].lower_bound(x);it++;
    if(it != st[a[x]].end())tree.update(*it,getans(*it));
    it = st[p[a[x]]].lower_bound(x);
    if(it != st[p[a[x]]].end())tree.update(*it,getans(*it));
    it = st[rp[a[x]]].lower_bound(x);
    if(it != st[rp[a[x]]].end())tree.update(*it,getans(*it));
}
void main(){
    n = read(), m = read();
    for(int i = 1;i <= n;i++){p[i] = read();rp[p[i]] = i;}
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++){
        st[a[i]].insert(i);
        int pos = max(lst[p[a[i]]],lst[rp[a[i]]]);
        if(pos > lst[a[i]]){res[i] = pos;tree.update(i,res[i]);}
        lst[a[i]] = i;
    }
    tree.build(1,n,1);int opt, u, v;
    while(m--){
        opt = read(), u = read(), v = read();
        if(opt == 2){puts(tree.query(u,v).maxx >= u ? "Yes" : "No");}
        else{erase(u);add(u,v);}
    }
    return;
}
};
bool edmemory;
signed main(){
    // freopen("tmp.in","r",stdin);
    // freopen("tmp.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}