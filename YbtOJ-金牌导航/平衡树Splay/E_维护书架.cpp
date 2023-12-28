#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int posi[maxn], a[maxn], n, m;
struct Splay{
    struct node{
        int fa, siz, val;
        int ch[2], lztag;
        node(int fa = 0,int c0 = 0,int c1 = 0,int val = 0,int siz = 0,int lztag = 0
            ):fa(fa),siz(siz),val(val),lztag(lztag){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    int rt, tot;
    bool get(int p){return p == d[d[p].fa].ch[1];}
    void maintain(int p){d[p].siz = d[d[p].ch[0]].siz + d[d[p].ch[1]].siz + 1;}
    void clearp(int p){d[p] = node();return;}
    void pushdown(int p){
        if(d[p].lztag){
            swap(d[p].ch[0],d[p].ch[1]);
            d[d[p].ch[0]].lztag ^= 1;
            d[d[p].ch[1]].lztag ^= 1;
            d[p].lztag = 0;
        }
    }
    void rotate(int p){
        int y = d[p].fa, z = d[y].fa, chk = get(p);
        // pushdown(y);pushdown(p);
        d[y].ch[chk] = d[p].ch[chk ^ 1];
        if(d[p].ch[chk ^ 1])d[d[p].ch[chk ^ 1]].fa = y;
        d[p].fa = z;d[y].fa = p;d[p].ch[chk ^ 1] = y;
        if(z)d[z].ch[y == d[z].ch[1]] = p;
        maintain(y);maintain(p);
    }
    stack<int> stk;
    void splay(int p,int root = 0){
        int u = p;while(u != root)stk.push(u), u = d[u].fa;
        while(!stk.empty()){pushdown(stk.top());stk.pop();}
        for(int f = d[p].fa;f = d[p].fa, f != root;rotate(p))
            if(d[f].fa != root)rotate(get(f) == get(p) ? f : p);
        if(root == 0)rt = p;
    }
    void build(){
        d[rt = ++tot] = node(0,0,2,-1,n + 2,0);
        for(int i = 1;i <= n;i++){tot++;d[tot] = node(tot - 1,0,tot + 1,a[i],n + 2 - i);posi[a[i]] = tot;}
        tot++;d[tot] = node(tot - 1,0,0,-1,1);
    }
    int find(int pos){
        int p = rt;pos++;
        while(1){
            pushdown(p);
            if(pos == d[d[p].ch[0]].siz + 1)return p;
            if(pos > d[d[p].ch[0]].siz + 1){
                pos -= d[d[p].ch[0]].siz + 1;p = d[p].ch[1];
            }
            else p = d[p].ch[0];
        }
    }
    void reverse(int l,int r){
        int pl = find(l - 1);splay(pl);
        int pr = find(r + 1);splay(pr,pl);
        d[d[d[rt].ch[1]].ch[0]].lztag ^= 1;
    }
    int rank(int val){
        splay(posi[val]);
        return d[d[rt].ch[0]].siz + 1;
    }
    void top(int x){
        int l = rank(x) - 1;
        if(l != 1){reverse(1,l);reverse(2, l);}
    }
    void bottom(int x){
        int l = rank(x) - 1;
        if(l != n){reverse(l,n);reverse(l,n - 1);}
    }
    void revnum(int x,int opt){
        int p = rank(x) - 1;
        if(opt == -1)reverse(p - 1,p);
        else reverse(p,p + 1);
    }
    void print(int p){
        pushdown(p);
        if(d[p].ch[0])print(d[p].ch[0]);
        printf("%d ",d[p].val);
        if(d[p].ch[1])print(d[p].ch[1]);
    }
}tree;
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    tree.build();char opt[10];int u, v;
    for(int i = 1;i <= m;i++){
        scanf(" %s",opt);u = read();
        if(opt[0] == 'T'){tree.top(u);}
        if(opt[0] == 'B'){tree.bottom(u);}
        if(opt[0] == 'I'){
            v = read();if(!v)continue;
            tree.revnum(u, v);
        }
        if(opt[0] == 'A'){printf("%d\n",tree.rank(u) - 2);}
        if(opt[0] == 'Q'){printf("%d\n",tree.d[tree.find(u)].val);}
        // tree.print(tree.rt);puts("");
    }
    return 0;
}