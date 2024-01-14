#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0 , f  =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct LCT{
    struct node{
        int fa, ch[2]; int val, sum, tag;
        node(int fa = 0,int c0 = 0,int c1 = 0,int val = 0,int sum = 0,bool tag = 0
        ):fa(fa),val(val),sum(sum),tag(tag){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].sum = d[C(p,0)].sum ^ d[p].val ^ d[C(p,1)].sum;}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}//return p == Fa(p,1),but return -1 when p is the root of Splay
    void connect(int p,int f,int chk){FA(p) = f; if(chk == 0 || chk == 1)C(f,chk) = p;}
    void pushdown(int p){
        if(d[p].tag){
            swap(C(p,0),C(p,1));
            if(C(p,0))d[C(p,0)].tag ^= 1;
            if(C(p,1))d[C(p,1)].tag ^= 1;
            d[p].tag = 0;
        }
    }
    void pushdownall(int p){
        if(get(p) != -1) pushdownall(FA(p));
        pushdown(p);
    }

    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u,y,chkx);connect(y,x,chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        pushdownall(p);
        while(get(p) != -1){
            int f = FA(p);
            if(get(f) == -1)rotate(p);
            else if(get(f) == get(p)){rotate(f);rotate(p);}
            else {rotate(p);rotate(p);}
        }
    }
    void access(int p){
        int rs = 0;
        while(p){
            splay(p);C(p,1) = rs;maintain(p);
            rs = p;p = FA(p);
        }
    }
    void makeroot(int p){
        access(p); splay(p);
        swap(C(p,0),C(p,1));
        if(C(p,0))d[C(p,0)].tag ^= 1;
        if(C(p,1))d[C(p,1)].tag ^= 1;
    }
    void split(int x,int y){
        makeroot(x);
        access(y);splay(y);
    }
    int findroot(int p){
        access(p);splay(p);
        while(C(p,0)){pushdown(p),p = C(p,0);}
        splay(p);return p;
    }
    void link(int x,int y){
        makeroot(x);
        if(findroot(y) == x) return;
        FA(x) = y;return;
    }
    void cut(int x,int y){
        if(findroot(x) != findroot(y))return;
        split(x, y);
        if(FA(x) != y || C(x,1))return;
        FA(x) = C(y,0) = 0;
        maintain(x);maintain(y);return;
    }
    void update(int p,int val){splay(p);d[p].val = val;maintain(p);}
    node query(int x,int y){split(x, y);return d[y];}
}tree;
int n, m;

signed main(){
    n = read(); m = read();int opt, u, v;
    for(int i = 1;i <= n;i++)tree.d[i].val = tree.d[i].sum = read();
    for(int i = 1;i <= m;i++){
        opt = read(); u = read();v = read();
        if(opt == 0){printf("%d\n",tree.query(u, v).sum);}
        if(opt == 1){tree.link(u, v);}
        if(opt == 2){tree.cut(u, v);}
        if(opt == 3){tree.update(u, v);}
    }
    return 0;
}