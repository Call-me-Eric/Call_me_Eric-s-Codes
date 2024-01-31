#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, q;
vector<int> vec[maxn];
struct Segment_Tree{
    struct node{
        int maxx, summ,tag;
        int l, r;
        node(int maxx = 0,int summ = 0,int l = 0,int r = 0,int tag = 0):maxx(maxx),summ(summ),tag(tag),l(l),r(r){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx),l.summ + r.summ,l.l,r.r);}

    void gettag(int p,int add){
        d[p].tag += add;
        d[p].summ += add * (d[p].r - d[p].l + 1);
        d[p].maxx += add;
    }
    void pushdown(int p){
        if(d[p].tag){
            gettag(p << 1,d[p].tag);gettag(p << 1 | 1,d[p].tag);
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0,0,l,l);return;}
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
    void update(int s,int t,int add){update(0,n,s,t,1,add);}
    node query(int s,int t){return query(0,n,s,t,1);}
}tree1,tree2;
vector<pair<int,int> > qry[maxn];
int ans[maxn], sum[maxn];
signed main(){
    n = read();q = read();int x, y;
    for(int i = 1;i <= n;i++){vec[read()].push_back(i);}
    for(int i = 1;i <= n;i++){sum[i] = sum[i - 1] + !vec[i].empty();}
    for(int i = 1;i <= q;i++){x = read(); y = read();qry[y].push_back(make_pair(x,i));}
    tree1.build(0,n,1);tree2.build(0,n,1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j < vec[i].size();j++){
            x = vec[i][j - 1];y = vec[i][j];
            tree2.update(0,tree1.query(x,y).maxx,1);
        }
        for(int j : vec[i])tree1.update(j,j,i);
        for(auto j : qry[i])
            ans[j.second] = sum[i] - sum[j.first - 1] + tree2.query(j.first,j.first).summ;
    }
    for(int i = 1;i <= q;i++)printf("%d\n",ans[i]);
    return 0;
}