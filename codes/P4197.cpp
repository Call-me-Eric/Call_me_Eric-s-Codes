#include<bits/stdc++.h>
// #define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxm = 7e5 + 10;

struct Segment_Tree{
    int total, son[maxn * 40][2];
    int d[maxn * 40];
    void update(int l,int r,int &p,int val){
        if(!p){p = ++total;}
        if(l == r){d[p]++;return;} int mid = l + r >> 1;
        if(val <= mid)update(l,mid,son[p][0],val);
        else update(mid + 1,r,son[p][1],val);
        d[p] = d[son[p][0]] + d[son[p][1]];
    }
    int query(int l,int r,int p,int goal){
        if(l == r){return l;}int mid = l + r >> 1;
        if(goal <= d[son[p][1]])return query(mid + 1,r,son[p][1],goal);
        else return query(l,mid,son[p][0],goal - d[son[p][1]]);
    }
    int mergetree(int l,int r,int p1,int p2){
        if(!p1 || !p2)return p1 | p2;
        if(l == r){d[p1] = d[p1] + d[p2];return p1;} int mid = l + r >> 1;
        son[p1][0] = mergetree(l,mid,son[p1][0],son[p2][0]);
        son[p1][1] = mergetree(mid + 1,r,son[p1][1],son[p2][1]);
        d[p1] = d[son[p1][0]] + d[son[p1][1]];
        return p1;
    }
}tree;

int n, m;
struct edge{
    int from, to, wei;
    edge(int from = 0,int to = 0,int we = 0):from(from),to(to),wei(we){}
    friend bool operator < (edge a,edge b){return a.wei < b.wei;}
}e[maxm];

int fa[maxn], siz[maxn];
int getf(int x){return fa[x] == x ? fa[x] : fa[x] = getf(fa[x]);}

int h[maxn], a[maxn], b[maxn], totall;

int q, ans[maxm];
struct quest{
    int st, weight, kth, id;
    quest(int s = 0,int w = 0,int k = 0,int id = 0):st(s),weight(w),kth(k),id(id){}
    friend bool operator < (quest a,quest b){return a.weight < b.weight;}
}qu[maxm];

signed main(){
    n = read(); m = read(); q = read(); tree.total = n;
    for(int i = 1;i <= n;i++){b[i] = h[i] = read();}
    for(int i = 1;i <= n;i++){fa[i] = i;siz[i] = 1;}
    
    sort(b + 1,b + 1 + n);totall = unique(b + 1,b + 1 + n) - b - 1;
    for(int i = 1;i <= n;i++){a[i] = lower_bound(b + 1,b + 1 + n,h[i]) - b;}

    for(int i = 1;i <= n;i++){tree.update(1,totall,i,a[i]);}
    
    for(int i = 1;i <= m;i++){int u = read(), v = read(), w = read();e[i] = edge(u,v,w);}
    sort(e + 1,e + 1 + m);

    for(int i = 1;i <= q;i++){int u = read(), v = read(),w =  read();qu[i] = quest(u,v,w,i);}
    sort(qu + 1,qu + 1 + q);

    int point = 0;
    for(int i = 1;i <= q;i++){
        while(e[point + 1].wei <= qu[i].weight && point + 1 <= m){
            point++;
            int u = e[point].from, v = e[point].to;
            int fu = getf(u), fv = getf(v);
            if(fu != fv){
                fa[fv] = fu;siz[fu] += siz[fv];
                tree.mergetree(1,totall,fu,fv);
            }
        }
        if(siz[getf(qu[i].st)] < qu[i].kth)ans[qu[i].id] = -1;
        else ans[qu[i].id] = b[tree.query(1,totall,getf(qu[i].st),qu[i].kth)];
    }
    for(int i = 1;i <= q;i++){printf("%d\n",ans[i]);}
    return 0;
}