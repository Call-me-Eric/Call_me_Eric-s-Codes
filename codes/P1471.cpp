#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
double a[maxn];
struct Segment_Tree{
    struct node{
        double sum, square;double tag;int l, r;
        node(double s = 0.0,double sq = 0.0,int l = 0,int r = 0,double tag = 0.0):sum(s),square(sq),l(l),r(r),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum,l.square + r.square,l.l,r.r);}
    void change(int p,double tag){
        d[p].square += tag * d[p].sum * 2.0 + (d[p].r - d[p].l + 1.0) * tag * tag;
        d[p].sum += tag * (d[p].r - d[p].l + 1.0);
    }
    void pushdown(int p){
        if(d[p].tag){
            change(p << 1,d[p].tag);d[p << 1].tag += d[p].tag;
            change(p << 1 | 1,d[p].tag);d[p << 1 | 1].tag += d[p].tag;
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],a[l] * a[l],l,l);return;}
        int mid = l + r >> 1;build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,double add){
        if(s <= l && r <= t){change(p,add);d[p].tag += add;return;}
        int mid = l + r >> 1; pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,add);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,add);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(){build(1,n,1);}
    void update(int l,int r,double add){update(1,n,l,r,1,add);}
    node query(int l,int r){return query(1,n,l,r,1);}
    double sum(int l,int r){return query(1,n,l,r,1).sum / (r - l + 1.0);}
    double ave(int l,int r){
        node tmp = query(1,n,l,r,1);
        return (tmp.square - (tmp.sum * tmp.sum / (r - l + 1.0))) / (r - l + 1.0);
    }
}tree;
signed main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)scanf("%lf",&a[i]);
    tree.build();int u, v, opt;double w;
    // for(int i = 1;i <= n;i++){printf("DEBUG:%.4lf %.4lf\n",tree.query(i,i).sum,tree.query(i,i).square);}
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&opt,&u,&v);
        if(opt == 1){scanf("%lf",&w);tree.update(u,v,w);}
        if(opt == 2){printf("%.4lf\n",tree.sum(u, v));}
        if(opt == 3){printf("%.4lf\n",tree.ave(u, v));}
    }
    return 0;
}