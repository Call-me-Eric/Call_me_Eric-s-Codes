#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e4 + 10;
int n, q;
int a[maxn], X[maxn];
int head[maxn], tot;
struct Segment_Tree{
    struct node{
        int sum, lmax, rmax;int ch[2];
        node(int sum = 0,int lmax = 0,int rmax = 0,int lp = 0,int rp = 0
        ):sum(sum),lmax(lmax),rmax(rmax){ch[0] = lp;ch[1] = rp;}
    }d[maxn * 30];
    #define C(p,x) d[p].ch[x]
    node mergenode(node l,node r,node p = node()){
        return node(l.sum + r.sum,max(l.lmax,l.sum + r.lmax),max(r.rmax,l.rmax + r.sum),p.ch[0],p.ch[1]);
    }
    void build(int l,int r,int &p){
        if(!p)p = ++tot;
        if(l == r){d[p] = node(1,1,1);return;}
        int mid = l + r >> 1;
        build(l,mid,C(p,0));build(mid + 1,r,C(p,1));
        d[p] = mergenode(d[C(p,0)],d[C(p,1)],d[p]);
    }
    void update(int l,int r,int pos,int &p,int lst,int upd){
        if(!p)p = ++tot;
        if(l == r && l == pos){d[p] = node(upd,upd,upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid){C(p,1) = C(lst,1);update(l,mid,pos,C(p,0),C(lst,0),upd);}
        else{C(p,0) = C(lst,0);update(mid + 1,r,pos,C(p,1),C(lst,1),upd);}
        d[p] = mergenode(d[C(p,0)],d[C(p,1)],d[p]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,C(p,0));
        if(mid < s)return query(mid + 1,r,s,t,C(p,1));
        return mergenode(query(l,mid,s,t,C(p,0)),query(mid + 1,r,s,t,C(p,1)));
    }
    node query(int l,int r,int p){if(r < l)return node();return query(1,n,l,r,p);}
}tree;
vector<int> vec[maxn];
bool check(int a,int b,int c,int d,int mid){
    return tree.query(a,b,head[mid]).rmax + tree.query(b + 1,c - 1,head[mid]).sum + tree.query(c,d,head[mid]).lmax >= 0;
}
void main(){
    n = read();
    for(int i = 1;i <= n;i++){X[i] = a[i] = read();}
    sort(X + 1,X + 1 + n);int tot = unique(X + 1,X + 1 + n) - X - 1;
    for(int i = 1;i <= n;i++){a[i] = lower_bound(X + 1,X + 1 + tot,a[i]) - X;vec[a[i]].push_back(i);}
    tree.build(1,n,head[1]);
    for(int i = 2;i <= tot;i++){
        int t = head[i - 1];for(int j : vec[i - 1]){head[i] = 0;tree.update(1,n,j,head[i],t,-1);t = head[i];}
    }
    q = read();int ans = 0;
    for(int i = 1;i <= q;i++){
        vector<int> vec;
        for(int j = 1;j <= 4;j++)vec.push_back((read() + ans) % n + 1);
        sort(vec.begin(),vec.end());
        int a = vec[0],b = vec[1], c = vec[2], d = vec[3];
        int l = 1, r = tot;
        while(l <= r){
            int mid = l + r >> 1;
            if(check(a,b,c,d,mid)){ans = X[mid];l = mid + 1;}
            else r = mid - 1;
        }
        printf("%d\n",ans);
    }
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}