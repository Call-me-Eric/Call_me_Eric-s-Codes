#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f =-1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn];
int lst[maxn];
struct Segment_Tree{
    struct node{
        int minn;
        node(int minn = 0):minn(minn){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(min(l.minn,r.minn));}
    void update(int l,int r,int pos,int p,int upd){
        if(l == r){d[p] = node(upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(t < s)return node(114514);
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
}tree;
bool book[maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();if(a[i] != 1)book[1] = 1;
        if(a[i] > 1 && tree.query(1,n,1,a[i] - 1,1).minn > lst[a[i]])book[a[i]] = 1;
        tree.update(1,n,a[i],1,i);lst[a[i]] = i;
    }
    for(int i = 2;i <= n + 1;i++){
        if(tree.query(1,n,1,i - 1,1).minn > lst[i])book[i] = 1;
    }
    int x = 1;while(book[x])x++;
    printf("%d\n",x);
    return 0;
}