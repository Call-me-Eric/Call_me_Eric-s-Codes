#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;

int n, m, k;
struct DSU{
    typedef pair<pair<int,int> ,int>  T;
    struct Stack{
        T s[maxn << 2];int tp;
        Stack(){tp = 0;}
        bool pop(){if(tp == 0)return false;tp--;return true;}
        T top(){return s[tp];}
        void push(T x){s[++tp] = x;}
    };
    Stack opt;
    int fa[maxn],hei[maxn];//按轶合并需要记录的是树高不是大小
    void init(int x){for(int i = 1;i <= x;i++)fa[i] = i, hei[i] = 1;opt.tp = 0;}
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}//可回溯并查集不能路径压缩
    void merge(int x,int y){
        x = getf(x);y = getf(y);
        if(x == y)return;
        if(hei[x] > hei[y])swap(x, y);
        opt.push(make_pair(make_pair(x, y),hei[x] == hei[y]));
        fa[x] = y;hei[y] += (hei[x] == hei[y]);
    }
    void trace(int lsttop){//回溯
        while(opt.tp != lsttop){
            auto u = opt.top();opt.pop();
            fa[u.first.first] = u.first.first;
            hei[u.first.second] -= u.second;
        }
    }
    inline int version(){return opt.tp;}
}dsu;

struct Segment_Tree{
    typedef pair<int,int> T;
    vector<T> d[maxn << 2];
    bool ans[maxn];
    void update(int l,int r,int s,int t,int p,T x){
        if(s <= l && r <= t){d[p].push_back(x);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,x);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,x);
    }
    void getans(int l,int r,int p){
        bool chk = true;int lsttop = dsu.version();
        for(auto i : d[p]){
            int u = i.first, v = i.second;
            int fu = dsu.getf(u), fv = dsu.getf(v);
            if(fu == fv){
                chk = false;
                for(int j = l;j <= r;j++)ans[j] = false;
                break;
            }
            dsu.merge(u,v + n);dsu.merge(u + n,v);
        }
        if(chk){
            int mid = l + r >> 1;
            if(l == r)ans[l] = true;
            else getans(l,mid,p << 1), getans(mid + 1,r,p << 1 | 1);
        }
        dsu.trace(lsttop);
    }
}tree;

signed main(){
    n = read(); m = read(); k = read();
    dsu.init(n * 2);
    int u, v, l , r;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); l = read() + 1;r = read();
        //时间从0开始，本来应该l++,r++，但是r是删除时刻，故r--，所以最后l++即可
        if(l > r)continue;
        tree.update(1,k,l,r,1,make_pair(u, v));
    }
    tree.getans(1,k,1);
    for(int i = 1;i <= k;i++){puts(tree.ans[i] ? "Yes" : "No");}
    return 0;
}