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
int a[maxn];
namespace Subtask1{
void solve(){
    int opt, u, v, w;
    for(int test = 1;test <= m;test++){
        opt = read(); u = read();
        if(opt == 1){
            v = read(); w = read();
            if(u > v)swap(u, v);
            for(int i = u;i <= v;i++){
                if(a[i] != -1)a[i] += w;
            }
        }
        if(opt == 2){
            v = read();int ans = 0;
            if(u > v)swap(u, v);
            for(int i = u;i <= v;i++)ans += max(0ll,a[i]);
            printf("%lld\n",ans);
        }
        if(opt == 3){
            a[u] = -1;
        }
        if(opt == 4){
            v = read();if(u > v)swap(u, v);
            for(int i = u;i <= v;i++)a[i] = max(a[i],0ll);
        }
        for(int i = 2;i <= n;i++){if(a[i] == -1)a[i - 1] = -1;}
        for(int i = n - 1;i;i--){if(a[i] == -1)a[i + 1] = -1;}
    }
}
};
namespace Subtask2{
struct Segment_Tree{
    struct node{
        int sum,ill , l, r;
        int addtag;
        node(int sum = 0,int ill = 0,int l = 0,int r = 0,int addtag = 0
        ):sum(sum),ill(ill),l(l),r(r),addtag(addtag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum,l.ill + r.ill,l.l,r.r);}
    void gettag(int p,int add){
        d[p].sum += (d[p].r - d[p].l + 1 - d[p].ill) * add;
        d[p].addtag += add;
    }
    void pushdown(int p){
        if(d[p].addtag){
            gettag(p << 1,d[p].addtag);
            gettag(p << 1 | 1,d[p].addtag);
            d[p].addtag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],0,l,r);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int add){
        if(s <= l && r <= t){gettag(p,add);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,add);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,add);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void getill(int l,int r,int p,int pos){
        if(l == r && l == pos){d[p].sum = 0;d[p].ill = 1;return;}
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)getill(l,mid,p << 1,pos);
        else getill(mid + 1,r,p << 1 | 1,pos);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    int query(int l,int r){return query(1,n,l,r,1).sum;}
    void getill(int pos){getill(1,n,1,pos);}
}tr;
bool ill[maxn];
queue<int> que;
void solve(){
    tr.build(1,n,1);
    int opt, u, v, w;ill[0] = ill[n + 1] = 1;
    for(int test = 1;test <= m;test++){
        opt = read(); u = read();
        if(opt == 1){
            v = read();if(u > v)swap(u, v);
            w = read();tr.update(u,v,w);
        }
        if(opt == 2){
            v = read();if(u > v)swap(u, v);
            printf("%lld\n",tr.query(u,v));
        }
        if(opt == 3){
            if(!ill[u]){tr.getill(u);ill[u] = 1;}
            que.push(u - 1);que.push(u + 1);
        }
        queue<int> tmp;
        while(!que.empty()){
            int u = que.front();que.pop();
            if(u < 1 || u > n || ill[u])continue;
            tr.getill(u);ill[u] = 1;
            if(!ill[u - 1])tmp.push(u - 1);
            if(!ill[u + 1])tmp.push(u + 1);
        }
        que = tmp;
    }
}
};
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    if(n >= 1e5 && m >= 1e5)Subtask2::solve();
    else Subtask1::solve();
    return;
}
};
bool edmemory;
signed main(){
    freopen("witch.in","r",stdin);
    freopen("witch.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
6 6
1 2 3 4 5 6
3 4
2 1 3
4 2 5
1 2 6 3
2 1 5
2 1 6
*/