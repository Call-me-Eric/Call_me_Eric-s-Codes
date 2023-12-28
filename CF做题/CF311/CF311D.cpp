#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 95542721;
int n, m, a[maxn];

struct Segment_Tree{
    struct node{
        int sum[48], tag;
        node(){memset(sum,0,sizeof(sum));tag = 0;}
        node(int a){for(int i = 0;i < 48;i++){sum[i] = a % mod;a = a * a % mod * a % mod;}tag = 0;}
        node(int a[],int b[],int l,int r){
            for(int i = 0;i < 48;i++){sum[i] = (a[(i + l) % 48] + b[(i + r) % 48]) % mod;}tag = 0;}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum,r.sum,l.tag,r.tag);}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag = (d[p << 1].tag + d[p].tag) % 48;
            d[p << 1 | 1].tag = (d[p << 1 | 1].tag + d[p].tag) % 48;
            d[p].tag = 0;
        }
    }
    void build(int l = 1,int r = n,int p = 1){
        if(l == r){d[p] = node(a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){d[p].tag = (d[p].tag + 1) % 48;return;}
        pushdown(p); int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    // node query(int l,int r,int s,int t,int p){
    //     if(s <= l && r <= t)return d[p];
    //     pushdown(p); int mid = l + r >> 1;
    //     if(t <= mid)return query(l,mid,s,t,p << 1);
    //     if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
    //     return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    // }
    // int query(int l,int r){node tmp =  query(1,n,l,r,1);return tmp.sum[tmp.tag] % mod;}
    int query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p].sum[d[p].tag % 48] % mod;
        pushdown(p); int mid = l + r >> 1;d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return (query(l,mid,s,t,p << 1) + query(mid + 1,r,s,t,p << 1 | 1)) % mod;
    }
    int query(int l,int r){return query(1,n,l,r,1) % mod;}
    void update(int l,int r){update(1,n,l,r,1);}
}tree;

signed main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read() % mod;
    int opt, l, r; m = read();tree.build();
    for(int j = 1;j <= m;j++){
        opt = read(); l = read(); r = read();
        if(opt == 1){printf("%lld\n",tree.query(l,r));}
        else tree.update(l,r);
        // for(int i = 1;i <= n;i++){printf("a[%lld] = %lld\n",i,tree.query(i,i));}
    }
    return 0;
}