#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3 )+ ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
int a[maxn];

class Segment_Tree{
    private:
    struct node{
        int maxx; int lztag;
        node(int mx = 0,int lz = 0):maxx(mx),lztag(lz){}
    }d[maxn << 2];
    void pushdown(int p){
        if(d[p].lztag){
            d[p << 1].lztag += d[p].lztag;
            d[p << 1].maxx += d[p].lztag;
            d[p << 1 | 1].lztag += d[p].lztag;
            d[p << 1 | 1].maxx += d[p].lztag;
            d[p].lztag = 0;
        }
    }
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node();return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1, r, p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int add){
        if(s <= l && r <= t){d[p] = node(d[p].maxx + add,d[p].lztag + add);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid){update(l,mid,s,t,p << 1,add);}
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,add);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int goal,int p,int add){
        if(l == r && l == goal){d[p] = node(d[p].maxx + add,d[p].lztag + add);return;}
        int mid = l + r >> 1;pushdown(p);
        if(goal <= mid){update(l,mid,goal,p << 1,add);}
        else update(mid + 1,r,goal,p << 1 | 1,add);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1; pushdown(p);node ans = node();
        if(s <= mid)ans = query(l,mid,s,t,p << 1);
        if(mid < t)ans = mergenode(ans,query(mid + 1,r,s,t,p << 1 | 1));
        return ans;
    }
    public:
    void build(){build(0,n,1);}
    void update(int goal,int add){update(0,n,goal,1,add);}
    void update(int l,int r,int add){update(0,n,l,r,1,add);}
    int query(int l,int r){return query(0,n,l,r,1).maxx;}
}tree;

vector<pair<int,int> > vec[maxn];

signed main(){
    n = read(); m = read(); int u, v, p;
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= m;i++){
        u = read(); v= read(); p = read();
        vec[v].push_back(make_pair(u,p));
    }
    int ans = 0;tree.build();
    for(int i = 1;i <= n;i++){
        tree.update(0,i - 1,-a[i]);
        for(auto j : vec[i]){tree.update(0,j.first - 1,j.second);}
        ans = max(ans,tree.query(0,i - 1));
        tree.update(i,ans);
    }
    cout << ans << '\n';
    return 0;
}