#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, f[maxn];
struct Segment_Tree{
    struct node{
        int minn, tag;
        node(int minn = 0,int tag = 0):minn(minn),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(min(l.minn,r.minn));}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag += d[p].tag;
            d[p << 1].minn += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;
            d[p << 1 | 1].minn += d[p].tag;
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(f[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].minn += upd;d[p].tag += upd;return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(){build(1,n,1);}
    void update(int l,int r,int upd){if(r < l)return;update(1,n,l,r,1,upd);}
    int query(int l,int r){if(r < l)return 0x3f3f3f3f;return query(1,n,l,r,1).minn;}
}tree;
int k, D[maxn], C[maxn],S[maxn],W[maxn];
int L[maxn], R[maxn];
vector<pair<int,int> > vec[maxn];
signed main(){
    n = read(); k = read();
    for(int i = 2;i <= n;i++)D[i] = read();
    for(int i = 1;i <= n;i++)C[i] = read();
    for(int i = 1;i <= n;i++)S[i] = read();
    for(int i = 1;i <= n;i++)W[i] = read();
    D[++n] = 0x3f3f3f3f;W[n] = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){
        L[i] = lower_bound(D + 1,D + 1 + n,D[i] - S[i]) - D;
        R[i] = lower_bound(D + 1,D + 1 + n,D[i] + S[i]) - D;
        if(D[R[i]] > D[i] + S[i])R[i]--;
        vec[R[i]].push_back(make_pair(L[i],W[i]));
    }
    int ans = 0,res = 0;
    for(int i = 1;i <= n;i++){
        f[i] = res + C[i];
        for(auto x : vec[i]){res += x.second;}
    }
    ans = f[n];
    for(int j = 1;j <= k;j++){
        tree.build();
        for(int i = 1;i <= n;i++){
            f[i] = tree.query(1,i - 1) + C[i];
            for(auto x : vec[i]){tree.update(1,x.first - 1,x.second);}
        }
        ans = min(ans,f[n]);
    }
    printf("%d\n",ans);
    return 0;
}