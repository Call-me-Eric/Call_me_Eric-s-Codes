#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 35100;
int n, k;
int a[maxn];
int col[maxn], pre[maxn];
class Segment_Tree{
    private:
    struct node{
        int maxx, tag;
        node(int mx = 0,int tg = 0):maxx(mx),tag(tg){}
    }d[maxn << 2];
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].maxx += d[p].tag;
            d[p << 1].tag += d[p].tag;
            d[p << 1 | 1].maxx += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;
            d[p].tag = 0;
        }
    }
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].maxx += upd;d[p].tag += upd;return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t, p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    public:
    void update(int upd,int s,int t){update(0,n,s,t,1,upd);}
    int query(int s,int t){return query(0,n,s,t,1).maxx;}
}tree[51];
signed main(){
    n = read(); k = read();
    for(int i = 1;i <= n;i++){
        a[i] = read(); pre[i] = col[a[i]]; col[a[i]] = i;
        for(int j = 0;j <= k;j++){tree[j].update(1,pre[i],i - 1);}
        for(int j = 1;j <= k;j++){tree[j].update(tree[j - 1].query(0,i),i,i);}
    }
    printf("%d\n",tree[k].query(n,n));
    return 0;
}