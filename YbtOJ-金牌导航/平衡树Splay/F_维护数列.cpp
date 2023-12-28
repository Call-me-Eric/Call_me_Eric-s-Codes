#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
const ll INF = 0x3f3f3f3f;
struct Splay{
    struct node{
        int fa, ch[2], siz;
        ll val, lmax, rmax, maxx, sum;
        ll covertag;int revtag;
        node(int fa = 0,int c0 = 0,int c1 = 0,ll val = 0,int siz = 0
        ,ll lmax = 0,ll rmax = 0,ll maxx = -INF,ll sum = 0
        ,ll covertag = INF,int revtag = 0):fa(fa),siz(siz),val(val),
        lmax(lmax),rmax(rmax),maxx(maxx),sum(sum),covertag(covertag)
        ,revtag(revtag){ch[0] = c0;ch[1] = c1;}
    }d[maxn * 2];
    #define C(p, x) d[p].ch[x]
    #define Fa(p) d[p].fa
    vector<int> trash;int rt, tot;
    void maintain(int p){
        d[p].siz = d[C(p,0)].siz + d[C(p,1)].siz + 1;
        d[p].lmax = max(d[C(p,0)].lmax,d[C(p,0)].sum + d[p].val + d[C(p,1)].lmax);
        d[p].rmax = max(d[C(p,1)].rmax,d[C(p,1)].sum + d[p].val + d[C(p,0)].rmax);
        d[p].maxx = max(max(d[C(p,0)].maxx,d[C(p,1)].maxx),d[C(p,0)].rmax + d[C(p,1)].lmax + d[p].val);
        d[p].sum = d[C(p,0)].sum + d[C(p,1)].sum + d[p].val;
        if(C(p,0) == 1 || C(p,0) == 2)d[p].sum += INF;
        if(C(p,1) == 1 || C(p,1) == 2)d[p].sum += INF;
    }
    int newnode(int val){
        int x = 0;if(trash.empty()){x = ++tot;}
        else{x = trash.back();trash.pop_back();}
        d[x] = node(0,0,0,val,1,val,val,val,val);
        if(d[x].lmax < 0)d[x].lmax = d[x].rmax = 0;
        return x;
    }
    void clearp(int p){d[p] = node();trash.push_back(p);}
    inline bool get(int p){return p == C(Fa(p),1);}
    void change(int p,int tag){
        if(!p)return;
        if(tag == -INF){
            swap(C(p,0),C(p,1));
            swap(d[p].lmax,d[p].rmax);
            return;
        }
        d[p].covertag = tag;
        d[p].sum = d[p].siz * d[p].covertag;
        if(d[p].covertag < 0){d[p].lmax = d[p].rmax = 0;d[p].maxx = d[p].covertag;}
        else d[p].lmax = d[p].rmax = d[p].maxx = d[p].sum;
        d[p].val = d[p].covertag;
    }
    void pushdown(int p){
        if(d[p].revtag){
            d[p].revtag ^= 1;
            if(C(p,0)){d[C(p,0)].revtag ^= 1;change(C(p,0),-INF);}
            if(C(p,1)){d[C(p,1)].revtag ^= 1;change(C(p,1),-INF);}
        }
        if(d[p].covertag != INF){
            if(C(p,0)){change(C(p,0),d[p].covertag);}
            if(C(p,1)){change(C(p,1),d[p].covertag);}
            d[p].covertag = INF;
        }
    }
    stack<int> stk;
    void rotate(int p){
        int y = Fa(p), z = Fa(y), chk = get(p);
        C(y,chk) = C(p,chk ^ 1);
        if(C(y,chk))Fa(C(y,chk)) = y;
        Fa(y) = p;Fa(p) = z;C(p,chk ^ 1) = y;
        if(z)C(z,y == C(z,1)) = p;
        maintain(y);maintain(p);
    }
    void splay(int p,int root = 0){
        int u = p;while(u != root)stk.push(u),u = Fa(u);
        while(!stk.empty()){pushdown(stk.top());stk.pop();}
        for(int f = Fa(p);f = Fa(p),f != root;rotate(p))
            if(Fa(f) != root)rotate(get(f) == get(p) ? f : p);//,printf("p = %d,f = %d\n",p,f);
        if(!root)rt = p;
    }
    void build(){
        trash.clear();rt = newnode(-INF); int p = newnode(-INF);
        d[0].maxx = d[1].maxx = d[2].maxx = -INF;
        C(rt,1) = p;Fa(p) = rt;maintain(p);maintain(rt);
    }
    int find(int pos){
        int p = rt;pos++;
        while(1){
            pushdown(p);
            if(pos == d[C(p,0)].siz + 1)return p;
            if(pos < d[C(p,0)].siz + 1)
                p = C(p,0);
            else{
                pos -= d[C(p,0)].siz + 1;
                p = C(p, 1);
            }
        }
    }
    int getrange(int l,int r){
        int pl = find(l - 1);splay(pl);
        int pr = find(r + 1);splay(pr,pl);
        return C(pr,0);
    }
    int prenum(int p = -1){
        if(p == -1)p = rt;
        pushdown(p); p = C(p,0);
        while(pushdown(p),C(p,1)){p = C(p,1);}
        splay(p);return p;
    }
    int sufnum(int p = -1){
        if(p == -1)p = rt;
        pushdown(p); p = C(p,1);
        while(pushdown(p),C(p,0)){p = C(p,0);}
        splay(p);return p;
    }
    vector<int> tmp;
    void insert(int l,int r,int f,int ch){
        if(r < l)return;
        int mid = l + r >> 1;
        int p = newnode(tmp[mid]);
        C(f,ch) = p;Fa(p) = f;
        if(l == r)return;
        insert(l,mid - 1,p,0);insert(mid + 1,r,p,1);
        maintain(p);
    }
    void insert(int pos,vector<int> vec){
        int f = find(pos), p = 0;sufnum(f);
        tmp = vec;insert(0,vec.size() - 1,f,1);
        maintain(f);splay(f);
    }
    void delet(int p){
        if(C(p,0))delet(C(p,0));
        if(C(p,1))delet(C(p,1));
        clearp(p);
    }
    void erase(int l,int r){
        int p = getrange(l,r), f = Fa(p);
        delet(p);C(f,p == C(f,1)) = 0;maintain(f); splay(f);
    }
    void update(int l,int r,int val = -INF){
        int p = getrange(l, r);
        if(val == -INF)d[p].revtag ^= 1;
        else d[p].covertag = val;
        change(p,val); maintain(Fa(p));splay(p);
    }
    ll query(int l,int r){return d[getrange(l, r)].sum;}
    ll querymax(int l,int r){return d[getrange(l,r)].maxx;}
    void print(int p = -1){
        if(p == -1)p = rt;
        pushdown(p);
        if(C(p,0))print(C(p,0));
        printf("%lld ",d[p].val);
        if(C(p,1))print(C(p,1));
    }
    void printtree(){
        for(int i = 1;i <= tot;i++){
            if(d[i].maxx != -INF)
            printf("fa = %d, p = %d, lc = %d, rc = %d,val = %lld,sum = %lld, lm = %lld, rm = %lld, max = %lld, siz = %d\n"
            ,d[i].fa,i,d[i].ch[0],d[i].ch[1],d[i].val,d[i].sum,d[i].lmax,d[i].rmax,d[i].maxx,d[i].siz);
            // printf("%d %d\n",i,C(i,0));
            // printf("%d %d\n",i,C(i,1));
        }
    }
}tree;
int n, m;
signed main(){
    vector<int> tmp;tmp.clear();
    n = read(); m = read();char opt[20];int u, v;
    for(int i = 1;i <= n;i++)tmp.push_back(read());
    tree.build(); tree.insert(0,tmp);
    for(int i = 1;i <= m;i++){
        scanf(" %s",opt);
        if(opt[0] == 'I'){
            u = read(); v = read();tmp.clear();
            for(int j = 1;j <= v;j++)tmp.push_back(read());
            tree.insert(u,tmp);
        }
        if(opt[0] == 'D'){
            u = read();v = read();
            tree.erase(u,u + v - 1);
        }
        if(opt[0] == 'M'){
            if(opt[2] == 'K'){
                u = read();v = read();
                tree.update(u,u + v - 1,read());
            }
            if(opt[2] == 'X'){
                printf("%lld\n",tree.d[tree.rt].maxx);
            }
        }
        if(opt[0] == 'R'){
            u = read(), v = read();
            tree.update(u,u + v - 1);
        }
        if(opt[0] == 'G'){
            u = read(), v = read();
            printf("%lld\n",tree.query(u,u + v - 1));
        }
        // if(i == 228){
        //     tree.print();puts("");
        //     tree.printtree();puts("");
        //     printf("i = %d opt = %s\n",i,opt);
        // }
    }
    return 0;
}