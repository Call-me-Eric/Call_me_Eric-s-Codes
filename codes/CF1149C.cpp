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
const int maxn = 2e5 + 10;
int n, q;
char ch[maxn];
int a[maxn];
struct Segment_Tree{
    struct node{
        int sum;
        int rmin, lmax;//rmin表示最小的\sum_{i\in[x,r]}c_i,lmax同理
        int lans, rans, ans,anss;//anss表示选择了整个区间但是分割点在这个区间内的最大值
        node(int val = 0){
            sum = val;lans = rans = ans = anss = (val != 0);
            rmin = min(val,0);lmax = max(val,0);
        }
        node(int sum,int rmin,int lmax,int lans,int rans,int anss,int ans
        ):sum(sum),rmin(rmin),lmax(lmax),lans(lans),rans(rans),anss(anss),ans(ans){}
    }d[maxn << 2];
    node mergenode(node l,node r){
        node ans = node();
        ans.sum = l.sum + r.sum;
        ans.rmin = min(r.rmin,r.sum + l.rmin);
        ans.lmax = max(l.lmax,r.lmax + l.sum);
        ans.lans = max(l.lans,max(l.anss + r.lmax,-l.sum + r.lans));
        ans.rans = max(r.rans,max(r.anss - l.rmin,r.sum + l.rans));
        ans.anss = max(l.anss + r.sum,-l.sum + r.anss);
        ans.ans = max(max(l.ans,r.ans),max(-l.rmin + r.lans,l.rans + r.lmax));
        return ans;
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int pos,int upd){update(1,n,pos,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
    void build(){build(1,n,1);}
}tree;
void main(){
    n = (read() << 1) - 2;q = read();
    scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++)a[i] = ch[i] == '(' ? 1 : -1;
    tree.build();
    printf("%d\n",tree.query(1,n).ans);
    for(int i = 1;i <= q;i++){
        int u = read(), v = read();
        if(u == v){printf("%d\n",tree.query(1,n).ans);continue;}
        int x = a[u], y = a[v];
        tree.update(u,y);tree.update(v,x);
        swap(a[u],a[v]);
        printf("%d\n",tree.query(1,n).ans);
        // tree.update(u,x);tree.update(v,y);
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