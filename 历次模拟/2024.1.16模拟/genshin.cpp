#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<pair<int,int> > edg[maxn];
namespace Subtask1{
    double ans = 0;
    int dep[maxn];bool leaf[maxn];
    double fact[maxn];
    void dfs(int u,int f){
        bool book = true;
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != f){
                fact[v] = 1.0 / ((double)edg[u].size() - (!!f) * 1.0) * fact[u];
                dep[v] = dep[u] + w;dfs(v, u);
                book = false;
            }
        }
        leaf[u] = book;
        if(book)ans += fact[u] * dep[u];
    }
    void main(){
        for(int i = 1;i <= n;i++){
            fact[i] = 1;dep[i] = 0;dfs(i, 0);
        }
        printf("%.8lf\n",ans * 1.0 / (double)n);
    }
};
// namespace Subtask2{
//     int dep[maxn];bool leaf[maxn];
//     double fact[maxn], ans;
//     int dfn[maxn], low[maxn], idx;
//     void dfs(int u,int f){
//         dfn[u] = ++idx;
//         bool book = true;
//         for(auto i : edg[u]){
//             int v = i.first, w = i.second;
//             if(v != f){
//                 fact[v] = 1.0 / ((double)edg[u].size() - (!!f) * 1.0) * fact[u];
//                 dep[v] = dep[u] + w;dfs(v, u);
//                 book = false;
//             }
//         }
//         leaf[u] = book;
//         low[u] = idx;
//     }
//     struct Segment_Tree{
//         struct node{
//             double summ, tagg;//summ 是答案,tagg是概率的乘积tag，
//             bool tag;double cnt, add;//cnt是叶子结点出现概率和,add是深度的改变tag
//             node(double summ = 0,double cnt = 0,int add = 0,double tagg = 1,bool tag = 0
//             ):summ(summ),tagg(tagg),tag(tag),cnt(cnt),add(add){}
//         }d[maxn << 2];
//         node mergenode(node l,node r){return node(l.summ + r.summ,l.cnt + r.cnt);}
//         void change(int p,double upd,int add){
//             d[p].cnt *= upd;
//             d[p].summ += d[p].cnt * add;
//             d[p].summ *= upd;d[p].tagg *= upd;
//             d[p].add += add;d[p].tag = 1;
//         }
//         void pushdown(int p){
//             if(d[p].tag){
//                 change(p << 1,d[p].tagg,d[p].add);change(p << 1 | 1,d[p].tagg,d[p].add);
//                 d[p].tagg = 1;d[p].add = 0;d[p].tag = false;
//             }
//         }
//         void build(int l,int r,int p){
//             if(l == r){
//                 if(leaf[dfn[l]])d[p] = node(fact[dfn[l]] * 1.0 * dep[dfn[l]],fact[dfn[l]]);
//                 else d[p] = node();
//                 return;
//             }
//             int mid = l + r >> 1;
//             build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
//             d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
//         }
//         void update(int l,int r,int s,int t,int p,double fac,int adddep){
//             if(s <= l && r <= t){change(p,fac,adddep);return;}
//             int mid = l + r >> 1; pushdown(p);
//             if(s <= mid)update(l,mid,s,t,p << 1,fac,adddep);
//             if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,fac,adddep);
//             d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
//         }
//         node query(int l,int r,int s,int t,int p){
//             if(s <= l && r <= t)return d[p];
//             int mid = l + r >> 1;pushdown(p);
//             if(t <= mid)return query(l,mid,s,t,p << 1);
//             if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
//             return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
//         }
//         void update(int l,int r,double fac,int adddep){if(l > r)return;update(1,n,l,r,1,fac,adddep);}
//     }tree;
//     void dfs1(int u,int f){
//         ans += tree.query(1,n,1,n,1).summ - tree.query(1,n,u,u,1).summ;
//         for(auto i : edg[u]){
//             int v = i.first, w = i.second;
//             if(v != f){
//                 tree.update(1,n,edg[u].size(),0);
//                 double upd1 = 1.0 / ((edg[u].size() - 1) * edg[v].size());
//                 tree.update(1,dfn[u] - 1,upd1,0);tree.update(low[u] + 1,n,upd1,0);
//                 double upd2 = tree.query(1,n,dfn[u],dfn[u],1).cnt;
//                 if(upd2 > 1e-10)tree.update(dfn[u],dfn[u],1.0 / (upd2 * edg[u].size()),0);
//             }
//         }
//     }
//     void main(){
//         dfs(1, 0);if(edg[1].size() == 1)leaf[1] = 1;
//         tree.build(1,n,1);
//         dfs1(1,0);
//     }
// };
namespace Subtask3{
    bool book[maxn];
    double ans;
    void dfs(int u,int dist,double fact){
        int tot = 0;book[u] = 1;
        for(auto v : edg[u])tot += !book[v.first];
        if(tot == 0){ans += fact * (double)dist;book[u] = 0;return;}
        for(auto v : edg[u]){
            if(!book[v.first])
                dfs(v.first,dist + v.second,fact * 1.0 / (double)tot);
        }
        book[u] = 0;
    }
    void main(){
        for(int i = 1;i <= n;i++){
            memset(book,0,sizeof(book));
            dfs(i, 0, 1);
        }
        printf("%.8lf\n",ans / (double)n);
    }
};
signed main(){
    freopen("genshin.in","r",stdin);
    freopen("genshin.out","w",stdout);
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();w = read();
        edg[u].push_back(make_pair(v,w));edg[v].push_back(make_pair(u,w));
    }
    if(n - 1 == m){Subtask1::main();}
    else Subtask3::main();
    return 0;
}