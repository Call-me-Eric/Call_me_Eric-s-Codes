#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int a[maxn];
class Segment_Tree{
    private:
    struct node{
        int sum;bool upd;
        node(int s = 0,bool u = false):sum(s),upd(u){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum, l.upd && r.upd);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],a[l] == 0 || a[l] == 1);return;}
        int mid = (l + r) >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p){
        if(d[p].upd)return;
        if(l == r){d[p].sum = floor(sqrt(d[p].sum));d[p].upd = d[p].sum == 1 || d[p].sum == 0;return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        else if(t <= mid) return query(l,mid,s,t,p << 1);
        else return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    public:
    void build(int n){build(1,n,1);}
    void update(int l,int r){update(1,n,l,r,1);}
    int query(int l,int r){return query(1,n,l,r,1).sum;}
}tree;
signed main(){
    n = read(); int opt, l, r;
    for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(n);
    m = read();
    for(int i = 1;i <= m;i++){
        opt = read(); l = read(); r = read();
        if(l > r)swap(l,r);
        if(!opt){tree.update(l,r);}
        else printf("%lld\n",tree.query(l,r));
    }
    return 0;
}