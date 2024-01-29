#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool st;
const int maxn = 5e5 + 10;
int n, m, k, q;
pair<int,int> edg[maxn];
int id[maxn], col[maxn];
int r[maxn];
struct DSU{

    typedef pair<pair<int,int>,int> T;
    struct Stack{
        T s[maxn];int tp;
        inline T top(){return s[tp];}
        inline bool pop(){if(!tp)return false;tp--;return true;}
        inline void push(T x){s[++tp] = x;}
        Stack(){tp = 0;}
    };
    stack<T> opt;
    int fa[maxn << 1], hei[maxn << 1];
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    void init(int x = 0){for(int i = 1;i <= x;i++)fa[i] = i, hei[i] = 1;}
    void merge(int x,int y){
        x = getf(x); y = getf(y);
        if(x == y)return;
        if(hei[x] > hei[y])swap(x, y);
        opt.push(make_pair(make_pair(x, y),hei[x] == hei[y]));
        fa[x] = y;hei[y] += hei[x] == hei[y];
    }
    void trace(){
        if(!opt.size())return;
        auto u = opt.top();opt.pop();
        fa[u.first.first] = u.first.first;
        hei[u.first.second] -= u.second;
    }
    void trace(int lsttop){
        while(opt.size() != lsttop){
            auto u = opt.top();opt.pop();
            fa[u.first.first] = u.first.first;
            hei[u.first.second] -= u.second;
        }
    }
    inline int version(){return opt.size();}
};

DSU dsu[51];

int lst[maxn], ncol[maxn];
bool ans[maxn];
struct Seg_Tree{
    typedef int T;
    vector<T> d[maxn << 2];
    void init(int x = 0,int y = 0){for(int i = 1;i <= x;i++)dsu[i].init(y * 2);}
    void update(int l,int r,int s,int t,int p,T x){
        if(s <= l && r <= t){d[p].push_back(x);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,x);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,x);
    }
    void getans(int l,int r,int p){
        vector<int> lsttop;lsttop.clear();lsttop.push_back(0);
        for(int i = 1;i <= k;i++){lsttop.push_back(dsu[i].version());}
        for(T i : d[p]){
            int pos = id[i], col = ::col[i];
            int u = edg[pos].first, v = edg[pos].second;
            if(col){
                dsu[col].merge(u, v + n);
                dsu[col].merge(u + n,v);
            }
        }
        if(l == r){
            int pos = id[l], col = ::col[l];
            int u = edg[pos].first, v = edg[pos].second;
            int fu = dsu[col].getf(u), fv = dsu[col].getf(v);
            if(fu == fv)puts("NO"),::col[l] = ncol[pos];
            else puts("YES"),ncol[pos] = ::col[l];
        }
        if(l != r){
            int mid = l + r >> 1;
            getans(l,mid,p << 1);
            getans(mid + 1,r,p << 1 | 1);
        }
        for(int i = 1;i <= k;i++){dsu[i].trace(lsttop[i]);}
    }
    void update(int l,int r,T x){update(1,q,l,r,1,x);}
}tree;

bool ed;

signed main(){
    // cerr << (&ed - &st) / 1024 /  1024 << " Mib" << endl;
    n = read(); m = read(); k = read(); q = read();
    tree.init(k,n);int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        edg[i] = make_pair(u, v);
    }
    for(int i = 1;i <= q;i++){id[i] = read(); col[i] = read();ans[i] = true;}
    for(int i = 1;i <= m;i++){lst[i] = q + 1;ncol[i] = 0;}
    for(int i = q;i;i--){
        r[i] = lst[id[i]];lst[id[i]] = i;
        if(i < r[i] - 1)tree.update(i + 1,r[i] - 1,i);
    }
    tree.getans(1,q,1);
    return 0;
}