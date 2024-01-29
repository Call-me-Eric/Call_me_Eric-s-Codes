#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, INF = 0x3f3f3f3f;

int n, k;
int a[maxn], b[maxn];

struct node1{
    int first, second;
    node1(int f = 0,int s = 0):first(f),second(s){}
    friend bool operator <(node1 x,node1 y){
    return a[x.first] + b[x.second] < a[y.first] + b[y.second];}
};

typedef node1 pii;

struct Segment_Tree{
    struct node{
        int mina, minb, la, lb, minn, tag; pii ans1, ans2,ans3;
        node(int mina = 0,int minb = 0,int la = 0,int lb = 0,int minn = 0,int tag = 0,pii a1 = node1(0,0), pii a2 = node1(0,0),
        pii a3 = node1(0,0)):mina(mina),minb(minb),la(la),lb(lb),minn(minn),tag(tag),ans1(a1),ans2(a2),ans3(a3){}
    }d[maxn << 2];
    node mergenode(node l,node r){
        node ans = node();
        ans.mina = a[l.mina] < a[r.mina] ? l.mina : r.mina;
        ans.minb = b[l.minb] < b[r.minb] ? l.minb : r.minb;
        ans.minn = min(l.minn,r.minn);
        
        ans.ans1 = min(min(l.ans1,r.ans1),node1(l.mina,r.minb));
        ans.ans3 = min(min(l.ans3,r.ans3),node1(r.mina,l.minb));
        ans.ans2 = min(l.ans2,r.ans2);

        if(l.minn > r.minn){
            ans.ans2 = min(ans.ans2,min(node1(r.la,l.minb),l.ans3));
            ans.la = a[l.mina] < a[r.la] ? l.mina : r.la; ans.lb = r.lb;
        }
        else if(l.minn < r.minn){
            ans.ans2 = min(ans.ans2,min(node1(r.mina,l.lb),r.ans3));
            ans.lb = b[r.minb] < b[l.lb] ? r.minb : l.lb; ans.la = l.la;
        }
        else{
            ans.la = l.la;ans.lb = r.lb;
            ans.ans2 = min(ans.ans2,node1(r.la,l.lb));
        }
        return ans;
    }
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag += d[p].tag;d[p << 1].minn += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;d[p << 1 | 1].minn += d[p].tag;
            d[p].tag = 0;
        }
    }
    void build(int l = 0,int r = n,int p = 1){
        if(l == r){d[p] = node(l,l,l,0,0,0,node1(l,l),node1(0,0),node1(l,l));return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p){
        if(l == r && l == pos){return;}
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)update(l,mid,pos,p << 1);
        else update(mid + 1,r,pos,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int add){
        if(s <= l && r <= t){d[p].tag += add;d[p].minn += add;return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,add);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,add);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int pos){update(0,n,pos,1);}
    void update(int s,int t,int add){update(0,n,s,t,1,add);}
}tree;
signed main(){
    n = read(); k = read();
    a[0] = b[0] = INF;
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)b[i] = read();
    tree.build(0,n,1);int ans = 0;
    while(k--){
        int x, y, upd = 0;
        if(tree.d[1].ans1 < tree.d[1].ans2){x = tree.d[1].ans1.first, y = tree.d[1].ans1.second;upd = 1;}
        else {x = tree.d[1].ans2.first, y = tree.d[1].ans2.second;upd = -1;}
        // printf("choose 1 : %lld %lld %lld\n",tree.d[1].ans1.first,tree.d[1].ans1.second,a[tree.d[1].ans1.first] + b[tree.d[1].ans1.second]);
        // printf("choose 2 : %lld %lld %lld\n",tree.d[1].ans2.first,tree.d[1].ans2.second,a[tree.d[1].ans2.first] + b[tree.d[1].ans2.second]);
        ans += a[x] + b[y];a[x] = b[y] = INF;
        tree.update(x);tree.update(y);
        if(x == y)continue;
        tree.update(min(x, y),max(x, y) - 1,upd);
    }
    printf("%lld\n",ans);
    return 0;
}
/*
8 4
3 8 7 9 9 4 6 8
2 5 9 4 3 8 9 1
*/