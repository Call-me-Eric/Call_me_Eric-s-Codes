#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int a[maxn];
class Segment_Tree{
    private:
    struct node{int sum;int lztag, l, r;node(int l = 0,int r = 0,int s = 0,int lz = -1):sum(s),lztag(lz),l(l),r(r){}}d[maxn << 2];
    node mergenode(node l,node r){return node(l.l,r.r,l.sum + r.sum);}
    void build(int l,int r,int p,int val){
        if(l == r){d[p] = node(l,r,a[l] >= val);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1,val);build(mid + 1,r,p << 1 | 1,val);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void pushdown(int p){
        if(d[p].lztag != -1){
            d[p << 1].lztag = d[p << 1 | 1].lztag = d[p].lztag;
            d[p << 1    ].sum = d[p].lztag * (d[p << 1    ].r - d[p << 1    ].l + 1);
            d[p << 1 | 1].sum = d[p].lztag * (d[p << 1 | 1].r - d[p << 1 | 1].l + 1);
            d[p].lztag = -1;
        }
    }
    node query(int l,int r,int s,int t,int p){
        // printf("%d %d %d %d %d %d\n",l,r,s,t,p,d[p].sum);
        if(s <= l && r <= t){return d[p];}
        if(r < s || t < l)return node();
        int mid = l + r >> 1; pushdown(p);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int s,int t,int p,int val){
        if(s <= l && r <= t){d[p] = node(l,r,val * (r - l + 1),val);return;}
        if(r < s || t < l)return;
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,val);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,val);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    public:
    void update(int l,int r,bool opt){
        int sum = query(1,n,l,r,1).sum;
        // printf("%d %d %d\n",l,r,sum);
        // debug();
        if(opt){update(1,n,l,l + sum - 1,1,1);update(1,n,l + sum,r,1,0);}
        else {update(1,n,r - sum + 1,r,1,1);update(1,n,l,r - sum,1,0);}
    }
    void build(int n,int mid){
        memset(d,0,sizeof(d));
        build(1,n,1,mid);
    }
    int query(int l,int r){return query(1,n,l,r,1).sum;}
    int query(int x){return query(1,n,x,x,1).sum;}
    void debug(){
        for(int i = 1;i <= n;i++)printf("%d %d\n",i,query(i,i + 1));puts("");
    }
}tree;

int opt[maxn], L[maxn], R[maxn], p;
bool check(int mid){
    tree.build(n,mid);
    for(int i = 1;i <= m;i++){
        tree.update(L[i],R[i],opt[i]);
        // tree.debug();
    }
    return tree.query(p,p);
}

signed main(){
    
    n = read(); m = read();
    for(int i = 1;i <= n;i++){a[i] = read();}
    for(int i = 1;i <= m;i++){opt[i] = read(); L[i] = read(); R[i] = read();}
    p = read();
    
    int l = 1, r = n, mid = 0, ans = 0;
    while(l <= r){
        mid = l + r >> 1;
        if(check(mid)){ans = mid;l = mid + 1;}
        else r = mid - 1;
    }
    
    printf("%d\n",ans);
    return 0;
}