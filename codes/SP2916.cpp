#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int a[maxn];
struct node{
    int sum, lmax, rmax, maxx;
    node(int sum = 0,int lmax =  0,int rmax = 0,int maxx = 0):sum(sum),lmax(lmax),rmax(rmax),maxx(maxx){}
};
struct Segment_Tree{
    node d[maxn << 2];
    node mergenode(node l,node r){
        return node(l.sum + r.sum,max(l.lmax,l.sum + r.lmax),
            max(r.rmax,r.sum + l.rmax),max(max(l.maxx, r.maxx),l.rmax + r.lmax));
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],a[l],a[l],a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t, p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    node query(int l,int r){if(l > r)return node(0,0,0,0);return query(1,n,l,r,1);}
}tree;
signed main(){
int T = read();
while(T--){
    n = read(); for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(1,n,1); m = read();int l1, r1, l2, r2, ans;
    for(int i = 1;i <= m;i++){
        l1 = read(); r1 = read(); l2 =  read(); r2 = read();
        
        if(r1 < l2){ans = tree.query(l1,r1).rmax + tree.query(r1 + 1,l2 - 1).sum + tree.query(l2,r2).lmax;}
        else{
            ans = tree.query(l2,r1).maxx;
            if(l1 < l2)ans = max(ans,tree.query(l1,l2).rmax + tree.query(l2,r2).lmax - a[l2]);
            if(r1 < r2)ans = max(ans,tree.query(l1,r1).rmax + tree.query(r1,r2).lmax - a[r1]);
        }
        printf("%d\n",ans);
    }
}
    return 0;
}