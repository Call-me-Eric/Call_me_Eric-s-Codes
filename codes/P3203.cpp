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
int n, m;
int k[maxn];
struct LCT{
    struct node{
        int fa, ch[2], tag, siz;
        node(int fa = 0,int c0 = 0,int c1 = 0,int siz = 0,int tag = 0
        ):fa(fa),siz(siz),tag(tag){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].siz = d[C(p,0)].siz + d[C(p,1)].siz + 1;}
    inline int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}
    void connect(int p,int f,int chk){FA(p) = f;if(chk >= 0)C(f,chk) = p;}
    void pushdown(int p){
        if(d[p].tag){
            swap(C(p,0),C(p,1));d[p].tag ^= 1;
            d[C(p,0)].tag ^= 1;d[C(p,1)].tag ^= 1;
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
            splay(p);C(p,1) = rs;
            maintain(p);rs = p;p = FA(p);
        }
    }
    void change(int u,int v){
        access(u);splay(u);
        C(u,0) = FA(C(u,0)) = 0;
        if(u + v <= n)FA(u) = u + v;
        maintain(u);
    }
    int querydep(int x){
        access(x);splay(x);int p = x;
        // for(p = x;C(p,0);p = C(p,0)){printf("%d->",p);}printf("%d\n",p);
        return d[x].siz;
    }
    #undef C
    #undef FA
}lct;
void main(){
    n = read();
    for(int i = 1;i <= n;i++){
        k[i] = read();lct.d[i].siz = 1;
        if(i + k[i] <= n)lct.d[i].fa = i + k[i];
    }
    m = read();
    for(int i = 1;i <= m;i++){
        int opt = read(), u = read() + 1;
        if(opt == 1)printf("%d\n",lct.querydep(u));
        else{lct.change(u, read());}
        // for(int j = 1;j <= n;j++){printf("dep[%d]=%d\n",j,lct.querydep(j));}
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