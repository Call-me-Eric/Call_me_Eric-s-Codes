#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10;
int n, H, W;
int x[maxn], y[maxn], l[maxn];

struct scanline{
    int l, r, h, val;
    scanline(int l = 0,int r = 0,int h = 0,int va = 0):l(l),r(r),h(h),val(va){}
}a[maxn << 1];
int X[maxn << 1], tot;
struct cmp{bool operator()(scanline a,scanline b){if(a.h != b.h)return a.h < b.h;return a.val > b.val;}};

class Segment_Tree{
    private:
    struct node{
        int maxx, tag;
        node(int maxx = 0,int tag = 0):maxx(maxx),tag(tag){}
    }d[maxn << 3];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].maxx += d[p].tag;
            d[p << 1 | 1].maxx += d[p].tag;
            d[p << 1].tag += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;
            d[p].tag = 0;
        }
    }
    void update(int l,int r,int s,int t,int p,int val){
        // printf("%d %d\n",l,r);
        if(s <= l && r <= t){d[p] = node(val + d[p].maxx,val + d[p].tag);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,val);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,val);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node();return;}
        int mid = l + r >> 1;
        build(l,mid, p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    public:
    void build(int n){build(1,n,1);}
    void update(int l,int r,int val){update(1,tot,l,r,1,val);}
    int query(){return d[1].maxx;}
}tree;

signed main(){
int T = read();
while(T--){
    n = read(); W =read(); H = read();
    for(int i = 1;i <= n;i++){
        x[i] =read(); y[i] =read(); l[i] =read();
        X[(i << 1) - 1] = x[i];X[i << 1] = x[i] + W - 1;
        a[(i << 1) - 1] = scanline(x[i],x[i] + W - 1,y[i],l[i]);
        a[i << 1] = scanline(x[i],x[i] + W - 1,y[i] + H - 1,-l[i]);
    }
    sort(a + 1,a + 1 + n * 2,cmp());
    sort(X + 1,X + 1 + n * 2);
    tot = unique(X + 1,X + 1 + n * 2) - (X + 1);
    // tree.build(tot);
    // puts("11132142314");
    int ans = 0;
    for(int i = 1;i <= n * 2;i++){
        a[i].l = upper_bound(X + 1,X + 1 + tot,a[i].l) - X;
        a[i].r = upper_bound(X + 1,X + 1 + tot,a[i].r) - X;
        tree.update(a[i].l,a[i].r,a[i].val);
        ans = max(ans,tree.query());
    }
    printf("%lld\n",ans);
}
    return 0;
}