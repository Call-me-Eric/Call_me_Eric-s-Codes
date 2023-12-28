# 数据结构优化DP

## 例题A题解

设 $f_{i,j}$ 表示以第 $i$ 位为结尾，长度为 $j$ 的严格单调上升子序列的数量。  
那么显然有 $f_{i,j}=\sum_{k=1}^{i-1}f_{k,j-1}\times(a_k<a_i)$  
然后发现这玩应 $O(n^2m)$ 直接寄掉了。  
考虑优化。  
发现只有当 $a_k<a_i$ 时才会有贡献。  
于是离散化+权值BIT就完事了。

## 例题A代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 123456789;
int n, a[maxn], m;
vector<int> vec;
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int upd){for(;x <= n;x += lowbit(x))c[x] = (c[x] + upd) % mod;}
    int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans = (ans + c[x]) % mod;return ans;}
    void clear(){for(int i = 0;i <= n;i++)c[i] = 0;}
}tree[101];
signed main(){
    while(scanf("%lld%lld",&n,&m) != EOF){
        for(int i = 1;i <= n;i++){vec.push_back(a[i] = read());}
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        int ans = 0;
        for(int i = 1;i <= n;i++){
            int x = lower_bound(vec.begin(),vec.end(),a[i]) - vec.begin() + 1;
            tree[1].upd(x,1);
            for(int j = 1;j <= m;j++)
                tree[j].upd(x,tree[j - 1].qry(x - 1));
        }
        ans = tree[m].qry(n);
        printf("%lld\n",ans);
        for(int i = 1;i <= m;i++)tree[i].clear();vec.clear();
    }
    return 0;
}
~~~

## 例题B题解

DP柿子是好想的：设 $f_{i,j}$ 表示在第 $i$ 位置建立第 $j$ 个基站，不考虑 $[i+1,n]$ 的花费的最小值，那么有：
$$
f_{i,j}=\min_{k<i} f_{k,j-1} + val_{k,i}
$$

其中 $val_{k,i}$ 表示在 $k,i$ 位置建立基站之后 $[k,i]$ 之间需要支付的代价。  
比较难算的是 $val_{k,i}$。  
发现对于一个村庄，如果设 $[L_i,R_i]$ 表示能够让这个村庄覆盖到信号的基站建立范围，那么所有没有选中 $[L_i,R_i]$ 区间内任意一个的方案，就需要加上这个村庄的代价。  
不难发现，这个定义与之前的DP式子不谋而合。  
具体而言，从左向右扫 $r$，每次维护 $l$ 位置表示不选 $[l+1,r-1]$ 中的任意一个位置作为基站的 $f_{l,j}+val_{l,r}$ 值。这个线段树维护即可。  
然后就没了。

## 例题B代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, f[maxn];
struct Segment_Tree{
    struct node{
        int minn, tag;
        node(int minn = 0,int tag = 0):minn(minn),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(min(l.minn,r.minn));}
    void pushdown(int p){
        if(d[p].tag){
            d[p << 1].tag += d[p].tag;
            d[p << 1].minn += d[p].tag;
            d[p << 1 | 1].tag += d[p].tag;
            d[p << 1 | 1].minn += d[p].tag;
            d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(f[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].minn += upd;d[p].tag += upd;return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(){build(1,n,1);}
    void update(int l,int r,int upd){if(r < l)return;update(1,n,l,r,1,upd);}
    int query(int l,int r){if(r < l)return 0x3f3f3f3f;return query(1,n,l,r,1).minn;}
}tree;
int k, D[maxn], C[maxn],S[maxn],W[maxn];
int L[maxn], R[maxn];
vector<pair<int,int> > vec[maxn];
signed main(){
    n = read(); k = read();
    for(int i = 2;i <= n;i++)D[i] = read();
    for(int i = 1;i <= n;i++)C[i] = read();
    for(int i = 1;i <= n;i++)S[i] = read();
    for(int i = 1;i <= n;i++)W[i] = read();
    D[++n] = 0x3f3f3f3f;W[n] = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){
        L[i] = lower_bound(D + 1,D + 1 + n,D[i] - S[i]) - D;
        R[i] = lower_bound(D + 1,D + 1 + n,D[i] + S[i]) - D;
        if(D[R[i]] > D[i] + S[i])R[i]--;
        vec[R[i]].push_back(make_pair(L[i],W[i]));
    }
    int ans = 0,res = 0;
    for(int i = 1;i <= n;i++){
        f[i] = res + C[i];
        for(auto x : vec[i]){res += x.second;}
    }
    ans = f[n];
    for(int j = 1;j <= k;j++){
        tree.build();
        for(int i = 1;i <= n;i++){
            f[i] = tree.query(1,i - 1) + C[i];
            for(auto x : vec[i]){tree.update(1,x.first - 1,x.second);}
        }
        ans = min(ans,f[n]);
    }
    printf("%d\n",ans);
    return 0;
}
~~~

## 例题C题解

首先将点排序（再带一步离散化）  
设 $f_{i,j,0/1}$ 表示以第 $i$ 个点为结尾的 0:向下/1:向上 的 $j$ 次折线的方案数。  
有：
$$
f_{i,j,0}=\sum_{k<i,a_k<a_i}f_{k,j,0}+f_{k,j-1,1}
f_{i,j,1}=\sum_{k<i,a_k>a_i}f_{k,j,1}+f_{k,j-1,0}
$$
这个树状数组做一下就完了。

## 例题C代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10, mod = 1e5 + 7;
int n, k;
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] = (c[x] + add) % mod;}
    int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans = (ans + c[x]) % mod;return ans;}
    void clear(){for(int i = 1;i <= n;i++)c[i] = 0;}
}tr[2];//[][0]=up,[][1]=down

struct node{
    int x, y;
    node(int x = 0,int y = 0):x(x),y(y){}
    friend bool operator < (node a,node b){return a.x < b.x;}
}a[maxn];
vector<int> X, Y;

int f[maxn][11][2];

signed main(){
    n = read(); k = read();
    for(int i = 1;i <= n;i++){
        a[i].x = read();
        Y.push_back(a[i].y = read());
    }
    sort(Y.begin(),Y.end());Y.erase(unique(Y.begin(),Y.end()),Y.end());
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        a[i].y = lower_bound(Y.begin(),Y.end(),a[i].y) - Y.begin() + 1;
        f[i][0][0] = f[i][0][1] = 1;
    }
    int ans = 0;
    for(int j = 1;j <= k;j++){
        tr[0].clear();tr[1].clear();
        for(int i = 1;i < n;i++){
            tr[0].upd(a[i].y,f[i][j][0] + f[i][j - 1][1]);
            tr[1].upd(a[i].y,f[i][j][1] + f[i][j - 1][0]);
            f[i + 1][j][0] = tr[0].qry(a[i + 1].y - 1);
            f[i + 1][j][1] = (tr[1].qry(n) - tr[1].qry(a[i + 1].y) + mod) % mod;
        }
    }
    for(int i = 1;i <= n;i++){ans = (ans + f[i][k][0] + f[i][k][1]) % mod;}
    printf("%d\n",ans % mod);
    return 0;
}
~~~
