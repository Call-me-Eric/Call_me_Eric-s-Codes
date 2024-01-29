#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
struct LCT{
    struct node{
        int fa, ch[2], tag;
        int siz, si;
        node(int fa = 0,int c0 = 0,int c1 = 0,int tag = 0,int siz = 0,int si = 0
                        ):fa(fa),tag(tag),siz(siz),si(si){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].siz = d[C(p,0)].siz + d[C(p,1)].siz + d[p].si + 1;}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}
    void connect(int p,int f,int chk){FA(p) = f;if(chk == 1 || chk == 0)C(f,chk) = p;}
    void pushdown(int p){
        if(d[p].tag){
            swap(C(p,0),C(p,1));
            if(C(p,0))d[C(p,0)].tag ^= 1;
            if(C(p,1))d[C(p,1)].tag ^= 1;
            d[p].tag = 0;
        }
    }
    void pushdownall(int p){if(get(p) != -1)pushdownall(FA(p));pushdown(p);}
    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u,y,chkx);connect(y,x,chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        pushdownall(p);
        for(int f = FA(p);f = FA(p),get(p) != -1;rotate(p))
            if(get(f) != -1)rotate(get(p) == get(f) ? f : p);
    }
    void access(int p){
        int rs = 0;
        while(p){
            splay(p);
            d[p].si += d[C(p,1)     ].siz;
            d[p].si -= d[C(p,1) = rs].siz;
            rs = p;maintain(p);p = FA(p);
        }
    }
    void makeroot(int p){
        access(p);splay(p);
        d[p].tag ^= 1;
    }
    void split(int x,int y){
        makeroot(x);
        access(y);splay(y);
    }
    int findroot(int p){
        access(p);splay(p);
        while(C(p,0)){pushdown(p);p = C(p,0);}
        splay(p);return p;
    }
    void link(int x,int y){
        makeroot(x);if(findroot(y) == x)return;
        FA(x) = y; d[y].si += d[x].siz;maintain(y);
    }
    int getmid(int root,int siz){
        int lsum = 0, rsum = 0;
        int u = root;siz /= 2;
        int rt = 0x3f3f3f3f;
        while(u){
            pushdown(u);
            int L = lsum + d[C(u,0)].siz;
            int R = rsum + d[C(u,1)].siz;
            if(L <= siz && R <= siz){rt = min(rt,u);}
            if(L < R){lsum = L + d[u].si + 1;u = C(u,1);}
            else {rsum = R + d[u].si + 1;u = C(u,0);}
        }
        return rt;
    }
}tree;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
int n, m;
int ans;
signed main(){
    n = read(); m = read();char opt[10];int u, v;
    for(int i = 1;i <= n;i++){ans ^= i;fa[i] = i;}
    for(int i = 1;i <= m;i++){
        scanf("%s",opt);
        if(opt[0] == 'A'){
            u = read(); v = read();
            int fu = getf(u), fv = getf(v);
            ans ^= fu ^ fv;tree.link(u, v);
            tree.split(fu, fv);
            int siz = tree.d[fv].siz;
            int rt = tree.getmid(fv,siz);
            ans ^= rt;tree.splay(rt);
            fa[rt] = fa[fu] = fa[fv] = rt;
        }
        if(opt[0] == 'Q'){printf("%d\n",getf(read()));}
        if(opt[0] == 'X'){printf("%d\n",ans);}
    }
    return 0;
}