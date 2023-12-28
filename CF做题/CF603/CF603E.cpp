#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxm = 3e5 + 10;
int n, m;
 
struct edge{
    int fr, to ,wei, id;
    edge(int fr = 0,int to = 0,int wei = 0,int id = 0):fr(fr),to(to),wei(wei),id(id){}
    friend bool operator < ( edge a,edge b){return a.wei < b.wei;}
}e[maxm];
 
struct mystk{
    struct node{
        int x, y, dep, updodd, siz;
        node(int x = 0,int y = 0,int dep = 0,int siz = 0,int updodd = 0):x(x),y(y),dep(dep),updodd(updodd),siz(siz){}
    };
    node st[maxm];
    int op;
    void pop(){op--;}
    node top(){return st[op];}
    void push(node x){st[++op] = x;}
    bool empty(){return op == 0;}
};
struct DSU{
    mystk stk;
    int oddblock;
    int fa[maxn], dep[maxn], siz[maxn];
    void init(int x = 0){oddblock = x;for(int i = 1;i <= x;i++){fa[i] = i;dep[i] = siz[i] = 1;}}
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    void merge(int x,int y){
        int fx = getf(x), fy = getf(y);
        // printf("getf(%d) = %d,getf(%d) = %d\n",x,fx,y,fy);
        if(fx == fy)return;
        // printf("merged %d, %d\n",x,y);
        if(dep[fx] > dep[fy])swap(fx,fy);
        stk.push(mystk::node(fx,fy,dep[fx] == dep[fy],siz[fx],((siz[fx] + siz[fy]) % 2 == 1) - ((siz[fx] % 2 == 1) + (siz[fy] % 2 == 1))));
        oddblock += (((siz[fx] + siz[fy]) % 2 == 1) - ((siz[fx] % 2 == 1) + (siz[fy] % 2 == 1)));
        fa[fx] = fy;dep[fy] += (dep[fx] == dep[fy]); siz[fy] += siz[fx];
    }
    void trace(int rev = -1){
        while(rev < stk.op){
            // printf("top = %d,rev=  %d\n",stk.op,rev);
            int x = stk.top().x, y = stk.top().y, dept = stk.top().dep, sz = stk.top().siz, updodd = stk.top().updodd;
            fa[x] = x;dep[y] -= dept;siz[x] = sz;siz[y] -= sz;oddblock -= updodd; stk.pop();
        }
    }
}dsu;
int pos, ans[maxm];
struct Segment_Tree{
    vector<int> d[maxm << 2];
    void update(int l,int r,int s,int t,int p,int id){
        if(s <= l && r <= t){d[p].push_back(id);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,id);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,id);
    }
    void update(int s,int t,int id){update(1,m,s,t,1,id);}
    void query(int l,int r,int p){
        int ver = dsu.stk.op;
        for(int i : d[p])dsu.merge(e[i].fr,e[i].to);
        int mid = l + r >> 1;
        if(l == r){
            while(dsu.oddblock != 0 && pos < m){
                pos++;
                // printf("in rev = %d, l = %d, pos = %d\n",ver, l, pos);
                // printf("u = %d v = %d w = %d\n",e[pos].fr,e[pos].to,e[pos].wei);
                if(e[pos].id <= l){
                    dsu.merge(e[pos].fr,e[pos].to);
                    if(l != 1) update(e[pos].id,l - 1,pos);
                }
                // printf("odd = %d\n",dsu.oddblock);
            }
            if(dsu.oddblock == 0)ans[l] = e[pos].wei;
            else ans[l] = -1;
        }
        else {query(mid + 1,r,p << 1 | 1);query(l,mid,p << 1);}
        dsu.trace(ver);
    }
}tree;
 
signed main(){
    n = read(); m = read();int u, v, w;
    if(n & 1){for(int i = 1;i <= m;i++)puts("-1");return 0;}
    for(int i = 1;i <= m;i++){
        u =  read(); v=  read(); w = read();
        e[i] = edge(u, v, w, i);
    }
    sort(e + 1,e + 1 + m);dsu.init(n); tree.query(1, m, 1);
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
    return 0;
}
 