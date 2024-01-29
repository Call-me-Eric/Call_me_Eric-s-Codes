#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0 ,f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x =(x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, Q;
int a[maxn], pre[maxn], suf[maxn];
struct query{int l, id;query(int l = 0,int id = 0):l(l),id(id){}};
vector<query> vec[maxn];
int ans[maxn];
struct Segment_Tree{
    struct node{
        int lstver, lsttag, sum, maxx;
        node(int maxx = 0,int sum = 0,int lsttag = 0,int lstver = 0
            ):maxx(maxx) ,sum(sum)   ,lsttag(lsttag),lstver(lstver){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx),l.sum + r.sum);}
    void settle(int p,int tim,int upd = -1){
        if(upd == -1)upd = d[p].lsttag;
        d[p].sum += (tim - d[p].lstver) * d[p].lsttag;
        d[p].lstver = tim;d[p].lstver = upd;
    }
    void pushdown(int p){
        if(d[p].lsttag){
            settle(p << 1,d[p].lstver,d[p].lsttag);
            settle(p << 1 | 1,d[p].lstver,d[p].lsttag);
            d[p].lsttag = 0;
        }
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){settle(p,t);return d[p];}
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    
}tree;
signed main(){
    n = read(); Q = read();
    for(int i = 1;i <= n;i++)suf[a[i] = read()] = i; for(int i = n;i;i--)pre[a[i]] = i;
    for(int i = 1;i <= Q;i++){int l = read(), r = read();vec[r].push_back(query(l,i));}

    return 0;
}