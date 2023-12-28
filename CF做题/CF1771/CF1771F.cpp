#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, mod = (1 << 30);
int n, m;
int a[maxn];
map<int,int> mp;
int head[maxn];
struct Segment_Tree{
    int tot;
    struct node{
        int lson, rson, sum;
        node(int sum = 0,int lson = 0,int rson = 0):lson(lson),rson(rson),sum(sum){}
    }d[maxn * 100];
    node mergenode(node l,node r,node f = node()){return node(l.sum ^ r.sum,f.lson,f.rson);}
    int update(int lst,int pos,int x,int l = 1,int r = mod){
        int u = ++tot;d[u] = d[lst];
        if(l == r){d[u].sum ^= x;return u;}
        int mid = l + r >> 1;
        if(pos <= mid)d[u].lson = update(d[lst].lson,pos,x,l,mid);
        else d[u].rson = update(d[lst].rson,pos,x,mid + 1,r);
        d[u] = mergenode(d[d[u].lson],d[d[u].rson],d[u]);
        return u;
    }
    int query(int now,int lst,int l = 1,int r = mod){
        if(l == r){return d[now].sum ^ d[lst].sum ? l : 0;}
        int mid = l + r >> 1, tmp = d[d[now].lson].sum ^ d[d[lst].lson].sum;
        if(tmp)return query(d[now].lson,d[lst].lson,l,mid);
        else return query(d[now].rson,d[lst].rson,mid + 1,r);
    }
}tree;

signed main(){
    n = read();
    mt19937 rand(time(0));
    for(int i = 1;i <= n;i++){
        a[i] = read();
        if(mp.count(a[i]))continue;
        mp[a[i]] = (rand() & mod - 1) + 1;
    }
    for(int i = 1;i <= n;i++){head[i] = tree.update(head[i - 1],a[i],mp[a[i]]);}
    m = read();int l, r, lastans = 0;
    for(int i = 1;i <= m;i++){
        l = read() ^ lastans; r = read() ^ lastans;
        printf("%d\n",lastans = tree.query(head[r],head[l - 1]));
    }
    return 0;
}