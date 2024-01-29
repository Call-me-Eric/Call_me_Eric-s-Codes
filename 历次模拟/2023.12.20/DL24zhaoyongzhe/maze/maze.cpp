#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10, mod = 998244353;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int m;
struct Segment_Tree{
    struct node{
        int summ, tag;
        node(int summ = 0,int tag = 0):summ(summ),tag(tag){}
    }d[maxn << 2];
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag += d[p].tag;
            d[p << 1].summ += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;
            d[p << 1 | 1].summ += d[p].tag;
            d[p].tag = 0;
        }
    }
    node mergenode(node l,node r){return node((l.summ + r.summ) % mod);}
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].tag += upd;d[p].summ += upd;return;}
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
}tree;
signed main(){
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    m = read(); int tp = read(), opt, l, r, lastans = 0;
    for(int i = 1;i <= m;i++){
        opt = read();l = read(); r = read();
        if(tp)opt ^= lastans, l ^= lastans, r ^= lastans;
        if(opt == 1){
            tree.update(1,1e5,l,r,1,read() ^ lastans);
        }
        if(opt == 2){
            int a = sqrt(l), b = l / a;
            if(a == 1 && b == 3){tree.update(1,1e5,1,4,1,r);continue;}
            if(a % 2 == 0 && b - a == 1){
                tree.update(1,1e5,1,1,1,r);
                for(int j = 1;j * 2 < a;j++){
                    int x = j * 2 * (j * 2 + 1);
                    x = x - j + 1;
                    tree.update(1,1e5,x,x + j * 2,1,r);
                }
                int x = l - a / 2 + 1;
                tree.update(1,1e5,x,x + a / 2 - 1,1,r);
                continue;
            }
            if(a % 2 == 1 && b - a == 1){
                tree.update(1,1e5,1,1,1,r);
                for(int j = 1;j * 2 < b;j++){
                    int x = j * 2 * (j * 2 - 1);
                    x = x - j + 1;
                    tree.update(1,1e5,x,x + j * 2,1,r);
                }
                int x = l - b / 2 + 1;
                tree.update(1,1e5,x,x + b / 2 - 1,1,r);
                continue;
            }
        }
        if(opt == 3){
            printf("%d\n",lastans = tree.query(1,1e5,l,r,1).summ);
        }
    }
    return 0;
}