#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, mod = 51061;
int n, q;
struct LCT{
    struct node{
        int fa, ch[2], revtag;
        int sum, val;
        int addtag, multag;
        node(int sum = 0,int val = 0,int fa = 0,int c0 = 0,int c1 = 0,int revtag = 0,int addtag = 0,int multag = 1
        ):sum(sum),val(val),fa(fa),revtag(revtag),addtag(addtag),multag(multag){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].sum = (0ll + d[C(p,0)].sum + d[C(p,1)].sum + d[p].val) % mod;}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}
    void connect(int p,int f,int x){FA(p) = f;if(x != -1)C(f,x) = p;}
    void getmul(int p,int mul = 1){
        d[p].val = 1ll * d[p].val * mul % mod;
        d[p].sum = 1ll * d[p].sum * mul % mod;
        d[p].multag = 1ll * d[p].multag * mul % mod;
    }
    void getadd(int p,int add = 0){
        d[p].val = (0ll + d[p].val + add) % mod;
        d[p].sum = (0ll + d[p].sum + add) % mod;
        d[p].addtag = (0ll + d[p].addtag + add) % mod;
    }
    void getrev(int p){swap(C(p,0),C(p,1));d[C(p,0)].revtag ^= 1;d[C(p,1)].revtag ^= 1;}
    void pushdown(int p){
        getmul(C(p,0),d[p].multag); getmul(C(p,1),d[p].multag); d[p].multag = 1;
        getadd(C(p,0),d[p].addtag); getadd(C(p,1),d[p].addtag); d[p].addtag = 0;
        if(d[p].revtag){getrev(p);d[p].revtag = 0;}
    }
    void pushdownall(int p){
        if(get(p) != -1)pushdownall(FA(p));
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
        for(int f = FA(p);f = FA(p),get(p) != -1;rotate(p))
            if(get(f) != -1)rotate(get(f) == get(p) ? f : p);
    }
    void access(int p){
        int rs = 0;
        while(p){splay(p);pushdown(p);C(p,1) = rs;maintain(p);rs = p;p = FA(p);}
    }
    void makeroot(int p){access(p);splay(p);getrev(p);}
    int split(int x,int y){makeroot(x);access(y);splay(y);return y;}
    void link(int x,int y){makeroot(x);access(y);splay(y);FA(x) = y;}
    void cut(int x,int y){split(x, y); C(x,1) = FA(y) = 0;maintain(x);}
    void DEBUG(){
        for(int i = 1;i <= n;i++){
            printf("i = %d, fa = %d, c0 = %d, c1 = %d, val = %d, sum = %d,multag = %d\n",i,FA(i),C(i,0),C(i,1),d[i].val,d[i].sum,d[i].multag);
        }
    }
}lct;
void main(){
    n = read(); q = read();
    for(int i = 1;i <= n;i++)lct.d[i].val = lct.d[i].sum = 1;
    char opt[3];int u, v, x, y;
    for(int i = 1;i < n;i++){
        u = read();v = read();lct.link(u, v);
    }
    while(q--){
        scanf(" %s",opt);u = read(), v = read();
        if(opt[0] == '+'){x = read();lct.split(u, v);lct.getadd(v,x);}
        if(opt[0] == '-'){x = read(), y = read(); lct.cut(u, v);lct.link(x, y);}
        if(opt[0] == '*'){x = read();lct.split(u, v);lct.getmul(v,x);}
        if(opt[0] == '/'){printf("%d\n",lct.d[lct.split(u,v)].sum);}
        // lct.DEBUG();
    }
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