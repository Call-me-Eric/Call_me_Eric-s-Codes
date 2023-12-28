#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a[maxn], n, m;
struct Splay{
    int rt, tot;
    struct node{
        int val, siz;
        int lztag, ch[2], fa;
        node(int fa = 0,int s0 = 0,int s1 = 0,int val = 0,int siz = 0,int lztag = 0
        ):fa(fa),val(val),siz(siz),lztag(lztag){ch[0] = s0;ch[1] = s1;}
    }d[maxn];
    void maintain(int p){d[p].siz = d[d[p].ch[0]].siz + d[d[p].ch[1]].siz + 1;}
    bool get(int p){return d[d[p].fa].ch[1] == p;}
    void clearp(int p){d[p] = node();}

    void pushdown(int p){
        if(d[p].lztag){
            swap(d[p].ch[0],d[p].ch[1]);d[p].lztag ^= 1;
            d[d[p].ch[0]].lztag ^= 1;d[d[p].ch[1]].lztag ^= 1;
        }
    }

    void rotate(int p){
        int y = d[p].fa, z = d[y].fa, chk = get(p);
        // pushdown(y);pushdown(p);
        d[y].ch[chk] = d[p].ch[chk ^ 1];
        if(d[p].ch[chk ^ 1])d[d[p].ch[chk ^ 1]].fa = y;
        d[y].fa = p;d[p].fa = z;d[p].ch[chk ^ 1] = y;
        if(z){d[z].ch[y == d[z].ch[1]] = p;}
        maintain(y);maintain(p);
    }
    void splay(int p,int root = 0){
        for(int f = d[p].fa;f = d[p].fa,f != root;rotate(p))
            if(d[f].fa != root)rotate(get(f) == get(p) ? f : p);
        if(root == 0)rt = p;
    }
    int find(int pos){
        int p = rt;pos++;
        while(1){
            pushdown(p);
            // printf("%d %d\n",p,pos);
            if(pos == (d[d[p].ch[0]].siz + 1))break;
            if(pos > (d[d[p].ch[0]].siz + 1)){
                pos -= (d[d[p].ch[0]].siz + 1);p = d[p].ch[1];
            }
            else p = d[p].ch[0];
        }
        return p;
    }
    void reverse(int l,int r){
        int pl = find(l - 1);splay(pl);
        int pr = find(r + 1);splay(pr,pl);
        d[d[d[rt].ch[1]].ch[0]].lztag ^= 1;
    }
    void build(){
        d[rt = ++tot] = node(0,0,2,-1,n + 2);
        for(int i = 1;i <= n;i++){tot++;d[tot] = node(tot - 1,0,tot + 1,a[i],n + 2 - i);}
        tot++;d[tot] = node(tot - 1,0,0,-1,1);
    }
    void print(int p){
        pushdown(p);
        if(d[p].ch[0])print(d[p].ch[0]);
        if(d[p].val != -1)printf("%d ",d[p].val);
        if(d[p].ch[1])print(d[p].ch[1]);
    }
}tree;
signed main(){
    n = read();m = read();for(int i = 1;i <= n;i++)a[i] = i;
    int opt, l, r;tree.build();
    for(int i = 1;i <= m;i++){
        l = read(), r = read();
        tree.reverse(l, r);
    // for(int i = 0;i <= n + 1;i++)printf("%d ",tree.find(i));puts("");
    //     tree.print(tree.rt);puts("");
    }
    tree.print(tree.rt);
    return 0;
}