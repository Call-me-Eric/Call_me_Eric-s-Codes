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
struct edge{
    int u, v, a, b;
    edge(int u = 0,int v = 0,int a = 0,int b = 0):u(u),v(v),a(a),b(b){}
    friend bool operator < (edge a,edge b){return a.a != b.a ? a.a < b.a : a.b < b.b;}
}e[maxn];
int n, m;
struct LCT{
    struct node{
        int fa, ch[2]; int val, maxx, tag,maxpos;
        node(int fa = 0,int c0 = 0,int c1 = 0,int val = 0,int maxx = 0,int maxpos = 0,bool tag = 0
        ):fa(fa),val(val),maxx(maxx),tag(tag),maxpos(maxpos){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){
        d[p].maxx = d[p].val;d[p].maxpos = p;
        if(d[C(p,0)].maxx > d[p].maxx){d[p].maxx = d[C(p,0)].maxx;d[p].maxpos = d[C(p,0)].maxpos;}
        if(d[C(p,1)].maxx > d[p].maxx){d[p].maxx = d[C(p,1)].maxx;d[p].maxpos = d[C(p,1)].maxpos;}
    }
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
        maintain(y);maintain(x);maintain(z);
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
        d[p].tag ^= 1;
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
    inline bool unicom(int u,int v){return findroot(u) == findroot(v);}
    void update(int p,int val){splay(p);d[p].val = val;maintain(p);}
    node query(int x,int y){split(x, y);return d[y];}
    #undef C
    #undef FA
}lct;

void main(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read(), a = read(), b = read();
        e[i] = edge(u, v, a, b);
    }
    sort(e + 1,e + 1 + m);int ans = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){lct.d[i].maxx = lct.d[i].val = -1;lct.d[i].maxpos = i;}
    for(int i = 1;i <= m;i++){lct.d[i + n].maxx = lct.d[i + n].val = e[i].b;lct.d[i + n].maxpos = i + n;}
    for(int i = 1;i <= m;i++){
        int u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        if(u == v)continue;
        if(lct.unicom(u, v)){
            auto tmp = lct.query(u, v);
            if(tmp.maxx > b){
                lct.cut(e[tmp.maxpos - n].u,tmp.maxpos);lct.cut(e[tmp.maxpos - n].v,tmp.maxpos);
                lct.link(u,i + n);lct.link(v,i + n);
            }
        }
        else{lct.link(u,i + n);lct.link(v,i + n);}
        if(lct.unicom(1, n)){ans = min(ans,a + lct.query(1,n).maxx);}
            // printf("i = %d, a = %d, query = %d\n",i,a,lct.query(1,n).maxx);
        // printf("i = %d, u = %d, v = %d, a = %d, b = %d\n",i,u,v,a,b);
    }
    printf("%d\n",ans == 0x3f3f3f3f ? -1 : ans);
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