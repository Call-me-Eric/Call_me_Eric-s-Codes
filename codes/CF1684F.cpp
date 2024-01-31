// LUOGU_RID: 137133385
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, a[maxn], m;
int L[maxn], R[maxn];
int lim[maxn];
vector<int> vec[maxn];
struct Segment_Tree{
    struct node{
        int maxx, minn;
        node(int maxx = 0,int minn = 0):maxx(maxx),minn(minn){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx),min(l.minn,r.minn));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(R[l],L[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int x,int y){
        if(l == r && l == pos){d[p] = node(y,x);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,x,y);
        else update(mid + 1,r,pos,p << 1 | 1,x,y);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int pos,int x,int y){update(1,n,pos,1,x,y);}
}tree;
inline bool check(int l,int r){
    Segment_Tree::node tmp = tree.query(1,n,1,n,1);
    return l <= tmp.minn && tmp.maxx <= r;
}

map<int,int> mp;int tot;

signed main(){
int T = read();
while(T--){
    n = read(); m = read();int u, v;mp.clear();tot = 0;
    for(int i = 1;i <= n;i++){
        a[i] = read(); if(!mp[a[i]])mp[a[i]] = ++tot;
        a[i] = mp[a[i]]; vec[i].clear();
        lim[i] = L[i] = R[i] = 0;
    }
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        vec[v].push_back(u);
    }
    u = n + 1;
    for(int i = n;i;i--){
        for(int j : vec[i]){u = min(u,j);}
        lim[i] = u;vec[i].clear();
    }
    for(int i = 1;i <= n;i++)vec[a[i]].push_back(i);
    for(int i = 1;i <= tot + 1;i++)vec[i].push_back(n + 1);
    for(int i = 1;i <= n;i++){
        if(lim[i] < i && i != vec[a[i]][0]){
            L[i] = vec[a[i]][lower_bound(vec[a[i]].begin(),vec[a[i]].end(),lim[i]) - vec[a[i]].begin()];
            R[i] = vec[a[i]][upper_bound(vec[a[i]].begin(),vec[a[i]].end(),i - 1) - vec[a[i]].begin() - 1];
        }
        else L[i] = n + 1;
        if(L[i] == n + 1 || R[i] < L[i])R[i] = 0, L[i] = n + 1;
        // printf("%d %d %d\n",i,L[i],R[i]);
    }
    u = 1; v = 0;tree.build(1,n,1);
    int ans = n, ll = 0, rr = 0;
    for(;u <= n;u++){
        while(v < n && !check(u, v)){v++;tree.update(v,n + 1,0);}
        if(check(u, v)){
            if(ans >= max(0,v - u + 1)){
                ans = max(0,v - u + 1);
                ll = u; rr = v;
            }
        }
        // if(a[1] == 827218149){
        //     if(u == 83119)printf("u = %d,v = %d ans = %d\n",u,v,ans);
        //     if(u == 53887)printf("u = %d,v = %d ans = %d\n",u,v,ans);
        // }
        tree.update(u,L[u],R[u]);
    }
    // if(ans == 62326)printf("l = %d, r = %d\n",ll,rr);
    printf("%d\n",ans);
    // for(int i = 3133;i <= 3140;i++)printf("a[%d]=%d\n",i,a[i]);
}
    return 0;
}